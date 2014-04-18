/*
 * utils.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: jan
 */
#include "utils.h"
#include "variable.h"
#include "grid.h"

namespace utils{
void set_vort_bc(variable* vort, variable* sf,int nx,int ny, double dx, double dy){

	int iy = 0;
	int ix = 0;
	double val;

	// South boundary
	for(ix=0;ix<nx;++ix){
		val = - 2.0*sf->get_value(ix,iy+1) / (dy*dy);
		vort->set_value(val,ix,iy);
	}

	// North boundary u=1
	iy = ny-1;
	for(ix=0;ix<nx;++ix){
		val = -2.0*(dy + sf->get_value(ix,iy-1)) / (dy*dy);
		vort->set_value(val,ix,iy);
	}

	// West boundary
	ix = 0;
	for(iy=0;iy<ny;++iy){
		val = - 2.0*sf->get_value(ix+1,iy) / (dx*dx);
		vort->set_value(val,ix,iy);
	}

	// East boundary
	ix = nx-1;
	for(iy=0;iy<ny;++iy){
		val = - 2.0*sf->get_value(ix-1,iy) / (dx*dx);
		vort->set_value(val,ix,iy);
	}
}

void get_velocities(variable* sf, variable* uvel,variable* vvel,grid* main_grid){

	double val;
	double dx = main_grid->get_dx();
	double dy = main_grid->get_dx();
	int nx = main_grid->get_nx();
	int ny = main_grid->get_ny();

	for (int ix=1;ix<nx-1;ix++){
				for(int iy=1;iy<ny-1;iy++){
			val = (sf->get_value(ix,iy+1) - sf->get_value(ix,iy-1))/ (2.0 * dy);
			uvel->set_value(val,ix,iy);
			val = -(sf->get_value(ix+1,iy) - sf->get_value(ix-1,iy))/ (2.0 * dx);
			vvel->set_value(val,ix,iy);
		}
	}

	for(int ix=0;ix<nx;++ix){
		uvel->set_value(1.0,ix,ny-1);
	}
}


}



