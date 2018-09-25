#include <ros/ros.h>

#include <std_msgs/Float32.h>


class Link{
   public:
     Link(); //error: ISO C++ forbids declaration of ‘Imu’ with no type [-fpermissive]

   private:
     void tempCallback(const std_msgs::Float32::ConstPtr& temp);
     void publish();
     ros::NodeHandle nh;
     ros::Publisher pub;
     ros::Subscriber temp;
     std_msgs::Float32 cooler;
	 std_msgs::Float32 LED left;
	 std_msgs::Float32 LED right;
	 std_msgs::Float32 temp;
};

//This will change when add the TF and pose 
Link::Link(){ //error: ISO C++ forbids declaration of ‘Imu’ with no type [-fpermissive]
   pub = nh.advertise<std_msgs::Float32> ("cooler", 1 );
   pub = nh.advertise<std_msgs::Float32> ("LED left", 10);
   pub = nh.advertise<std_msgs::Float32> ("LED right", 10);
 
   temp_sub = nh.subscribe<std_msgs::Float32> ("temp", 10, &Link::tempCallback, this);
}

void Link::publish(){
	
	cooler.data = rpm;
	LED left.data = ; // add function for turning lights ON and OFF and controlling intensity
	LED right.data = ; // add function for turning lights ON and OFF and controlling intensity
	pub.publish(cooler);
	pub.publish(LED left);
	pub.publish(LED right);
}

void Link::tempCallback(const std_msgs::Float32::ConstPtr& temp){
   
   temp.data = temp->data; 
   pub.publish(temp); //need to review how to do this
}

int main(int argc, char** argv){
   ros::init(argc, argv, "commlink");
   Link Link; //object did not understand why
   ros::spin();
}