/*
 * solverADI.h
 *
 *  Created on: Apr 18, 2014
 *      Author: jan
 */

#ifndef SOLVERADI_H_
#define SOLVERADI_H_

#include "solver.h"
#include<vector>

class grid;
class variable;
namespace solver_tools{
	void solveTDM(const std::vector<double>& diagonal_a
			     ,const std::vector<double>& diagonal_b
			     ,std::vector<double>& diagonal_c
			     ,std::vector<double>& rhs);
}

class solverADI: public solver {
public:
	solverADI(double tolerance,grid* grid);
	virtual ~solverADI();
	virtual int solve();

protected:

	variable* _var_int;
	std::vector<double> _diagonal_a;
	std::vector<double> _diagonal_b;
	std::vector<double> _diagonal_c;
	std::vector<double> _rhs;
};

#endif /* SOLVERADI_H_ */
