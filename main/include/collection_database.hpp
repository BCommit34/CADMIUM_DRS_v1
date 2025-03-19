#ifndef COLLECTION_DATABASE_HPP
#define COLLECTION_DATABASE_HPP


#include "collection_pt.hpp"


class collection_database{
    public:
        static std::vector<std::vector<collection_pt>> set_collection_database(){
            return set_collection_database("./main/include/Dataset_Simulation.csv");
        }



        static std::vector<std::vector<collection_pt>> set_collection_database(std::string database_csv_file){

            std::ifstream io_csv_file(database_csv_file);
            std::vector<std::vector<collection_pt>> collection_map = {};
            std::string tmp_street_name = "";
            int index_street=0;


            if (!io_csv_file.is_open()){
                std::cerr << "Error opening file: " << database_csv_file << std::endl;
            }else{
                //Create vector collection of street
                std::stringstream file_buffer;
                file_buffer << io_csv_file.rdbuf();
                char* str_file_buffer = new char[file_buffer.str().length()+1];
                std::strcpy(str_file_buffer, file_buffer.str().c_str());

                char *token_street;
                std::string token_location;
                std::vector<collection_pt> vector_street;
                token_street = std::strtok(str_file_buffer, "\n");
                while (token_street != nullptr) {
                    index_street = 0;

                    int tmp_index;
                    int tmp_num;
                    std::string tmp_name;
                    double tmp_x;
                    double tmp_y;
                    bool tmp_bool_intersection;
                    int* tmp_index_closest_pt;
                    tmp_index_closest_pt = (int *)malloc(sizeof(int));

                    std::string tmp_token_street(token_street);
                    
                    std::stringstream lineStream(tmp_token_street);
                    
                    while (std::getline(lineStream, token_location, ',')) {

                        switch(index_street){
                            case 0:
                                tmp_index = std::stoi(token_location);
                            
                                break;
                            case 1:
                                
                                tmp_num = std::stoi(token_location);

                                break;
                            
                            case 2:
                                tmp_name = token_location;
                                
                                break;
                            case 3:
                                
                                tmp_x = std::stod(token_location);
                                
                                break;
                            case 4:
                                tmp_y = std::stod(token_location);
                               
                                break;
                            case 5:
                                if (token_location.compare("TRUE") == 0){
                                    tmp_bool_intersection = true;
                                }else{
                                    tmp_bool_intersection = false;
                                }
                                
                                break;
                            default:
                                try {
                                    *tmp_index_closest_pt = std::stoi(token_location);
                                } catch (const std::exception& e) {
                                    *tmp_index_closest_pt = -1;
                                }
                                tmp_index_closest_pt++;
                                break;
                        }
                        index_street++;
                    }
                    tmp_index_closest_pt -= 2;
                    index_street = 0;
                    collection_pt add_pt = {tmp_index, tmp_num,tmp_name,tmp_x,tmp_y,tmp_bool_intersection,tmp_index_closest_pt};
                
                    
                    if((tmp_street_name.compare(tmp_name)==0) || (vector_street.empty())){
                        vector_street.push_back(add_pt);
                    }else{
                        //Push vector street to the map
                        std::vector<collection_pt> map_vector_street (vector_street);
                        collection_map.push_back(map_vector_street);
                        vector_street = {};
                        vector_street.push_back(add_pt);
                    }
                    tmp_street_name = tmp_name;
                    token_street = std::strtok(NULL, "\n");
                }
                std::vector<collection_pt> map_vector_street (vector_street);
                collection_map.push_back(map_vector_street);
            

            }
            
            io_csv_file.close();

            return collection_map;
        }
    
        void print_map(std::vector<std::vector<collection_pt>> map){
            for(int i = 0 ; i < map.size() ; i++){
                for (int j = 0 ; j<map[i].size() ; j++){
                    std::cout << map[i][j].index <<" : " <<map[i][j].num_street << " : " << map[i][j].name_street << " : " << map[i][j].xCoordinate << " : " << map[i][j].yCoordinate << " : " << map[i][j].bool_intersection << " : " << map[i][j].index_closest_pt[0] << " " << map[i][j].index_closest_pt[1] << std::endl;
                }

                std::cout <<"_________________________________________________________________________________"<<std::endl;

            }
        }

};

#endif





