/*
 * equation.h
 *
 *  Created on: Mar 14, 2014
 *      Author: jan
 */

#ifndef EQUATION_H_
#define EQUATION_H_

class variable;
class solver;
#include "grid.h"


class equation {
public:
	equation(variable* var, variable* source,solver* solver);

    int update();
	virtual ~equation();
	variable* get_var(){return _var;}
	variable* get_source(){return _source;}
protected:
	variable* _var;
	variable* _source;
	solver* _solver;
};

#endif /* EQUATION_H_ */
