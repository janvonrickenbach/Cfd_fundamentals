/*
 * variable.h
 *
 *  Created on: Mar 14, 2014
 *      Author: jan
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "grid.h"
#include <string>
class vector;

class variable {
public:
	variable(grid* grid_in,grid::var_enum var,std::string name);
	void read_from_file(int iter);
	void write_to_file(int iter) const;
	double get_value(const int& ix,const int& iy) const;
	void set_value(double val,int ix,int iy);
	grid::var_enum get_enum(){return _en_name;}
	std::string get_name(){return _name;}
	void copy(variable *var);
	virtual ~variable();
	std::vector<double> _grid_vector;
private:
	grid* _agrid;
	int _nx, _ny;
	grid::var_enum _en_name;
	std::string _name;
};

#endif /* VARIABLE_H_ */
