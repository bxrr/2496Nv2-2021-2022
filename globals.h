#include "main.h"
#include "ports.h"

namespace globj
{    
    // misc
    pros::Imu imu(P_IMU);
    pros::Controller con(pros::E_CONTROLLER_MASTER);

    // chassis
    pros::Motor left_front(P_LEFT_FRONT, pros::E_MOTOR_GEARSET_6, false);
    pros::Motor left_mid_front(P_LEFT_MID_FRONT, pros::E_MOTOR_GEARSET_6, false);
    pros::Motor left_mid_back(P_LEFT_MID_FRONT, pros::E_MOTOR_GEARSET_6, false);
    pros::Motor left_back(P_LEFT_BACK, pros::E_MOTOR_GEARSET_6, false);

    pros::Motor right_front(P_RIGHT_FRONT, pros::E_MOTOR_GEARSET_6, false);
    pros::Motor right_mid_front(P_RIGHT_MID_FRONT, pros::E_MOTOR_GEARSET_6, false);
    pros::Motor right_mid_back(P_RIGHT_MID_FRONT, pros::E_MOTOR_GEARSET_6, false);
    pros::Motor right_back(P_RIGHT_BACK, pros::E_MOTOR_GEARSET_6, false);
}