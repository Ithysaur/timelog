#include "main.h"

int main(int argc, char* argv[])
{
	#ifndef N_DEBUG
	try {
	#endif
		if (argc != 3)
		{
			std::cerr << "error: unexpected number of inputs" << std::endl;
			return 1;
		}
		
		if (std::string(argv[2]) == "clear")
		{
			std::filesystem::remove_all("C:\\Users\\" + std::string(argv[1]) + "\\log\\timelog");
			std::filesystem::create_directories("C:\\Users\\" + std::string(argv[1]) + "\\log\\timelog");
			
			return 0;
		}

		static std::ofstream log("C:\\Users\\" + std::string(argv[1]) + "\\log\\timelog\\" + std::string(argv[2]) + ".txt", std::ios::app);

		if (!log.is_open())
		{
			std::cerr << "error: could not open log file" << std::endl;
			return 2;
		}
		
		log << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "\n";
		log.close();
	#ifndef N_DEBUG
	} catch (short e) 
	{
		std::cout << "Exception caught: " << e << std::endl;
	}
	#endif

	return 0;
}