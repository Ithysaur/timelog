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

		if (!std::filesystem::exists(std::string(ROOT_DIRECTORY) + "Users/" + username))
		{
			std::cerr << "error: user does not exist" << std::endl;
			return 2;
		}

		if (!std::filesystem::exists(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/times"))
		{
			std::filesystem::create_directories(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/times");
		}

		if (!std::filesystem::exists(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/reports"))
		{
			std::filesystem::create_directories(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/reports");
		}

		static const std::string flag = std::string(argv[2]);
		static const std::string arg3 = std::string(argv[3]);

		if (flag == "--log" || flag == "-l")
		{
			static std::ofstream log(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/times/" + arg3 + ".txt", std::ios::app);

			if (!log.is_open())
			{
				std::cerr << "error: could not open or failed to create specified log file" << std::endl;
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
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(std::string(ROOT_DIRECTORY) + "Users/" + username + "/log/timelog/times"))
				{
					reportTimelog(entry.path().filename().string(), username);
				}
				return 0;
			}
			else
			{
				reportTimelog(arg3 + ".txt", username);
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