/*
 * LivingBeing.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#include "LivingBeing.h"

LivingBeing::LivingBeing(LivingBeingTemplate* lbt, bool random) {
	liveTemplate = lbt;
	// TODO: Behavior
	if (random) {
		this->setSize(normalDistValue(liveTemplate->getTrait(LivingBeingTemplate::AVG_SIZE),liveTemplate->getTrait(LivingBeingTemplate::STD_SIZE)));
		this->setDensity(normalDistValue(liveTemplate->getTrait(LivingBeingTemplate::AVG_DENSITY),liveTemplate->getTrait(LivingBeingTemplate::STD_DENSITY)));
		this->setWeight(normalDistValue(liveTemplate->getTrait(LivingBeingTemplate::AVG_WEIGHT),liveTemplate->getTrait(LivingBeingTemplate::STD_WEIGHT)));
	}
	else {
		this->setSize(liveTemplate->getTrait(LivingBeingTemplate::AVG_SIZE));
		this->setDensity(liveTemplate->getTrait(LivingBeingTemplate::AVG_DENSITY));
		this->setWeight(liveTemplate->getTrait(LivingBeingTemplate::AVG_WEIGHT));
	}
}

LivingBeing::~LivingBeing() {
	// TODO Auto-generated destructor stub
}
