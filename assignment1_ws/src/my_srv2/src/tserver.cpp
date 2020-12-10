#include "ros/ros.h"
#include "my_srv2/Target.h"

double randMtoN(double M, double N){
return M+(rand() / (RAND_MAX / (N-M)));

}

bool callback_random(my_srv2::Target::Request &req, my_srv2::Target::Response &res){
    res.x_t = randMtoN(req.min, req.max);
    res.y_t = randMtoN(req.min, req.max);
    return true;
}


int main(int argc, char **argv){

    ros::init(argc,argv, "tserver");

    ros::NodeHandle n;

    ros::ServiceServer tgt_serv = n.advertiseService("/Target_random", callback_random);


    ros::spin();
    return 0;
}
