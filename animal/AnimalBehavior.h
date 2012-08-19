/*
 * AnimalBehavior.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef ANIMALBEHAVIOR_H_
#define ANIMALBEHAVIOR_H_

#include "../Behavior.h"

class AnimalBehavior : public Behavior {
private:
	float aggression;
	float stealth; 		// Stealth use
	float intelligence;

public:
	AnimalBehavior();
	virtual ~AnimalBehavior();

	float getAggression() {return this->aggression;}
	float getStealth() {return this->stealth;}
	float getIntelligence() {return this->intelligence;}
	void setAggression(float a) {this->aggression = a;}
	void setStealth(float s) {this->stealth = s;}
	void setIntelligence(float i) {this->intelligence = i;}
};

#endif /* ANIMALBEHAVIOR_H_ */
