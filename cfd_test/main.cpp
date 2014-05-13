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
#include <ctime>
#include <fstream>


int main(){


	std::string input_file = "input.txt";
	grid* main_grid    = new grid(input_file);


	clock_t begin = std::clock();
	if (main_grid->get_test_id() == grid::en_input_output){
		tests::test_input_output(main_grid);
	}
	if (main_grid->get_test_id() == grid::en_sor ||
	    main_grid->get_test_id() == grid::en_adi){
		// Do it ten times for more accurate timing
		for (int idx;idx<10;++idx){
		tests::test_solver(main_grid);
		}
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
	clock_t end = std::clock();
	double elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;

	std::ofstream time_file;
	time_file.open("timing.dat");
	time_file << elapsed_secs << std::endl;
	time_file.close();


	return 0;
}

