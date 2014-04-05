/*
 * grid.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: jan
 */

#include <fstream>
#include <string>
#include <map>
#include "grid.h"
#include "variable.h"
#include "exceptions.h"


grid::grid(std::string input_file){


	std::string key;
	double item;
	std::ifstream file_in;
	file_in.open(input_file.c_str());

	if (!file_in.is_open()){
		throw failed_to_open_file();
	}


	std::string line;
	while (!file_in.eof())
	{
        file_in >> key >> item;
		_input_map[key] = item;
	}
	file_in.close();

	_nx  = (int)_input_map["nx"];
	_ny  = (int)_input_map["ny"];
	_Lx  = _input_map["Lx"];
	_Ly  = _input_map["Ly"];

	_test_id = static_cast<test_enum> ((int)_input_map["test_id"]);
	variable* x_val = new variable(this,en_x,"x_coord");
	variable* y_val = new variable(this,en_y,"y_coord");

	_dx = _Lx/(_nx-1);
	_dy = _Ly/(_ny-1);

	for (int i_idx=0;i_idx < _nx;++i_idx){
		for (int j_idx=0;j_idx < _ny;++j_idx){
			x_val->set_value(i_idx*_dx,i_idx,j_idx);
			y_val->set_value(i_idx*_dy,i_idx,j_idx);
		}
	}

}

int grid::get_nx(){return _nx;}
int grid::get_ny(){return _ny;}

void grid::add_var(variable* var){
	_var_map[var->get_enum()] = var;
}


variable* grid::get_var(grid::var_enum var_name){
	return (_var_map[var_name]);
}

grid::~grid() {
	// TODO Auto-generated destructor stub
}

double grid::get_input(std::string input) {
	return _input_map[input];
}
