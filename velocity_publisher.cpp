# include <ros/ros.h>
# include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
	ros::init(argc,argv, "velocity_publisher");
	ros::NodeHandle n;
	ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);

	 	 ros ::param::set("/turtlesm/background_r",225);
	     ros ::param::set("/turtlesm/background_b",0);
	     ros ::param::set("/turtlesm/background_g",0);
		ros::Rate loop_rate(10);	 
	int count = 0;
	int pd=1;
	while (ros::ok())
	{	

		n.setParam("background_r",255);
		n.setParam("background_b",0);
		n.setParam("background_g",0);		

	      geometry_msgs::Twist vel_msg;
		   vel_msg.linear.x = 1;
		   vel_msg.angular.z=pd; 
		  while(count==63){
			  count=0;
              pd = pd*-1;

		  }
		  count ++;
		 
		 turtle_vel_pub.publish(vel_msg);
		 ROS_INFO("Publish turtle velocity command[%0.2f m/s, %0.2f rad/s]",
		                       vel_msg.linear.x,vel_msg.angular.z);
		loop_rate.sleep();







	}	
	

return 0;


}
