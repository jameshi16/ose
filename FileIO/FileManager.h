#ifndef FileManager
#define FileManager

//Standard includes
#include <iostream>
#include <vector>
#include <string>

//ProgressTracker include
#include "../ProgressTracker.h"
#include "../osuBeatmap.h"

typedef void(*readingFunction)(std::string, ProgressTracker*);

namespace fileOperations
{
	/*File finding sorcery (non-osu specific)*/
	std::vector<std::wstring> FindFiles(std::wstring directory, std::wstring fileType, ProgressTracker *pt = 0); //find files (wstring)
	std::vector<std::string> FindFiles(std::string directory, std::string fileType, ProgressTracker *pt = 0); //find files (normal string)

	/*File reading sorcery (non-osu specific)*/
	void readFile(std::string file, readingFunction, ProgressTracker *pt = 0); //reads the file using provided function (wrapper kinda function)
	void readFiles(std::vector<std::string> files, readingFunction, ProgressTracker *pt = 0); //reads all the files using provided function
};

#endif //File Manager.