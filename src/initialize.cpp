#include "main.h"
#include "hardware.h"

pros::vision_signature blue_signature = pros::Vision::signature_from_utility(1, -3817, -3307, -3562, 12179, 13435, 12807, 8.8, 0);//BLUE
pros::vision_signature red_signature = pros::Vision::signature_from_utility(2, 8595, 8905, 8750, -717, -353, -535, 8.8, 0);//RED

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	Hardware::camera.set_signature(1, &blue_signature);
	Hardware::camera.set_signature(2, &red_signature);


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
