/*
 * solverSOR.h
 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

#ifndef SOLVERSOR_H_
#define SOLVERSOR_H_

#include "solver.h"
class equation;

class solverSOR: public solver {
public:
	solverSOR(double tolerance,grid* grid, double omega);
	virtual int solve();
	virtual ~solverSOR();
protected:
	double _omega;
};

#endif /* SOLVERSOR_H_ */
