#ifndef INTERFACE_H
#define INTERFACE_H

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <cstdlib> 
#include <vector> 
#include "reader.hpp"
#include "aes.hpp"
#include "io.hpp"
#include "utils.hpp"


extern word w[4*(Nr+1)]; 
char const * const menutxt[] = {"1: Home", "2: Search", "3: Add", "4: List", "Q: Quit"};
char const * const registertxt[] = {"Content : ", "  User :  ", "Password :"};

void design(std::string page);

#endif