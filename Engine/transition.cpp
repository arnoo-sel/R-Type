#include "transition.hpp"

namespace Transition
{
	QMap<QString, trans> transFunct;
}

void Transition::initTransition()
{
	transFunct["linear_up"] = &Transition::linear_up;
	transFunct["linear_down"] = &Transition::linear_down;
	transFunct["square_up"] = &Transition::square_up;
	transFunct["squareroot_up"] = &Transition::squareRoot_up;
	transFunct["sinus_up"] = &Transition::sinus_up;
	transFunct["sinus_down"] = &Transition::sinus_down;

}

float Transition::linear_up(float x)
{
	return x;
}

float Transition::linear_down(float x)
{
	return 1 - x;
}

float Transition::square_up(float x)
{
	return x * x;
}

float Transition::squareRoot_up(float x)
{
	return sqrt(x);
}

float Transition::sinus_up(float x)
{
	return (1. - cos(x * 3.14159)) / 2.;
}

float Transition::sinus_down(float x)
{
	return (1. + cos(x * 3.14159)) / 2.;
}
