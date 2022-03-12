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
    void solo_awp()
    {
        spin_dist(500, 50);
        chain_clamp.toggle();
        spin_lift(5000);
        drive(-390, 124.5, 1400);
        rotate_to(-90, 1500, 1.1);
        drive(500, 120, 1400);
        rotate_to(-1.5, 1800, 1.05);
        drive(3650, 124.5, 3200, 2000);
        front_clamp.toggle();
        toggle_2bar();
        rotate_to(35, 1800, 1.2);
        spin_dist(-1700);
        toggle_2bar();
        goal_cover.toggle();
        spin_dist(-140);
        rotate_to(40, 1000, 1.4);
        spin_dist(1600);
        front_clamp.toggle();
    }

    void awp_elev() // start forward; half awp -> middle goal TODO
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

    void back_neu() // start backward; neutral goal -> middle goal -> alliance goal
    {
        spin_lift(2500);
        spin_dist(-580, 124.5, 2000);
        toggle_2bar();
        spin_dist(-860, 124.5, 2500);
        goal_cover.toggle();
        spin_lift(-2000);
        spin_dist(-120, 124.5, 500);
        toggle_2bar();
        rotate_to(87, 1500);
        spin_dist(300, 90);
        spin_dist(500, 70);
        mtr::stop(mtr::chas);
        spin_lift(-700);
        delay(400);
        spin_dist(150, 70);
        chain_clamp.toggle();
        drive(0, 0, 0);
        delay(300);
        spin_lift(4300);
        delay(400);
        rotate_to(130, 1500, 1.3);
        drive(-1700, 100, 2200);
        rotate_to(280, 1500);
        drive(800, 120, 1500);
    }

    void rush_tree() // start backward; middle goal -> neutral goal -> alliance goal
    {
        spin_dist(2200);
        chain_clamp.toggle();
        spin_lift(5000);
        rotate_to(-50, 1500);
        toggle_2bar();
        spin_dist(-1000);
        goal_cover.toggle();
        spin_dist(-150, 125, 150);
        toggle_2bar();
        rotate_to(-125, 1500, 1.3);
        drive(1200, 3000);
        rotate_to(117, 2000, 1.2);
        drive(900);


        /*
        spin_lift(2500);
        spin_dist(-520, 120, 2000);
        toggle_2bar();
        spin_dist(-1300, 120, 2500);
        goal_cover.toggle();
        spin_lift(-2000);
        spin_dist(-150, 124.5, 500);
        mtr::stop(mtr::chas);
        toggle_2bar();
        spin_dist(-30, 70);
        rotate_to(-61.6, 1500);
        spin_dist(500, 100);
        spin_dist(740, 70);
        mtr::stop(mtr::chas);
        spin_lift(-700);
        spin_dist(-30, 30);
        mtr::stop(mtr::chas);
        spin_dist(250, 60);
        chain_clamp.toggle();
        drive(0, 0, 0);
        delay(300);
        spin_lift(4300);
        delay(400);
        rotate_to(225, 1500, 1.2);
        drive(-1200, 100, 2200);
        rotate_to(-73.6, 1500, 1.2);
        drive(750, 120, 1500);
        */
    }

    void elev_neu()
    {
        spin_dist(1440);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        rotate_to(90, 1100);
        toggle_2bar();
        spin_dist(-800);
        goal_cover.toggle();
        spin_dist(-100, 100, 300);
        toggle_2bar();
        rotate_to(135, 1500);
        drive(1700, 3000);
        rotate_to(87, 1500, 1.2);
        drive(800, 125, 2000);
    }

    void rush_elev()
    {
        spin_dist(1430);
        chain_clamp.toggle();
        spin_dist(50, 50);
        spin_lift(5000);
        drive(-1400);
    }

    void rush_de_elev()
    {
        spin_lift(2500);
        spin_dist(-800, 124.5, 2000);
        toggle_2bar();
        spin_dist(-1400, 124.5, 2500);
        toggle_2bar();
        goal_cover.toggle();
        drive(60, 100, 100);
        rotate_to(40, 1300);
        drive(400, 120, 1500);
        rotate_to(-17, 1000);
        drive(2100, 100, 4000);
        rotate_to(-108, 1500);
        drive(400, 120, 1500);
        front_clamp.toggle();
        delay(300);
        drive(-200, 100, 500);
        front_clamp.toggle();
        delay(100);
        drive(-100);

    }

    void back_tree() // elev side
    {
        spin_dist(2000, 127, 2000);
        spin_dist(100, 80, 200);
        chain_clamp.toggle();
        spin_dist(40, 127, 100);
        spin_lift(5000);
        spin_dist(-800);
    }


    // callable list of autons
    std::vector<void (*)()>  auton_calls{ solo_awp,   awp_elev,   elev_neu,   rush_tree,   back_neu,   rush_elev,   rush_de_elev,   back_tree };
    std::vector<std::string> auton_names{"solo_awp", "awp_elev", "elev_neu", "rush_tree", "back_neu", "rush_elev", "rush_de_elev", "back_tree"};
}


#endif
