/*
 * BodySection.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#include "BodySection.h"
/*
BodySection::BodySection() {

}*/

BodySection::~BodySection() {
}


string BodySection::getDescription() {
	ostringstream os;
	os << ((BodyPart*) this)->getDescription();
	os << endl << endl;
	// TODO: finish
	return os.str();
}
