/*
 * LivingBeingTemplate.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: leiterboss
 */

#include "LivingBeingTemplate.h"

LivingBeingTemplate::LivingBeingTemplate(TiXmlElement* el) {
	// TODO Auto-generated constructor stub

}

LivingBeingTemplate::~LivingBeingTemplate() {
	// TODO Auto-generated destructor stub
}

string LivingBeingTemplate::getDescription() {
	ostringstream os;

	os << "The " << this->getName() << " is " << this->getSizeDescription() << " animal, " <<
			"with an average weight of " <<	this->getPrettyWeight() << ". ";

	os << this->getBodyDescription();

	return os.str();
}

string LivingBeingTemplate::getPrettyWeight() {
	//float w = this->getStatsWeight().average;
	float w = this->getTrait(AVG_WEIGHT);
	ostringstream os;

	if (w < 1e-3) os << (w * 1e6) << " mg" ;
	else if (w < 1) os << (w * 1e3) << " g";
	else if (w < 1e3) os << w << " kg";
	else os << (w / 1e3) << " tonnes";

	return os.str();
}

string LivingBeingTemplate::getSizeDescription() {
	//float s = this->getStatsSize().average;
	float s = this->getTrait(AVG_SIZE);
	string desc;
	if (s < 1e-6) desc = "an almost microscopic";
	else if (s < 1e-3) desc = "a tiny";
	else if (s < 0.4) desc = "a small";
	else if (s < 8) desc = "a smallish";
	else if (s < 20) desc = "a medium";
	else if (s < 80) desc = "a human-sized";
	else if (s < 800) desc = "quite big";
	else if (s < 1e4) desc = "a large";
	else if (s < 1e7) desc = "an enormous";
	else desc = "an awe-inspiringly big";

	return desc;
}
