/*
 * Animal.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <cmath>
#include "../utils/common.h"
#include "../LivingBeing.h"
#include "AnimalTemplate.h"
#include "AnimalBehavior.h"
#include "AnimalBodySection.h"
#include "../tinyxml/tinyxml.h"

class AnimalTemplate;

class Animal : public LivingBeing {
private:
	double BMR;					// Basal metabolic rate
	double muscleCS;				// Muscle cross-section
	double boneCS;				// Bone cross-section
	double muscleLength;			// Muscle length

	void buildBody(TiXmlNode*);
	double getRealSpeed(float rat);
	int getAttributeRating(int, float, float, float);

public:
	Animal();
	Animal(AnimalTemplate* at,bool random=true);
	virtual ~Animal();
	double getStrength(); int getStrengthRating(int, float, float);
	double getAgility(); int getAgilityRating(int, float, float);
	double getStamina(); int getStaminaRating(int, float, float);
	double getConstitution(); int getConstitutionRating(int, float, float);
	double getSpeed(int);
	double getMuscleCS() {return this->muscleCS;}
	void setMuscleCS(float m) {this->muscleCS = m;}
	double getBoneCS() {return this->boneCS;}
	void setBoneCS(float b) {this->boneCS = b;}
	double getMuscleLength() {return this->muscleLength;}
	void setMuscleLength(float ml) {this->muscleLength = ml;}
	double getBMR() {return this->BMR;}
	void setBMR(float bmr) {this->BMR = bmr;}
	vector<Skill::RatedSkill> getAllSkills();

	void dumpTraits();
	void dumpBody();
	void dumpSkills();
	void dumpAttributes();
	void dumpAllSpeeds();
	short getSkillRating(short);
	string getDescription();

};

#endif /* ANIMAL_H_ */
