/*
 * utils.cpp
 *
 *  Created on: Feb 7, 2012
 *      Author: leiterboss
 */

#include "common.h"
#include <time.h>

MTRand drand(time(NULL)); // double in [0, 1)

string toUpper(string s1) {
	for (string::iterator i = s1.begin(); i != s1.end(); i++) {
	*i = toupper(*i);
	}
	return s1;
}

bool isVowel(char c) {
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
			c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

double normalDistValue(normalStats st) {
	// Marsaglia Polar Method for normal distribution-generated
	// values with average mu and standard deviation sigma

	double s,u,v,x;
	s = 2; // Any number greater than one really
	while (s > 1) {
		u = drand() * 2 - 1;
		v = drand() * 2 - 1;
		s = u*u+v*v;
	}
	x = u * sqrt((-2*log(s))/s);

	// It will only return positive numbers, so we get the absolute value.
	// If we get negative it means that we are dealing with very small numbers,
	// so we just flip the value to the positive axis and it should be fine.
	return abs(st.average + st.stdeviation * x);
}

double normalDistValue(double avg, double stdev) {
	return normalDistValue(makeNormalStats(avg,stdev));
}

normalStats makeNormalStats(double avg, double std) {
	struct normalStats ns;
	ns.average = avg; ns.stdeviation = std;
	return ns;
}
