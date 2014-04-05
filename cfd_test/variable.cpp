/*
 * variable.cpp
 *
 *  Created on: Mar 14, 2014
 *      Author: jan
 */

#include <fstream>
#include <string>
#include <sstream>
#include "variable.h"
#include "grid.h"
#include "math.h"
#include "exceptions.h"


variable::variable(grid* grid_in,grid::var_enum en_name,std::string name):
  _agrid(grid_in),_en_name(en_name),_name(name){
  // More efficient to store here
  _nx = _agrid->get_nx();
  _ny = _agrid->get_ny();
  _agrid->add_var(this);
  _grid_vector.resize(_nx*_ny);

}


void variable::read_from_file(int iter) {
	  std::string line;
	  std::string filename;
	  std::stringstream ss;
	  ss << _name << "_" << iter <<".dat";
	  filename = ss.str();
	  std::fstream in_file(filename, std::ios_base::in);
	  _grid_vector.resize(0);

	  if (!in_file.is_open()){
		  throw failed_to_open_file();
	  }

	  double value;
	  while (!in_file.eof())
	  {
		 in_file >> value;
	     _grid_vector.push_back(value);
	  }
	  in_file.close();

}

void variable::write_to_file(int iter) const {
	std::ofstream out_file;
	std::stringstream filename;
	std::string fname;

	filename << _name << "_" << iter << ".dat";
	fname = filename.str();
	out_file.open(fname.c_str());
	if (!out_file.is_open()){
	  throw failed_to_open_file();
	}

	for(auto var_it=_grid_vector.begin();
		var_it != _grid_vector.end();
		++var_it){
		out_file << *var_it << " ";
	}

	out_file.close();
}

double variable::get_value(int ix, int iy) const {
	return _grid_vector[_nx*iy+ix];
}

void variable::set_value(double val,int ix, int iy) {
	_grid_vector[_nx*iy+ix] = val;
}



variable::~variable() {
}

