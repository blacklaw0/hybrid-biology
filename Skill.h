/*
 * Skill.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef SKILL_H_
#define SKILL_H_

#include "utils/common.h"
using namespace std;

class Skill {
private:
	BYTE id;
	BYTE type;


	static const string skillId[];
	static const string skillPrettyName[];
	static const string skillActionName[];

	static int getSkillNumber(string);

public:
	enum skillNumber {RUN,SWIM,FLY,GLIDE,CLIMB,FEED,BREATHE,BASH,STING_ACT,RAM,GORE,SCRATCH,BITE,DIG,POISON_ACT,SHOCK_ACT,
		INFESTATION,PLAGUE,WEB,BLIND,VISION,THERMAL_VISION,NIGHT_VISION,RADAR,REGENERATION,SHOCK_PAS,POISON_PAS,DISEASE,
		SMELL,HEARING,STING_PAS,NUMBER_OF_SKILLS};
	// skillNumber include the movement types e.g. RUN, SWIM, ...
	// Types of movement must be included in skillNumber (run, swim, fly, glide, climb)
	enum movement_kinds {MOV_RUN = 0, MOV_SWIM = 1, MOV_FLY = 2, MOV_GLIDE = 3, MOV_CLIMB = 4, NUMBER_MOVS = 5};
	//static const int KINDS_OF_MOVEMENT = 5;

	static Skill* skillPointers[Skill::NUMBER_OF_SKILLS];

	Skill(BYTE id) {this->id = id; this->type = 0;};
	struct RatedSkill { Skill *skill; float rating; };
	virtual ~Skill() {};

	static void init();
	static Skill* getSkill(string);
	static string getSkillFullName(int n) {return Skill::skillPrettyName[n];}
	static string getSkillActionName(int n) {return Skill::skillActionName[n];}
	static string getRatingAdjective(float,bool);
	static bool isMovementSkill(short id) {return id < NUMBER_MOVS;}

	short getID() { return this->id; }
	string getFullName() { return Skill::skillPrettyName[(int)this->id]; }
	string getActionName() {return Skill::skillActionName[(int)this->id];}
	string getName() { return Skill::skillId[(int)this->id]; }
	RatedSkill getRatedSkill(string, BYTE);
};


#endif /* SKILL_H_ */
