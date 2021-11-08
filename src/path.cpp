#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>

main (int argc, char **argv)
{
	ros::init (argc, argv, "by_path");

	ros::NodeHandle ph;
	ros::Publisher path_pub = ph.advertise<nav_msgs::Path>("trajectory",1, true);


	float f = 0.0;
	ros::Rate loop_rate(1);
	while (ros::ok())
	{
		nav_msgs::Path path;
		//nav_msgs::Path path;
		path.header.stamp=ros::Time::now();
		path.header.frame_id="/map";
		for (uint32_t i = 0; i < 100; ++i)
		{
			//float y = 5 * sin(f + i / 1000.0f * 2 * M_PI);
			//float x = 5 * cos(f + i / 1000.0f * 2 * M_PI);

			float scale = 0.05;
			
			float t = 2*3.1415927*i/100.0;// 2*pi s
			// circle
			float sint = sin(t);
			float x = scale*(16*sint*sint*sint)+0.95;
			float y = scale*(13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t))+0.2;

			//x /= 3.0;
			//y /= 3.0;

			// 8 zi
			//float x = 0.8*sin(2*t);
			//float y = 0.8*sin(t);

			geometry_msgs::PoseStamped this_pose_stamped;
			this_pose_stamped.pose.position.x = x;
			this_pose_stamped.pose.position.y = y;
			this_pose_stamped.pose.position.z = 1.0;

			//geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(1);
			this_pose_stamped.pose.orientation.x = 0;
			this_pose_stamped.pose.orientation.y = 0;
			this_pose_stamped.pose.orientation.z = 0;
			this_pose_stamped.pose.orientation.w = 1;

			this_pose_stamped.header.stamp=ros::Time::now();;
			this_pose_stamped.header.frame_id="/map";

			path.poses.push_back(this_pose_stamped);
		}
		path_pub.publish(path);
		//ros::spinOnce();               // check for incoming messages
		loop_rate.sleep();
		f += 0.04;
	}

	return 0;
}