#ifndef DEFS_H_
#define DEFS_H_

#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>

using namespace std;

class InvalidID: public std::exception
{
    virtual const char* what() const throw(){
        return "Please enter valid id";
    }
};

class InvalidName: public std::exception
{
    virtual const char* what() const throw(){
        return "Please enter valid name";
    }
};

class InvalidInput: public std::exception
{
    virtual const char* what() const throw(){
        return "Please enter valid details";
    }
};

#endif /* DEFS_H_ */