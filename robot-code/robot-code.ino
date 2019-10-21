#include <PS2X_lib.h>
#include <Psx.h>


//playstation controller pinout
#define PS_DATA_PIN 2
#define PS_CMND_PIN 3
#define PS_ATT_PIN 4
#define PS_CLOCK_PIN 5
#define PS_DELAY 10

#define RIGHT_JOY_X 40 
#define RIGHT_JOY_Y 48

//ps controller object
Psx controller;

//vars for seperated controller data
byte controllerRightX;
byte controllerRightY;
int controllerLeftX;
int controllerLeftY;

//var raw controller data
unsigned int controller_data;

void setup() {
//init controller pins
controller.setupPins(PS_DATA_PIN, PS_CMND_PIN, PS_ATT_PIN,PS_CLOCK_PIN,PS_DELAY);

//init serial
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  readController();
}


/*

*/
void readController(){
  controller_data = controller.read();

  Serial.print("data1: ");
  Serial.println(controller_data, BIN);

  // controller_data = controller_data >> RIGHT_JOY_X;
  byte tempLeftY = controller_data >> 8;

  Serial.print("data2: ");
  Serial.println(controller_data, DEC);

   Serial.print("data3: ");
  Serial.println(tempLeftY, DEC);

  // controllerRightX >> 8;

  // Serial.print("data3: ");
  // Serial.println(controllerLeftX, DEC);

  delay(15);
}
