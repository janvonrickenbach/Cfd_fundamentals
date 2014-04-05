/*
 * tests.h

 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

class main_grid;

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
