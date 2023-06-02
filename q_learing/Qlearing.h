#ifndef __QLEARING_H__
#define __QLEARING_H__

#include <Eigen/Dense>

#define     Y           0
#define     N           -1
#define     END     100

class Qlearing{

                public:
                                                                        Qlearing(double ga ,double lr ,double eps);
                                Eigen::MatrixXd        init_Q(Eigen::MatrixXi map);
                                Eigen::VectorXi         init_action();
                                double                          gamma;
                                double                          learing_rate;
                                double                          epsilon;
                                int                                   choose_state();
                                int                                   state_transfer(int state , int action);
                                Eigen::VectorXi          feasible_action(int state);
                                int                                    get_reward(Eigen::MatrixXi     map , int state);
                                Eigen::VectorXi          take_action( Eigen::MatrixXd Q , int state);
                                double                          maxQ(Eigen::MatrixXd Q , int state);
                                int                                   useQ(Eigen::MatrixXd Q , int state);
                                double                          learn(int state , int action ,  int state_ ,
                                                                                     Eigen::MatrixXd Q , 
                                                                                     Eigen::MatrixXi  map);
                                //Q(state , action_nextstete(0)) = Q(state , action_nextstete(0)) +  lr*(  R(state , action_nextstete(0)) + q.gamma * q.maxQ(Q , action_nextstete(1))  -  Q(state , action_nextstete(0)) );

};



#endif