#ifndef __AUTONS_H__
#define __AUTONS_H__

#include "main.h"
#include "global.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace pid;


namespace aut
{
    void elev()
    {
        drive(100);
    }

    void de_elev()
    {
        drive(200);
    }

    void win_point()
    {
        drive(400);
    }

    void rush()
    {
        drive(600);
    }

    void skills()
    {
        drive(1000);
    }

    std::vector<void (*)()> auton_list{elev, de_elev, win_point, rush, skills};
    std::vector<std::string> auton_names{"elev", "de_elev", "win_point", "rush", "skills"};
}


#endif