#include "main.h"
#include "globals.h"

using namespace pros;
using namespace globj;

class Chassis
{

public:
  void spinLeft(double speed) // value range from -127 to 127
  {
    left_front.move(speed);
    left_mid_front.move(speed);
    left_mid_back.move(speed);
    left_back.move(speed);
  }
  
  void spinRight(double speed)
  {
    left_front.move(speed);
    left_mid_front.move(speed);
    left_mid_back.move(speed);
    left_back.move(speed);
  }
};