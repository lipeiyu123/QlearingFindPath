#include "rand.h"
#include <iostream>

int     int_rand( int min , int max ){

            if (min == max){
                        return min;
            }
            if (min > max){
                        std::cout << "int_rand error :  min should  < max " << std::endl;
            }
            std::random_device          seed ; 
            std::mt19937                        engine( seed() ); 
            std::uniform_int_distribution<int>       distrib(min, max);
            return  distrib(engine);
}


double      double_rand(double min , double max){

            if (min == max){
                        return min;
            }
            if (min > max){
                        std::cout << "double_rand error :  min should  < max " << std::endl;
            }
            std::random_device          seed ; 
            std::mt19937                        engine( seed() ); 
            std::uniform_real_distribution<double>       distrib(min, max);
            return  distrib(engine);
}