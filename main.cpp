#include <iostream>
#include "q_learing/Qlearing.h"
#include "config.h"

#define     E    0
#define     O   -1000
#define     F    1000

int main(){


            double test = 0;
            int state = 0;
            int start = 0;
            int eps    = 0;
            int next_state = 0;
            int steps = 0;
            Eigen::VectorXi action_nextstete = Eigen::VectorXi::Zero(2);
            int action = 0;
            int  nextstate_vale = 0;
            Eigen::MatrixXi     map(6 , 6);
            map    <<      E , E , E , E , E , E,
                                    E , E , O , E , E , E ,
                                    E , E , O , E , F , E ,
                                    E , E , O , O , O , E ,
                                    E , E , E , E , E , E,
                                    E , E , E , E , E , E;

            Eigen::MatrixXd     Q(36 , 8) ;
            for (int i = 0 ; i < 36 ; i++){
                                    for(int j = 0 ; j < 8 ; j++){
                                                    Q(i , j ) = 0;
                                    }
            }


            Qlearing        q(0.8 , 0.9 , 0.1);
            std::cout << "input start"<<std::endl;
            std::cin >> start;
            while(eps < MAX_EPS){

                        
                        state = start;//q.choose_state();
                        //std::cout << "state     " << state << std::endl;
                        while((state !=  16) && (steps <= MAX_STEPS)){
                                    steps ++;
                                    action_nextstete = q.take_action(Q , state);
                                    Q(state , action_nextstete(0)) = q.learn(state , action_nextstete(0) , action_nextstete(1) , Q , map);

                                    state = action_nextstete(1);
                        }
                        eps++;
            }

            std::cout <<"finish Q:\n" << Q << " \n\n\n\n"<<  std::endl;

            eps = 0;
            steps = 0;
            //state = q.choose_state();
            state = start;
            std::cout << "\n\n\n" << std::endl;
            std::cout << "start 初始状态        x: "<<  state % 6 << "          y:" << (state - (state %6))/6 << std::endl;
            while(state != 16&& (steps <= MAX_STEPS)){
                        std::cout << "当前状态  x: "<<  state % 6 << "          y:" << (state - (state %6))/6 << std::endl;
                        action = q.useQ(Q , state);
                        state = q.state_transfer(state , action);
                        std::cout << "下个状态  x: "<<  state % 6 << "          y:" << (state - (state %6))/6<< std::endl;
                        steps++;
            }



            return 0;
}
