/*
 * equation.h
 *
 *  Created on: Mar 14, 2014
 *      Author: jan
 */

#ifndef EQUATION_H_
#define EQUATION_H_

class variable;

class equation {
public:
	equation(variable* var);

	virtual ~equation();
};

#endif /* EQUATION_H_ */
