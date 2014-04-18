/*
 * utils.h
 *
 *  Created on: Apr 18, 2014
 *      Author: jan
 */

#ifndef UTILS_H_
#define UTILS_H_

class variable;
class grid;

namespace utils {
 void set_vort_bc(variable* vort, variable* sf,int nx,int ny, double dx, double dy);
 void get_velocities(variable* sf, variable* uvel,variable* vvel,grid* main_grid);
}

#endif /* UTILS_H_ */
