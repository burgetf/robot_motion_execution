/*
 *run_motion_execution_rviz.cpp
 *
 *  Created on: June 21, 2015
 *      Author: Felix Burget
 */


#include <ros/ros.h>
#include <motion_trajectory_execution/trajectory_execution_rviz.h>


using namespace std;

int main(int argc, char** argv)
{
    //Init Node
    ros::init(argc, argv, "motion_execution_rviz");

    string PLANNING_GROUP = "kuka_complete_arm";
    string PLANNER_NAME = "bi_informed_rrt_star";
    string PLANNING_SCENE = "three_gates";
    string PLANNING_RUN = "0";

    //Set planning group for visualization (as specified in URDF)
    if(argc > 1) {
      stringstream s(argv[1]);
      s >> PLANNING_GROUP;
    }
    //Set planner name
    if(argc > 2) {
      stringstream s(argv[2]);
      s >> PLANNER_NAME;
    }
    //Set scene name
    if(argc > 3) {
      stringstream s(argv[3]);
      s >> PLANNING_SCENE;
    }
    //Set sleep duration between trajectory points for visualization
    if(argc > 4) {
      stringstream s(argv[4]);
      s >> PLANNING_RUN;
    }

    //Node Handle
    ros::NodeHandle nh;


    //Read package path for planner from parameter server
    //string planner_package_path;
    //nh.param("planner_package_path", planner_package_path, std::string("/home/burgetf/catkin_ws/src/manipulator_motion_control/rrt_star_algorithm"));

    //Get package path of "planner_statistics"
    string planner_package_path;
    planner_package_path = ros::package::getPath("planner_statistics");


    //Set path to the file that will store the planned joint trajectory
    string folder_path = planner_package_path + "/data/" + PLANNER_NAME + "/" + PLANNING_SCENE + "_scene_joint_trajectory_run_"+ PLANNING_RUN +".txt";
    char *file_path_joint_trajectory = new char[folder_path.size() + 1];
    copy(folder_path.begin(), folder_path.end(), file_path_joint_trajectory);
    file_path_joint_trajectory[folder_path.size()] = '\0'; // don't forget the terminating 0
    cout<<file_path_joint_trajectory<<endl;

    //Set path to the file that will store the planned ee trajectory
    folder_path = planner_package_path + "/data/" + PLANNER_NAME + "/" + PLANNING_SCENE + "_scene_ee_trajectory_run_"+ PLANNING_RUN +".txt";
    char *file_path_ee_trajectory = new char[folder_path.size() + 1];
    copy(folder_path.begin(), folder_path.end(), file_path_ee_trajectory);
    file_path_ee_trajectory[folder_path.size()] = '\0'; // don't forget the terminating 0
    cout<<file_path_ee_trajectory<<endl;
    

    //Motion Commander Object
    trajectory_execution::MotionCommanderRVIZ mc(PLANNING_GROUP, PLANNING_SCENE);

    //Execute joint trajectory from file
    mc.executeJointTrajectory(file_path_joint_trajectory, file_path_ee_trajectory);

    cout<<"Finished trajectory visualization"<<endl;
   	
    ros::shutdown();

    return 0;
}

