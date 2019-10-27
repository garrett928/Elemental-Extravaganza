#ifdef EASYPS2X
#define EASYPS2X

#include "Arduino.h"
#include <PS2X_lib.h>

class EasyPS2X : PS2X{

public:
    float rightX;
    float rightY;
    float leftX;
    float leftY;

    void updateJoySticks();
    void refresh();
};


#endif