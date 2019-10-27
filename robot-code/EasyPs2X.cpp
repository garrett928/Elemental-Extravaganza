
#include "EasyPS2X.h"
#include "Arduino.h"

EASYPS2X :: updateJoySticks(){
        //update joystick's states
        leftX = Analog(PSS_LX);
        leftY = Analog(PSS_LY);
        rightX = Analog(PSS_RX);
        rightY = Analog(PSS_RY);

      //apply deadband to positions
      if(abs(leftX - JOY_MID) < 25)
        leftX = JOY_MID;
      if(abs(leftY - JOY_MID) < 25)
  leftY = JOY_MID;
      if(abs(rightX - JOY_MID) < 25)
        rightX = JOY_MID;
      if(abs(rightY - JOY_MID) < 25)
        rightY = JOY_MID;

  //NEEDS TO NOT FLOOR VALUES

  //map joy vals to -1 to 1
  leftX = map(leftX, 0, 255, -1, 1);
  leftY =  map(leftY, 0, 255, -1, 1);
  rightX =  map(rightX, 0, 255, -1, 1);
  rightY =  map(rightY, 0, 255, -1, 1);

  } 

    //   //refresh the gamepad and update joystick and button vals
    // //hide extra work from rest of code
    // void refresh(){
    //   //update gamepad values from PS2X
    //   read_gamepad();

    //   updateJoySticks();
      
    // }
}
