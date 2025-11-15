#include "main.h"

void clear(clearOptions clearInput, const std::string& user)
{
	switch (clearInput)
	{
	case CLEAR_ALL:
		std::filesystem::remove_all(std::string(ROOT_DIRECTORY) + "Users/" + user + "/log/timelog");
		std::filesystem::create_directories(std::string(ROOT_DIRECTORY) + "Users/" + user + "/log/timelog");
		break;
	case CLEAR_TIMES:
		std::filesystem::remove_all(std::string(ROOT_DIRECTORY) + "Users/" + user + "/log/timelog/times");
		std::filesystem::create_directories(std::string(ROOT_DIRECTORY) + "Users/" + user + "/log/timelog/times");
		break;
	case CLEAR_REPORTS:
		std::filesystem::remove_all(std::string(ROOT_DIRECTORY) + "Users/" + user + "/log/timelog/reports");
		std::filesystem::create_directories(std::string(ROOT_DIRECTORY) + "Users/" + user + "/log/timelog/reports");
		break;
	}
}

std::vector<unsigned int> processLog(std::ifstream& logname)
{
	std::vector<unsigned int> reportData;
	static std::string startTime;
	static std::string stopTime;
	unsigned short currentLine = 0;

	while (std::getline(logname, startTime))
	{
		currentLine++;

		if (!std::getline(logname, stopTime) || stopTime == "")
		{
			std::cout << "warning: log file has odd number of entries, ignoring last entry" << std::endl;
			break;
		}

		reportData.emplace_back(std::stoi(stopTime) - std::stoi(startTime));
	}

	return reportData;
}

void printUsage()
{
	std::cerr << "valid usage: timelog <username> --log <logname> | --report [logname|all] | --clear [all|times|reports]" << std::endl;
}