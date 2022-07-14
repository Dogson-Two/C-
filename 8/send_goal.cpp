#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

struct goal_pose
{
    double pose[3];
    double orientation[4];
};

struct goal_pose set_point[]=
{
	 //这里可以添加自己的多个导航目标点
     {0.0, 0.00, 0.000 ,  0.000, 0.000, 0.0, 1.00},
     {2.305, -0.130, 0.000,0.000, 0.000, -0.447, 0.895},
   //  {1.859, -0.168, 0.000,0.000, 0.000, -0.009, 1.000},
  //   {2.37, -0.168, 0.000,0.000, 0.000, -0.009, 1.000},
  //   {2.279, -0.162, 0.000,0.000, 0.000, -0.641, 0.768},
   //  {2.057, -0.026, 0.000,0.000, 0.000, -0.300, 0.954},
 
     {5.122, -4.002, 0.000,0.000, 0.000, -0.004, 1.000},   		
     {5.052, -5.058, 0.000,0.000, 0.000, -0.361, 0.933},

     {5.031, -3.107, 0.000 ,  0.000, 0.000, 0.360, 0.933}, 
     {3.087, -4.590, 0.000,0.000, 0.000, -0.001, 1.000}, 
     {3.033, -5.124, 0.000,0.000, 0.000, -0.692, 0.722},  
     {2.885, -4.544, 0.000,0.000, 0.000, 1.000, 0.002},
    // {2.397, -1.967, 0.000,0.000, 0.000, 0.000, 1.000}, 	
     {1.141, -5.105, 0.000,0.000, 0.000, -0.757, 0.653}, 
    // {1.230, -1.793, 0.000,0.000, 0.000, -0.126, 0.992},


     {-0.001, -1.184, 0.000,0.000, 0.000, -0.095, 0.995},
    // {-0.103, -1.172, 0.000,0.000, 0.000, 0.007, 1.000 },  
};

int size =sizeof(set_point)/sizeof(goal_pose);

 int main(int argc, char *argv[])
{
    ros::init(argc, argv, "simple_navigation_goals");
    MoveBaseClient ac("move_base",true);

    while (!ac.waitForServer(ros::Duration(1.0)))
    {
       ROS_INFO("waiting for the move_base action server to come up");
    }
    
    for(int i=0;i<size;i++)  
    {
        struct goal_pose point=set_point[i];
        move_base_msgs::MoveBaseGoal goal;

        //goal.target_pose.header.frame_id="base_link"; //局部定位
	    goal.target_pose.header.frame_id="map";			//全局定位
        goal.target_pose.header.stamp=ros::Time::now();

        goal.target_pose.pose.position.x=point.pose[0];
        goal.target_pose.pose.position.y=point.pose[1];
        goal.target_pose.pose.position.z=point.pose[2];
        goal.target_pose.pose.orientation.x=point.orientation[0];
        goal.target_pose.pose.orientation.y=point.orientation[1];
        goal.target_pose.pose.orientation.z=point.orientation[2];        
        goal.target_pose.pose.orientation.w=point.orientation[3];
 ROS_INFO("sending goal ...");
        ac.sendGoal(goal);
        ROS_INFO("goal executing ...");
        ac.waitForResult();
        if(ac.getState()==actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            ROS_INFO("the base move goal execute succsess ...");
            continue;   //如果到达目标点想继续循环运动，则设为continue
           // break;        //如果到达目标点之后，想停止，则break     
        }	 
        else{
            ROS_INFO("the base move goal execute failed ...");
            break;
        }
    }
    return 0;
}


















































