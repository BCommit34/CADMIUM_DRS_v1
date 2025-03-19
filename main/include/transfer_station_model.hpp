#ifndef TRANSFER_STATION_MODEL_HPP
#define TRANSFER_STATION_MODEL_HPP

#include "collection_pt.hpp"

using namespace cadmium;
using namespace std;

#define STATUS_IDLE 0
#define STATUS_TRUCK_RECEPTION 6

struct transfer_station_modelState {
    bool active_dispatch_truck[4];
    bool update_active_truck[4];
    double t_advance;
    int internal_status;

    //you can have as many state variables as you want/ need

    explicit transfer_station_modelState() : internal_status(STATUS_IDLE), t_advance(1){
    }
};



#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out_station, const transfer_station_modelState& state) {
    out_station  << "{Active Status of trucks :" << state.active_dispatch_truck[0] << "," << state.active_dispatch_truck[1] << "," << state.active_dispatch_truck[2]<< "," << state.active_dispatch_truck[3]  << "}";
    return out_station;
}
#endif

class transfer_station_model : public Atomic<transfer_station_modelState> {

    public:
        Port<bool> in_arrival_station_1;
        Port<bool> in_arrival_station_2;
        Port<bool> in_arrival_station_3;
        Port<bool> in_arrival_station_4;

        Port<bool> out_active_truck_1;
        Port<bool> out_active_truck_2;
        Port<bool> out_active_truck_3;
        Port<bool> out_active_truck_4;
    //Declare your ports here

    transfer_station_model(const std::string id) : Atomic<transfer_station_modelState>(id, transfer_station_modelState()){
        //Constructor of your atomic model. Initialize ports here.
        in_arrival_station_1 = addInPort<bool>("in_arrival_station_1");
        in_arrival_station_2 = addInPort<bool>("in_arrival_station_2");
        in_arrival_station_3 = addInPort<bool>("in_arrival_station_3");
        in_arrival_station_4 = addInPort<bool>("in_arrival_station_4");

        out_active_truck_1 = addOutPort<bool>("out_active_truck_1");
        out_active_truck_2 = addOutPort<bool>("out_active_truck_2");
        out_active_truck_3 = addOutPort<bool>("out_active_truck_3");
        out_active_truck_4 = addOutPort<bool>("out_active_truck_4");

        for(int i =0; i<4; i++){
            state.active_dispatch_truck[i] = true;
        }
    }

    // inernal transition
    void internalTransition(transfer_station_modelState& state) const override {
        if (state.internal_status==STATUS_TRUCK_RECEPTION){
            if(!(state.active_dispatch_truck[0])&&!(state.active_dispatch_truck[1])&&!(state.active_dispatch_truck[2])&&!(state.active_dispatch_truck[3])){
                state.t_advance = std::numeric_limits<double>::infinity();
            }
        }
        
    }

    // external transition
    void externalTransition(transfer_station_modelState& state, double e) const override {
        if(!in_arrival_station_1->empty()){
            for(const bool& a_status: in_arrival_station_1 -> getBag()){
                state.active_dispatch_truck[0] = a_status;
            }
            state.internal_status = STATUS_TRUCK_RECEPTION;
        }else if(!in_arrival_station_2->empty()){
            for(const bool& a_status: in_arrival_station_2 -> getBag()){
                state.active_dispatch_truck[1] = a_status;
            }
            state.internal_status = STATUS_TRUCK_RECEPTION;
        }else if(!in_arrival_station_3->empty()){
            for(const bool& a_status: in_arrival_station_3 -> getBag()){
                state.active_dispatch_truck[2] = a_status;
            }
            state.internal_status = STATUS_TRUCK_RECEPTION;
        }else if(!in_arrival_station_4->empty()){
            for(const bool& a_status: in_arrival_station_4 -> getBag()){
                state.active_dispatch_truck[3] = a_status;
            }
            state.internal_status = STATUS_TRUCK_RECEPTION;
        }else{
            state.internal_status = STATUS_IDLE;
        }
    }
    
    // output function
    void output(const transfer_station_modelState& state) const override {
        if(state.internal_status==STATUS_TRUCK_RECEPTION){
            out_active_truck_1 -> addMessage(state.update_active_truck[0]);
            out_active_truck_2 -> addMessage(state.update_active_truck[1]); 
            out_active_truck_3 -> addMessage(state.update_active_truck[2]);
            out_active_truck_4 -> addMessage(state.update_active_truck[3]);
        }
        
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const transfer_station_modelState& state) const override { 
          
        return state.t_advance;
    }

    
};

#endif