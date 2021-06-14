#ifndef INTERFACE_H
#define INTERFACE_H

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <cstdlib> 
#include <vector>
#include <conio.h>
#include <random>
#include "reader.hpp"
#include "aes.hpp"
#include "io.hpp"
#include "utils.hpp"

int COLS, LINES;
extern word w[4*(Nr+1)]; 
std::default_random_engine generator;
int menuSize = 7;
char const * const menutxt[] = {"1: Home", "2: Search", "3: Add", "4: List", "5: Modify", "6: Generate", "Q: Quit"};
char const * const gentxt[] = {"Upper case", "Lower case", "Numbers", "Special characters", "Generate"};
char const * const registertxt[] = {"Content : ", "  User :  ", "Password :"};

void design(std::string page);

void initializeWindowSize();

#endif