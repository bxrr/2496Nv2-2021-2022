#ifndef __AUTONS_H__
#define __AUTONS_H__

#include "main.h"
#include "pid.hpp"
#include "global.hpp"
#include <vector>
#include <string>

using namespace pid;
using namespace glb;


namespace aut
{
    void driver()
    {
        init_twobar();
    }

    void elev()
    {
        drive(1000);
    }

    void de_elev()
    {
        drive(-1000);
    }

    void neu_tree()
    {
        rotate(90);
        rotate(-90);
        rotate_to(180);
    }

    void win_point()
    {
        drive(4000);
    }

    void rush()
    {
        drive(300);
    }

    void skills()
    {
        rotate(45);
    }

    // callable list of autons
    std::vector<void (*)()> auton_list{driver, elev, de_elev, neu_tree, win_point, rush, skills};
    std::vector<std::string> auton_names{"driver", "elev", "de_elev", "neu_tree", "win_point", "rush", "skills"};
}


#endif
