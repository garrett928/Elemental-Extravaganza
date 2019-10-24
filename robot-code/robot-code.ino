#include <PS2X_lib.h>
#include <Psx.h>
#include <Servo.h>
#include <EIRremote.h>
#include <EIRremoteInt.h>

//test for git

//playstation controller pinout
#define PS_DATA_PIN 4
#define PS_CMND_PIN 5
#define PS_ATT_PIN 6 //sel pin for ps2 library
#define PS_CLOCK_PIN 7

#define IR_IN_PIN 10

#define HIT_LED_PIN 9

#define JOY_MID 133
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

#define RIGHT_JOY_X 40 
#define RIGHT_JOY_Y 48

//ir reciver pin
#define receiver_pin 8

#define sending_pin 3

//var to store button hex val,
//results.value is  an unsigned long
unsigned long irValue;

//create IR object and var to store results
IRrecv irrecv(receiver_pin);
decode_results results;


IRsend irsend;

//ps controller object
PS2X controller;

//vars for seperated controller data
float joyRightX;
float joyRightY;
float joyLeftX;
float joyLeftY;

//var raw controller data
unsigned int controller_data;

// servos
Servo rightWheel;
Servo left_wheel;

void setup() {

//attach servos to pins
rightWheel.attach(12);
left_wheel.attach(13);

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
  // put your main code here, to run repeatedly:
  // readJoyController();

readControllerButtons();

//checkForHits();

  readIRController();

  drive(joyLeftY, joyRightY);

  // delay(500);
}



void readIRController(){

// joyLeftY = 0;
// joyRightY = 0;

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
  joyLeftY = 1;
  Serial.println("VOL-");
  break;
  case 0xFF22DD: 
    joyLeftY = -1;
    
Serial.println("FAST BACK");    
break;

case 0xFF02FD:
    joyLeftY = 0;
joyRightY = 0;
  break;
  case 0xFFC23D: 
     joyRightY = -1;
  Serial.println("FAST FORWARD");   
  break;
  case 0xFF629D: 
  joyRightY = 1;  
  break;
  }
    //give remote a small delay
    delay(250);
    irrecv.resume();
  }

    // Serial.print("left y");
  Serial.println(joyLeftY);

  // Serial.print("right x");
  Serial.println(joyRightY);
}

void readControllerButtons(){

  controller.read_gamepad();

    if(controller.Button(PSB_CROSS)){              //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
      // Send the code 3 times. First one is often received as garbage
for (int i = 0; i < 3; i++) {
 irsend.sendSony(0x5A5, 12); //Transmit the code 0x5A5 signal from IR LED
 delay(100);
 }
    }
 
      irrecv.enableIRIn();

}

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

/*

*/
void readJoyController(){
   //read gamepad to refresh library vals
  controller.read_gamepad();


  //update joystick's states
  joyLeftX = controller.Analog(PSS_LX);
  joyLeftY = controller.Analog(PSS_LY);
  joyRightX = controller.Analog(PSS_RX);
  joyRightY = controller.Analog(PSS_RY);

  Serial.println(joyLeftY);
 //needs to not floor vals
 if(abs(joyLeftX - JOY_MID) < 25)
    joyLeftX = JOY_MID;
if(abs(joyLeftY - JOY_MID) < 25)
    joyLeftY = JOY_MID;
if(abs(joyRightX - JOY_MID) < 25)
    joyRightX = JOY_MID;
    if(abs(joyRightY - JOY_MID) < 25)
    joyRightY = JOY_MID;

  //map joy vals to -1 to 1
  joyLeftX = map(joyLeftX, 0, 255, -1, 1);
  joyLeftY =  map(joyLeftY, 0, 255, -1, 1);
  joyRightX =  map(joyRightX, 0, 255, -1, 1);
  joyRightY =  map(joyRightY, 0, 255, -1, 1);

  // Serial.print("left y");
  Serial.println(joyLeftY);

  // Serial.print("right x");
  Serial.println(joyRightY);

  delay(30);
}



void drive(float left, float right){
  if(left == -1){
    left_wheel.writeMicroseconds(2000);
  }
  else if(left == 1){
    left_wheel.writeMicroseconds(1000);
  }
  else{
    left_wheel.writeMicroseconds(1500);
    // left_wheel.write(90);
  }

  if(right == -1){
    rightWheel.writeMicroseconds(1000);
  }
  else if(right == 1){
    rightWheel.writeMicroseconds(2000);
  }
  else{
    rightWheel.writeMicroseconds(1500);
    // rightWh
eel.write(90);
  }
  

  
}
