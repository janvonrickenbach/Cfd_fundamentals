/*
 * exceptions.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

#include "exceptions.h"

const char* failed_to_open_file::what() const throw()
{
	return "Error opening file";
}
