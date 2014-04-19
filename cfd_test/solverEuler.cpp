/*
 * solverEuler.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

#include "solverEuler.h"
#include "variable.h"
#include "grid.h"
#include "equation.h"

solverEuler::solverEuler(double tolerance,grid* grid,double dt,double visc):
         solver::solver(tolerance,grid),
         _dt(dt),_visc(visc){

}

int solverEuler::solve() {
	variable* sf       = _grid->get_var(grid::en_sf);
	variable* vort_new = _grid->get_var(grid::en_vort_new);

	variable* vort     = _equation->get_var();

	variable* vort_src = _equation->get_source();

	double new_vort;

	double rhs;
	double dx = _grid->get_dx();
	double dy = _grid->get_dy();

	for (int iy=1;iy < _grid->get_ny()-1;++iy){
		for(int ix=1;ix < _grid->get_nx()-1;++ix){
	        rhs =  -(  sf->get_value(ix,iy+1) -   sf->get_value(ix,iy-1))
	        	 *  (vort->get_value(ix+1,iy) - vort->get_value(ix-1,iy)) / (4.0*dx*dx);
	        rhs += (   sf->get_value(ix+1,iy) -   sf->get_value(ix-1,iy))
	        	 *  (vort->get_value(ix,iy+1) - vort->get_value(ix,iy-1)) / (4.0*dy*dy);

	        rhs += _visc * (vort->get_value(ix-1,iy) + vort->get_value(ix+1,iy)
	        		 -2.0 * vort->get_value(ix,iy))/ (dx*dx);
	        rhs += _visc * (vort->get_value(ix,iy-1) + vort->get_value(ix,iy+1)
	        		 -2.0 * vort->get_value(ix,iy))/ (dy*dy);
	        rhs += vort_src->get_value(ix,iy);
	        new_vort = vort->get_value(ix,iy) + _dt * rhs;
	        vort_new->set_value(new_vort,ix,iy);

		}
	}

	vort->copy(vort_new);
	return 0;
}

solverEuler::~solverEuler() {
	// TODO Auto-generated destructor stub
}

