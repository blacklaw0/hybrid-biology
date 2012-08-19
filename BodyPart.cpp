/*
 * BodyPart.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#include "BodyPart.h"
/*
BodyPart::BodyPart() {
	// TODO Auto-generated constructor stub

}*/

BodyPart::~BodyPart() {
	// TODO Auto-generated destructor stub
}

void BodyPart::setNames(string names) {
	stringstream ss(names);
	string s, sold;

	getline(ss, s, ','); // s <- noun singular
	this->setName(s); sold = s;
	getline(ss, s, ','); // s <- noun plural
	if (s.compare(sold) != 0) {
		this->setNamePlural(s); sold = s;
		getline(ss, s, ','); // s <- definite article (i.e. "an")
		if (s.compare(sold) != 0)
			this->setArticle(s);
		else this->setArticle("a");
	}
	else {
		this->setNamePlural(s + "s");
		this->setArticle((isVowel(this->getName()[0])?"an":"a"));
	}
}

string BodyPart::getDescription() {
	ostringstream os;
	bool multipleNum = (this->getNumber() > 1);
	bool hasSkills = (this->getSkills()->size() > 0);


	if (!multipleNum) {
		os << "The " << this->getName() << " is made of " << this->getMaterial().getColor() <<
				" " << this->getMaterial().getName();
	}
	else { //TODO: Fix plurals
		os << "The " << this->getNamePlural() << " are made of " << this->getMaterial().getColor() <<
				" " << this->getMaterial().getName();
	}

	if (!hasSkills && this->parts.size() == 0) os << ". ";
	else os << ", ";

	if (hasSkills) {
		if (!multipleNum) os << "and it grants ";
		if (hasSkills && multipleNum) os << "and they grant ";

		vector<Skill::RatedSkill>* rs = this->getSkills();
		if (rs->size() )
		for(unsigned int i = 0; i < rs->size(); i++) {
			string adj = Skill::getRatingAdjective(rs->at(i).rating, Skill::isMovementSkill(rs->at(i).skill->getID()));
			string sep = (adj.length() > 0?" ":"");
			os << adj << sep << rs->at(i).skill->getActionName();
			if (i + 2 < rs->size()) os << ", ";
			if (i + 2 == rs->size()) os << " and ";
		}
		os << ". ";
	}


	if (this->parts.size() > 0) {
		if (hasSkills) os << ((this->getNumber()==1)?"The ":"Each ") << this->getName() << " has ";
		else os << "and " << ((this->getNumber()==1)?"it ":"each ") << "has ";
		for(unsigned int i = 0; i < this->parts.size(); i++) {
			if (this->parts.at(i)->getNumber() > 1) {
				os << this->parts.at(i)->getNumber() << " " << this->parts.at(i)->getNamePlural();
			}
			else {
				os << this->parts.at(i)->getArticle() << " " << this->parts.at(i)->getName();
			}
			if (i + 2 < this->parts.size()) os << ", ";
			if (i + 2 == this->parts.size()) os << " and ";
		}
		os << ". ";
		for(unsigned int i = 0; i < this->parts.size(); i++) {
			os << this->parts.at(i)->getDescription();
		}
	}

	return os.str();
}

/*
string name;
vector<Skill::RatedSkill> skills;
struct Material material;
unsigned short num;*/
