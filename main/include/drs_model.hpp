#ifndef DNS_MODEL_HPP
#define DNS_MODEL_HPP


#include "collection_database.hpp"



using namespace cadmium;


#define STATUS_IDLE 0
#define STATUS_START_DRS 4
#define STATUS_CALCULATE_ROUTE 5
#define STATUS_END_SIMULATION 7
#define MAX_CAPACITY 36000                    //maximum capacity of a truck in pounds (lbs)
#define AVERAGE_WEIGHT_WASTE 175

struct drs_modelState {
    int internal_status;
    std::vector<std::vector<collection_pt>> map_collection;
    bool index_progress[815];
    int count_progress;
    bool active_trucks[4];
    int initialize_route[4];
    Tuple_update received_truck_data_1;
    Tuple_update received_truck_data_2;
    Tuple_update received_truck_data_3;
    Tuple_update received_truck_data_4;
    int calculated_next_route[4];
    double t_advance;
    explicit drs_modelState() : t_advance(1.0), count_progress(0),internal_status(STATUS_CALCULATE_ROUTE),received_truck_data_1({0,0.0}),received_truck_data_2({0,0.0}),received_truck_data_3({0,0.0}),received_truck_data_4({0,0.0}){

    }
};


#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out_drs_model, const drs_modelState& state) {
    out_drs_model  << "{ Completed routes : " << state.count_progress << "}" ;
    return out_drs_model;
}
#endif

class drs_model : public Atomic<drs_modelState> {
    public:
        Port<int> in_updatel_1;
        Port<double> in_updatew_1;
        Port<int> in_updatel_2;
        Port<double> in_updatew_2;
        Port<int> in_updatel_3;
        Port<double> in_updatew_3;
        Port<int> in_updatel_4;
        Port<double> in_updatew_4;
        Port<double> in_updatet;

        Port<int>  out_new_route_1;
        Port<int>  out_new_route_2;
        Port<int>  out_new_route_3;
        Port<int>  out_new_route_4;

        Port<bool> in_active_truck_1;
        Port<bool> in_active_truck_2;
        Port<bool> in_active_truck_3;
        Port<bool> in_active_truck_4;

    //Declare your ports here

    drs_model(const std::string id) : Atomic<drs_modelState>(id, drs_modelState()) {
        //Constructor of your atomic model. Initialize ports here.
        in_updatel_1 = addInPort<int>("in_updatel_1");
        in_updatew_1 = addInPort<double>("in_updatew_1");

        in_updatel_2 = addInPort<int>("in_updatel_2");
        in_updatew_2 = addInPort<double>("in_updatew_2");

        in_updatel_3 = addInPort<int>("in_updatel_3");
        in_updatew_3 = addInPort<double>("in_updatew_3");

        in_updatel_4 = addInPort<int>("in_updatel_4");
        in_updatew_4 = addInPort<double>("in_updatew_4");

        in_updatet = addInPort<double>("in_updatet");

        out_new_route_1 = addOutPort<int>("out_new_route_1");
        out_new_route_2 = addOutPort<int>("out_new_route_2");
        out_new_route_3 = addOutPort<int>("out_new_route_3");
        out_new_route_4 = addOutPort<int>("out_new_route_4");

        in_active_truck_1 = addInPort<bool>("in_active_truck_1");
        in_active_truck_2 = addInPort<bool>("in_active_truck_2");
        in_active_truck_3 = addInPort<bool>("in_active_truck_3");
        in_active_truck_4 = addInPort<bool>("in_active_truck_4");

        state.map_collection= collection_database::set_collection_database();
        state.calculated_next_route[0] = 1;
        state.calculated_next_route[1] = 204;
        state.calculated_next_route[2] = 398;
        state.calculated_next_route[3] = 608;

        for(int i =0; i<4; i++){
            state.active_trucks[i] = true;
        }

        for(int i = 0; i<185; i++){
            state.index_progress[i] = false;
        }
           
    }

    

    // internal transition
    void internalTransition(drs_modelState& state) const override {

        if ((state.internal_status==STATUS_CALCULATE_ROUTE || state.internal_status == STATUS_START_DRS) && state.count_progress<=815){
             int *list_location[4] = {find_index(state.map_collection,state.received_truck_data_1.coordinate),find_index(state.map_collection,state.received_truck_data_2.coordinate),find_index(state.map_collection,state.received_truck_data_3.coordinate),find_index(state.map_collection,state.received_truck_data_4.coordinate)};

            double current_weight_1 = state.received_truck_data_1.weight;
            double current_weight_2 = state.received_truck_data_2.weight;
            double current_weight_3 = state.received_truck_data_3.weight;
            double current_weight_4 = state.received_truck_data_4.weight;
            double list_weight[4] = {current_weight_1,current_weight_2,current_weight_3,current_weight_4};
            int closest_index[4] = {-1,-1,-1,-1};
            int closest_distance[4] = {-1,-1,-1,-1};
            
            
            for (int i=0; i<4 ;i++){
                
                int first_street = (state.map_collection[list_location[i][0]][0].index)-1;
                int last_street = state.map_collection[list_location[i][0]][list_location[i][1]].index;
                for (int j = first_street; j<last_street;j++){
                    if (state.count_progress == 815){
                        break;
                    }
                    state.count_progress += 1;
                    state.index_progress[j] = true;
                }

                if ((list_location[i][0]>=0)&&(list_location[i][1]>=0)){
                    collection_pt current_pt = state.map_collection[list_location[i][0]][list_location[i][1]];
                    std::vector<collection_pt> street = state.map_collection[list_location[i][0]];
                    for (int j=0; j<street.size(); j++){
                        if (street[j].bool_intersection==1){

                            int* next_intersection = street[j].index_closest_pt;
                            for (int k=0 ; k < 2; k++){
                                if(next_intersection[k]>0){
                                    int* next_pt = find_index(state.map_collection,next_intersection[k]);
                                    collection_pt pt_next_street = state.map_collection[next_pt[0]][next_pt[1]];
                                    
                                    int tmp_distance = calculate_distance_points(pt_next_street,current_pt);
                                    
                                    if (((tmp_distance<closest_distance[i]) || (closest_distance[i]==-1)) && !(state.index_progress[street[j].index_closest_pt[k]-1])){
                                        closest_index[i] = pt_next_street.index;
                                        closest_distance[i] = tmp_distance;
                                    }
                                }
                            }
                                
                        }
                    }
                    
                }
                
                if (closest_index[i] == -1 ){
                    for (int j=0; j<state.map_collection.size(); j++){
                            if (!(state.index_progress[state.map_collection[j][0].index-1]) && ((list_weight[i]+(state.map_collection[j].size()*AVERAGE_WEIGHT_WASTE))<MAX_CAPACITY)){
                                    closest_index[i] = state.map_collection[j][0].index;  
                                    break; 
                            } 
                    }
                    state.internal_status = STATUS_END_SIMULATION;
                    state.calculated_next_route[i] = -2;
                }
                    state.calculated_next_route[i] = closest_index[i];
                    state.index_progress[closest_index[i]-1] = true;
                    
                
                
            }
            
            state.t_advance = 5;
        }
        
        
        
        
        
    }

    // external transition
    void externalTransition(drs_modelState& state, double e) const override {

        int coordinate;
        double weight;
        int truck_id;
        int bool_data = 0 ;
        if((!in_updatel_1->empty()) && (!in_updatew_1->empty())){

            for(const int &update_l: in_updatel_1 -> getBag()){
                if (update_l > 0 && truck_end_street(state,update_l)){
                    state.received_truck_data_1.coordinate = update_l;
                }
            }
            for(const double &update_w: in_updatew_1 -> getBag()){
                state.received_truck_data_1.weight = update_w;
            }
        }
        
        
        if ((!in_updatel_2->empty()) && (!in_updatew_2->empty())){
            
            for(const int &update_l: in_updatel_2 -> getBag()){
                if (update_l > 0 && truck_end_street(state,update_l)){
                    state.received_truck_data_2.coordinate  = update_l;
                }
                
            }
            for(const double &update_w: in_updatew_2-> getBag()){
                if (update_w > 0){
                    state.received_truck_data_2.weight = update_w;
                }
            }
            
        }

        if ((!in_updatel_3 -> empty()) && (!in_updatew_3->empty())){
            
            for(const int &update_l: in_updatel_3 -> getBag()){
                if (update_l > 0 && truck_end_street(state,update_l)){
                    state.received_truck_data_3.coordinate = update_l;
                }
                
            }
            for(const double &update_w: in_updatew_3 -> getBag()){
                if (update_w > 0){
                    state.received_truck_data_3.weight = update_w;
                }
                
            }
        }
        
        if((!in_updatel_4->empty()) && (!in_updatew_4->empty())){
            
            for(const int &update_l: in_updatel_4 -> getBag()){
                if (update_l > 0 && truck_end_street(state,update_l)){
                    state.received_truck_data_4.coordinate  = update_l;
                }
                
            }
            for(const double &update_w: in_updatew_4 -> getBag()){
                if (update_w > 0){
                    state.received_truck_data_4.weight = update_w;
                }
                
            }

        }

        if(!in_updatet->empty()){ 
            for(const double &update_ta: in_updatet-> getBag()){
                state.t_advance = update_ta;
            }
        }
        
        state.internal_status = STATUS_CALCULATE_ROUTE;

        
        

        if(!in_active_truck_1->empty()){
            for(const bool &active_truck: in_active_truck_1->getBag()){
                state.active_trucks[0]= active_truck;
            }
        }
        if(!in_active_truck_2->empty()){
            for(const bool &active_truck: in_active_truck_2->getBag()){
                state.active_trucks[1]= active_truck;
            }
        }
        if(!in_active_truck_3->empty()){
            for(const bool &active_truck: in_active_truck_3->getBag()){
                state.active_trucks[2]= active_truck;
            }
        }
        if(!in_active_truck_4->empty()){
            for(const bool &active_truck: in_active_truck_4->getBag()){
                state.active_trucks[3]= active_truck;
            }
        }
    
    }
    
    
    // output function
    void output(const drs_modelState& state) const override {
        out_new_route_1 -> addMessage(state.calculated_next_route[0]);
        out_new_route_2 -> addMessage(state.calculated_next_route[1]);
        out_new_route_3 -> addMessage(state.calculated_next_route[2]);
        out_new_route_4 -> addMessage(state.calculated_next_route[3]);  
    }

    static bool truck_end_street(const drs_modelState& state, int location){
        bool rt_end = false;
        for (int i = 0 ; i<state.map_collection.size(); i++){
            int end_street = state.map_collection[i][state.map_collection[i].size()-1].index;
             if(location == end_street){
                rt_end = true;
                break;
            } 
        }
        return rt_end;

    }

    

    // time_advance function
    [[nodiscard]] double timeAdvance(const drs_modelState& state) const override {  
        if ((!(state.active_trucks[0]) && !(state.active_trucks[1]) && !(state.active_trucks[2]) && !(state.active_trucks[3])) || (state.internal_status==STATUS_END_SIMULATION)){
            return std::numeric_limits<double>::infinity();
        }     
        return state.t_advance;
    }

};

#endif