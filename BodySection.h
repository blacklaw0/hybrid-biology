/*
 * BodySection.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef BODYSECTION_H_
#define BODYSECTION_H_

#include "BodyPart.h"
#include <string>
#include <vector>
using namespace std;

class BodySection : public BodyPart {
private:
	string name;
	vector<BodyPart*> parts;

public:
	//BodySection();
	virtual ~BodySection();

	string getName() {return this->name;}
	void setName(string n) {this->name = n;}
	vector<BodyPart*> getParts();
	string getDescription();
};

#endif /* BODYSECTION_H_ */
