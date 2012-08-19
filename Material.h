/*
 * Material.h
 *
 *  Created on: Mar 6, 2012
 *      Author: leiterboss
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
using namespace std;

class Material {
private:
	string name;
	string color;
	float hardness;

public:
	Material() {this->name = "skin"; this->color = "brown"; this->hardness = 0;}
	Material(string n, string c, float h) {this->name = n; this->color = c; this->hardness=h;}
	virtual ~Material();

	string getName() {return this->name;}
	string getColor() {return this->color;}
	float getHardness() {return this->hardness;}
	void setName(string n) {this->name = n;}
	void setColor(string c) {this->color = c;}
	void setHardness(float h) {this->hardness = h;}

};

#endif /* MATERIAL_H_ */
