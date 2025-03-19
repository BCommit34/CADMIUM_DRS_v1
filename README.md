
# DEVS : Dynamic Routing System
The project is a prototype of a Dynamic Routing System used in the context of waste collect. The project utilize CADMIUM to simulate the model. The system contains three atomic models : Transfer Sation (transfer_station_model.hpp), Dynamic Routing System (drs_model.hpp) and the collection vehicules (truck_model.hpp). The atomic models are coupled within the Top level file (top.hpp). The simulation will estimate the collection time and the weight of the waste collected by 4 trucks. The Dynamic Routing System will assign the routes to the vehicules and manage 815 collection points. The documentation list the files listed and the supporting files.
## Reference

The author would like to acknowledge [@Sasisekhar](https://github.com/Sasisekhar/blank_project_rt) for providing a template to develop a DEVS model.

Link : https://github.com/Sasisekhar/blank_project_rt


## Script Writer
Name : Brigitte H.

Github: https://github.com/BCommit34/CADMIUM_DRS_v1


## Documentations for CADMIUM_DRS_v1
Atomic Model Files
 - [drs_model.hpp](https://linktodocumentation) : The script simulate a dynamic Routing System responsible to provide the route to the collection vehicules
 - [transfer_station_model.hpp](https://linktodocumentation) : The model represent the location where the waste is deposited. Assumed to be the starting point and end point of the vehicules route.
 - [truck_model.hpp](https://linktodocumentation) : Models the process of collection at each collection point.

Coupling model level:
- [top.hpp](https://linktodocumentation) : The script couples the different atomic models. The file list the coupling of the input and output port of the atomic model.


Supporting file : Collection Point Data
- [Dataset_Simulation.csv](https://linktodocumentation) : File containing data of the different collecting point
- [collection_database.hpp](https://linktodocumentation): Script used to iterate though the csv file containing the data of the collecting point
[collection_pt.hpp](https://linktodocumentation) Script implementing a structure and function allowing to manage the data of the collection point


## Running Tests : Terminal

```Compilation
{Computer name\ Linux Server}:~/CADMIUM_DRS_v1$ source build_sim.sh
-- Building without ESP32
-- Building for simulation
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.4s)
-- Generating done (0.0s)
-- Build files have been written to: /home/{username}/CADMIUM_DRS_v1/build
[ 50%] Building CXX object main/CMakeFiles/CADMIUM_DRS_v1.dir/main.cpp.o
[100%] Linking CXX executable /home/{username}/CADMIUM_DRS_v1/bin/CADMIUM_DRS_v1
[100%] Built target CADMIUM_DRS_v1
Compilation done. Executable in the bin folder
```

```Execution
{Computer name\ Linux Server}:~/CADMIUM_DRS_v1$ ./bin/CADMIUM_DRS_v1
time;model_id;model_name;port_name;data
0;1;Dynamic Routing System;;{ Completed routes : 0}
0;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
0;3;1st Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;4;2nd Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;5;3rd Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;6;4th Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;1;Dynamic Routing System;;{ Completed routes : 0}
0;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
0;3;1st Truck;out_updatel_truck;0
0;3;1st Truck;out_updatew_truck;0
0;3;1st Truck;out_arrival_station;1
0;3;1st Truck;out_updatet;0
0;3;1st Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;4;2nd Truck;out_updatel_truck;0
0;4;2nd Truck;out_updatew_truck;0
0;4;2nd Truck;out_arrival_station;1
0;4;2nd Truck;out_updatet;0
0;4;2nd Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;5;3rd Truck;out_updatel_truck;0
0;5;3rd Truck;out_updatew_truck;0
0;5;3rd Truck;out_arrival_station;1
0;5;3rd Truck;out_updatet;0
0;5;3rd Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;6;4th Truck;out_updatel_truck;0
0;6;4th Truck;out_updatew_truck;0
0;6;4th Truck;out_arrival_station;1
0;6;4th Truck;out_updatet;0
0;6;4th Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 0, Weight: 0}
0;1;Dynamic Routing System;out_new_route_1;1
0;1;Dynamic Routing System;out_new_route_2;204
0;1;Dynamic Routing System;out_new_route_3;398
0;1;Dynamic Routing System;out_new_route_4;608
0;1;Dynamic Routing System;;{ Completed routes : 0}
0;3;1st Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 1, Weight: 0}
0;4;2nd Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 204, Weight: 0}
0;5;3rd Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 398, Weight: 0}
0;6;4th Truck;; Truck : { Time Elapsed - 0.0166667 minutes , Location - 608, Weight: 0}
0.2;1;Dynamic Routing System;;{ Completed routes : 0}
0.2;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
0.2;3;1st Truck;out_updatel_truck;72
0.2;3;1st Truck;out_updatew_truck;0
0.2;3;1st Truck;out_arrival_station;1
0.2;3;1st Truck;out_updatet;0.2
0.2;3;1st Truck;; Truck : { Time Elapsed - 57.0628 minutes , Location - 1, Weight: 12923.2}
0.2;4;2nd Truck;out_updatel_truck;225
0.2;4;2nd Truck;out_updatew_truck;0
0.2;4;2nd Truck;out_arrival_station;1
0.2;4;2nd Truck;out_updatet;0.2
0.2;4;2nd Truck;; Truck : { Time Elapsed - 18.2476 minutes , Location - 204, Weight: 3948.76}
0.2;5;3rd Truck;out_updatel_truck;414
0.2;5;3rd Truck;out_updatew_truck;0
0.2;5;3rd Truck;out_arrival_station;1
0.2;5;3rd Truck;out_updatet;0.2
0.2;5;3rd Truck;; Truck : { Time Elapsed - 14.4705 minutes , Location - 398, Weight: 3051.32}
0.2;6;4th Truck;out_updatel_truck;609
0.2;6;4th Truck;out_updatew_truck;0
0.2;6;4th Truck;out_arrival_station;1
0.2;6;4th Truck;out_updatet;0.2
0.2;6;4th Truck;; Truck : { Time Elapsed - 0.881718 minutes , Location - 608, Weight: 358.978}
0.4;1;Dynamic Routing System;out_new_route_1;1
0.4;1;Dynamic Routing System;out_new_route_2;73
0.4;1;Dynamic Routing System;out_new_route_3;80
0.4;1;Dynamic Routing System;out_new_route_4;103
0.4;1;Dynamic Routing System;;{ Completed routes : 113}
0.4;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
0.4;3;1st Truck;out_updatel_truck;72
0.4;3;1st Truck;out_updatew_truck;12923.2
0.4;3;1st Truck;out_arrival_station;1
0.4;3;1st Truck;out_updatet;0.2
0.4;3;1st Truck;; Truck : { Time Elapsed - 114.109 minutes , Location - 1, Weight: 25846.4}
0.4;4;2nd Truck;out_updatel_truck;225
0.4;4;2nd Truck;out_updatew_truck;3948.76
0.4;4;2nd Truck;out_arrival_station;1
0.4;4;2nd Truck;out_updatet;0.2
0.4;4;2nd Truck;; Truck : { Time Elapsed - 36.4786 minutes , Location - 73, Weight: 7897.52}
0.4;5;3rd Truck;out_updatel_truck;414
0.4;5;3rd Truck;out_updatew_truck;3051.32
0.4;5;3rd Truck;out_arrival_station;1
0.4;5;3rd Truck;out_updatet;0.2
0.4;5;3rd Truck;; Truck : { Time Elapsed - 28.9244 minutes , Location - 80, Weight: 6102.63}
0.4;6;4th Truck;out_updatel_truck;609
0.4;6;4th Truck;out_updatew_truck;358.978
0.4;6;4th Truck;out_arrival_station;1
0.4;6;4th Truck;out_updatet;0.2
0.4;6;4th Truck;; Truck : { Time Elapsed - 1.74677 minutes , Location - 103, Weight: 717.956}
0.6;1;Dynamic Routing System;out_new_route_1;232
0.6;1;Dynamic Routing System;out_new_route_2;301
0.6;1;Dynamic Routing System;out_new_route_3;718
0.6;1;Dynamic Routing System;out_new_route_4;296
0.6;1;Dynamic Routing System;;{ Completed routes : 226}
0.6;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
0.6;3;1st Truck;out_updatel_truck;72
0.6;3;1st Truck;out_updatew_truck;25846.4
0.6;3;1st Truck;out_arrival_station;1
0.6;3;1st Truck;out_updatet;0.2
0.6;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 232, Weight: 36077.3}
0.6;4;2nd Truck;out_updatel_truck;79
0.6;4;2nd Truck;out_updatew_truck;7897.52
0.6;4;2nd Truck;out_arrival_station;1
0.6;4;2nd Truck;out_updatet;0.2
0.6;4;2nd Truck;; Truck : { Time Elapsed - 41.56 minutes , Location - 301, Weight: 9153.95}
0.6;5;3rd Truck;out_updatel_truck;102
0.6;5;3rd Truck;out_updatew_truck;6102.63
0.6;5;3rd Truck;out_arrival_station;1
0.6;5;3rd Truck;out_updatet;0.2
0.6;5;3rd Truck;; Truck : { Time Elapsed - 41.1903 minutes , Location - 718, Weight: 10230.9}
0.6;6;4th Truck;out_updatel_truck;103
0.6;6;4th Truck;out_updatew_truck;717.956
0.6;6;4th Truck;out_arrival_station;1
0.6;6;4th Truck;out_updatet;0.2
0.6;6;4th Truck;; Truck : { Time Elapsed - 1.91822 minutes , Location - 296, Weight: 897.446}
0.8;1;Dynamic Routing System;out_new_route_1;230
0.8;1;Dynamic Routing System;out_new_route_2;342
0.8;1;Dynamic Routing System;out_new_route_3;434
0.8;1;Dynamic Routing System;out_new_route_4;751
0.8;1;Dynamic Routing System;;{ Completed routes : 329}
0.8;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
0.8;3;1st Truck;out_updatel_truck;249
0.8;3;1st Truck;out_updatew_truck;36077.3
0.8;3;1st Truck;out_arrival_station;1
0.8;3;1st Truck;out_updatet;0.2
0.8;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 230, Weight: 36077.3}
0.8;4;2nd Truck;out_updatel_truck;308
0.8;4;2nd Truck;out_updatew_truck;9153.95
0.8;4;2nd Truck;out_arrival_station;1
0.8;4;2nd Truck;out_updatet;0.2
0.8;4;2nd Truck;; Truck : { Time Elapsed - 50.0132 minutes , Location - 342, Weight: 10589.9}
0.8;5;3rd Truck;out_updatel_truck;726
0.8;5;3rd Truck;out_updatew_truck;10230.9
0.8;5;3rd Truck;out_arrival_station;1
0.8;5;3rd Truck;out_updatet;0.2
0.8;5;3rd Truck;; Truck : { Time Elapsed - 47.761 minutes , Location - 434, Weight: 11846.3}
0.8;6;4th Truck;out_updatel_truck;301
0.8;6;4th Truck;out_updatew_truck;897.446
0.8;6;4th Truck;out_arrival_station;1
0.8;6;4th Truck;out_updatet;0.2
0.8;6;4th Truck;; Truck : { Time Elapsed - 6.27668 minutes , Location - 751, Weight: 1974.38}
1;1;Dynamic Routing System;out_new_route_1;299
1;1;Dynamic Routing System;out_new_route_2;694
1;1;Dynamic Routing System;out_new_route_3;621
1;1;Dynamic Routing System;out_new_route_4;376
1;1;Dynamic Routing System;;{ Completed routes : 432}
1;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
1;3;1st Truck;out_updatel_truck;247
1;3;1st Truck;out_updatew_truck;36077.3
1;3;1st Truck;out_arrival_station;1
1;3;1st Truck;out_updatet;0.2
1;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 299, Weight: 36077.3}
1;4;2nd Truck;out_updatel_truck;344
1;4;2nd Truck;out_updatew_truck;10589.9
1;4;2nd Truck;out_arrival_station;1
1;4;2nd Truck;out_updatet;0.2
1;4;2nd Truck;; Truck : { Time Elapsed - 51.8051 minutes , Location - 694, Weight: 11128.3}
1;5;3rd Truck;out_updatel_truck;445
1;5;3rd Truck;out_updatew_truck;11846.3
1;5;3rd Truck;out_arrival_station;1
1;5;3rd Truck;out_updatet;0.2
1;5;3rd Truck;; Truck : { Time Elapsed - 56.2825 minutes , Location - 621, Weight: 14000.2}
1;6;4th Truck;out_updatel_truck;755
1;6;4th Truck;out_updatew_truck;1974.38
1;6;4th Truck;out_arrival_station;1
1;6;4th Truck;out_updatet;0.2
1;6;4th Truck;; Truck : { Time Elapsed - 10.4173 minutes , Location - 376, Weight: 2871.83}
1.2;1;Dynamic Routing System;out_new_route_1;262
1.2;1;Dynamic Routing System;out_new_route_2;519
1.2;1;Dynamic Routing System;out_new_route_3;325
1.2;1;Dynamic Routing System;out_new_route_4;677
1.2;1;Dynamic Routing System;;{ Completed routes : 535}
1.2;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
1.2;3;1st Truck;out_updatel_truck;304
1.2;3;1st Truck;out_updatew_truck;36077.3
1.2;3;1st Truck;out_arrival_station;1
1.2;3;1st Truck;out_updatet;0.2
1.2;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 262, Weight: 36077.3}
1.2;4;2nd Truck;out_updatel_truck;706
1.2;4;2nd Truck;out_updatew_truck;11128.3
1.2;4;2nd Truck;out_arrival_station;1
1.2;4;2nd Truck;out_updatet;0.2
1.2;4;2nd Truck;; Truck : { Time Elapsed - 62.2872 minutes , Location - 519, Weight: 13461.7}
1.2;5;3rd Truck;out_updatel_truck;634
1.2;5;3rd Truck;out_updatew_truck;14000.2
1.2;5;3rd Truck;out_arrival_station;1
1.2;5;3rd Truck;out_updatet;0.2
1.2;5;3rd Truck;; Truck : { Time Elapsed - 65.5193 minutes , Location - 325, Weight: 16513}
1.2;6;4th Truck;out_updatel_truck;409
1.2;6;4th Truck;out_updatew_truck;2871.83
1.2;6;4th Truck;out_arrival_station;1
1.2;6;4th Truck;out_updatet;0.2
1.2;6;4th Truck;; Truck : { Time Elapsed - 39.8906 minutes , Location - 677, Weight: 8974.46}
1.4;1;Dynamic Routing System;out_new_route_1;255
1.4;1;Dynamic Routing System;out_new_route_2;284
1.4;1;Dynamic Routing System;out_new_route_3;290
1.4;1;Dynamic Routing System;out_new_route_4;104
1.4;1;Dynamic Routing System;;{ Completed routes : 638}
1.4;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
1.4;3;1st Truck;out_updatel_truck;275
1.4;3;1st Truck;out_updatew_truck;36077.3
1.4;3;1st Truck;out_arrival_station;1
1.4;3;1st Truck;out_updatet;0.2
1.4;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 255, Weight: 36077.3}
1.4;4;2nd Truck;out_updatel_truck;545
1.4;4;2nd Truck;out_updatew_truck;13461.7
1.4;4;2nd Truck;out_arrival_station;1
1.4;4;2nd Truck;out_updatet;0.2
1.4;4;2nd Truck;; Truck : { Time Elapsed - 88.5635 minutes , Location - 284, Weight: 18307.9}
1.4;5;3rd Truck;out_updatel_truck;342
1.4;5;3rd Truck;out_updatew_truck;16513
1.4;5;3rd Truck;out_arrival_station;1
1.4;5;3rd Truck;out_updatet;0.2
1.4;5;3rd Truck;; Truck : { Time Elapsed - 79.973 minutes , Location - 290, Weight: 19743.8}
1.4;6;4th Truck;out_updatel_truck;693
1.4;6;4th Truck;out_updatew_truck;8974.46
1.4;6;4th Truck;out_arrival_station;1
1.4;6;4th Truck;out_updatet;0.2
1.4;6;4th Truck;; Truck : { Time Elapsed - 56.3747 minutes , Location - 104, Weight: 12025.8}
1.6;1;Dynamic Routing System;out_new_route_1;300
1.6;1;Dynamic Routing System;out_new_route_2;105
1.6;1;Dynamic Routing System;out_new_route_3;137
1.6;1;Dynamic Routing System;out_new_route_4;132
1.6;1;Dynamic Routing System;;{ Completed routes : 741}
1.6;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
1.6;3;1st Truck;out_updatel_truck;268
1.6;3;1st Truck;out_updatew_truck;36077.3
1.6;3;1st Truck;out_arrival_station;1
1.6;3;1st Truck;out_updatet;0.2
1.6;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 300, Weight: 36077.3}
1.6;4;2nd Truck;out_updatel_truck;289
1.6;4;2nd Truck;out_updatew_truck;18307.9
1.6;4;2nd Truck;out_arrival_station;1
1.6;4;2nd Truck;out_updatet;0.2
1.6;4;2nd Truck;; Truck : { Time Elapsed - 91.9274 minutes , Location - 105, Weight: 19384.8}
1.6;5;3rd Truck;out_updatel_truck;293
1.6;5;3rd Truck;out_updatew_truck;19743.8
1.6;5;3rd Truck;out_arrival_station;1
1.6;5;3rd Truck;out_updatet;0.2
1.6;5;3rd Truck;; Truck : { Time Elapsed - 83.7922 minutes , Location - 137, Weight: 20461.8}
1.6;6;4th Truck;out_updatel_truck;104
1.6;6;4th Truck;out_updatew_truck;12025.8
1.6;6;4th Truck;out_arrival_station;1
1.6;6;4th Truck;out_updatet;0.2
1.6;6;4th Truck;; Truck : { Time Elapsed - 56.5462 minutes , Location - 132, Weight: 12205.3}
1.8;1;Dynamic Routing System;out_new_route_1;196
1.8;1;Dynamic Routing System;out_new_route_2;138
1.8;1;Dynamic Routing System;out_new_route_3;251
1.8;1;Dynamic Routing System;out_new_route_4;154
1.8;1;Dynamic Routing System;;{ Completed routes : 815}
1.8;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
1.8;3;1st Truck;out_updatel_truck;307
1.8;3;1st Truck;out_updatew_truck;36077.3
1.8;3;1st Truck;out_arrival_station;1
1.8;3;1st Truck;out_updatet;0.2
1.8;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 196, Weight: 36077.3}
1.8;4;2nd Truck;out_updatel_truck;131
1.8;4;2nd Truck;out_updatew_truck;19384.8
1.8;4;2nd Truck;out_arrival_station;1
1.8;4;2nd Truck;out_updatet;0.2
1.8;4;2nd Truck;; Truck : { Time Elapsed - 110.065 minutes , Location - 138, Weight: 24231}
1.8;5;3rd Truck;out_updatel_truck;142
1.8;5;3rd Truck;out_updatew_truck;20461.8
1.8;5;3rd Truck;out_arrival_station;1
1.8;5;3rd Truck;out_updatet;0.2
1.8;5;3rd Truck;; Truck : { Time Elapsed - 87.7324 minutes , Location - 251, Weight: 21538.7}
1.8;6;4th Truck;out_updatel_truck;137
1.8;6;4th Truck;out_updatew_truck;12205.3
1.8;6;4th Truck;out_arrival_station;1
1.8;6;4th Truck;out_updatet;0.2
1.8;6;4th Truck;; Truck : { Time Elapsed - 60.4864 minutes , Location - 154, Weight: 13282.2}
1.8;1;Dynamic Routing System;;{ Completed routes : 815}
1.8;2;Transfer Station;;{Active Status of trucks :1,1,1,1}
1.8;3;1st Truck;; Truck : { Time Elapsed - 156.672 minutes , Location - 196, Weight: 36077.3}
1.8;4;2nd Truck;; Truck : { Time Elapsed - 110.065 minutes , Location - 138, Weight: 24231}
1.8;5;3rd Truck;; Truck : { Time Elapsed - 87.7324 minutes , Location - 251, Weight: 21538.7}
1.8;6;4th Truck;; Truck : { Time Elapsed - 60.4864 minutes , Location - 154, Weight: 13282.2}
```




## Acknowledgements

 - [@Sasisekhar](https://github.com/Sasisekhar/blank_project_rt)


