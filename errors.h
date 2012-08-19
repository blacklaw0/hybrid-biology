/*
 * XMLException.h
 *
 *  Created on: Feb 5, 2012
 *      Author: leiterboss
 */

#ifndef XMLEXCEPTION_H_
#define XMLEXCEPTION_H_

// XML Exceptions (on animal handling)
#define BADANIMALXML_EX 0
#define NONAME_EX 1
#define NOSIZE_EX 2
#define BADSKILL_EX 3
#define BADMODIFIER_EX 4

#include <string>
using namespace std;

const string errors[] = {
		"The XML file does not describe a valid animal.",
		"The animal doesn't have a name.",
		"The animal doesn't have a valid size"};

#endif /* XMLEXCEPTION_H_ */
