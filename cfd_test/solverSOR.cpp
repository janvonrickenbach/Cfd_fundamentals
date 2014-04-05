/*
 * solverSOR.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

#include "solverSOR.h"
#include "variable.h"
#include "equation.h"
#include <cmath>

solverSOR::solverSOR(double tolerance,grid* grid, double omega):
                     solver::solver(tolerance,grid), _omega(omega){

}

void solverSOR::solve(){
	variable*  var   = _equation->get_var();
	variable* source = _equation->get_source();

	double dx= _grid->get_dx();
	double dy= _grid->get_dy();
	double tol;
	double new_val;
	double x_cont, y_cont, div;
	double abstol = 1E-10;
	double old_val;

	tol = 1.0;
    div = (2.0*(dx*dx + dy*dy));
	while(_tolerance < tol){
		tol = 0.0;
		for (int ix=1;ix<_grid->get_nx()-1;ix++){
			for(int iy=1;iy<_grid->get_ny()-1;iy++){
				x_cont =(var->get_value(ix-1,iy) +
	     				 var->get_value(ix+1,iy ))*dy*dy;

				y_cont =(var->get_value(ix ,iy-1) +
						 var->get_value(ix ,iy+1))*dx*dx;
				new_val = ((x_cont+y_cont) - source->get_value(ix,iy) *dx*dx*dy*dy)/div;
				old_val = var->get_value(ix,iy);
				new_val = (1.0-_omega) * old_val + _omega*new_val;
				tol = std::max(std::abs(new_val - old_val)/(old_val+abstol),tol);
				var->set_value(new_val,ix,iy);
			}
		}
	}

}

solverSOR::~solverSOR() {
	// TODO Auto-generated destructor stub
}

