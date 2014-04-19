/*
 * equation.cpp
 *
 *  Created on: Mar 14, 2014
 *      Author: jan
 */

#include "equation.h"
#include "variable.h"
#include "solver.h"

equation::equation(variable* var, variable* source, solver* solver):
  _var(var),_source(source),_solver(solver){
	_solver->set_equation(this);


}

int equation::update(){
	return _solver->solve();

}

equation::~equation() {
	// TODO Auto-generated destructor stub
}

