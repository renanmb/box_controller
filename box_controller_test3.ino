#include <Wire.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <PWM.h> //PWM library for controlling the steppers

ros::NodeHandle  nh;

std_msgs::Float32 temp_msg;
ros::Publisher temp("temp", &temp_msg);

//use pin 11 on the Mega instead, otherwise there is a frequency cap at 31 Hz
const int cooler_pin = 9;     
const int LED_left_pin = 10;     
const int LED_right_pin = 11;
const int sensor1 = A0;

int32_t frequency1 = 0; //frequency (in Hz)
int32_t frequency2 = 0; //frequency (in Hz)
int32_t frequency3 = 0;


void boxCallback ( const geometry_msgs::Twist& twistMsg ){
  frequency1 = abs( twistMsg.linear.x );
  frequency2 = abs( twistMsg.linear.y );
  frequency3 = abs( twistMsg.linear.z );
  SetPinFrequency(cooler_pin, frequency1);
  SetPinFrequency(LED_left_pin, frequency2); 
  SetPinFrequency(LED_right_pin, frequency3);
}

ros::Subscriber<geometry_msgs::Twist> sub("box", &boxCallback) ;

void setup(){
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 
  nh.initNode();

  // Subscribe 
  nh.subscribe(sub);
  nh.advertise(temp);

  // =======================================================================================
  /* ================ PWM Function  ======================================================= */

  pinMode(cooler_pin, OUTPUT);
  pinMode(LED_left_pin, OUTPUT);
  pinMode(LED_right_pin, OUTPUT);
  
  
}

void loop(){
  
  temp_msg.data = analogRead(sensor1);
  temp.publish( &temp_msg);
  
  nh.spinOnce();

  //setting the duty to 50% with the highest possible resolution that 
  //can be applied to the timer (up to 16 bit). 1/2 of 65536 is 32768.
    pwmWriteHR(cooler_pin, 32768);
    pwmWriteHR(LED_left_pin, 32768);
    pwmWriteHR(LED_right_pin, 32768);
    
  delay(100);
}
