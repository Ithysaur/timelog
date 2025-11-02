#ifndef MAIN_H
#define MAIN_H
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>

enum clearOptions
{
	CLEAR_TIMES,
	CLEAR_REPORTS,
	CLEAR_ALL
};

const void clear(clearOptions clearInput, const std::string& user);
std::vector<unsigned int> processLog(std::ifstream& logname);
const void printUsage();
#endif