#include "Qlearing.h"
#include "../random/rand.h"
#include <iostream>

Qlearing::Qlearing(double ga = 0.8 , double lr = 0.9 , double eps = 0.1){
                
                gamma = ga;
                learing_rate = lr;
                epsilon = eps;
}




Eigen::MatrixXd     Qlearing::init_Q(Eigen::MatrixXi map){

            Eigen::MatrixXd  Q = Eigen::MatrixXd::Zero(map.size(),8);
            return Q;
}



Eigen::VectorXi     Qlearing::init_action(){

           Eigen::VectorXi action = Eigen::VectorXi::Zero(8);
           return action; 
}

int                               Qlearing::state_transfer(const int state , int action){

            int next_state = state;
            if (action == 0){next_state = next_state - 6;}    //     ^
            if (action == 1){next_state = next_state +1;}    //      >
            if (action == 2){next_state = next_state + 6;}   //     v
            if (action == 3){next_state = next_state - 1;}    //      <

            if (action == 4){next_state = next_state - 5;}    
            if (action == 5){next_state = next_state +7;}
            if (action == 6){next_state = next_state + 5;}
            if (action == 7){next_state = next_state - 7;}
            return next_state;
}   

int            Qlearing::choose_state(){

            int state = 0;
            do{
                state = int_rand(0,35);}
            while ( (state == 8)    && (state == 14) && (state == 20));
            return state;         
}


Eigen::VectorXi            Qlearing::feasible_action(const int state){
            int next_state = state;
            Eigen::VectorXi feasible_action = Eigen::VectorXi::Zero(8);

            if ((next_state - 6) > 35  || (next_state - 6) < 0)             {feasible_action(0) = 1;} //     ^
            if ((next_state + 1) > 35  || (next_state +1) < 0 || ((next_state+1) % 6) == 0)             {feasible_action(1) = 1;}  //    >
            if ((next_state + 6) > 35  || (next_state + 6) < 0)             {feasible_action(2) = 1;}//     v
            if ((next_state - 1) > 35  || (next_state - 1) < 0  || (next_state % 6) == 0)             {feasible_action(3) = 1;}//       <

            if ((next_state - 5) > 35  || (next_state - 5) < 0 || ((next_state+1) % 6) == 0)             {feasible_action(4) = 1;}
            if ((next_state + 7) > 35  || (next_state +7) < 0 || ((next_state+1) % 6) == 0)             {feasible_action(5) = 1;}
            if ((next_state + 5) > 35  || (next_state + 5) < 0  || (next_state % 6) == 0)             {feasible_action(6) = 1;}
            if ((next_state - 7) > 35  || (next_state - 7) < 0 || (next_state % 6) == 0)             {feasible_action(7) = 1;}
            
            return feasible_action;

}

Eigen::VectorXi             Qlearing::take_action(const Eigen::MatrixXd Q , int state){

            Eigen::VectorXi action_state = Eigen::VectorXi::Zero(2);
            Eigen::VectorXi all_action = Eigen::VectorXi::Zero(8);
            Eigen::VectorXi temp_action = Eigen::VectorXi::Zero(8);
            int len = 0;
            int action = 0;

            if (double_rand(0 , 1) > 0.9){
                                action = useQ(Q , state);
                                action_state(0) = action;
                                action_state(1) = state_transfer(state , action);

            }
            else{
                                all_action =  feasible_action(state);
                                for (int i = 0 ; i < 8 ; i++){
                                                if (all_action(i) != 1 ){
                                                               temp_action(len) = i;
                                                               len++;
                                                }
                                }
                                action_state(0) = temp_action( int_rand(0,len-1) ) ;
                                action_state(1) = state_transfer(state , action_state(0));
            }

            return action_state;
}



double          Qlearing::maxQ( const Eigen::MatrixXd Q , int state){

                double maxq = -65535.0;
                for(int i = 0 ; i  < 8 ; i++){
                            if (maxq < (Q(state,i) ) ){
                                        maxq = Q(state,i);
                            }
                }
                return maxq;               
}



int        Qlearing::useQ(const Eigen::MatrixXd Q , int state){

                int vale = -65535;
                int action = 0;
                Eigen::VectorXi   action_list = feasible_action(state);
                for(int i = 0 ; i  < 8 ; i++){
                            if (vale < Q(state,i) && action_list(i) == 0){
                                        vale = Q(state,i);
                                        action = i;
                            }
                }
                return action;              
}

int                                   Qlearing::get_reward(Eigen::MatrixXi  map , int state_){
                                        int lines = state_ % 6 ;
                                        int cols  =  (state_ - lines)/6;
                                        return map(cols , lines);
}

double                         Qlearing::learn(int state , 
                                                                        int action  , 
                                                                        int state_ ,
                                                                        Eigen::MatrixXd Q , 
                                                                        Eigen::MatrixXi  map  ){
                return      Q(state , action) +  learing_rate *(get_reward(map , state_ )  + gamma * maxQ(Q , state_)  -  Q(state , action) );
}
