/*
 * tests.h

 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

class grid;
#include "solver.h"
#include "solverSOR.h"
#include "solverEuler.h"
#include "equation.h"

void test_input_output(grid* main_grid){

	variable* sf = new variable(main_grid,grid::en_sf,"streamfunction");

	sf->read_from_file(0);
	for (auto& val : sf->_grid_vector){
	 	val = val*2;
	}
	sf->write_to_file(1);

	delete main_grid;
	delete sf;
}

void test_sor(grid* main_grid){

	solver* sol_sor = new solverSOR(main_grid->get_input("tol"),main_grid,
			                        main_grid->get_input("omega"));
	variable* sf    = new variable(main_grid,grid::en_sf,"streamfunction");

	sf->read_from_file(0);

	variable* sf_src = new variable(main_grid,grid::en_sf_src,"stream_source");
	equation* eq     = new equation(sf,sf_src,sol_sor);
	sf_src->read_from_file(0);

	eq->update();

	sf->write_to_file(1);

	delete sol_sor;
	delete sf;
	delete sf_src;
	delete eq;
}

void test_euler(grid* main_grid){

	solver* sol_eul = new solverEuler(main_grid->get_input("tol"),main_grid,
									  main_grid->get_input("dt"),
									  main_grid->get_input("visc"));
	variable* sf        = new variable(main_grid,grid::en_sf,"streamfunction");
	variable* vort      = new variable(main_grid,grid::en_vort,"vorticity");
	variable* vort_new  = new variable(main_grid,grid::en_vort_new,"vorticity_new");

	vort->read_from_file(0);
	sf->read_from_file(0);

	variable* vort_src = new variable(main_grid,grid::en_vort_src,"vort_source");
	equation* eq       = new equation(sf,vort_src,sol_eul);
	vort_src->read_from_file(0);

	eq->update();

	vort->write_to_file(1);

	delete sol_eul;
	delete sf;
	delete vort;
	delete vort_new;
	delete vort_src;
	delete eq;
}

