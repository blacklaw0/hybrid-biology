/*
 * Skill.cpp
 *
 *  Created on: Feb 6, 2012
 *      Author: leiterboss
 */

#include "Skill.h"

const string Skill::skillId[] = {"run", "swim", "fly", "glide", "climb", "feed", "breathe", "bash", "sting_act",
"ram", "gore", "scratch", "bite", "dig", "poison_act", "shock_act", "infestation", "plague", "web", "blind",
"vision", "thermalvision", "nightvision", "radar", "regeneration", "shock_pas", "poison_pas", "disease",
"smell", "hearing", "sting_pas"};

const string Skill::skillPrettyName[] = {"run", "swim", "fly", "glide", "climb", "feed", "breathe", "bash", "sting (active)",
"ram", "gore", "scratch", "bite", "dig", "poison (active)", "shock (active)", "infestation", "plague", "web", "blind",
"vision", "thermal vision", "night vision", "radar", "regeneration", "shock (passive)", "poison (passive)", "disease",
"smell", "hearing", "sting (passive)",""};

const string Skill::skillActionName[] = {"running", "swimming", "flying", "gliding", "climbing", "feeding", "breathing", "bashing", "stinging",
		"ramming", "goring", "scratching", "biting", "digging", "poisoning", "electrically shocking", "infestate territories", "bringing forth plagues", "web weaving", "blinding",
		"seeing", "seeing (thermally)", "seeing (in darkness)", "radar", "regenerating", "protection by shocking", "protection by poisoning", "disease transmission",
		"smelling", "hearing", "protection by stinging",""};

Skill* Skill::skillPointers[Skill::NUMBER_OF_SKILLS];

void Skill::init() {
	for(int i = 0; i < Skill::NUMBER_OF_SKILLS; i++)
		skillPointers[i] = 0;
}

int Skill::getSkillNumber(string s) {
	for(int i = 0; i < NUMBER_OF_SKILLS; i++)
		if (Skill::skillId[i].compare(s) == 0) return i;
	return -1;
}

Skill* Skill::getSkill(string str) {
	int sn = getSkillNumber(str);
	if (sn == -1) {printf("Exception: Skill does not exist."); throw BADSKILL_EX;}
	if (Skill::skillPointers[sn] == 0) Skill::skillPointers[sn] = new Skill(sn);
	return Skill::skillPointers[sn];
}

Skill::RatedSkill Skill::getRatedSkill(string id, BYTE rating) {
	struct RatedSkill rs = {Skill::getSkill(id), rating};
	return rs;
}

string Skill::getRatingAdjective(float rat, bool movement) {
	ostringstream os;
	if (movement) os << "a top speed of " << rat << " km/h";
	else {
		if (rat < 50) os << "very bad";
		else if (rat < 80) os << "mediocre";
		else if (rat == 100) os << "";
		else if (rat < 120) os << "quite good";
		else if (rat < 150) os << "very good";
		else if (rat < 200) os << "extraordinary";
		else os << "otherworldly";
	}
	return os.str();
}

