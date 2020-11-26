#include "stdafx.h"
#include "Controller.h"

// Calculate the shot speed to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotAngleRadians: the angle of the shot, in radians from horizontal (positive angles are upwards)
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotSpeed(const Vector2& tankPos, const Vector2& enemyPos, float shotAngleRadians, float gravity, float wind)
{
	// TODO: calculate the required shot speed (in pixels per second) and return it

	const Vector2 displacement = enemyPos - tankPos;
	const float alpha = ((displacement.x * -gravity) + ((-displacement.y) * wind));
	/**
	 * Part 1:
	 * Solve Sx = ut ++ 1/2at^2 with a = 0
	 * Sx = ut
	 * rearrange for t = Sx/Ucos(x)
	 * Sub the rearrange t value into Sy = ut + 1/2at^2 
	 * Sy = usin(x) * Sx/ucos(x) + 1/2 * -g * (Sx/ucos(x))^2
	 * as Sy = 0 can reaarange for 1/2 * g * (Sx/ucos(x))^2 = usin(x) * Sx/ucos(x)
	 * Divide t for each side
	 * 1/2 * g * Sx/ucos(x) = usin(x)
	 * times by u to get rid off u on the left and get u^2 on the right hand side also divide by sin(x) to get just u^2 on the right hand side
	 * Then sqrt the result to get u =
	 * u = sqrt(1/2 * g * Sx / cos(x) * sin(x))
	 */
	// Part 1 formula
	//const float initialVelocity = sqrt((displacement.x * (0.5 * gravity)) / (cos(shotAngleRadians) * sin(shotAngleRadians)));

	/**
	* Part 2
	 * taking the same t value as in part 1
	 * Sub t into Sy = ut + 1/2at^2
	 * Sy = usin(x) * Sx/ucos(x) + 1/2 * -g * (Sx/ucos(x))^2
	 * as sin/cos = tan we can use this identity in the formula
	 * Sy = tan(x) * Sx + 1/2 * -g * (Sx/ucos(x))^2
	 * minus tan(x) * Sx on both sides and times by (ucos(x))^2
	 * (Ucos(x))^2(Sy - tan(x) * Sx = 1/2 * -g * Sx^2
	 * Divide by Sy - tan(x) to get it onto the right hand side and off the left side
	 * (Ucos(x))^2 = 1/2 * -g * Sx^2 / Sy - tan(x)
	 * Do the same again but divide by (ucos(x))^2 and sqrt the end result to get u = 
	 * u = sqrt(-g * Sx^2 / 2 * cos(x)^2 * Sy - tan(x)
	 */
	// Part 2 formula 
	const float initialVelocity = sqrt((-gravity * pow(displacement.x, 2)) / (2 * pow(cos(shotAngleRadians), 2) * (-displacement.y - tan(shotAngleRadians) * displacement.x)));

	/**
	 * Part 3
	 * Use similtanious equatiosns and time Sx by gravity and Sy by w
	 * + one away from the other to get Sx*gravity + Sy*wind / ucosx*gravity + usinx*wind = t
	 */

	//const float initialVelocity = sqrt((-gravity * (pow(displacement.y, 2) * pow(wind, 2) + pow(displacement.x, 2) * pow(gravity, 2) + 2 * displacement.x * -displacement.y * gravity * wind)) / (2 * (wind * sin(shotAngleRadians) + gravity * cos(shotAngleRadians)) * -displacement.y * (wind * sin(shotAngleRadians) + gravity * cos(shotAngleRadians)) - sin(shotAngleRadians) * (-displacement.y * wind + displacement.x * -gravity)));

 	return initialVelocity;
	
}

// Calculate the shot angle to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotSpeed: the speed of the shot, in pixels per second
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotAngle(const Vector2& tankPos, const Vector2& enemyPos, float shotSpeed, float gravity, float wind)
{
	// TODO: calculate the required shot angle (in radians) and return it
	return M_PI * 0.25f;
}

