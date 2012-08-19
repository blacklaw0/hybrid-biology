/*
 * LivingBeing.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef LIVINGBEING_H_
#define LIVINGBEING_H_

#include "utils/common.h"
#include "BodySection.h"
#include "LivingBeingTemplate.h"
#include "Behavior.h"
#include <cmath>
using namespace std;


class LivingBeing {
private:
	float size;
	float weight;
	float density;
	float length; // cube root of size
	LivingBeingTemplate* liveTemplate;

	Behavior behavior;

public:
	LivingBeing(LivingBeingTemplate* lbt, bool random=true);
	virtual ~LivingBeing();
	string getName() {return this->liveTemplate->getName();};
	LivingBeingTemplate* getTemplate() {return this->liveTemplate;}
	float getSize() {return this->size;};
	float getWeight() {return this->weight;};
	float getDensity() {return this->density;};
	float getLength() {return this->length;};
	void setSize(float s) {this->size = s; this->length = cbrt(s);}
	void setWeight(float w) {this->weight = w;}
	void setDensity(float d) {this->density = d;};
	bool hasTag(int t) {return this->liveTemplate->hasTag(t);}
	void setBehavior(Behavior b) {this->behavior = b;}
	Behavior getBehavior() {return this->behavior;}

};
#endif /* LIVINGBEING_H_ */
