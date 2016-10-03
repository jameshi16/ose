#ifndef FileManager
#define FileManager

//Standard includes
#include <iostream>
#include <vector>
#include <string>

//ProgressTracker include
#include "../ProgressTracker.h"

namespace fileOperations
{
	std::vector<std::wstring> FindFiles(std::wstring directory, std::wstring fileType, ProgressTracker *pt = 0); //find files
	std::vector<std::string> FindFiles(std::string directory, std::string fileType, ProgressTracker *pt = 0); //find files
};

#endif //File Manager.