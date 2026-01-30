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

void reportTimelog(std::string filename, std::string username)
{
	static std::ifstream log(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/times/" + filename);

	if (!log.is_open())
	{
		std::cerr << "error: could not open specified log file" << std::endl;
		return;
	}

	static std::ofstream report(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/reports/" + filename + ".txt");

	if (!report.is_open())
	{
		std::cerr << "error: could not open report file" << std::endl;
		return;
	}

	static std::vector<unsigned int> reportResults;
	static std::vector<std::chrono::zoned_time<std::chrono::seconds>> reportTimestamps;

	{//fill in times and timestamps
		static std::string startTime;
		static std::string stopTime;
		unsigned short currentLine = 0;

		while (std::getline(log, startTime))
		{	
			reportTimestamps.emplace_back(std::chrono::current_zone(), std::chrono::sys_time<std::chrono::seconds>{std::chrono::seconds(std::stoi(startTime))});
			currentLine++;

			if (!std::getline(log, stopTime) || stopTime == "")
			{
				std::cout << "warning: log file has odd number of entries, ignoring last entry" << std::endl;
				break;
			}

			reportResults.emplace_back(std::stoi(stopTime) - std::stoi(startTime));
		}
	}

	log.close();

	if (reportResults.size() != reportTimestamps.size())
	{
		std::cerr << "error: report data size mismatch" << std::endl;
		return;
	}

	static const unsigned short reportSize = reportResults.size();
	static unsigned short minimum = reportResults[0];
	static unsigned short maximum = 0;
	static float mean = 0;
	static float stddev = 0;
	static unsigned short total = 0;

	for (const unsigned short& item : reportResults)
	{
		if (item > maximum)
		{
			maximum = item;
		}
		else if (item < minimum)
		{
			minimum = item;
		}

		mean += item / reportSize;
		total += item;
	}

	for (const unsigned short& item : reportResults)
	{
		stddev += abs((mean - item) / reportSize);
	}

	report << "Report of " << filename << std::endl;
	report << "Entries: " << reportSize << std::endl;
	report << "Total time: " << total / 3600 << " hours" << std::endl;
	report << "Average time: " << mean /   60 << " minutes" << std::endl;
	report << "Maximum time: " << maximum / 60 << " minutes" << std::endl;
	report << "Minimum time: " << minimum / 60 << " minutes" << std::endl;
	report << "Standard Deviation: " << stddev / 60 << " minutes" << std::endl;
	report << std::endl;
	report << "Full report:" << std::endl;

	for (unsigned int i = 0; i < reportResults.size(); i++)
	{
		report << reportTimestamps[i] << ":" << reportResults[i] / 60 << " minutes" << std::endl;
	}

	report.close();
	return;
}

void printUsage()
{
	std::cerr << "valid usage: timelog <username> --log <logname> | --report [logname|all] | --clear [all|times|reports]" << std::endl;
}