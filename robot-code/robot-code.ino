#include <PS2X_lib.h>

//playstation controller pinout
#define PS_DATA_PIN 2
#define PS_CMND_PIN 3
#define PS_ATT_PIN 4 //sel pin for ps2 library
#define PS_CLOCK_PIN 5

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

//ps2 controller object
PS2X controller;

//vars for seperated controller data
float joyRightX;
float joyRightY;
float joyLeftX;
float joyLeftY;

//var raw controller data
unsigned int controller_data;

void setup() {
//init controller pins
controller.config_gamepad(PS_CLOCK_PIN, PS_CMND_PIN, PS_ATT_PIN, PS_DATA_PIN, pressures, rumble);

//give controller time for wireless setup
delay(300);

//init serial
Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readController();
}


/*

*/
void readController(){
  //read gamepad to refresh library vals
  controller.read_gamepad();



  //update joystick's states
  joyLeftX = controller.Analog(PSS_LX);
  joyLeftY = controller.Analog(PSS_LY);
  joyRightX = controller.Analog(PSS_RX);
  joyRightY = controller.Analog(PSS_RY);

 //needs to not floor vals

  //map joy vals to -1 to 1
  joyLeftX = map(joyLeftX, 0, 255, -1, 1);
  joyLeftY =  map(joyLeftY, 0, 255, -1, 1);
  joyRightX =  map(joyRightX, 0, 255, -1, 1);
  joyRightY =  map(joyRightY, 0, 255, -1, 1);

  Serial.print("left x");
  Serial.println(joyLeftX);

  delay(30);
}
