/*
 * HybridBiologyController.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef HybridBiologyController_H_
#define HybridBiologyController_H_

#include <stdio.h>
#include "animal/Animal.h"
#include "utils/common.h"
#include "tinyxml/tinyxml.h"
#include "animal/AnimalTemplate.h"


class HybridBiologyController {
private:
	AnimalTemplate *animals;
	int numAnimals;

public:
	HybridBiologyController();
	virtual ~HybridBiologyController();

	void init();
	AnimalTemplate getAnimal(int n);
	void openFile(string file);
	static void test();
};

#endif /* HybridBiologyController_H_ */
