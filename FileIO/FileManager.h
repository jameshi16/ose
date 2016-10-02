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
	std::vector<std::wstring> FindFiles(std::string directory, std::wstring fileType, ProgressTracker *pt = 0); //find files
	//std::vector<std::string> FindFiles(std::string directory, std::wstring fileType, ProgressTracker *pt = 0); //find files
	//^ I need to implement the above
};

#endif //File Manager.