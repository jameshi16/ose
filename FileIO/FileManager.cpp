#include "FileManager.h"

//Boost includes
#include <boost/filesystem.hpp>

/*This function will take some time, it is a good idea to run it with a thread! (wstring, useful for directories of other languages)*/
std::vector<std::wstring> fileOperations::FindFiles(std::wstring directory, std::wstring fileType, ProgressTracker *pt)
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

/*This function will take some time, it is a good idea to run it with a thread! (non-unicode, useful for English)*/
std::vector<std::string> fileOperations::FindFiles(std::string directory, std::string fileType, ProgressTracker *pt)
{
	namespace fs = boost::filesystem; //typedef (or namespacedef, up to you)
	fs::path directoryToSearch(directory.c_str()); //defines directory to search
	std::vector<std::string> files; //create a string vector to contain the files

	fs::directory_iterator end_iter; //this is the final iterator

	if (fs::exists(directoryToSearch) && fs::is_directory(directoryToSearch))
	{
		for (fs::directory_iterator dir_iter(directoryToSearch); dir_iter != end_iter; dir_iter++) //search the directory
		{
			if (fs::is_regular_file(dir_iter->status())) //if the directory found is a file
			{
				if (fileType != "" && dir_iter->path().filename().string().find(fileType) != std::string::npos) //and contains the fileType
				{
					files.push_back(dir_iter->path().string()); //pushes back the file into the file array
				}
			}
		}
	}

	return files; //returns files.
}

void fileOperations::readFile(std::string file, readingFunction rf, ProgressTracker *pt)
{
	*pt << std::string("Reading file ") + file; //reports to progress tracker
	rf(file, pt); //gives the process to the reading function.
}

void fileOperations::readFiles(std::vector<std::string> files, readingFunction rf, ProgressTracker *pt)
{
	//This function will loop thorugh every single file through readFile (WARNING: THIS FUNCTION WILL TAKE SOME TIME, RUN ON THREAD!)
	for (unsigned int n_entries = 0; n_entries < files.size(); n_entries++)
		readFile(files[n_entries], rf, pt); //reads every single one file.
}