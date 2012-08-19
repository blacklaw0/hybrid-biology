/*
 * AnimalBodyPart.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef ANIMALBODYPART_H_
#define ANIMALBODYPART_H_

#include "../BodyPart.h"
#include "../Skill.h"
#include "../utils/common.h"
#include <sstream>

enum Attribute { STRENGTH, AGILITY, ENDURANCE, STAMINA, SPEED, NUMBER_OF_ATTRS };
struct Modifier { enum Attribute attr; unsigned short mod; };

class AnimalBodyPart : public BodyPart {
private:
	vector<Modifier> mods;
	// name
	// RatedSkills
	// Material

	void dumpSkills(int);
	void dumpMods(int);
	static string attrName[NUMBER_OF_ATTRS];
	static Attribute getAttribute(string);

public:
	AnimalBodyPart(TiXmlNode*);
	virtual ~AnimalBodyPart();
	void dumpPartInfo(int);
	bool addPart(AnimalBodyPart* abp) {this->parts.push_back(abp); return true;}
	vector<Skill::RatedSkill> getAllSkills();
	vector<AnimalBodyPart>* getBodyParts() {return (vector<AnimalBodyPart>*) &this->parts;}

};

#endif /* ANIMALBODYPART_H_ */
