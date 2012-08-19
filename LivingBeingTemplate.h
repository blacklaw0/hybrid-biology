/*
 * LivingBeingTemplate.h
 *
 *  Created on: Mar 5, 2012
 *      Author: leiterboss
 */

#ifndef LIVINGBEINGTEMPLATE_H_
#define LIVINGBEINGTEMPLATE_H_

#include <cmath>
#include <sstream>
#include "utils/common.h"
#include "BodySection.h"
#include "Behavior.h"
#include <bitset>


// Average human body density: 1.01 kg/dm^3
#define DEFAULT_BODY_DENSITY 1.01
#define DEFAULT_BODY_DENSITY_STDEV 0.10	// In %

// Gestation period estimation
// log(gestationPeriod) = GESTATION_COEFFICIENT * log(weight) + GESTATION_CONSTANT
#define GESTATION_COEFFICIENT 0.333
#define GESTATION_CONSTANT 1.527

// Empirical rule:
//  1 stdev -> 68%
//  2 stdev -> 95%
//  3 stdev -> 99%
#define DEFAULT_SIZE_STDEV 5.0
#define DEFAULT_WEIGHT_STDEV DEFAULT_SIZE_STDEV
#define DEFAULT_DENSITY_STDEV
#define DEFAULT_LENGTH_STDEV cbrt(DEFAULT_SIZE_STDEV)
#define DEFAULT_LIFESPAN_STDEV
#define DEFAULT_PACKSIZE_STDEV 50.0

using namespace std;

class LivingBeingTemplate {
	public:
		enum commonTraitsID {	AVG_SIZE=0, STD_SIZE, AVG_WEIGHT, STD_WEIGHT, AVG_DENSITY, STD_DENSITY,
						AVG_LENGTH, STD_LENGTH, AVG_LIFESPAN, STD_LIFESPAN, AVG_PACKSIZE, STD_PACKSIZE,
						AVG_GESTATION, STD_GESTATION, NUM_OF_COMMON_TRAITS};

	private:
		string name, namePlural, article;

/*
		float avgSize, stdSize;
		float avgWeight, stdWeight;
		float avgDensity, stdDensity;
		float avgLength, stdLength; // cube root of size

		float avgLifespan, stdLifespan;
		float avgPackSize, stdPackSize;	// average size and deviation of pack, herd, colony, ...
		float avgGestation, stdGestation;			// Stats for gestation period
*/		float adulthoodAge;
		float dietKind;

		Behavior typicalBehavior;

	protected:
		vector<BodySection*> sects;
		double commonTraits[NUM_OF_COMMON_TRAITS];

	public:
		enum tagIDs {TAG_INVERTEBRATE, TAG_FLYING, TAG_SWIMMING, TAG_ENDOFTAGS};
		enum dietKinds {DIET_OMNIVOROUS, DIET_CARNIVOROUS, DIET_HERBIVOROUS,
			DIET_INSECTIVOROUS, DIET_DETRITIVOROUS, DIET_NECTARIVOROUS, DIET_ENDOFDIETS};
		LivingBeingTemplate() {};
		LivingBeingTemplate(TiXmlElement*);
		virtual ~LivingBeingTemplate();
		string getName() {return this->name;}
		string getNamePlural() {return this->namePlural;}
		string getArticle() {return this->article;}
		void setName(string n) {this->name = n;}
		void setNamePlural(string n) {this->namePlural = n;}
		void setArticle(string n) {this->article = n;}
		bool hasTag(int t) {return tags[t];}
		void addTag(int t) {tags[t] = true;}
		void removeTag(int t) {tags[t] = false;}

		// Integer t is from enum traits (or its derivates: animalTraits, ...)
		virtual void setTrait(int t, double val) {
			if (t >= 0 && t < NUM_OF_COMMON_TRAITS) this->commonTraits[t] = val;
		}
		virtual double getTrait(int t) {
			if (t >= 0 && t < NUM_OF_COMMON_TRAITS) return this->commonTraits[t];
			return -1;
		}

	/*	void setAverageSize(float s) {this->avgSize = s;}
		void setStdSize(float s) {this->stdSize = s;}
		void setAverageWeight(float w) {this->avgWeight = w;}
		void setStdWeight(float w) {this->stdWeight = w;}
		void setAverageDensity(float d) {this->avgDensity = d;}
		void setStdDensity(float d) {this->stdDensity = d;}
		void setAverageLength(float l) {this->avgLength = l;}
		void setStdLength(float l) {this->stdLength = l;}
		void setAverageGestationPeriod(float g) {this->avgGestation = g;}
		void setStDevGestationPeriod(float g) {this->stdGestation = g;}
		void setBehavior(Behavior b) {this->typicalBehavior = b;}

		normalStats getStatsSize() {return makeNormalStats(this->avgSize, this->stdSize);}
		normalStats getStatsWeight() {return makeNormalStats(this->avgWeight, this->stdWeight);}
		normalStats getStatsDensity() {return makeNormalStats(this->avgDensity, this->stdDensity);}
		normalStats getStatsLength() {return makeNormalStats(this->avgLength, this->stdLength);}
		normalStats getStatsGestationPeriod() {return makeNormalStats(this->avgGestation, this->stdGestation);}
	*/
		Behavior getBehavior() {return this->typicalBehavior;}

		string getDescription();

	protected:
		string getSizeDescription();
		string getPrettyWeight();
		virtual string getBodyDescription() = 0;

	private:
		bitset<TAG_ENDOFTAGS> tags;
	};

#endif /* LIVINGBEINGTEMPLATE_H_ */
