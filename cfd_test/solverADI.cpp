/*
 * solverADI.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: jan
 */

#include "solverADI.h"
#include "grid.h"
#include "equation.h"
#include "variable.h"
#include <cmath>
#include <iostream>

void solver_tools::solveTDM(const std::vector<double>& diagonal_a
	     	 	 	 	   ,const std::vector<double>& diagonal_b
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

	for (int i=n; i-- >0;){
		rhs[i] -= diagonal_c[i]* rhs[i+1];
	}
}


solverADI::solverADI(double tolerance,grid* grid): solver(tolerance,grid) {
	int diag_size = _grid->get_nx()-2;
	_diagonal_a.resize(diag_size,0.0);
	_diagonal_b.resize(diag_size,0.0);
	_diagonal_c.resize(diag_size,0.0);
	_rhs.resize(diag_size,0.0);
	_var_int = new variable(grid,grid::en_var_int,"var_int");

}

solverADI::~solverADI() {
	delete _var_int;
}

int solverADI::solve() {
	// This routine assumes dx=dy=h
	const double dx = _grid->get_dx();
	const double nx = _grid->get_nx();
	const double ny = _grid->get_ny();
	const double term1 = 4.0*pow(cos(0.5*M_PI*dx),2);
	const double term2 = pow(tan(0.5*M_PI*dx),2);
	const int pmax     = std::max(1,(int)(0.5*log10(term2)/log10(sqrt(2.0)-1.0)));

	variable* var = _equation->get_var();
	variable* src = _equation->get_source();


	int p=0;

	const int maxiter = 10000;
	const double abstol = 1E-10;

	int    iter=0;
	double tol =1;
	double rho;

	for (auto& item : _diagonal_a) item = -1.0;
	for (auto& item : _diagonal_c) item = -1.0;

	_var_int->copy(var);

	while(_tolerance < tol && iter < maxiter){
		iter = iter + 1;

		p = p + 1;
		if(p== (pmax+1)) p=1;

		// Update relaxation coefficient
		rho = term1*pow(term2,(2.0*p-1.0)/(2.0*pmax));
		tol = 0.0;
		// Update relaxation coefficient and diagonal
		for (auto& item : _diagonal_b) item = 2.0*(1.0+rho);


		// First ADI half step
		for (int iy=1;iy<ny-1;++iy){

			// Set rhs
			for(int ix=1;ix<nx-1;++ix){

				_rhs[ix-1] = var->get_value(ix,iy+1)
						   - 2.0*(1.0-rho)*var->get_value(ix,iy)
						   + var->get_value(ix,iy-1)
						   - src->get_value(ix,iy) * dx * dx;
			}
			// Boundary conditions
			_rhs[0]    += var->get_value(0,iy);
			_rhs[nx-3] += var->get_value(nx-1,iy);

			// Solve linear system
		    solver_tools::solveTDM(_diagonal_a,_diagonal_b,_diagonal_c,_rhs);
	        for (auto& item : _diagonal_c) item = -1.0;

			// Get tolerance and update solution
			for(int ix=1;ix<nx-1;++ix){
//				tol = std::max(std::abs((var->get_value(ix,iy)-_rhs[ix-1])
//				              /(var->get_value(ix,iy)+abstol)),tol);
				tol = std::max(std::abs(var->get_value(ix,iy)-_rhs[ix-1]),tol);
				_var_int->set_value(_rhs[ix-1],ix,iy);
			}
		}

		// Second ADI half step
		for (int ix=1;ix<nx-1;++ix){

			// Set rhs
			for(int iy=1;iy<ny-1;++iy){

				_rhs[iy-1] = _var_int->get_value(ix+1,iy)
						   - 2.0*(1.0-rho)*_var_int->get_value(ix,iy)
						   + _var_int->get_value(ix-1,iy)
						   - src->get_value(ix,iy) * dx * dx;
			}
			// Boundary conditions
			_rhs[0]    += _var_int->get_value(ix,0);
			_rhs[ny-3] += _var_int->get_value(ix,ny-1);

			// Solve linear system
		    solver_tools::solveTDM(_diagonal_a,_diagonal_b,_diagonal_c,_rhs);
	        for (auto& item : _diagonal_c) item = -1.0;

			// Get tolerance and update solution
			for(int iy=1;iy<ny-1;++iy){
//				tol = std::max(std::abs((var->get_value(ix,iy)-_rhs[iy-1])
//				              /(var->get_value(ix,iy)+abstol)),tol);
				tol = std::max(std::abs((var->get_value(ix,iy)-_rhs[iy-1])),tol);
				var->set_value(_rhs[iy-1],ix,iy);
			}
		}

	}
	return iter;


}
