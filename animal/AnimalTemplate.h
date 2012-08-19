/*
 * AnimalTemplate.h
 *
 *  Created on: Mar 5, 2012
 *      Author: leiterboss
 */

#ifndef ANIMALTEMPLATE_H_
#define ANIMALTEMPLATE_H_

#include <cmath>
#include "../utils/common.h"
#include "AnimalBodySection.h"
#include "AnimalBehavior.h"
#include "Animal.h"
#include "../LivingBeingTemplate.h"
#include "../tinyxml/tinyxml.h"
using namespace std;


// Average human size (volume): 70 dm3 -> "length" = 4.1212 dm -> "surface" = 16.985 dm2
// Average human biceps: 33 cm -> 5.25 cm radius -> CS area: 0.866 dm2
// Ratio: 0.866 / 16.985 = 0.051
#define SURFACE_TO_MUSCLE_CS_RATIO 0.051

// Average human femur: 1.4 cm radius -> CS area: 0.06158 dm2
// Ratio: 0.06158 / 16.985 = 0.00363
#define SURFACE_TO_BONE_CS_RATIO 0.00363

// Average thigh length: 40.132 cm
// Ratio: 4.1212 / 4.0132 = 1.0269
#define LENGTH_TO_MUSCLE_LENGTH_RATIO 1.0269

// Average BMR (male, 30 years, 1.7m, 65kg): 1616 kcal/day
// Kleiber's law: BMR ~ mass^(3/4)
// avg_mass^(3/4) = 22.892
// Ratio (BMR to avg_mass^(3/4)): 1616 / 22.892 = 70.5923
#define BMR_TO_PMASS_RATIO 70.5923

#define DEFAULT_BMR_STDEV 0.15
#define DEFAULT_MUSCLECS_STDEV 0.30
#define DEFAULT_BONECS_STDEV 0.20
#define DEFAULT_MUSCLELENGTH_STDEV sqrt(DEFAULT_MUSCLECS_STDEV)
#define DEFAULT_GESTATION_STDEV 0.10

#define BONE_DENSITY 1.8
#define FAT_DENSITY 0.85
#define MUSCLE_DENSITY 1.15
#define OTHER_DENSITY 1

class Animal;

class AnimalTemplate : public LivingBeingTemplate {

	// TODO: Vital systems (circulatory, digestive, ...)
	// www.wisegeek.com
	// Circulatory system (closed, open, none)

public:
	enum animalTraitsID {	AVG_MUSCLECS=NUM_OF_COMMON_TRAITS, STD_MUSCLECS, AVG_BONECS, STD_BONECS, AVG_MUSCLELENGTH, STD_MUSCLELENGTH,
					AVG_BMR, STD_BMR, RATIO_MUSCLECS, RATIO_BONECS, RATIO_MUSCLELENGTH, RATIO_BMR, NUM_OF_ANIMAL_TRAITS};

protected:
	double animalTraits[NUM_OF_ANIMAL_TRAITS-NUM_OF_COMMON_TRAITS];

private:
	// Percentage of each component in the body.
	char bonePercentage, fatPercentage, musclePercentage, otherPercentage;
/*
	float avgMuscleCS, stdMuscleCS;				// Average muscle cross-section
	float avgBoneCS, stdBoneCS;					// Average bone cross-section
	float avgMuscleLength, stdMuscleLength;		// Average muscle length
	float avgBMR, stdBMR;						// Average basal metabolic rate

	float BMRHRatio;			// BMR to body ratio (human -> 1)
	float muscleCSHRatio;		// Muscle CS surface to body ratio (human -> 1)
	float boneCSHRatio;			// Bone CS surface to body ratio (human -> 1)
	float muscleLengthHRatio;	// Muscle length to body ratio (human -> 1)
*/
	void initInfo(TiXmlNode*);
	void initAttributes(TiXmlElement*);
	void initNullAnimal();
	void setTags(AnimalTemplate*, string);
	void buildBody(TiXmlNode*);
	void setNames(string);
	int getAttributeRating(int, float, float, float);

public:

	AnimalTemplate();
	AnimalTemplate(TiXmlElement*);
	virtual ~AnimalTemplate();
	void estimateTraits();
	Animal* getAverageAnimal();

	void estimateMuscleCS();
	void estimateBoneCS();
	void estimateMuscleLength();
	void estimateBMR();
	void estimateGestationPeriod();

	// Integer t is from enum animalTraits
	virtual void setTrait(int t, double val) {
		if (t < 0) return;
		if (t < NUM_OF_COMMON_TRAITS) this->commonTraits[t] = val;
		else if (t < NUM_OF_ANIMAL_TRAITS) this->animalTraits[t-NUM_OF_COMMON_TRAITS] = val;
	}
	virtual double getTrait(int t) {
		if (t < 0) return -1;
		if (t < NUM_OF_COMMON_TRAITS) return this->commonTraits[t];
		else if (t < NUM_OF_ANIMAL_TRAITS) return this->animalTraits[t-NUM_OF_COMMON_TRAITS];
		return -1;
	}


/*	normalStats getStatsBMR() {return makeNormalStats(this->avgBMR, this->stdBMR);}
	normalStats getStatsMuscleCS() {return makeNormalStats(this->avgMuscleCS, this->stdMuscleCS);}
	normalStats getStatsBoneCS() {return makeNormalStats(this->avgBoneCS, this->stdBoneCS);}
	normalStats getStatsMuscleLength() {return makeNormalStats(this->avgMuscleLength, this->stdMuscleLength);}
	void setAverageBMR(float b) {this->avgBMR = b;}
	void setStDevBMR(float b) {this->stdBMR = b;}
	void setAverageMuscleCS(float m) {this->avgMuscleCS = m;}
	void setStDevMuscleCS(float m) {this->stdMuscleCS = m;}
	void setAverageBoneCS(float b) {this->avgBoneCS = b;}
	void setStDevBoneCS(float b) {this->stdBoneCS = b;}
	void setAverageMuscleLength(float l) {this->avgMuscleLength = l;}
	void setStDevMuscleLength(float l) {this->stdMuscleLength = l;}

	float getAverageBMRRatio() {return this->BMRHRatio;}
	float getAverageMuscleCSRatio() {return this->muscleCSHRatio;}
	float getAverageBoneCSRatio() {return this->boneCSHRatio;}
	float getAverageMuscleLengthRatio() {return this->muscleLengthHRatio;}
	void setAverageBMRRatio(float b) {this->BMRHRatio = b;}
	void setAverageMuscleCSRatio(float m) {this->muscleCSHRatio = m;}
	void setAverageBoneCSRatio(float b) {this->boneCSHRatio = b;}
	void setAverageMuscleLengthRatio(float l) {this->muscleLengthHRatio = l;}
*/
	bool addBodySection(AnimalBodySection* bs) {this->sects.push_back((BodySection*) bs); return true;}
	//bool addBodySection(BodySection *bs) {return false;}

	vector<Skill::RatedSkill> getAllSkills();
	void dumpBody();
	void dumpSkills();
	//string getDescription();
	string getBodyDescription();

/*
	double getStrength(); int getStrengthRating(int, float, float);
	double getAgility(); int getAgilityRating(int, float, float);
	double getStamina(); int getStaminaRating(int, float, float);
	double getConstitution(); int getConstitutionRating(int, float, float);
*/
};

#endif /* ANIMALTEMPLATE_H_ */
