#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    
    // ����ƽ�Ʋ���
    transform.setOrigin(tf::Vector3(msg->pose.pose.position.x, 
                                    msg->pose.pose.position.y, 
                                    msg->pose.pose.position.z));

    // ������ת����
    tf::Quaternion q;
    tf::quaternionMsgToTF(msg->pose.pose.orientation, q);
    transform.setRotation(q);

    // ���� odom -> base_link �� tf
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom_to_tf");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/odom", 10, odomCallback);

    ros::spin();
    return 0;
}
