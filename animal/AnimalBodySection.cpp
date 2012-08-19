/*
 * AnimalBodySection.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#include "AnimalBodySection.h"

AnimalBodySection::AnimalBodySection(TiXmlNode *n) : AnimalBodyPart(n) {
/*	this->setName(n->Value());
	for(TiXmlNode *n2 = n->FirstChild(); n2 != 0; n2 = n2->NextSibling()) {
		AnimalBodyPart part = AnimalBodyPart(n2);
		this->addPart(part);
	}*/
}

AnimalBodySection::~AnimalBodySection() {
	// TODO Auto-generated destructor stub
}

void AnimalBodySection::dumpBodyParts() {
/*	cout << "\t\t" << this->getName() << endl;
	vector<AnimalBodyPart> *bp = this->getBodyParts();
	for(unsigned int i = 0; i < bp->size(); i++)
		bp->at(i).dumpPartInfo(3);
		*/
	this->dumpPartInfo(2);
}

vector<Skill::RatedSkill> AnimalBodySection::getAllSkills() {
	vector<Skill::RatedSkill> vs;
	vector<AnimalBodyPart> *v = this->getBodyParts();
	for (vector<AnimalBodyPart>::iterator it = v->begin(); it != v->end(); ++it) {
		vector<Skill::RatedSkill> aux = it->getAllSkills();
		vs.insert(vs.end(),aux.begin(),aux.end());
	}
	return vs;
}
