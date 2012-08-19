/*
 * common.h
 *
 *  Created on: Feb 4, 2012
 *      Author: leiterboss
 */

#ifndef COMMON_H_
#define COMMON_H_

#define BYTE unsigned char

#include <string>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include "../errors.h"
#include "../xmlSpec.h"
#include "../tinyxml/tinyxml.h"
#include <cmath>
#include "mtrand.h"

struct normalStats {double average; double stdeviation;};

normalStats makeNormalStats(double,double);
string toUpper(string s1);
bool isVowel(char c);
double normalDistValue(normalStats s);
double normalDistValue(double avg, double stdev);

#endif /* COMMON_H_ */
