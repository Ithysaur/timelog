#ifndef MAIN_H
#define MAIN_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>

#ifdef _MSC_VER
#define ROOT_DIRECTORY "C:/"
#else
#define ROOT_DIRECTORY "/"
#endif

enum clearOptions
{
	CLEAR_TIMES,
	CLEAR_REPORTS,
	CLEAR_ALL
};

void clear(clearOptions clearInput, const std::string& user);
std::vector<unsigned int> processLog(std::ifstream& logname);
void printUsage();
#endif