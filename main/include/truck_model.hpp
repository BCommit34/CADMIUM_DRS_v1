#ifndef TRUCK_MODEL_HPP
#define TRUCK_MODEL_HPP


#include "collection_database.hpp"

using namespace cadmium;
using namespace std;

#define STATUS_IDLE 0
#define STATUS_LOADING 1
#define STATUS_DRIVING 2
#define STATUS_RETURN_STATION 3
#define STATUS_START_DRS 4
#define MAX_CAPACITY 36000                    

struct truck_modelState {
    double sensor_capacity;
    int location_truck;
    int end_street;
    int i_route;
    std::vector<std::vector<collection_pt>> map_collection;
    std::vector<collection_pt> truck_route;
    int internal_status;

    double t_advance;
    double total_travel;

    explicit truck_modelState() : total_travel(1),sensor_capacity(0.0), location_truck(0), i_route(0) , internal_status(STATUS_LOADING),t_advance(0.0){
    }
};



#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out_truck_model, const truck_modelState& state) {
    out_truck_model  << " Truck : { Time Elapsed - "<< (state.total_travel/60)<<" minutes , Location - " << state.location_truck << ", Weight: " << state.sensor_capacity << "}";
   return out_truck_model;
}
#endif

class truck_model : public Atomic<truck_modelState> {
    private:
        const double range_collection_time [2] = {5,15};       //5 to 15 seconds per location      
        const double range_weight_waste [2] = {150,200};       // 150-200 lbs waste per houshold in a week 
        const double range_speed_truck [2] = {1.944,2.777};    // 1.944 - 2.777 m/s ,  7-10 km/h 
        const double range_intersection_delay[2] = {10,60};    // Delay at intersection
        

    public:
        Port<bool> out_arrival_station;
        Port<int> out_updatel_truck;
        Port<double> out_updatew_truck;
        Port<int>  in_new_route;
        Port<double> out_updatet;
        

    //Declare your ports here

    truck_model(const std::string id) : Atomic<truck_modelState>(id, truck_modelState()){
        //Constructor of your atomic model. Initialize ports here.
        in_new_route = addInPort<int>("in_new_route");
        out_updatel_truck = addOutPort<int>("out_updatel_truck");
        out_updatew_truck = addOutPort<double>("out_updatew_truck");
        out_arrival_station = addOutPort<bool>("out_arrival_station");
        out_updatet  = addOutPort<double>("out_updatet");
       
        state.map_collection= collection_database::set_collection_database();
        
    }

    // inernal transition
    void internalTransition(truck_modelState& state) const override {
        
        if(state.internal_status == STATUS_LOADING){
            state.i_route = 0;
            while ((state.sensor_capacity < MAX_CAPACITY ) && (state.i_route < state.truck_route.size())){
                srand(time(NULL));
                float rnd = (float)rand()/(float)RAND_MAX;
                float rnd2 = (float)rand()/(float)RAND_MAX;
                float rnd3 = (float)rand()/(float)RAND_MAX;
                float rnd4 = (float)rand()/(float)RAND_MAX;
                state.total_travel = state.total_travel + ((range_collection_time[1]-range_collection_time[0])*rnd) + range_collection_time[0];
                state.sensor_capacity = state.sensor_capacity + ((range_weight_waste[1]-range_weight_waste[0])*rnd2) + range_weight_waste[0];

                if((state.i_route < (state.truck_route.size()-1))){
                    collection_pt current_pt = state.truck_route[state.i_route];
                    collection_pt next_pt = state.truck_route[state.i_route + 1];
                    double distance_next = calculate_distance_points(next_pt,current_pt);
                    state.total_travel = state.total_travel + (distance_next/((rnd3*(range_speed_truck[1]-range_speed_truck[0]))+range_speed_truck[0]));
                    state.total_travel = state.total_travel + (rnd4*(range_intersection_delay[1]-range_intersection_delay[0]))+range_intersection_delay[0];
                }
                state.i_route += 1;
                state.t_advance += 1;
                if (state.sensor_capacity>=MAX_CAPACITY){
                    state.internal_status = STATUS_RETURN_STATION;
                    break;
                }
            
            }
            state.i_route -=1;

        }
        state.t_advance = 0.2;
          
      
    }

    // external transition
    void externalTransition(truck_modelState& state, double e) const override {
       
        if(!in_new_route->empty()){
            int tmp; 
            for(const int& i: in_new_route -> getBag()){
                tmp = i;
                
            }
            if((tmp>0) && (tmp<=815) && tmp != state.location_truck) {
                state.location_truck = tmp;
                state.end_street = state.location_truck - 1 + state.map_collection[find_index(state.map_collection,state.location_truck)[0]].size();
                int *index_street = find_index(state.map_collection,state.location_truck);
                state.truck_route = state.map_collection[index_street[0]];
                state.internal_status = STATUS_LOADING;
            }
            
        }
   
    }
    
    
    // output function
    void output(const truck_modelState& state) const override {
        out_arrival_station -> addMessage(state.internal_status!=STATUS_RETURN_STATION);
        out_updatel_truck -> addMessage(state.end_street);
        out_updatew_truck -> addMessage(state.sensor_capacity);
        out_updatet -> addMessage(state.t_advance);
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const truck_modelState& state) const override {
        if (state.internal_status==STATUS_RETURN_STATION){
            return std::numeric_limits<double>::infinity();
        }
        return state.t_advance;
             
        
    }

};

#endif