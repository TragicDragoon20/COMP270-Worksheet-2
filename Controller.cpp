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
	 * as 1/2 * g = g / 2
	 * we can reaarange this to be
	 * u = sqrt(g * Sx / 2 * cos(x) * sin(x))
	 * using trig identities we can chenge the bottom to be sin(2x)
	 * Therefore u = sqrt(g * Sx / sin(2x)
	 */
	// const float initialVelocity = sqrt((displacement.x *  gravity) / sin(2 * shotAngleRadians));

	/**
	* Part 2
	 * taking the same t value as in part 1
	 * Sub t into Sy = ut + 1/2at^2
	 * Sy = usin(x) * Sx / ucos(x) + 1/2 * -g * (Sx/ucos(x))^2
	 * as sin/cos = tan we can use this identity in the formula
	 * Sy = tan(x) * Sx + 1/2 * -g * (Sx/ucos(x))^2
	 * minus tan(x) * Sx on both sides and times by (ucos(x))^2
	 * (Ucos(x))^2(Sy - tan(x) * Sx = 1/2 * -g * Sx^2
	 * Divide by Sy - tan(x) to get it onto the right hand side and off the left side
	 * (Ucos(x))^2 = 1/2 * -g * Sx^2 / Sy - tan(x)
	 * Do the same again but divide by (ucos(x))^2 and sqrt the end result to get u = 
	 * u = sqrt(-g * Sx^2 / 2 * cos(x)^2 * Sy - tan(x)
	 */
	//const float initialVelocity = sqrt((-gravity * pow(displacement.x, 2)) / (2 * pow(cos(shotAngleRadians), 2) * (-displacement.y - tan(shotAngleRadians) * displacement.x)));

	/**
	 * Part 3
	 * Use similtanious equatiosns and times the Sx eqation by gravity and the Sy equation by wind
	 * add them together other to get Sx*gravity + Sy*wind = gravity * u * cos(x) * t + wind * u * sin(x) * t
	 * Rearrange for t = gravity * Sx + wind * Sy / u * (gravity * cos(x) + wind * sin(x))
	 * Use lets say a = gravity * Sx + wind * Sy / gravity * cos(x) + wind * sin(x)
	 * Therfore t = a / u
	 * Plug this back into the Sy Equation
	 * Sy = u * a *sin(x) / u - gravity * a^2 / 2 * u^2
	 * rearrange to get u^2 = gravity * a^2 / 2(a * sin(x) - Sy)
	 * then square root the formula to get u
	 */
	const float alpha = (gravity * displacement.x + wind * -displacement.y) / (gravity * cos(shotAngleRadians) + wind * sin(shotAngleRadians));
	
	const float initialVelocity = sqrt((gravity * pow(alpha, 2)) / (2 * (alpha * sin(shotAngleRadians) - -displacement.y)));
	
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

	/**
	 * Task 4 - no wind 
	 * using the equation from task 2 Sy = Sx * sin(x) / cos(x) - gravity * Sx^2 / 2 * u^2 * cos^2(x)
	 * with trig idenities we can get Sy = Sx * tan(x) - gravity * Sx^2 * sec^2(x) / 2 * u^2
	 * with another identity we can then get Sy = x * tan(x) - gravity * Sx^2 * (1 + tan^2(x)) / 2 * u^2
	 * we can then rearrange this to equal 0
	 * we then get (gravity * Sx^2 / 2 * u^2) * tan^2(x) - Sx * tan(x) + (gravity * Sx^2 / 2 * u^2) + y = 0
	 * we can then use this equation with a quadratic formula
	 * where:
	 * a = gravity * Sx^2 / 2 * u^2
	 * b = Sx
	 * c = gravity * Sx^2 / 2 * u^2 + Sy
	 */
	const Vector2 displacement = enemyPos - tankPos;

	float a = (gravity * pow(displacement.x, 2)) / (2 * pow(shotSpeed, 2));
	float b = displacement.x;
	float c = (gravity * pow(displacement.x, 2)) / (2 * pow(shotSpeed, 2)) + -displacement.y;

	// Both of these appear to hit the target threw testing with angleCheck1 Having an actual arc to the shot
	const float angleCheck1 = atan((b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
	const float angleCheck2 = atan((b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
	
	return angleCheck1;
}

