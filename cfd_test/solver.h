/*
 * solver.h
 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

#ifndef SOLVER_H_
#define SOLVER_H_
class equation;
class grid;

class solver {
public:
	solver(double tolerance, grid* grid);
	virtual void set_equation(equation* equation){_equation = equation;}
	virtual int solve() = 0;
	virtual ~solver();
protected:
	equation* _equation;
	grid*  _grid;
	double _tolerance;
};

#endif /* SOLVER_H_ */
