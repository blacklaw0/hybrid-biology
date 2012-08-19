/*
 * AnimalBodySection.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef ANIMALBODYSECTION_H_
#define ANIMALBODYSECTION_H_

#include "../utils/common.h"
#include "../BodySection.h"
#include "AnimalBodyPart.h"

class AnimalBodySection : public AnimalBodyPart {
private:

public:
	AnimalBodySection(TiXmlNode*);
	virtual ~AnimalBodySection();

	void dumpBodyParts();
	vector<Skill::RatedSkill> getAllSkills();

};

#endif /* ANIMALBODYSECTION_H_ */
