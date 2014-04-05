/*
 * exceptions.h
 *
 *  Created on: Apr 5, 2014
 *      Author: jan
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>


class failed_to_open_file: public std::exception{
   virtual const char* what() const throw();
};


#endif /* EXCEPTIONS_H_ */
