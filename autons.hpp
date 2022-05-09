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
    void test()
    {
        deploy_two_bar();
    }

    void solo_awp()
    {
        drive(300, 100, 1200);
        chain_clamp.toggle();
        drive(0, 0, 0);
        delay(300);
        spin_lift(-4500);
        drive(-220, 120, 1200);
        delay(400);
        rotate_to(90, 1500, 1.15);
        drive(-690, 120, 3000);
        rotate_to(0, 2000, 1.15);
        drive(3530, 95, 4000);
        front_clamp.toggle();
        rotate_to(-5, 1000, 2.5);
        drive(-2000, 90, 3000);
        front_clamp.toggle();
        rotate_to(90);
        spin_lift(2500);
        deploy_goal_cover();
    }

    void slow_awp()
    {
        drive(300, 100, 1200);
        chain_clamp.toggle();
        drive(0, 0, 0);
        delay(300);
        spin_lift(-4500);
        drive(-220, 120, 1200);
        delay(400);
        rotate_to(90, 1500, 1.15);
        drive(-690, 120, 3000);
        rotate_to(0, 2000, 1.15);
        delay(3000);
        drive(3530, 95, 4000);
        front_clamp.toggle();
        rotate_to(-5, 1000, 2.5);
        drive(-1200, 100, 3000);
        front_clamp.toggle();
    }

    void half_awp()
    {
        drive(300, 100, 1200);
        chain_clamp.toggle();
        delay(300);
        spin_lift(-4500);
        drive(-220, 120, 1200);
    }

    void half_tree()
    {
        deploy_goal_cover();
        deploy_two_bar();
        drive(900, 65, 2500);
        spin_dist(70, 40);
        chain_clamp.toggle();
        delay(300);
        drive(-500, 80, 1200);
        spin_lift(-200);
        delay(300);
        rotate_to(87, 2000, 1.3, 0.1);
        chain_clamp.toggle();
        drive(-300, 120, 900);
        spin_lift(-2000);
        deploy_goal_cover();
        delay(700);
        toggle_2bar();
        spin_dist(-400, 120);
        drive(-1600);
        spin_lift(2200);
        delay(3000);
    }

    void elev_neu()
    {
        spin_dist(1400);
        spin_dist(100, 90);
        chain_clamp.toggle();
        spin_lift(-4500);
        drive(-600, 120, 1000, 1.3);
        toggle_2bar();
        rotate_to(123.5, 2500, 1.3);
        spin_dist(-1250);
        drive(-100, 120, 1000);
        toggle_2bar();
        delay(500);
        drive(2600, 120, 3500);
        front_clamp.toggle();
    }// hello how are you BRANDON it is good to see you should play BTD6 woith me <3

    void elev_tree()
    {
        spin_dist(1665);
        chain_clamp.toggle();
        spin_lift(0);
        spin_dist(60);
        spin_lift(-4500);
        spin_dist(80);
        drive(-450, 120, 1800);
        rotate_to(69, 2200, 1.2);
        spin_dist(750);
        spin_dist(100, 90);
        front_clamp.toggle();
        spin_dist(120, 90);
        drive(-780, 120, 1500);
        toggle_2bar();
        rotate_to(-38, 3000, 1.4);
        drive(-1250);
    }

    void deelev_neu()
    {
        spin_dist(1500);
        spin_dist(100, 90);
        chain_clamp.toggle();
        spin_lift(-4800);
        drive(-750, 120, 1500);
        rotate_to(43, 1500, 1.3);
        spin_dist(1300);
        spin_dist(290, 90);
        front_clamp.toggle();
        spin_dist(40, 90);
        drive(-2000, 120, 3000);
        rotate_to(0, 2000, 1.3);
        drive(-900, 120, 2000);
        rotate_to(-90, 2000, 1.3);
        delay(500);
        toggle_2bar();
        drive(-600);
    }

    void deelev_tree()
    {
        spin_dist(2260);
        chain_clamp.toggle();
        spin_lift(-4500);
        drive(-800);
        rotate_to(-90);
    }
    
    void b_deelev_neu()
    {
        deploy_two_bar();
        deploy_goal_cover();
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1200);
        goal_cover.toggle();
        spin_dist(-150);
        toggle_2bar();
        drive(-425, 90, 1500, 2.0, 1500);
        drive(1400, 120, 2000);
        // rotate_to(-135, 2000);
        // spin_dist(800);
        // spin_dist(500, 70);
        // chain_clamp.toggle();
        // spin_lift(-2300);
        // drive(0,0,0,0,0);
        // delay(400);
        // drive(-1300);
        // rotate_to(180);
    }

    void b_elev_tree()
    {
        deploy_two_bar();
        deploy_goal_cover();
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1650);
        goal_cover.toggle();
        toggle_2bar();
        drive(-650, 100, 1500, 2.0, 1500);
        drive(775, 120, 1500);
        rotate_to(90, 2000);
        drive(950, 120, 1500);
        chain_clamp.toggle();
        spin_lift(0);
        delay(50);
        spin_dist(65, 60);
        spin_lift(-2700);
        delay(300);
        rotate_to(0, 1500);
        ideal_degree = 0;
        drive(1600);
    }

    void b_elev_neu()
    {
        deploy_two_bar();
        deploy_goal_cover();
        spin_dist(-200);
        toggle_2bar();
        spin_dist(-1300);
        goal_cover.toggle();
        spin_dist(-150);
        toggle_2bar();
        drive(-275, 100, 1500, 2.0, 1500);
        drive(775, 120, 1500);
        rotate_to(124, 2000);
        spin_dist(1000);
        spin_dist(300, 70);
        chain_clamp.toggle();
        spin_lift(-2300);
        drive(-1500);
    }

    void tip_elev()
    {
        deploy_two_bar();
        deploy_goal_cover();
        spin_dist(-1600);
        drive(200);
        deploy_two_bar();
        drive(-400);
        toggle_2bar();
        delay(500);
        drive(775);
        rotate_to(120);
        drive(1000);
        chain_clamp.toggle();
    }

    void tip_de_elev()
    {
        deploy_two_bar();
        deploy_goal_cover();
        spin_dist(-1600);
        drive(200);
        deploy_two_bar();
        drive(-450);
        toggle_2bar();
        delay(500);
        drive(775);
        rotate_to(-130);
        drive(1000);
        chain_clamp.toggle();
    }

    // callable list of autons
    std::vector<void (*)()>  auton_calls{ test,   solo_awp,   slow_awp,   half_awp,   half_tree,   elev_neu,   elev_tree,   deelev_neu,   deelev_tree,   b_deelev_neu,   b_elev_tree,   tip_elev,   tip_de_elev};
    std::vector<std::string> auton_names{"test", "solo_awp", "slow_awp", "half_awp", "half_tree", "elev_neu", "elev_tree", "deelev_neu", "deelev_tree", "b_deelev_neu", "b_elev_tree", "tip_elev", "tip_de_elev"};
}


#endif
