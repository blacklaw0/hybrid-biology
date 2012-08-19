/*
 * Animal.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#include "Animal.h"


Animal::Animal(AnimalTemplate *at, bool random): LivingBeing((LivingBeingTemplate*) at, random) {
	if (random) {
		this->setBMR(normalDistValue(at->getTrait(AnimalTemplate::AVG_BMR),at->getTrait(AnimalTemplate::STD_BMR)));
		this->setMuscleCS(normalDistValue(at->getTrait(AnimalTemplate::AVG_MUSCLECS),at->getTrait(AnimalTemplate::STD_MUSCLECS)));
		this->setBoneCS(normalDistValue(at->getTrait(AnimalTemplate::AVG_BONECS),at->getTrait(AnimalTemplate::STD_BONECS)));
		this->setMuscleLength(normalDistValue(at->getTrait(AnimalTemplate::AVG_MUSCLELENGTH),at->getTrait(AnimalTemplate::STD_MUSCLELENGTH)));
	}
	else {
		this->setBMR(at->getTrait(AnimalTemplate::AVG_BMR));
		this->setMuscleCS(at->getTrait(AnimalTemplate::AVG_MUSCLECS));
		this->setBoneCS(at->getTrait(AnimalTemplate::AVG_BONECS));
		this->setMuscleLength(at->getTrait(AnimalTemplate::AVG_MUSCLELENGTH));
	}
}

Animal::~Animal() {
	// TODO Auto-generated destructor stub
}


void Animal::dumpTraits() {
	cout << "Animal (" << this->getName() <<  "):" << endl;
	cout << "\tSize: " << this->getSize() << " dm^3" << endl;
	cout << "\tBody density: " << this->getDensity() << " kg/dm^3" << endl;
	cout << "\tWeight: " << this->getDensity()*this->getSize() << " kg" << endl;
	cout << "\tMuscle cross-section: " << this->getMuscleCS() << " dm^2" << endl;
	cout << "\tBone cross-section: " << this->getBoneCS() << " dm^2" << endl;
	cout << "\tAverage muscle length: " << this->getMuscleLength() << " dm" << endl;
	cout << "\tBasal metabolic rate: " << this->getBMR() << " kcal/day" << endl;
	cout << "\tSkills: "; this->dumpSkills(); cout << endl;
	cout << "\tAttributes: " << endl; this->dumpAttributes();
	cout << "\tBody:" << endl; this->dumpBody(); cout << endl;

}

void Animal::dumpAttributes() {
	cout << "\t\tStrength: " << this->getStrength() << endl;
	cout << "\t\tConstitution: " << this->getConstitution() << endl;
	cout << "\t\tStamina: " << this->getStamina() << endl;
	cout << "\t\tAgility: " << this->getAgility() << endl;
	this->dumpAllSpeeds();
}

void Animal::dumpAllSpeeds() {
	for(int i = 0; i < Skill::NUMBER_MOVS; i++)
		if (this->getSpeed(i) > 0) cout << "\tSpeed (" << Skill::getSkillFullName(i) << "): " << this->getSpeed(i) << endl;
}

void Animal::dumpSkills() {
	vector<Skill::RatedSkill> v = this->getAllSkills();
	for (vector<Skill::RatedSkill>::iterator it = v.begin(); it != v.end();) {
		cout << it->skill->getFullName();
		if (++it != v.end()) cout << ",";
	}
}

void Animal::dumpBody() {
	AnimalTemplate* at = (AnimalTemplate*) this->getTemplate();
	at->dumpBody();
}

double Animal::getStrength() {
	double tmp = this->getMuscleCS()*this->getBMR(); // TODO: Aggressivity check
	return (double) this->getSize() + tmp*tmp;
}

int Animal::getStrengthRating(int num, float min, float max) {
	return getAttributeRating(num, this->getStrength(), min, max);
}

double Animal::getAgility() {
	double m = this->getMuscleLength();
	double b = sqrt(this->getBMR());
	double s = this->getSize();
	return m * b / s;
	//return ((double) this->getMuscleLength() * (double) sqrt(this->getBMR())) / (double) this->getSize();
}

int Animal::getAgilityRating(int num, float min, float max) {
	return getAttributeRating(num, this->getAgility(), min, max);
}

double Animal::getStamina() {
	return (double) (this->getBoneCS()+1.0) / ((double) this->getSize() * (double) sqrt(this->getBMR()));
}

int Animal::getStaminaRating(int num, float min, float max) {
	return getAttributeRating(num, this->getStamina(), min, max);
}

double Animal::getConstitution() {
	return (double) this->getSize() * (double) (this->getBoneCS() + 1.0);
}

int Animal::getConstitutionRating(int num, float min, float max) {
	return getAttributeRating(num, this->getConstitution(), min, max);
}

int Animal::getAttributeRating(int num, float val, float min, float max) {
	float minl = log10(min);
	float maxl = log10(max);
	val = log10(val);
	maxl -= minl;
	val -= minl;
	return (val / maxl * (num-1)) + 1;
}

double Animal::getSpeed(int mov) {
	return this->getSkillRating(mov);
	/*
	short rat;
	switch(mov) {
		case Skill::RUN: rat = this->getSkillRating(Skill::RUN); break;
		case Skill::SWIM: rat = this->getSkillRating(Skill::SWIM); break;
		case Skill::FLY: rat = this->getSkillRating(Skill::FLY); break;
		case Skill::CLIMB: rat = this->getSkillRating(Skill::CLIMB); break;
		case Skill::GLIDE: rat = this->getSkillRating(Skill::GLIDE); break;
	}
	if (rat < 0) return -1;
	else return rat;*/
}

/*
double Animal::getRealSpeed(float rat) {
	if (this->getSize() < 1) {
		return 0.6*(1-exp(-1.1889e5*rat*this->getSize()*this->getMuscleLength()));
	}
	else if (this->getSize() > 200) {
		//return sqrt(rat * this->getMuscleLength() * this->getSize());
		return 575 - 1.11e-4 * rat * this->getMuscleLength() * this->getSize() * 0.004854419;
	}
	else {
		return rat * this->getMuscleLength() * this->getSize() * 0.004854419;
	}
}
*/

vector<Skill::RatedSkill> Animal::getAllSkills() {
	AnimalTemplate* at = (AnimalTemplate*) this->getTemplate();
	return at->getAllSkills();
}

short Animal::getSkillRating(short id) {
	vector<Skill::RatedSkill> sk = this->getAllSkills();
	for (vector<Skill::RatedSkill>::iterator it = sk.begin(); it != sk.end(); ++it)
		if (it->skill->getID() == id) return it->rating;
	return -1;
}

string Animal::getDescription() {
	ostringstream os;
	os << "This is a " << this->getName()
			<< ". It weighs " << this->getWeight() << " kilograms"
			<< endl;;

	return os.str();
}
