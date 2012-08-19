/*
 * AnimalTemplate.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: leiterboss
 */

#include "AnimalTemplate.h"

AnimalTemplate::AnimalTemplate() : LivingBeingTemplate() {
	this->initNullAnimal();
}

AnimalTemplate::AnimalTemplate(TiXmlElement* el) : LivingBeingTemplate(el) { // <animal>...
	this->initNullAnimal();
	this->initAttributes(el);
	this->initInfo(el->FirstChildElement());
}

AnimalTemplate::~AnimalTemplate() {
	// TODO Auto-generated destructor stub
}

void AnimalTemplate::initAttributes(TiXmlElement* el) {
	for(TiXmlAttribute *at = el->FirstAttribute(); at != 0; at = at->Next()) {
		string tag = at->Name();
		if (tag.compare(XML_TAGS) == 0)
			this->setTags(this,at->Value());
	}

}

void AnimalTemplate::setTags(AnimalTemplate* a, string tags) {
	stringstream ss(tags);
	string s;

	while (getline(ss, s, ',')) {
		if (s.compare(XML_TAG_INVERTEBRATE)==0) this->addTag(TAG_INVERTEBRATE);
	}
}

void AnimalTemplate::setNames(string names) {
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

void AnimalTemplate::initNullAnimal() {
	this->setName("");
	this->setTrait(AVG_SIZE,-1); this->setTrait(AVG_DENSITY,-1);
	this->setTrait(AVG_WEIGHT,-1); this->setTrait(AVG_LENGTH,-1);
	this->bonePercentage=15; this->fatPercentage=20; this->musclePercentage=40; this->otherPercentage=25;
	this->setTrait(AVG_BONECS,-1); this->setTrait(RATIO_BONECS,1);
	this->setTrait(AVG_MUSCLECS,-1); this->setTrait(RATIO_MUSCLECS,1);
	this->setTrait(AVG_MUSCLELENGTH,-1); this->setTrait(RATIO_MUSCLELENGTH,1);
	this->setTrait(AVG_BMR,-1); this->setTrait(RATIO_BMR,1);
	this->setTrait(AVG_GESTATION,-1); this->setTrait(AVG_LIFESPAN,-1);
}

void AnimalTemplate::initInfo(TiXmlNode* el) { // <name>.. <size>...

	//float length = -1;

	for(; el != 0; el=el->NextSibling()) {
		TiXmlNode* info = el->FirstChild();
		string tag = el->Value();
		if (tag.compare(XML_NAME) == 0)
			this->setNames(info->ToText()->Value());
		else if (tag.compare(XML_SIZE) == 0)
			this->setTrait(AVG_SIZE,atof(info->ToText()->Value()));
		else if (tag.compare(XML_DENSITY) == 0)
			this->setTrait(AVG_DENSITY,atof(info->ToText()->Value()));
		else if (tag.compare(XML_MUSCLECROSS_SECTION) == 0)
			this->setTrait(AVG_MUSCLECS,atof(info->ToText()->Value()));
		else if (tag.compare(XML_MUSCLECS_RATIO) == 0)
			this->setTrait(RATIO_MUSCLECS,atof(info->ToText()->Value()));
		else if (tag.compare(XML_BONECROSS_SECTION) == 0)
			this->setTrait(AVG_BONECS,atof(info->ToText()->Value()));
		else if (tag.compare(XML_BONECS_RATIO) == 0)
			this->setTrait(RATIO_BONECS,atof(info->ToText()->Value()));
		else if (tag.compare(XML_MUSCLELENGTH) == 0)
			this->setTrait(AVG_MUSCLELENGTH,atof(info->ToText()->Value()));
		else if (tag.compare(XML_MUSCLELENGTH_RATIO) == 0)
			this->setTrait(RATIO_MUSCLELENGTH,atof(info->ToText()->Value()));
		else if (tag.compare(XML_METABOLISM) == 0)
			this->setTrait(AVG_BMR,atof(info->ToText()->Value()));
		else if (tag.compare(XML_METABOLISM_RATIO) == 0)
			this->setTrait(RATIO_BMR,atof(info->ToText()->Value()));
		else if (tag.compare(XML_WEIGHT) == 0)
			this->setTrait(AVG_WEIGHT,atof(info->ToText()->Value()));
	/*	else if (tag.compare(XML_LENGTH) == 0)
			length = atof(info->ToText()->Value());*/
		else if (tag.compare(XML_BODY) == 0)
			buildBody(info);
	}

	this->estimateTraits();
}

void AnimalTemplate::buildBody(TiXmlNode *n) {
	for(; n != 0; n=n->NextSibling()) {
		AnimalBodySection* bs = new AnimalBodySection(n);
		this->addBodySection(bs);
	}
}

// Estimations are made in relation to human measure

// Average human size (volume): 70 dm3 -> "length" = 4.1212 dm -> "surface" = 16.985 dm2
// Average human biceps: 33 cm -> 5.25 cm radius -> CS area: 0.866 dm2
// Ratio: 0.866 / 16.985 = 0.051
void AnimalTemplate::estimateMuscleCS() {
	double mcs = this->getTrait(AVG_LENGTH) * this->getTrait(AVG_LENGTH) * SURFACE_TO_MUSCLE_CS_RATIO * this->getTrait(RATIO_MUSCLECS);
	this->setTrait(AVG_MUSCLECS,mcs);
	this->setTrait(STD_MUSCLECS,mcs*DEFAULT_MUSCLECS_STDEV);
}

// Average human femur: 1.4 cm radius -> CS area: 0.06158 dm2
// Ratio: 0.06158 / 16.985 = 0.00363
void AnimalTemplate::estimateBoneCS() {
	double bcs = 0;
	if (!this->hasTag(TAG_INVERTEBRATE)) bcs = this->getTrait(AVG_LENGTH) * this->getTrait(AVG_LENGTH) * SURFACE_TO_BONE_CS_RATIO * this->getTrait(RATIO_BONECS);
	this->setTrait(AVG_BONECS,bcs);
	this->setTrait(STD_BONECS,bcs*DEFAULT_BONECS_STDEV);
}

// Average thigh length: 40.132 cm
// Ratio: 4.1212 / 4.0132 ~= 1
void AnimalTemplate::estimateMuscleLength() {
	double ml = this->getTrait(AVG_LENGTH) * LENGTH_TO_MUSCLE_LENGTH_RATIO * this->getTrait(RATIO_MUSCLELENGTH);
	this->setTrait(AVG_MUSCLELENGTH,ml);
	this->setTrait(STD_MUSCLELENGTH,ml*DEFAULT_MUSCLELENGTH_STDEV);
}

// Average BMR (male, 30 years, 1.7m, 65kg): 1616 kcal/day
// Kleiber's law: BMR ~ mass^(3/4)
// avg_mass^(3/4) = 22.892
// Ratio (BMR to avg_mass^(3/4)): 1616 / 22.892 = 70.5923
void AnimalTemplate::estimateBMR() {
	double m = this->getTrait(AVG_SIZE) * this->getTrait(AVG_DENSITY);
	double bmr = sqrt(sqrt(m));
	bmr = m * m * m * BMR_TO_PMASS_RATIO * this->getTrait(RATIO_BMR);
	this->setTrait(AVG_BMR,bmr);
	this->setTrait(STD_BMR,bmr*DEFAULT_BMR_STDEV);
}

// Gestation period estimate, given animal's weight
// log10(gestationPeriod) = GESTATION_COEFFICIENT*log10(weight) + GESTATION_CONSTANT
// Reference: http://www.sjsu.edu/faculty/watkins/gestation.htm
void AnimalTemplate::estimateGestationPeriod() {
	double w = this->getTrait(AVG_WEIGHT);
	double gest = pow(10,GESTATION_COEFFICIENT*log10(w)+GESTATION_CONSTANT);
	this->setTrait(AVG_GESTATION,gest);
	this->setTrait(STD_GESTATION,gest*DEFAULT_GESTATION_STDEV);

}

void AnimalTemplate::estimateTraits() {
	if (this->getName().compare("") == 0) throw NONAME_EX;

	if (this->getTrait(AVG_DENSITY) < 0 && this->getTrait(AVG_SIZE) < 0) {
		double avgDensity =
				this->bonePercentage *  BONE_DENSITY +
				this->fatPercentage * FAT_DENSITY +
				this->musclePercentage * MUSCLE_DENSITY +
				this->otherPercentage * OTHER_DENSITY;
		this->setTrait(AVG_DENSITY,avgDensity);
		this->setTrait(STD_DENSITY,avgDensity*DEFAULT_BODY_DENSITY_STDEV);
	}

/*	if (this->getTrait(AVG_LENGTH) < 0)
			this->setTrait(AVG_LENGTH,length * length * length / this->getTrait(AVG_DENSITY));*/
	if (this->getTrait(AVG_WEIGHT) > 0 && this->getTrait(AVG_SIZE) < 0)
		this->setTrait(AVG_SIZE,this->getTrait(AVG_WEIGHT) / this->getTrait(AVG_DENSITY));
	if (this->getTrait(AVG_WEIGHT) < 0 && this->getTrait(AVG_SIZE) > 0)
		this->setTrait(AVG_WEIGHT,this->getTrait(AVG_SIZE) * this->getTrait(AVG_DENSITY));
	if (this->getTrait(AVG_LENGTH) < 0)
		this->setTrait(AVG_LENGTH,cbrt(this->getTrait(AVG_SIZE)));

	if (this->getTrait(AVG_SIZE) < 0) throw NOSIZE_EX;
	if (this->getTrait(AVG_MUSCLECS) < 0)
		estimateMuscleCS();
	if (this->getTrait(AVG_BONECS) < 0)
		estimateBoneCS();
	if (this->getTrait(AVG_MUSCLELENGTH) < 0)
		estimateMuscleLength();
	if (this->getTrait(AVG_BMR) < 0)
		estimateBMR();
	if (this->getTrait(AVG_GESTATION) < 0)
		estimateGestationPeriod();
	if (this->getTrait(AVG_LIFESPAN) < 0)
		;//estimateLifespan();

}

Animal* AnimalTemplate::getAverageAnimal() {
	return new Animal(this,false);
}

void AnimalTemplate::dumpSkills() {
	vector<Skill::RatedSkill> v = this->getAllSkills();
	for (vector<Skill::RatedSkill>::iterator it = v.begin(); it != v.end();) {
		cout << it->skill->getFullName();
		if (++it != v.end()) cout << ",";
	}
}

void AnimalTemplate::dumpBody() {
	for(unsigned int i = 0; i < this->sects.size(); i++) {
		((AnimalBodySection*)(this->sects.at(i)))->dumpBodyParts();
	}
}

vector<Skill::RatedSkill> AnimalTemplate::getAllSkills() {
	vector<Skill::RatedSkill> vs;
	vector<BodySection*> v = this->sects;
	for (vector<BodySection*>::iterator it = v.begin(); it != v.end(); ++it) {
		AnimalBodySection *bs = (AnimalBodySection*) *it;
		vector<Skill::RatedSkill> aux = bs->getAllSkills();
		vs.insert(vs.end(),aux.begin(),aux.end());
	}
	return vs;
}

//string AnimalTemplate::getDescription() : getDescription() {};

/*
string AnimalTemplate::getDescription() {
	ostringstream os;
	float str, mbr, bone, mlen;

	str = this->getTrait(RATIO_MUSCLECS);
	mbr = this->getTrait(RATIO_BMR);
	bone = this->getTrait(RATIO_BONECS);
	mlen = this->getTrait(RATIO_MUSCLELENGTH);

	os << "The " << this->getName() << " is " << this->getSizeDescription() << " animal, " <<
			"with an average weight of " <<	this->getPrettyWeight() << ". ";

	if (str < 0.99) os << "It looks quite weak given its size. ";
	else if (str > 1.01) os << "It looks quite strong given its size. ";

	if (mbr < 0.99) os << "It looks quite hyperactive given its size. ";
	else if (mbr > 1.01) os << "It looks quite inactive given its size. ";

	if (bone < 0.99) os << "It looks quite flimsy given its size. ";
	else if (bone > 1.01) os << "It looks quite sturdy given its size. ";

	if (mlen < 0.99) os << "It looks quite clumsy given its size. ";
	else if (mlen > 1.01) os << "It looks quite nimble given its size. ";

	os << "Its skills include ";
	vector<Skill::RatedSkill> s = this->getAllSkills();

	unsigned int i = 0;
	for(i = 0; i < s.size() - 1; i++) {
		os << Skill::getSkillActionName(s.at(i).skill->getID());
		if (i != s.size() - 2) os << ", ";
	}
	if (s.size() != 1) os << " and ";
	os << Skill::getSkillActionName(s.at(i).skill->getID()) << ". ";

	return os.str();
}*/

string AnimalTemplate::getBodyDescription() {
	ostringstream os;

	unsigned int siz = this->sects.size();
	if (this->sects.size() == 1)
		os << "It has 1 body section: " << ((AnimalBodyPart*) this->sects.at(0))->getName() << ".";
	else {
		os << "It has " << this->sects.size() << " body sections: ";
		for(unsigned int i = 0; i < siz; i++) {
			AnimalBodyPart *bs = (AnimalBodyPart*) this->sects.at(i);
			os << bs->getName();
			if (i + 2 < siz) os << ", ";
			else if (i + 2 == siz) os << " and ";
		}
		os << ".";
	}
	os << endl << endl;
	for(unsigned int i = 0; i < siz; i++) {
		AnimalBodySection* abs = (AnimalBodySection*) this->sects.at(i);
		os << abs->getDescription();
		if (i + 1 < siz) os << endl << endl;
	}
	os << endl;
	return os.str();
}


/*
double AnimalTemplate::getStrength() {
	//return this->getSize()/10 + this->getMuscleCS();
	double tmp = this->getMuscleCS()*this->getBMR(); // TODO: Aggressivity
	return (double) this->getSize() + tmp*tmp;
}

int AnimalTemplate::getStrengthRating(int num, float min, float max) {
	return getAttributeRating(num, this->getStrength(), min, max);
}

double AnimalTemplate::getAgility() {
	return ((double) this->getMuscleLength() * (double) sqrt(this->getBMR())) / (double) this->getSize();
}

int AnimalTemplate::getAgilityRating(int num, float min, float max) {
	return getAttributeRating(num, this->getAgility(), min, max);
}

double AnimalTemplate::getStamina() {
	return (double) (this->getBoneCS()+1.0) / ((double) this->getSize() * (double) sqrt(this->getBMR()));
}

int AnimalTemplate::getStaminaRating(int num, float min, float max) {
	return getAttributeRating(num, this->getStamina(), min, max);
}

double AnimalTemplate::getConstitution() {
	return (double) this->getSize() * (double) (this->getBoneCS() + 1.0);
}

int AnimalTemplate::getConstitutionRating(int num, float min, float max) {
	return getAttributeRating(num, this->getConstitution(), min, max);
}

int AnimalTemplate::getAttributeRating(int num, float val, float min, float max) {
	float minl = log10(min);
	float maxl = log10(max);
	val = log10(val);
	maxl += (minl < 0)?-minl:minl;
	val += (minl < 0)?-minl:minl;
	return (val / maxl * (num-1)) + 1;
}
*/
