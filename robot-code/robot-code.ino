#include <PS2X_lib.h>
#include <Psx.h>
#include <Servo.h>
#include <EIRremote.h>
#include <EIRremoteInt.h>
#include "EasyPS2X.h"

//playstation controller pinout
#define PS_DATA_PIN 4
#define PS_CMND_PIN 5
#define PS_ATT_PIN 6 //sel pin for ps2 library
#define PS_CLOCK_PIN 7

//used to init ps controller
#define pressures   false
#define rumble      false

//offset for servo power
#define SERVOR_OFFSET 0

//middle position of joystick
#define JOY_MID 133

#define IR_IN_PIN 10

#define HIT_LED_PIN 9

//ir reciver pin
#define receiver_pin 8

#define sending_pin 3



// class EasyPS2X : public PS2X
// {
//   public:
//     float rightX;
//     float rightY;
//     float leftX;
//     float leftY;

//   // private:
//     void upateJoySticks(){
//         //update joystick's states
//         leftX = Analog(PSS_LX);
//         leftY = Analog(PSS_LY);
//         rightX = Analog(PSS_RX);
//         rightY = Analog(PSS_RY);

//       //apply deadband to positions
//       if(abs(leftX - JOY_MID) < 25)
//         leftX = JOY_MID;
//       if(abs(leftY - JOY_MID) < 25)
//   leftY = JOY_MID;
//       if(abs(rightX - JOY_MID) < 25)
//         rightX = JOY_MID;
//       if(abs(rightY - JOY_MID) < 25)
//         rightY = JOY_MID;

//   //NEEDS TO NOT FLOOR VALUES

//   //map joy vals to -1 to 1
//   leftX = map(leftX, 0, 255, -1, 1);
//   leftY =  map(leftY, 0, 255, -1, 1);
//   rightX =  map(rightX, 0, 255, -1, 1);
//   rightY =  map(rightY, 0, 255, -1, 1);

//   } 

//       //refresh the gamepad and update joystick and button vals
//     //hide extra work from rest of code
//     void refresh(){
//       //update gamepad values from PS2X
//       read_gamepad();

//       updateJoySticks();
      
//     }
// };


//robot state, robot will not be in auto right now
bool isAuto = false;

//ps controller object
EasyPS2X controller;

//servo objects
Servo rightWheel;
Servo leftWheel;

//IRsednding object
IRsend irsend;

//create IR object and var to store results
IRrecv irrecv(receiver_pin);
decode_results results;

//var for raw controller data
unsigned int controller_data;

//var to store button hex val,
//results.value is  an unsigned long
unsigned long irValue;

void setup() {

//attach servos to pins
rightWheel.attach(12);
leftWheel.attach(13);

controller.config_gamepad(PS_CLOCK_PIN, PS_CMND_PIN, PS_ATT_PIN, PS_DATA_PIN, pressures, rumble);

//give controller time for wireless setup
delay(300);

pinMode(HIT_LED_PIN, OUTPUT);

//init serial
Serial.begin(57600);

//enable ir receiving 
irrecv.enableIRIn();
}

void loop() {

//what to do when in auto mode
if(isAuto){

}
//normal driving and comp code
else{
  controller.refresh();

  // readJoyController();

// readControllerButtons();

//checkForHits();

  // readIRController();

  drive(controller.leftY, controller.rightY);

}
}



void readIRController(){

// have we received an IR signal and no object
  if (irrecv.decode(&results)) {
    //if button is not a repeat
    if(results.value != 0xFFFFFFFF)
      //update the button code
      irValue = results.value;

    //print remote val
    // Serial.println(irValue, HEX);

  //act based on rwhat remote button was pressed
  switch(irValue){
  case 0xFFA857: 
  controller.leftY = 1;
  Serial.println("VOL-");
  break;
  case 0xFF22DD: controller.leftY = -1;
    
Serial.println("FAST BACK");    
break;

case 0xFF02FD:
controller.leftY = 0;
controller.rightY = 0;
  break;
  case 0xFFC23D: 
     controller.rightY = -1;
  Serial.println("FAST FORWARD");   
  break;
  case 0xFF629D: 
  controller.rightY = 1;  
  break;
  }
    //give remote a small delay
    delay(250);
    irrecv.resume();
  }

    // Serial.print("left y");
  // Serial.print(controller.leftY);

  // Serial.print("right x");
  // Serial.println(controller.rightY);
}

// void readControllerButtons(){

//   controller.read_gamepad();

//     if(controller.Button(PSB_CROSS)){              //will be TRUE if button was JUST pressed OR released
//       Serial.println("X just changed");
//       // Send the code 3 times. First one is often received as garbage
// for (int i = 0; i < 3; i++) {
//  irsend.sendSony(0x5A5, 12); //Transmit the code 0x5A5 signal from IR LED
//  delay(100);
//  }
//     }
 
//       irrecv.enableIRIn();

// }

void checkForHits(){

 if (irrecv.decode(&results)) {
    //if button is not a repeat
    if(results.value != 0xFFFFFFFF)
      //update the button code
      irValue = results.value;

      Serial.println(irValue, HEX);
  if(irValue == 0xFFA857){
    digitalWrite(HIT_LED_PIN, HIGH);
    delay(100);
  }
  else{
    digitalWrite(HIT_LED_PIN, LOW);
  }
 }


}



void drive(float left, float right){
  if(left == -1){
    leftWheel.writeMicroseconds(2000);
  }
  else if(left == 1){
    leftWheel.writeMicroseconds(1000);
  }
  else{
    leftWheel.writeMicroseconds(1500);
  }

  if(right == -1){
    rightWheel.writeMicroseconds(1000);
  }
  else if(right == 1){
    rightWheel.writeMicroseconds(2000);
  }
  else{
    rightWheel.writeMicroseconds(1500);
  }
  

  
}
