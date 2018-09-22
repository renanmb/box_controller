#include <ros.h>

#include <Wire.h>
#include <std_msgs/Float32.h>
#include "std_msgs/Int32MultiArray.h"
#include <PWM.h> //PWM library for controlling the steppers

ros::NodeHandle  nh;
std_msgs::Int32MultiArray array;

//use pin 11 on the Mega instead, otherwise there is a frequency cap at 31 Hz
const int cooler_pin = 9;     
const int LED_left_pin = 10;     
const int LED_right_pin = 11;

int32_t frequency1 = 0; //frequency (in Hz)
int32_t frequency2 = 0; //frequency (in Hz)
int32_t frequency3 = 0;

int Arr[3];

void arrayCallback(std_msgs::Int32MultiArray::ConstPtr& array);

int main(int argc, char **argv)
{
  frequency1 = Arr[0]; 
  frequency2 = Arr[1];
  frequency3 = Arr[2];

  return 0;
}

void arrayCallback(const std_msgs::Int32MultiArray::ConstPtr& array)
{
  int i = 0;
  // print all the remaining numbers
  for(std::vector<int>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
  {
    Arr[i] = *it;
    i++;
  }

  return;
}


ros::Subscriber<(std_msgs::Int32MultiArray> sub1("array", cooler_callback) ;


void setup(){
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 
  nh.initNode(argc, argv, "arraySubscriber");

  // Subscribe 
  nh.subscribe(sub1);

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
