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
		test_input_output(main_grid);
	}
	if (main_grid->get_test_id() == grid::en_sor){
		test_sor(main_grid);
	}

	if (main_grid->get_test_id() == grid::en_euler){
		test_euler(main_grid);
	}

	return 0;
}

