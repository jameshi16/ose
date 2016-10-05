#include "commandHandler.h"

//Standard headers
#include <functional>

//Boost headers
#include <boost/filesystem.hpp>

//Self headers
#include "FileIO/FileManager.h"
#include "osuBeatmap.h"

/* Needed to make the whole file work (Declaration of Commands) */
namespace Commands
{
	std::map<std::string, commandFunction> commandsAvailable =
	{ /*List of commands here*/
		std::pair<std::string, commandFunction>("lc", printAllCommands), //print all commands
		std::pair<std::string, commandFunction>("print", print), //print all arguments
		std::pair<std::string, commandFunction>("testTag", testTaggingOnFile), //test tagging on a single file
		std::pair<std::string, commandFunction>("testOsuTag", testOsuTag) //test tag on osu directory
	}; //pretty cool, right?
}

/* Command Handler */
CommandHandler::CommandHandler()
{
	//ctor
}

CommandHandler::CommandHandler(std::string s, ProgressTracker *pt)
{
	processCommand(s, pt);
}

void CommandHandler::processCommand(std::string command, ProgressTracker *pt)
{
	//Process Command.
	using namespace Commands;

	Arguments a_arg; //declare argument

	//First, split the command from the arguments.
	if (command.find(" ", 0) != std::string::npos) //nested if
	{
		a_arg.setFullArgument(command.substr(command.find(" ", 0) + 1, command.length() - command.find(" ", 0)));
		command = command.substr(0, command.find(" ", 0));
	}

	if (commandsAvailable.count(command) != 0 && commandsAvailable.count(command) == 1)
	{
		//launches the command
		commandFunction cf = commandsAvailable[command]; //gets the command
		cf(pt, a_arg); //plays the command
		*pt << "";
		return;
	}
	if (commandsAvailable.count(command) == 0)
	{
		//report to progress tracker
		*pt << "Error processing command: Command not found";
		*pt << "Try using lc";
		*pt << "";
		return;
	}
	if (commandsAvailable.count(command) > 1)
	{
		//report to progress tracker
		*pt << "Error processing command: Lazy programmer forgot to check code";
		*pt << "";
		return;
	}
	*pt << "Error processing command: EOF reached.";
	*pt << "";
}

CommandHandler::~CommandHandler()
{
	//dtor
}

/* Arguments */
Arguments::Arguments(){ }; //NoConstruct
Arguments::~Arguments() { }; //Don't have to destroy anything here

Arguments::Arguments(std::string s)
{
	//sets the full argument
	setFullArgument(s);
}

void Arguments::setFullArgument(std::string s)
{
	s_fullArgument = s; //sets the full argument
	splitArguments(); //splits the arguments into meaningful arguments
}

std::string Arguments::getFullArgument()
{
	return s_fullArgument;
}

std::string Arguments::getArgument(int iii)

{
	return v_Arguments[iii];
}

void Arguments::setArgument(int iii, std::string s)
{
	v_Arguments[iii] = s; //very simple and fast way (error handling and everything done by vector class)
}

void Arguments::splitArguments()
{
	//Begin spliting arguments
	std::string buffer = s_fullArgument; //sets full argument

	int n_lastPosition = 0; //sets last position
	while (buffer.find(" ", n_lastPosition) != std::string::npos) //this is the while loop
	{
		if ((buffer[buffer.find(" ", n_lastPosition) - 1] != ' ' || buffer[buffer.find(" ", n_lastPosition) - 1] != '\0') && (buffer.find("\"") != string::npos) && (buffer.find("\"", n_lastPosition) < buffer.find(" ", n_lastPosition))) //if quotes are found
		{
			v_Arguments.push_back(buffer.substr(buffer.find("\"", n_lastPosition) + 1, buffer.find("\"", buffer.find("\"", n_lastPosition) + 1) - buffer.find("\"", n_lastPosition) - 1)); //finds arguments within a quote
			n_lastPosition = buffer.find("\"", n_lastPosition + 1) + 1; //sets n_lastPosition to the latest position
			continue; //don't process the things below
		}
		if (buffer[buffer.find(" ", n_lastPosition) - 1] != ' ' || buffer[buffer.find(" ", n_lastPosition) - 1] != '\0') //if the character next to found "space" is blank, or if the argument found before "space" is blank
		{
			v_Arguments.push_back(removeAllSpaces(buffer.substr(n_lastPosition, buffer.find(" ", n_lastPosition) - n_lastPosition))); //pushes back this anonymous string
			n_lastPosition = buffer.find(" ", n_lastPosition) + 1; //sets n_lastPosition to the latest position
		}
		else
		{
			buffer.erase(n_lastPosition + 1, 1); //erases the blank and tries to find more arguments
		}
	}
	//This is for the last argument.
	std::string lastArgumentBuffer = "";
	n_lastPosition = 0;

	if (buffer.find(" "), 0 != std::string::npos)
	{
		//If it does find " "
		lastArgumentBuffer = buffer.substr(buffer.find_last_of(" ") + 1, buffer.length() - buffer.find_last_of(" ")); //the last space represents the last argument
	}
	else
	{
		//If it doesn't find " "
		lastArgumentBuffer = buffer; //the whole thing is the last argument
	}

	if (removeAllSpaces(lastArgumentBuffer) != "")
	{
		v_Arguments.push_back(removeAllSpaces(lastArgumentBuffer));
	}

	removeEmptyArguments(); //remove all the empty arguments that might be generated from this function
	//Done.
}

std::string Arguments::removeAllSpaces(std::string s)
{
	//kill all spaces
	int n_lastPosition = 0;
	while (s.find(" ", n_lastPosition) != std::string::npos)
	{
		s.erase(s.find(" ", n_lastPosition), 1);
		n_lastPosition = s.find(" ", n_lastPosition + 1);
	}

	return s;
}

void Arguments::removeEmptyArguments()
{
	for (unsigned int iii = 0; iii < v_Arguments.size(); iii++)
	{
		while (removeAllSpaces(v_Arguments[iii]) == "" && v_Arguments.size() != 0) //keeps swapping with the last element until the argument is valid (unless everything has been swapped)
		{
			v_Arguments[iii].swap(v_Arguments.back()); //swaps with the last argument
			v_Arguments.erase(v_Arguments.end()); //erases the argument at the back
		}
	}
}

int Arguments::size()
{ return v_Arguments.size(); }

/* Commands */
void Commands::printAllCommands(ProgressTracker* pt, Arguments)
{
	*pt << "List of commands:";
	for (std::map<std::string, commandFunction>::iterator it = commandsAvailable.begin(); it != commandsAvailable.end(); ++it)
	{
		*pt << it->first.c_str(); //prints the commands
	}
}

void Commands::print(ProgressTracker* pt, Arguments a)
{
	if (a.size() != 0)
	{
		for (int iii = 0; iii < a.size(); iii++)
		{
			*pt << std::string("Argument: ") + a.getArgument(iii);
		}

		*pt << std::string("Full argument passed: ") + a.getFullArgument();
	}
}

void Commands::testTaggingOnFile(ProgressTracker* pt, Arguments a)
{
	if (a.size() == 0)
	{
		*pt << "Usage: testTag <full path to music> <full path to picture>";
	}

	std::vector<std::string> Files = {}; //the object to contain the file directory

	for (int iii = 0; iii < a.size(); iii++)
	{
		if (boost::filesystem::exists(a[iii]))
		{
			Files.push_back(a[iii]);
		}
		if (Files.size() == 2) {break;}
	}

	if (Files.size())
	{
		osuBeatmap os{"TestTag", Files[1], Files[0]}; //make new os
		TagAgent().autoTag(os); //autotags os.

		*pt << "Sucessfully tagged";
	}
}

void Commands::testOsuTag(ProgressTracker* pt, Arguments a)
{
	/*Clean up block*/
	a.removeEmptyArguments(); //removes all the empty arguments

	if (a.size() != 2) //only do this function if there are exactly two arguments
	{
		*pt << "Command syntax: testOsuTag <source> <destination>";
	}

	using namespace fileOperations; //lazy
	using namespace osuFileOperations; //also lazy

	std::vector<osuBeatmap> *obv = new std::vector<osuBeatmap>; //initialized osuBeamap vector

	std::function<void(std::string, ProgressTracker*)> f_osu = std::bind(readSingleFile, obv, std::placeholders::_1, std::placeholders::_2); //new function (using auto, very convinient thing!)

	if (a[0] == "")
		return; //returns straight away

	//Changes both arguments into working paths
	if (a[0][a[0].length() - 1] != '\\' && a[0][a[0].length() - 1] != '/')
		a[0][a[0].length()] = '/';

	if (a[1][a[1].length() - 1] != '\\' && a[1][a[1].length()- 1] != '/')
		a[1][a[1].length()] = '/';

	//Read the files
	readFiles(FindFiles(a[0], ".osu", pt), f_osu, pt); //read files

	//Removes duplicates
	//osuBeatmapFunctions::fixBeatmapDuplicates(*obv); //fixes the beatmap duplicates

	//Copies the mp3 files to the working folder
	for (unsigned int iii = 0; iii < obv->size(); iii++) //will modify osuBeatmap
	{
		copyFile(obv->at(iii).MusicLocation, a[1] + justTheFile(obv->at(iii).MusicLocation)); //copies each and every file
		obv->at(iii).MusicLocation = a[1] + justTheFile(obv->at(iii).MusicLocation); //sets the osubeatmap again.

		//Console output
		*pt << "";
		*pt << "Copied: ";
		*pt << std::string("Beatmap Name: ") + obv->at(iii).BeatmapName;
		*pt << std::string("Music Location: ") + obv->at(iii).MusicLocation;
		*pt << std::string("Background Photo Location: ") + obv->at(iii).BackgroundPhoto;
	}

	//Tag the audio
	for (unsigned int iii = 0; iii < obv->size(); iii++) //will *not* modify osuBeatmap
	{
		TagAgent ta;
		ta.autoTag(obv->at(iii)); //tags the files
	}
}
