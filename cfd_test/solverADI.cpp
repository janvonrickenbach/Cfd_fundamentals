/*
 * solverADI.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: jan
 */

#include "solverADI.h"
#include "grid.h"

void solver_tools::solveTDM(std::vector<double>& diagonal_a
	     	 	 	 	   ,std::vector<double>& diagonal_b
	                       ,std::vector<double>& diagonal_c
	                       ,std::vector<double>& rhs){

	// RHS is also used as the solution vector

	int n = rhs.size() - 1;

	diagonal_c[0] /= diagonal_b[0];
	rhs[0]        /= diagonal_b[0];

	for(int i=1;i<n;++i){
		diagonal_c[i] /= diagonal_b[i] - diagonal_a[i]*diagonal_c[i-1];
		rhs[i]         = (rhs[i] - diagonal_a[i]*rhs[i-1]) /
				         (diagonal_b[i] - diagonal_a[i]*diagonal_c[i-1]);
	}

	rhs[n] = (rhs[n] - diagonal_a[n] * rhs[n-1] ) /
			 (diagonal_b[n] - diagonal_a[n] * diagonal_c[n-1]);

	for (int i=n; i>= 0; --i){
		rhs[i] -= diagonal_c[i]* rhs[i+1];
	}
}


solverADI::solverADI(double tolerance,grid* grid): solver(tolerance,grid) {
	// TODO Auto-generated constructor stub

}

solverADI::~solverADI() {
	// TODO Auto-generated destructor stub
}

