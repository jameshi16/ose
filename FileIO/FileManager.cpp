#include "FileManager.h"

//Boost includes
#include <boost/filesystem.hpp>

/*This function will take some time, it is a good idea to run it with a thread!*/
std::vector<std::wstring> fileOperations::FindFiles(std::string directory, std::wstring fileType, ProgressTracker *pt)
{
	namespace fs = boost::filesystem; //typedef (or namespacedef, up to you)
	fs::path directoryToSearch(directory.c_str()); //defines directory to search
	std::vector<std::wstring> files; //create a string vector to contain the files

	fs::directory_iterator end_iter; //this is the final iterator

	if (fs::exists(directoryToSearch) && fs::is_directory(directoryToSearch))
	{
		for (fs::directory_iterator dir_iter(directoryToSearch); dir_iter != end_iter; dir_iter++) //search the directory
		{
			if (fs::is_regular_file(dir_iter->status())) //if the directory found is a file
			{
				if (fileType != "" && dir_iter->path().filename().native().find(fileType) != std::string::npos) //and contains the fileType
				{
					files.push_back(dir_iter->path().native()); //pushes back the file into the file array
				}
			}
		}
	}

	return files; //returns files.
}