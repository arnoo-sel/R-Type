#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <QMap>
#include <QString>
#include <math.h>

#define LINEAR_UP Transition::linear_up
#define LINEAR_DOWN Transition::linear_down
#define SQUARE_UP Transition::square_up
#define SQRT_UP Transition::squareRoot_up
#define SINUS_UP Transition::sinus_up
#define SINUS_DOWN Transition::sinus_down

/// Utilitaires permettant des transitions fluides entre deux valeurs
/** Chaque fonction prends en parametre l'avancement de la transition (entre 0 et 1).\n
  * Elles renvoient une valeur entre 0 et 1.
  **/

namespace Transition
{
	typedef float (*trans)(float);

	extern QMap<QString, trans> transFunct;

	/// Initialise le tableau transFunct
	void initTransition();
	/// Retourne x
	float linear_up(float x);
	/// Retourne 1 - x
	float linear_down(float x);
	/// Retourne x * x
	float square_up(float x);
	/// Retourne sqrt(x)
	float squareRoot_up(float x);
	/// Retourne (1. - cos(x * 3.14159)) / 2.
	float sinus_up(float x);
	/// Retourne (1. + cos(x * 3.14159)) / 2.
	float sinus_down(float x);
}

#endif // TRANSITION_HPP
