
/** @file opcontrol.c

 * @brief File for operator control code

 *

 * This file should contain the user operatorControl() function and any functions related to it.

 *

 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be

 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.

 */



#include "main.h"

#include "portDef.h"



/*

 * Runs the user operator control code. This function will be started in its own task with the

 * default priority and stack size whenever the robot is enabled via the Field Management System

 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or

 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling

 * the robot will restart the task, not resume it from where it left off.

 *

 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will

 * run the operator control task. Be warned that this will also occur if the VEX Cortex is

 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.

 *

 * Code running in this task can take almost any action, as the VEX Joystick is available and

 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly

 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.

 *

 * This task should never exit; it should end with some kind of infinite loop, even if empty.

 */



void liftMove(int speed) {

   motorSet(LIFT_LEFT, -speed);

   motorSet(LIFT_RIGHT, speed);  // left and right need to go opposite directions



}

void clawMove(int speed) {

  motorSet(CLAW, speed);

}



void operatorControl() {

 int left;

 int right;

 while (1) {

			right = joystickGetAnalog(1, 2); // vertical axis on right joystick

			left  = joystickGetAnalog(1, 3); // vertical axis on left joystick



			motorSet(MOTOR_F_LEFT, left); // set right wheels

			motorSet(MOTOR_B_LEFT, left); // set right wheels

			motorSet(MOTOR_F_RIGHT, -right); // set right wheels

			motorSet(MOTOR_B_RIGHT, -right); // set right wheels


      if(joystickGetDigital(1, 7, JOY_RIGHT)) {

        clawMove(50);

      } else if(joystickGetDigital(1, 7, JOY_LEFT)) {

        clawMove(-50);

      }



      // Move the lift up and down using button 6 Up/Down

      if(joystickGetDigital(1, 6, JOY_UP)) {

        liftMove(75); // pressing up, so lift should go up

      }

      else if(joystickGetDigital(1, 6, JOY_DOWN)) {

        liftMove(-75); // pressing down, so lift should go down

      }

      else {

       liftMove(0); // no buttons are pressed, stop the lift

      }



			delay(20);
   }
 }
