/*
 * AnimalBodyPart.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#include "AnimalBodyPart.h"

AnimalBodyPart::AnimalBodyPart(TiXmlNode* n) {
	//this->setName(n->ToElement()->Value());
	string tagName = n->ToElement()->Value();
	bool nameSet = false;

	this->setNumber(1);
	for(TiXmlAttribute *at = n->ToElement()->FirstAttribute(); at != 0; at = at->Next()) {
		string tag = at->Name();
		if (tag.compare(XML_NAME) == 0) {
			this->setNames(at->Value()); nameSet = true;
		}
		else if (tag.compare(XML_NUMBER) == 0) {
			this->setNumber(atoi(at->Value()));
		}
		else if (tag.compare(XML_SKILLS) == 0) {
			string a = at->Value();
			stringstream ss(a);
			string s;

			while (getline(ss, s, ',')) {
				stringstream ss2(s);
				string s2;
				float r;
				getline(ss2, s2, ':');
				Skill *sk = Skill::getSkill(s2);
				getline(ss2, s2, ':');
				r = atof(s2.c_str());	// Default skill is 0 (if no value specified)
				this->addSkill(sk,r);
			}
		}
		else if (tag.compare(XML_MODIFIERS) == 0) {
			string a = at->Value();
			stringstream ss(a);
			string s;

			while (getline(ss, s, ',')) {
				stringstream ss2(s);
				string s2;

				getline(ss2, s2, ':');
				Attribute at = getAttribute(s2);
				getline(ss2, s2, ':');
				struct Modifier mo = {at, atoi(s2.c_str())};
				this->mods.push_back(mo);
			}
		}
	}
	if (!nameSet) this->setNames(tagName);
	for(TiXmlNode *n2 = n->FirstChild(); n2 != 0; n2 = n2->NextSibling()) {
		AnimalBodyPart* part = new AnimalBodyPart(n2);
		this->parts.push_back(part);
	}
}

Attribute AnimalBodyPart::getAttribute(string s) {
	for(int i = 0; i < NUMBER_OF_ATTRS; i++)
		if (toUpper(s).compare(AnimalBodyPart::attrName[i]) == 0) return (Attribute) i;
	throw BADMODIFIER_EX;
}

AnimalBodyPart::~AnimalBodyPart() {
	// TODO Auto-generated destructor stub
}


void AnimalBodyPart::dumpPartInfo(int count) {
	int snum = this->getSkills()->size();
	int mnum = this->mods.size();

	for(int i = 0; i < count; i++) cout << "\t";
	cout << this->getName();
	if (this->getNumber() > 1) cout << " (x" << this->getNumber() << ")";
	if (snum > 0 || mnum > 0) cout << " {";// << endl;
	if (snum > 0) dumpSkills(count);
	if (snum > 0 && mnum > 0) cout << ", ";
	if (mnum > 0) dumpMods(count);
	if (snum > 0 || mnum > 0) cout << "}";
	cout << endl;
	for(unsigned int i = 0; i < this->parts.size(); i++) {
		AnimalBodyPart* abp = (AnimalBodyPart*) this->parts.at(i);
		abp->dumpPartInfo(count + 1);
	}
}

void AnimalBodyPart::dumpSkills(int count) {
	for(unsigned int i = 0; i < this->getSkills()->size(); i++) {
		Skill::RatedSkill rs = this->getSkills()->at(i);
		cout << rs.skill->getName() << " [" << rs.rating << "]";
		if (i < this->getSkills()->size() - 1)
			cout << ", ";
	}
}

void AnimalBodyPart::dumpMods(int count) {
	for(unsigned int i = 0; i < this->mods.size(); i++) {
		Modifier m = this->mods.at(i);
		cout << "[" << AnimalBodyPart::attrName[m.attr];
		if (m.mod>=0) cout << "+";
		cout << m.mod << "]";
		if (i < this->mods.size() - 1)
			cout << ", ";
	}
}

vector<Skill::RatedSkill> AnimalBodyPart::getAllSkills() {
	vector<Skill::RatedSkill> vs;
	vector<Skill::RatedSkill>* vs2 = this->getSkills();
	vs.insert(vs.end(),vs2->begin(),vs2->end());

	vector<BodyPart*> v = this->parts;
	for (vector<BodyPart*>::iterator it = v.begin(); it != v.end(); ++it) {
		AnimalBodyPart* abp = (AnimalBodyPart*) *it;
		vector<Skill::RatedSkill> aux = abp->getAllSkills();
		vs.insert(vs.end(),aux.begin(),aux.end());
	}
	return vs;
}

string AnimalBodyPart::attrName[] = {"STR", "AGI", "CON", "STA", "SPE"};
