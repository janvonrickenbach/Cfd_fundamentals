/*
 * main.cpp

 *
 *  Created on: Feb 28, 2014
 *      Author: jan
 */
#include "grid.h"
#include "variable.h"
#include <iostream>
#include <string>
#include "tests.h"




int main(){


	std::string input_file = "input.txt";
	grid* main_grid    = new grid(input_file);

	if (main_grid->get_test_id() == grid::en_input_output){
		tests::test_input_output(main_grid);
	}
	if (main_grid->get_test_id() == grid::en_sor ||
	    main_grid->get_test_id() == grid::en_adi){
		tests::test_solver(main_grid);
	}

	if (main_grid->get_test_id() == grid::en_euler){
		tests::test_euler(main_grid);
	}

	if ((main_grid->get_test_id() == grid::en_cavity_sor)
	 || (main_grid->get_test_id() == grid::en_cavity_adi)){
		tests::test_cavity(main_grid);
	}

	if (main_grid->get_test_id() == grid::en_TDM){
		tests::test_TDM(main_grid);
	}

	return 0;
}

