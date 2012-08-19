/*
 * HybridBiologyController.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#include "HybridBiologyController.h"

HybridBiologyController::HybridBiologyController() {
	this->init();
}

HybridBiologyController::~HybridBiologyController() {
	// TODO Auto-generated destructor stub
}

void HybridBiologyController::init() {
	Skill::init();
	numAnimals = 0;
}

AnimalTemplate HybridBiologyController::getAnimal(int n) {
	if (n > this->numAnimals) return 0;
	else return this->animals[n];
}

void HybridBiologyController::openFile(string file) {
	TiXmlDocument doc(file.c_str());
	TiXmlElement *animal;
	int count; count = 0;
	bool loadOkay = doc.LoadFile();

	if (loadOkay)
	{
		for(animal = (TiXmlElement*) doc.FirstChild();
				animal != 0;
				animal = (TiXmlElement*) animal->NextSibling())
		    this->numAnimals++;

		this->animals = new AnimalTemplate[this->numAnimals];

		for(animal = (TiXmlElement*) doc.FirstChild(); animal != 0; animal = (TiXmlElement*) animal->NextSibling()) {
			try {
				animals[count++] = AnimalTemplate(animal);
			}
			catch (int ex) {
				cout << "Parsing error";
			}
		}
	}
	else
	{
		printf("Failed to load file\n");
	}
}

int main() {
	HybridBiologyController controller = HybridBiologyController();
	controller.openFile("animals.mbm");
	AnimalTemplate at = controller.getAnimal(0);



	TiXmlDocument doc("animals.mbm");
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		TiXmlElement *animal;
		AnimalTemplate* an[5]; int cont = 0;
		Animal* an2[5];
		for(animal = (TiXmlElement*) doc.FirstChild(); animal != 0; animal = (TiXmlElement*) animal->NextSibling()) {
			try {
				AnimalTemplate* a = new AnimalTemplate(animal);
				an[cont] = a;
				an2[cont++] = a->getAverageAnimal();
			}
			catch (int ex) {
				cout << "ERROR";
			}
		}
		cout << "MCS: " << an[2]->getTrait(AnimalTemplate::AVG_MUSCLECS) << " (" << an[2]->getTrait(AnimalTemplate::STD_MUSCLECS) << ") - "
				"BCS: " 		<< an[2]->getTrait(AnimalTemplate::AVG_BONECS) << " (" << an[2]->getTrait(AnimalTemplate::STD_BONECS) << ") - "
				"ML: " 		<< an[2]->getTrait(AnimalTemplate::AVG_MUSCLELENGTH) << " (" << an[2]->getTrait(AnimalTemplate::STD_MUSCLELENGTH) << ") - "
				"BMR: " 		<< an[2]->getTrait(AnimalTemplate::AVG_BMR) << " (" << an[2]->getTrait(AnimalTemplate::STD_BMR) << ")";
	/*
		cout << "Names:\t\t " << an[0]->getName() << "\t" << an[1]->getName() << "\t" << an[2]->getName() << "\t\t" << an[3]->getName() << "\t" << an[4]->getName() << "\t" << endl;
		cout << "Size:\t\t " <<
				an[0]->getTrait(LivingBeingTemplate::AVG_SIZE) << "\t" <<
				an[1]->getTrait(LivingBeingTemplate::AVG_SIZE) << "\t\t" <<
				an[2]->getTrait(LivingBeingTemplate::AVG_SIZE) << "\t\t" <<
				an[3]->getTrait(LivingBeingTemplate::AVG_SIZE) << "\t\t\t" <<
				an[4]->getTrait(LivingBeingTemplate::AVG_SIZE) << "\t" << endl;
		cout << "Strength:\t " <<
				an2[0]->getStrength() << "\t" <<
				an2[1]->getStrength() << "\t\t" <<
				an2[2]->getStrength() << "\t\t\t" <<
				an2[3]->getStrength() << "\t\t" <<
				an2[4]->getStrength() << "\t" << endl;
		cout << "Agility:\t " <<
				an2[0]->getAgility() << "\t" <<
				an2[1]->getAgility() << "\t\t\t" <<
				an2[2]->getAgility() << "\t\t\t" <<
				an2[3]->getAgility() << "\t\t\t" <<
				an2[4]->getAgility() << "\t" << endl;
		cout << "Constitution:\t " <<
				an2[0]->getConstitution() << "\t" <<
				an2[1]->getConstitution() << "\t\t" <<
				an2[2]->getConstitution() << "\t\t" <<
				an2[3]->getConstitution() << "\t\t\t" <<
				an2[4]->getConstitution() << "\t" << endl;
		cout << "Stamina:\t " <<
				an2[0]->getStamina() << "\t" <<
				an2[1]->getStamina() << "\t\t\t" <<
				an2[2]->getStamina() << "\t\t" <<
				an2[3]->getStamina() << "\t\t" <<
				an2[4]->getStamina() << "\t" << endl;

		float max[4] = {an2[4]->getStrength(), an2[0]->getAgility(), an2[4]->getConstitution(), an2[0]->getStamina()};
		float min[4] = {an2[0]->getStrength(), an2[4]->getAgility(), an2[0]->getConstitution(), an2[4]->getStamina()};

		cout << "------------------------" << endl;
		//for(int i = 0; i < 4; i++) { max[i] = (log2(max[i])+10) / MAX_RAT; if (log2(min[i]) < MIN_RAT) MIN_RAT = log2(min[i]);}
		cout << "Strength:\t " <<
				an2[0]->getStrengthRating(100,min[0],max[0]) << "\t\t" <<
				an2[1]->getStrengthRating(100,min[0],max[0]) << "\t\t\t" <<
				an2[2]->getStrengthRating(100,min[0],max[0]) << "\t\t\t" <<
				an2[3]->getStrengthRating(100,min[0],max[0]) << "\t\t\t" <<
				an2[4]->getStrengthRating(100,min[0],max[0]) << "\t" << endl;
		cout << "Agility:\t " <<
				an2[0]->getAgilityRating(100,min[1],max[1]) << "\t\t" <<
				an2[1]->getAgilityRating(100,min[1],max[1]) << "\t\t\t" <<
				an2[2]->getAgilityRating(100,min[1],max[1]) << "\t\t\t" <<
				an2[3]->getAgilityRating(100,min[1],max[1]) << "\t\t\t" <<
				an2[4]->getAgilityRating(100,min[1],max[1]) << "\t" << endl;
		cout << "Constitution:\t " <<
				an2[0]->getConstitutionRating(100,min[2],max[2]) << "\t\t" <<
				an2[1]->getConstitutionRating(100,min[2],max[2]) << "\t\t\t" <<
				an2[2]->getConstitutionRating(100,min[2],max[2]) << "\t\t\t" <<
				an2[3]->getConstitutionRating(100,min[2],max[2]) << "\t\t\t" <<
				an2[4]->getConstitutionRating(100,min[2],max[2]) << "\t" << endl;
		cout << "Stamina:\t " <<
				an2[0]->getStaminaRating(100,min[3],max[3]) << "\t\t" <<
				an2[1]->getStaminaRating(100,min[3],max[3]) << "\t\t\t" <<
				an2[2]->getStaminaRating(100,min[3],max[3]) << "\t\t\t" <<
				an2[3]->getStaminaRating(100,min[3],max[3]) << "\t\t\t" <<
				an2[4]->getStaminaRating(100,min[3],max[3]) << "\t" << endl;
*/
		try {
		AnimalTemplate* a = new AnimalTemplate((TiXmlElement*) doc.FirstChild());
		//a->dumpTraits();
		cout << a->getDescription();
		}
		catch (int ex) {
			cout << "ERROR";
		}
	}
}
