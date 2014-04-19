/*
 * solverEuler.h
 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

#ifndef SOLVEREULER_H_
#define SOLVEREULER_H_

#include "solver.h"
class grid;

class solverEuler: public solver {
public:
	solverEuler(double tolerance, grid* grid,double dt,double visc);
	virtual int solve();
	virtual ~solverEuler();
protected:
	double _dt;
	double _visc;
};

#endif /* SOLVEREULER_H_ */
