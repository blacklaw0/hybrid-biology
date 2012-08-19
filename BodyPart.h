/*
 * BodyPart.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef BODYPART_H_
#define BODYPART_H_

#include "utils/common.h"
#include "Material.h"
#include <sstream>
#include "Skill.h"


class BodyPart {
private:
	string name, namePlural, article;
	vector<Skill::RatedSkill> skills;
	Material mat;
	unsigned short num;

protected:
	vector<BodyPart*> parts;

public:
	virtual ~BodyPart();

	string getName() {return this->name;};
	string getNamePlural() {return this->namePlural;}
	string getArticle() {return this->article;}
	void setName(string s) {this->name = s;};
	void setNamePlural(string s) {this->namePlural = s;};
	void setArticle(string s) {this->article = s;};
	unsigned short getNumber() {return this->num;};
	void setNumber(unsigned short n) {this->num = n;};
	vector<Skill::RatedSkill> getRatedSkills();
	void addSkill(Skill* s, float rat) {
		struct Skill::RatedSkill rs = {s, rat}; skills.push_back(rs);
	};
	vector<Skill::RatedSkill>* getSkills() {return &this->skills;}
	Material getMaterial() {return this->mat;}
	void setMaterial(Material m) {this->mat = m;}
	string getDescription();
	void setNames(string);

};

#endif /* BODYPART_H_ */
