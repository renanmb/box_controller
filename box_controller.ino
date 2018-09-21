#include <ros.h>

#include <Wire.h>
#include <std_msgs/Float32.h>

#include <PWM.h> //PWM library for controlling the steppers
//#include <inttypes.h> //not sure about this for the int32_t


ros::NodeHandle  nh;
std_msgs::Float32 cooler;
std_msgs::Float32 LED_left;
std_msgs::Float32 LED_right;

//use pin 11 on the Mega instead, otherwise there is a frequency cap at 31 Hz
const int cooler_pin = 9;     
const int LED_left_pin = 10;     
const int LED_right_pin = 11;

int32_t frequency1 = 0; //frequency (in Hz)
int32_t frequency2 = 0; //frequency (in Hz)
int32_t frequency3 = 0;


void cooler_callback(const std_msgs::Float32& cooler){
  frequency1 = (int)cooler.data;  
}

void LED_left_callback(const std_msgs::Float32& LED_left){
  frequency2 = (int)LED_left.data;
}

void LED_right_callback(const std_msgs::Float32& LED_right){
  frequency3 = (int)LED_right.data;
}

ros::Subscriber<std_msgs::Float32> sub1("cooler", cooler_callback) ;
ros::Subscriber<std_msgs::Float32> sub2("LED left", LED_left_callback) ;
ros::Subscriber<std_msgs::Float32> sub3("LED right", LED_right_callback) ;

void setup(){
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 
  nh.initNode();

  // Subscribe 
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);

  // =======================================================================================
  /* ================ PWM Function  ======================================================= */
  //PWM to cooler
  pinMode(cooler_pin, OUTPUT);
  SetPinFrequency(cooler_pin, frequency1);
  //PWM to LED_left
  pinMode(LED_left_pin, OUTPUT);
  SetPinFrequency(LED_left_pin, frequency2);
  //PWM to LED_right  
  pinMode(LED_right_pin, OUTPUT);
  SetPinFrequency(LED_right_pin, frequency3);
  
    while(true){
    //setting the duty to 50% with the highest possible resolution that 
    //can be applied to the timer (up to 16 bit). 1/2 of 65536 is 32768.
    pwmWriteHR(cooler_pin, 32768);
    pwmWriteHR(LED_left_pin, 32768);
    pwmWriteHR(LED_right_pin, 32768);
  }
  
}

void loop(){
  nh.spinOnce();

  delay(1);
}
