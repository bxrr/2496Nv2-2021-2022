#ifndef __AUTONS_H__
#define __AUTONS_H__

#include "main.h"
#include "aut_func.hpp"
#include "global.hpp"
#include <vector>
#include <string>

using namespace pros;
using namespace fnc;
using namespace glb;

namespace aut
{
    void half_awp()
    {
        spin_dist(500, 50);
        chain_clamp.toggle();
        spin_lift(5000);
        drive(-500);
        rotate(45);
    }

    void solo_awp()
    {
        spin_dist(500, 50);
        chain_clamp.toggle();
        spin_lift(5000);
        drive(-400, 1000);
        rotate_to(-90, 1800, 1.1);
        drive(600, 120, 1300);
        rotate_to(0, 1200);
        drive(4000, 120, 2200, 2000);
        front_clamp.toggle();
        rotate_to(30, 1000);
        toggle_2bar();
        spin_dist(-1900);
        spin_dist(375, 70); 
        toggle_2bar();
        goal_cover.toggle();
        spin_dist(40, 70);
        drive(2100);
        rotate_to(0);
        spin_dist(-2000);
    }

    void awp_elev() // start forward; half awp -> middle goal 
    {
        drive(550, 120, 1500);
        drive(-550, 120, 1500);
        rotate(-45, 1500);
        spin_dist(2200, 90);
        spin_dist(300, 60);
        chain_clamp.toggle();
        spin_dist(40, 50);
        spin_lift(5000);
        drive(-2100, 80);
        rotate(60, false);
    }

    void elev_neu()
    {
        spin_dist(1300);
        spin_dist(300, 70);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        drive(-400);
        rotate_to(-60, 1500);
        spin_dist(1120);
        spin_dist(300, 70);
        front_clamp.toggle();
        spin_dist(50, 50);
        toggle_2bar();
        drive(-2100, 70);
    }

    void back_neu() // start backward; neutral goal -> middle goal -> alliance goal
    {
        spin_lift(2500);
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1300);
        spin_dist(-250, 73);
        toggle_2bar();
        goal_cover.toggle();
        spin_dist(-50, 50);
        spin_lift(-2500);
        drive(500, 900);
        rotate_to(115, 1800);
        spin_dist(1000);
        spin_dist(400, 70);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        drive(-2000);
        rotate_to(-90);
        spin_dist(250, 60);
        front_clamp.toggle();
    }

    void back_tree() // start backward; middle goal -> neutral goal -> alliance goal
    {
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1800);
        toggle_2bar();
        spin_dist(-70, 80);
        goal_cover.toggle();
        drive(400);
        rotate_to(-102);
        spin_dist(800, 80);
        chain_clamp.toggle();
        spin_dist(40, 60);
        drive(-400);
        rotate_to(-192);
        drive(1000);
        front_clamp.toggle();
    }

    void rush_elev()
    {
        spin_dist(1400, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-700);
    }

    void rush_de_elev()
    {
        spin_dist(1600, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-800);
    }

    void rush_tree() // elev side
    {
        spin_dist(2000, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-800);
    }


    // callable list of autons
    std::vector<void (*)()>  auton_calls{ half_awp,   solo_awp,   awp_elev,   elev_neu,   back_neu,   back_tree,   rush_elev,   rush_de_elev,   rush_tree };
    std::vector<std::string> auton_names{"half_awp", "solo_awp", "awp_elev", "elev_neu", "back_neu", "back_tree", "rush_de_elev", "rush_de_elev", "rush_tree"};
}


#endif
