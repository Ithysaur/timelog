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
#define HOME_DIRECTORY "users/"
#else
#define ROOT_DIRECTORY "/"
#define HOME_DIRECTORY "home/"
#endif

enum clearOptions
{
	CLEAR_TIMES,
	CLEAR_REPORTS,
	CLEAR_ALL
};

void clear(clearOptions clearInput, const std::string& user);
std::vector<unsigned int> processLog(std::ifstream& logname);
void reportTimelog(std::string filename, std::string username);
void printUsage();
#endif