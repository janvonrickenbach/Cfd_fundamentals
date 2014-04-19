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
#include "utils.h"
#include "solverADI.h"
#include <cmath>


namespace tests{
   void test_input_output(grid* main_grid);
   void test_solver(grid* main_grid);
   void test_euler(grid* main_grid);
   void test_cavity(grid* main_grid);
   void test_TDM(grid* main_grid);


}
void tests::test_input_output(grid* main_grid){

	variable* sf = new variable(main_grid,grid::en_sf,"streamfunction");

	sf->read_from_file(0);
	for (auto& val : sf->_grid_vector){
	 	val = val*2;
	}
	sf->write_to_file(1);

	delete main_grid;
	delete sf;
}

void tests::test_solver(grid* main_grid){

	solver* sol;
	if (main_grid->get_test_id() == grid::en_sor){
	   sol = new solverSOR(main_grid->get_input("tol"),main_grid,
		    	                       main_grid->get_input("omega"));
	}
	if (main_grid->get_test_id() == grid::en_adi){
	   sol = new solverADI(main_grid->get_input("tol"),main_grid);
	}
	variable* sf    = new variable(main_grid,grid::en_sf,"streamfunction");
	sf->read_from_file(0);

	variable* sf_src = new variable(main_grid,grid::en_sf_src,"stream_source");
	sf_src->read_from_file(0);

	equation* eq     = new equation(sf,sf_src,sol);

	eq->update();

	sf->write_to_file(1);

	delete sol;
	delete sf;
	delete sf_src;
	delete eq;
}

void tests::test_euler(grid* main_grid){

	solver* sol_eul = new solverEuler(main_grid->get_input("tol"),main_grid,
									  main_grid->get_input("dt"),
									  main_grid->get_input("visc"));
	variable* sf        = new variable(main_grid,grid::en_sf,"streamfunction");
	variable* vort      = new variable(main_grid,grid::en_vort,"vorticity");
	variable* vort_new  = new variable(main_grid,grid::en_vort_new,"vorticity_new");

	vort->read_from_file(0);
	sf->read_from_file(0);

	variable* vort_src = new variable(main_grid,grid::en_vort_src,"vort_source");
	equation* eq       = new equation(vort,vort_src,sol_eul);
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


void tests::test_cavity(grid* main_grid){

	solver* sol_eul = new solverEuler(main_grid->get_input("tol"),main_grid,
									  main_grid->get_input("dt"),
									  main_grid->get_input("visc"));

	solver* sol_sf;
	if (main_grid->get_test_id() == grid::en_cavity_sor){
	   sol_sf = new solverSOR(main_grid->get_input("tol"),
			                  main_grid,main_grid->get_input("omega"));
	} else if (main_grid->get_test_id() == grid::en_cavity_adi){
		sol_sf = new solverADI(main_grid->get_input("tol"),main_grid);
	}
	variable* sf        = new variable(main_grid,grid::en_sf,"streamfunction");
	variable* vort      = new variable(main_grid,grid::en_vort,"vorticity");
	variable* vort_new  = new variable(main_grid,grid::en_vort_new,"vorticity_new");

	variable* zero_src = new variable(main_grid,grid::en_zero_src,"zero_src");
	variable* sf_src   = new variable(main_grid,grid::en_sf_src,"sf_src");

	variable* uvel = new variable(main_grid,grid::en_uvel,"uvel");
	variable* vvel   = new variable(main_grid,grid::en_vvel,"vvel");

	equation* eq_vort  = new equation(vort,zero_src,sol_eul);
	equation* eq_sf    = new equation(sf,sf_src,sol_sf);

	std::cout << "Initializing" << std::endl;
	vort->read_from_file(0);
	sf->read_from_file(0);
	sf_src->copy(vort);
	sf_src->multiply(-1.0);

	utils::set_vort_bc(vort,sf,main_grid->get_nx(),main_grid->get_nx()
			           ,main_grid->get_dx(),main_grid->get_dy());

	double t=0.0;
	double dt = main_grid->get_input("dt");
	int iter;
	int output_freq = (int) (main_grid->get_input("max_dt")) / 10;
	for (int ts=0;ts<main_grid->get_input("max_dt");++ts){
	  t = t + dt;
	  eq_vort->update();
      sf_src->copy(vort);
	  sf_src->multiply(-1.0);
      utils::set_vort_bc(vort,sf,main_grid->get_nx(),main_grid->get_nx()
			             ,main_grid->get_dx(),main_grid->get_dy());

	  iter=eq_sf->update();
      utils::get_velocities(sf,uvel,vvel,main_grid);
      if (ts%output_freq == 0  || ts==main_grid->get_input("max_dt")-1){
         vort->write_to_file(ts);
         sf->write_to_file(ts);
         sf_src->write_to_file(ts);
         uvel->write_to_file(ts);
         vvel->write_to_file(ts);
	     std::cout << "At t=" << t << std::endl;
	     std::cout << "Solver converged in " << iter << " iterations" << std::endl;
      }
	}


	delete sol_eul;
	delete sol_sf;
	delete sf;
	delete vort;
	delete vort_new;
	delete zero_src;
	delete sf_src;
	delete eq_vort;
	delete eq_sf;
}

void tests::test_TDM(grid* main_grid){



	std::vector<double> diagonal_a;
	std::vector<double> diagonal_b;
	std::vector<double> diagonal_c;
	std::vector<double> rhs;
	std::vector<double> sol;


	diagonal_a = {0,-1,-1,-1};
	diagonal_b = {4,4,4,4};
	diagonal_c = {-1,-1,-1,0};
	rhs        = {5,5,10,23};
	sol        = {2,3,5,7};

	solver_tools::solveTDM(diagonal_a,diagonal_b,diagonal_c,rhs);

	auto iter_rhs = rhs.begin();
	auto iter_sol = sol.begin();

	double error = 0.0;
	double diff  = 0.0;
	for (iter_sol = sol.begin(), iter_rhs = rhs.begin();
		 iter_sol != sol.end(); ++iter_sol, ++iter_rhs){
		 diff = *iter_sol - *iter_rhs;
		 error += pow(diff,2);
	}

	std::cout << "Error in TDM= " << error << std::endl;

}
