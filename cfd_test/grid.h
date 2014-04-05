/*
 * grid.h
 *
 *  Created on: Feb 28, 2014
 *      Author: jan
 */

#ifndef GRID_H_
#define GRID_H_
#include <vector>
#include <map>
#include<string>
class variable;


class grid{
public:
	enum var_enum {en_x,en_y,en_sf,en_sf_src,en_vort,en_vort_new,en_vort_src};
	enum source_enum {from_file,en_fun};
	enum test_enum {en_input_output,en_sor,en_euler};
	grid(std::string);
	int get_nx();
	int get_ny();
	double get_dx(){return _dx;}
	double get_dy(){return _dy;}
	double get_Lx(){return _Lx;}
	double get_Ly(){return _Ly;}
	double get_test_id(){return _test_id;}
	void add_var(variable* var);
	variable* get_var(var_enum var);
	virtual ~grid();
	double get_input(std::string);
protected:
	std::map<std::string,double> _input_map;
	int _nx, _ny;
	test_enum _test_id;
	double _Lx, _Ly, _dx, _dy;
	std::map <var_enum,variable*> _var_map;
};

#endif /* GRID_H_ */
