#ifndef TOP_HPP
#define TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "transfer_station_model.hpp"
#include "truck_model.hpp"
#include "drs_model.hpp"

using namespace cadmium;

struct top_coupled : public Coupled {

    /**
     * Constructor function for the blinkySystem model.
     * @param id ID of the blinkySystem model.
     */
    top_coupled(const std::string& id) : Coupled(id) {
        
        auto truck_model_4 = addComponent<truck_model>("4th Truck");
        auto truck_model_3 = addComponent<truck_model>("3rd Truck");
        auto truck_model_2 = addComponent<truck_model>("2nd Truck");
        auto truck_model_1 = addComponent<truck_model>("1st Truck");
        auto transfer_station_1 = addComponent<transfer_station_model>("Transfer Station");
        auto drs_model_1 = addComponent<drs_model>("Dynamic Routing System"); 

        
        
        //Coupling between DNS and Trucks
        addCoupling(drs_model_1->out_new_route_1, truck_model_1->in_new_route);
        addCoupling(drs_model_1->out_new_route_2, truck_model_2->in_new_route);
        addCoupling(drs_model_1->out_new_route_3, truck_model_3->in_new_route);
        addCoupling(drs_model_1->out_new_route_4, truck_model_4->in_new_route);

        addCoupling(truck_model_1 -> out_updatew_truck, drs_model_1->in_updatew_1);
        addCoupling(truck_model_2 -> out_updatew_truck, drs_model_1->in_updatew_2);
        addCoupling(truck_model_3 -> out_updatew_truck, drs_model_1->in_updatew_3);
        addCoupling(truck_model_4 -> out_updatew_truck, drs_model_1->in_updatew_4);

        addCoupling(truck_model_1 -> out_updatel_truck, drs_model_1 -> in_updatel_1);
        addCoupling(truck_model_2 -> out_updatel_truck, drs_model_1 -> in_updatel_2);
        addCoupling(truck_model_3 -> out_updatel_truck, drs_model_1 -> in_updatel_3);
        addCoupling(truck_model_4 -> out_updatel_truck, drs_model_1 -> in_updatel_4); 

        addCoupling(truck_model_1 -> out_updatet, drs_model_1->in_updatet);
        addCoupling(truck_model_2 -> out_updatet, drs_model_1->in_updatet);
        addCoupling(truck_model_3 -> out_updatet, drs_model_1->in_updatet);
        addCoupling(truck_model_4 -> out_updatet, drs_model_1->in_updatet);
        
        //Coupling between Transfer Station and Trucks
        addCoupling(truck_model_1->out_arrival_station,transfer_station_1->in_arrival_station_1);
        addCoupling(truck_model_2->out_arrival_station,transfer_station_1->in_arrival_station_2);
        addCoupling(truck_model_3->out_arrival_station,transfer_station_1->in_arrival_station_3);
        addCoupling(truck_model_4->out_arrival_station,transfer_station_1->in_arrival_station_4);
        
        //std::cout<<"top ->  in : " << (drs_model_1 -> in_updatel_1 == nullptr) << std::endl;
        
	    

        //Coupling between DNS and Transfer_Station
        //addCoupling(drs_model->out_DNS_dispatch,transfer_station->in_request_release);
        addCoupling(transfer_station_1->out_active_truck_1,drs_model_1->in_active_truck_1); 
        addCoupling(transfer_station_1->out_active_truck_2,drs_model_1->in_active_truck_2); 
        addCoupling(transfer_station_1->out_active_truck_3,drs_model_1->in_active_truck_3); 
        addCoupling(transfer_station_1->out_active_truck_4,drs_model_1->in_active_truck_4); 
        //std::cout<< "couplings added" << std::endl;
    }
};

#endif