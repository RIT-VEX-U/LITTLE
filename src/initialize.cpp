#include "main.h"
#include "hardware.h"

<<<<<<< HEAD
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

pros::vision_signature blue_signature = pros::Vision::signature_from_utility(1, -4143, -2977, -3560, 11037, 12053, 11546, 10, 0);//BLUE
pros::vision_signature red_signature = pros::Vision::signature_from_utility(2, 5761, 6235, 5998, -625, 1, -312, 9.9, 0);//RED
=======
pros::vision_signature blue_signature = pros::Vision::signature_from_utility(1, -3817, -3307, -3562, 12179, 13435, 12807, 8.8, 0);//BLUE
pros::vision_signature red_signature = pros::Vision::signature_from_utility(2, 8595, 8905, 8750, -717, -353, -535, 8.8, 0);//RED
>>>>>>> 5c7af6d767123247c7f3433c37b03f1109379369

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
