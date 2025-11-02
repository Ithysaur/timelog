#include "main.h"

int main(int argc, char* argv[])
{
	#ifndef N_DEBUG
	try {
	#endif

		if (argc != 4)
		{
			printUsage();
			return 1;
		}

		static const std::string username = std::string(argv[1]);

		if (!std::filesystem::exists("C:\\Users\\" + username))
		{
			std::cerr << "error: user does not exist" << std::endl;
			return 2;
		}

		if (!std::filesystem::exists("C:\\Users\\" + username + "\\log\\timelog\\times"))
		{
			std::filesystem::create_directories("C:\\Users\\" + username + "\\log\\timelog\\times");
		}

		if (!std::filesystem::exists("C:\\Users\\" + username + "\\log\\timelog\\reports"))
		{
			std::filesystem::create_directories("C:\\Users\\" + username + "\\log\\timelog\\reports");
		}

		static const std::string flag = std::string(argv[2]);
		static const std::string arg3 = std::string(argv[3]);

		if (flag == "--log" || flag == "-l")
		{
			static std::ofstream log("C:\\Users\\" + username + "\\log\\timelog\\times\\" + arg3 + ".txt", std::ios::app);

			if (!log.is_open())
			{
				std::cerr << "error: could not open specified log file" << std::endl;
				return 3;
			}

			log << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "\n";
			log.close();

			return 0;
		}

		if (flag == "--report" || flag == "-r")
		{
			if (arg3 == "all")
			{
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("C:\\Users\\" + username + "\\log\\timelog\\times"))
				{
					std::ifstream log(entry.path());

					if (!log.is_open())
					{
						std::cerr << "error: could not open log file" << std::endl;
						return 3;
					}

					std::ofstream report("C:\\Users\\" + username + "\\log\\timelog\\reports\\" + entry.path().filename().string());
					//std::cout << "lol" << std::endl;
					if (!report.is_open())
					{
						std::cerr << "error: could not open report file" << std::endl;
						return 4;
					}

					std::vector<unsigned int> reportResults = processLog(log);
					log.close();
					const unsigned short reportSize = reportResults.size();
					unsigned short minimum = reportResults[0];
					unsigned short maximum = 0;
					float mean = 0;
					float stddev = 0;

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
					}

					for (const unsigned short& item : reportResults)
					{
						stddev += abs((mean - item) / reportSize);
					}

					report << "Report of " << entry.path().filename().string() << std::endl;
					report << "Entries: " << reportSize << std::endl;
					report << "Average time: " << mean << " seconds" << std::endl;
					report << "Maximum time: " << maximum << " seconds" << std::endl;
					report << "Minimum time: " << minimum << " seconds" << std::endl;
					report << "Standard Deviation: " << stddev << " seconds" << std::endl;
					report << std::endl;
					report << "Full report:" << std::endl;

					for (const unsigned short& item : reportResults)
					{
						report << item << " seconds" << std::endl;
					}

					report.close();
				}
				return 0;
			}
			else
			{
				static std::ifstream log("C:\\Users\\" + username + "\\log\\timelog\\times\\" + arg3 + ".txt");

				if (!log.is_open())
				{
					std::cerr << "error: could not open specified log file" << std::endl;
					return 3;
				}

				static std::ofstream report("C:\\Users\\" + username + "\\log\\timelog\\reports\\" + arg3 + ".txt");

				if (!report.is_open())
				{
					std::cerr << "error: could not open report file" << std::endl;
					return 4;
				}

				static std::vector<unsigned int> reportResults = processLog(log);
				log.close();
				static const unsigned short reportSize = reportResults.size();
				static unsigned short minimum = reportResults[0];
				static unsigned short maximum = 0;
				static unsigned short mean = 0;
				static unsigned short stddev = 0;

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
				}

				for (const unsigned short& item : reportResults)
				{
					stddev += abs((mean - item) / reportSize);
				}

				report << "Report of " << arg3 << std::endl;
				report << "Entries: " << reportSize << std::endl;
				report << "Average time: " << mean << " seconds" << std::endl;
				report << "Maximum time: " << maximum << " seconds" << std::endl;
				report << "Minimum time: " << minimum << " seconds" << std::endl;
				report << "Standard Deviation: " << stddev << " seconds" << std::endl;
				report << std::endl;
				report << "Full report:" << std::endl;
				
				for (const unsigned short& item : reportResults)
				{
					report << item << " seconds" << std::endl;
				}

				report.close();
				return 0;
			}
		}

		if (flag == "--clear" || flag == "-c")
		{
			if (argc != 4)
			{
				printUsage();
				return 1;
			}
			if (arg3 == "all")
			{
				clear(CLEAR_ALL, username);
				return 0;
			}
			else if (arg3 == "times")
			{
				clear(CLEAR_TIMES, username);
				return 0;
			}
			else if (arg3 == "reports")
			{
				clear(CLEAR_REPORTS, username);
				return 0;
			}
			else
			{
				printUsage();
				return 1;
			}
		}

		printUsage();
		return 1;
	#ifndef N_DEBUG
	} catch (short e) 
	{
		std::cout << "Exception caught: " << e << std::endl;
	}
	#endif
}