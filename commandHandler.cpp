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
		std::pair<std::string, commandFunction>("testOsuTag", testOsuTag), //test tag on osu directory
		std::pair<std::string, commandFunction>("testIfFileMp3", testIfFileMP3), //tests if the file is mp3
		std::pair<std::string, commandFunction>("clear", clear), //clears the console screen somehow
		std::pair<std::string, commandFunction>("launchGUI", launchGUI), //launches the GUI
		std::pair<std::string, commandFunction>("launchConsole", launchConsole), //launches the console
		std::pair<std::string, commandFunction>("OsuTag", OsuTag), //the tagging for the GUI
		std::pair<std::string, commandFunction>("testProgressBar", testProgressBar) //test the progress bar
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
		pt->threadReportOperationsComplete(); //report to ProgressTracker command has completed
		return;
	}
	if (commandsAvailable.count(command) == 0)
	{
		//report to progress tracker
		*pt << "Error processing command: Command not found";
		*pt << "Try using lc";
		*pt << "";
		pt->threadReportOperationsComplete(); //report to ProgressTracker command has completed
		return;
	}
	if (commandsAvailable.count(command) > 1)
	{
		//report to progress tracker
		*pt << "Error processing command: Lazy programmer forgot to check code";
		*pt << "";
		pt->threadReportOperationsComplete(); //report to ProgressTracker command has completed
		return;
	}
	*pt << "Error processing command: EOF reached.";
	*pt << "";

	/*Command completed*/
	pt->threadReportOperationsComplete(); //report to ProgressTracker command has completed
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
	/*Variables*/
	std::string buffer = s_fullArgument; //sets the buffer to the full argument
	unsigned int iterator = 0; //the iterator

	/*Constant detectors*/
	const std::string parameterSyntax = "-"; //this is the paramter syntax
	const std::string quoteSyntax			= "\""; //this is the quote syntax

	/*Fast Checks*/
	if (buffer == "") {return;}
	if (removeAllSpaces(buffer) == "") {return;}

	/*Validity checkers*/
	const std::function<bool(unsigned int)> isValidParameter = [buffer, parameterSyntax](unsigned int pos)
	{
		if (buffer[pos] != parameterSyntax)
			return false; //if the character at the position is not parameterSyntax

		if (static_cast<int>(pos) - 1 < 0) //if the position before the iterator is nothing
		{
			if (buffer[pos + 1] != '\0' && buffer.find(" ", pos) != std::string::npos) //if the character at the next position is a letter of any sort, and the character and there is a blank
				return true; //then the parameter is a valid parameter

			if (buffer[pos + 1] != '\0') //if the character at the next position is a letter of any sort
				return true; //then the parameter is a valid parameter
		}

		if (!(static_cast<int>(pos) - 1 < 0)) //instead of using else, I use another if(), just in case iterator becomes maxint
		{
			if (buffer[pos + 1] != '\0' && buffer.find(" ", pos) != std::string::npos && buffer[pos - 1] == ' ') // if the character at the next position is a letter of any sort, and the character and there is a blank, and the position before is blank
				return true; //then the parameter is a valid parameter

			if (buffer[pos + 1] != '\0') //if the character at the next position is a letter of any sort
				return true; //then the parameter ia a valid parameter
		}

		return false; //it is not a valid paramter
	};

	const std::function<bool(unsigned int)> isValidPure = [buffer, parameterSyntax, quoteSyntax](unsigned int pos)
	{
		if (buffer[pos] == parameterSyntax || buffer[pos] == quoteSyntax)
			return false; //if the character at the position is not pure

		if (static_cast<int>(pos) - 1 < 0) //if the position before the iterator is nothing
		{
			if (buffer[pos + 1] != '\0') //if the character next to the position is not empty
				return true; //it is a valid pure
		}

		if (!(static_cast<int>(pos) - 1 < 0)) //instead of using else, I use another if(), just in case iterator becomes maxint
		{
			if (buffer[pos + 1] != '\0' && buffer[pos - 1] == ' ') //if the character at the next position is a letter of any sort, and the position before is blank
			return true; //then the pure is a valid pure
		}

		return false; //it is not a valid pure
	};

	const std::function<bool(unsigned int)> isValidQuote = [buffer, quoteSyntax](unsigned int pos)
	{
		if (buffer[pos] != quoteSyntax)
			return false; //if the character at the position is not quoteSyntax

		if (static_cast<int>(pos) - 1 < 0) //if the position before the iterator is nothing
		{
			if (buffer[pos + 1] != '\0') //if the character next to the position is not empty
				return true; //it is a valid quote
		}

		if (!(static_cast<int>(pos) - 1 < 0)) //instead of using else, I use another if(), just in case iterator becomes maxint
		{
			if (buffer[pos + 1] != '\0' && buffer[pos - 1] == ' ') //if the character at the next position is a letter of any sort, and the position before is blank
			return true; //then the quote is a valid quote
		}

		return false; //it is not a valid quote
	};

	/*Command parsers*/
	const std::function<std::string(unsigned int)> parsePure = [buffer, &iterator, this](unsigned int pos)
	{
		unsigned int nextEmptyPos = 0;

		if ((nextEmptyPos = buffer.find(" ", pos + 1 /*Start to search for " " 1 position after the position provided*/)) == std::string::npos)
		{
			iterator = buffer.size(); //sets iterator to max point
			return removeAllSpaces(buffer.substr(pos, std::string::npos)); //Copies everything
		}

		iterator = nextEmptyPos - 1 /*To remove the space at the end*/;
		return removeAllSpaces(buffer.substr(pos, iterator - pos /*Removes the original value of iterator*/ + 1 /*adjustment from 0 -> 1*/));
	};

	const std::function<std::string(unsigned int)> parseQuote = [buffer, &iterator, quoteSyntax](unsigned int pos)
	{
		unsigned int nextQuotePos = 0;

		if ((nextQuotePos = buffer.find(quoteSyntax, pos + 1 /*Start to search for "\"" 1 position after the position provided*/)) == std::string::npos)
		{
			iterator = buffer.size(); //sets iterator to max point
			return buffer.substr(pos + 1 /*starts copying from the next character on*/, std::string::npos); //copies everything
		}

		iterator = nextQuotePos + 1 /*Skips the quote*/;
		return buffer.substr(pos + 1 /*starts copying from the next character on*/, iterator - 1 /*To remove the quote at the end*/ - 1 /*To remove adjustment to iterator*/ - pos /*removes the original value of iterator*/);
	};

	const std::function<std::string(unsigned int)> parseParameter = [buffer, &iterator, this, &parseQuote, &parsePure, &isValidQuote, &isValidPure](unsigned int pos)
	{
		unsigned int emptyPosition;

		if ((emptyPosition = buffer.find(" ", pos)) == std::string::npos)
		{
			iterator = buffer.size() + 1; //sets iterator to max point
			return removeAllSpaces(buffer.substr(pos, std::string::npos)); //copies everything
		}

		if (isValidQuote(emptyPosition + 1))
		{
			iterator = emptyPosition;
			std::string s_param = buffer.substr(pos, iterator - pos /*Removes the original value of iterator*/ + 1 /*adjustment from 0 -> 1*/);
			std::string s_quote = parseQuote(emptyPosition + 1); //parses the quote

			//For some reason, buffer.substr(pos, iterator - pos + 1) + parseQuote(emptyPosition + 1) does not work!

			return s_param + s_quote; //returns the sum
		}

		if (isValidPure(emptyPosition + 1))
		{
			iterator = emptyPosition;
			std::string s_param = buffer.substr(pos, iterator - pos /*Removes the original value of iterator*/ + 1 /*adjustment from 0 -> 1*/);
			std::string s_pure  = parsePure(emptyPosition + 1);

			//For some reason, buffer.substr(pos, iterator - pos + 1) + parsePure(emptyPosition + 1) does not work!

			return s_param + s_pure;
		}

		iterator = emptyPosition;
		return removeAllSpaces(buffer.substr(pos, iterator  - 1 /*To remove the space at the end*/ - pos /*Removes the original value of iterator*/ + 1 /*adjustment from 0 -> 1*/));
	};

	/*Order of detection: Parameter, Pure, Quote*/
	while (true)
	{
		if (iterator > buffer.size() || iterator == std::string::npos)
		{ iterator = 0; break; } //escapes the loop

		if (isValidParameter(iterator)) //Parameter detection
		{
			std::string s_argument = parseParameter(iterator); //uses a temporary variable
			v_Arguments.push_back(s_argument); //sends the argument to the v_Arguments vector
		}

		if (isValidPure(iterator)) //Pure detection
		{
			std::string s_argument = parsePure(iterator); //uses a temporary variable
			v_Arguments.push_back(s_argument); //sends the argument to the v_Arguments vector
		}

		if (isValidQuote(iterator)) //Quote detection
		{
			std::string s_argument = parseQuote(iterator); //uses a temporary variable
			v_Arguments.push_back(s_argument); //sends the argument to the v_Arguments vector
		}

		++iterator; //increments the iterator
	}

	/*Clean up of arguments*/
	removeEmptyArguments();

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

int Arguments::getArgumentPos(std::string s)
{
	if (s == "")
		return EMPTY_STRING; //return empty string error

	if (s[0] != '-')
		s.insert(0, "-"); //inserts the paramSyntax

	for (int iii = 0; iii < size(); iii++) //tries to find s within the array
	{
		if (v_Arguments[iii].find(s) != std::string::npos)
			return iii;
	}

	return NOTFOUND; //return not found
}

std::string Arguments::getArgumentString(int pos)
{
	std::string buffer = getArgument(pos); //gets the argument at the position

	unsigned int emptyPosition; //empty position
	if ((emptyPosition = buffer.find(" ")) != std::string::npos)
	{
		return buffer.substr(emptyPosition + 1 /*Copies from after the blank*/, std::string::npos /*copies the whole string afterwards*/); //returns the argument string
	}

	return ""; //default return
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
		*pt << "Command syntax: testOsuTag -i <source> -o <destination>";
		return;
	}

	using namespace fileOperations; //lazy
	using namespace osuFileOperations; //also lazy

	std::vector<osuBeatmap> *obv = new std::vector<osuBeatmap>; //initialized osuBeamap vector

	std::function<void(std::string, ProgressTracker*)> f_osu = std::bind(readSingleFile, obv, std::placeholders::_1, std::placeholders::_2); //new function (using auto, very convinient thing!)

	if (a[0] == "")
		return; //returns straight away

	//Changes both arguments into working paths
	int n_input 	= a.getArgumentPos("-i");
	int n_output 	= a.getArgumentPos("-o");

	if (n_input == NOTFOUND || n_output == NOTFOUND)
	{
		*pt << "Paths not found. Command syntax: testOsuTag -i <source> -o <destination>";
		return;
	}

	if (n_input != NOTFOUND)
	{
		if ((a[n_input].rfind("\\") == std::string::npos && a[n_input].rfind("/") == std::string::npos) ||
		(a[n_input].rfind("\\") != (a[n_input].length() - 1 /*Adjustment from 1 -> 0*/) && a[n_input].rfind("/") != (a[n_input].length() - 1 /*Adjustment from 1 -> 0*/)))
		{
			a[n_input].append("/"); //adds a path ender at the end
			*pt << std::string("Path appended to: " + a.getArgumentString(n_input));
		}
	}
	if (n_output != NOTFOUND)
	{
		if ((a[n_output].rfind("\\") == std::string::npos && a[n_output].rfind("/") == std::string::npos) ||
		(a[n_output].rfind("\\") != (a[n_output].length() - 1 /*Adjustment from 1 -> 0*/) && a[n_output].rfind("/") != (a[n_output].length() - 1 /*Adjustment from 1 -> 0*/)))
		{
			a[n_output].append("/"); //adds a path ender at the end
			*pt << std::string("Path appended to: " + a.getArgumentString(n_output));
		}
	}

	//Read the files
	readFiles(FindFiles(a.getArgumentString(n_input), ".osu", pt), f_osu, pt); //read files

	//Removes duplicates
	osuBeatmapFunctions::fixBeatmapDuplicates(*obv); //fixes the beatmap duplicates

	//Copies the mp3 files to the working folder
	for (unsigned int iii = 0; iii < obv->size(); iii++) //will modify osuBeatmap
	{
		copyFile(obv->at(iii).MusicLocation, a.getArgumentString(n_output) + justTheFile(obv->at(iii).MusicLocation)); //copies each and every file
		obv->at(iii).MusicLocation = a.getArgumentString(n_output) + justTheFile(obv->at(iii).MusicLocation); //sets the osubeatmap again.

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
		*pt << "";
		*pt << "Tagged: ";
		*pt << std::string("Beatmap Name: ") + obv->at(iii).BeatmapName;
		*pt << std::string("Music Location: ") + obv->at(iii).MusicLocation;
		*pt << std::string("Background Photo Location: ") + obv->at(iii).BackgroundPhoto;

		if (iii + 1 >= obv->size())
			break;

		*pt << "Next to tag: ";
		*pt << std::string("Beatmap Name: ") + obv->at(iii + 1).BeatmapName;
		*pt << std::string("Music Location: ") + obv->at(iii + 1).MusicLocation;
		*pt << std::string("Background Photo Location: ") + obv->at(iii + 1).BackgroundPhoto;
	}

	//Memory management
	delete obv;
}

//The Tagging function that is directly accessible though GUI
void Commands::OsuTag(ProgressTracker* pt, Arguments a)
{
	/*Clean up block*/
	a.removeEmptyArguments(); //removes all the empty arguments

	if (a.size() != 2) //only do this function if there are exactly two arguments
	{
		*pt << "Command syntax: OsuTag -i <source> -o <destination>";
		return;
	}

	using namespace fileOperations; //lazy
	using namespace osuFileOperations; //also lazy

	std::vector<osuBeatmap> *obv = new std::vector<osuBeatmap>; //initialized osuBeamap vector

	std::function<void(std::string, ProgressTracker*)> f_osu = std::bind(readSingleFile, obv, std::placeholders::_1, std::placeholders::_2); //new function (using auto, very convinient thing!)

	//Changes both arguments into working paths
	int n_input 	= a.getArgumentPos("-i");
	int n_output 	= a.getArgumentPos("-o");

	if (n_input == NOTFOUND || n_output == NOTFOUND)
	{
		*pt << "Paths not found. Command syntax: testOsuTag -i <source> -o <destination>";
		return;
	}

	if (n_input != NOTFOUND)
	{
		if ((a[n_input].rfind("\\") == std::string::npos && a[n_input].rfind("/") == std::string::npos) ||
		(a[n_input].rfind("\\") != (a[n_input].length() - 1 /*Adjustment from 1 -> 0*/) && a[n_input].rfind("/") != (a[n_input].length() - 1 /*Adjustment from 1 -> 0*/)))
		{
			a[n_input].append("/"); //adds a path ender at the end
			*pt << std::string("Path appended to: " + a.getArgumentString(n_input));
		}
	}
	if (n_output != NOTFOUND)
	{
		if ((a[n_output].rfind("\\") == std::string::npos && a[n_output].rfind("/") == std::string::npos) ||
		(a[n_output].rfind("\\") != (a[n_output].length() - 1 /*Adjustment from 1 -> 0*/) && a[n_output].rfind("/") != (a[n_output].length() - 1 /*Adjustment from 1 -> 0*/)))
		{
			a[n_output].append("/"); //adds a path ender at the end
			*pt << std::string("Path appended to: " + a.getArgumentString(n_output));
		}
	}

	//Read the files
	readFiles(FindFiles(a.getArgumentString(n_input), ".osu", pt), f_osu, pt); //read files

	//Removes duplicates
	osuBeatmapFunctions::fixBeatmapDuplicates(*obv); //fixes the beatmap duplicates

	//Copies the mp3 files to the working folder
	for (unsigned int iii = 0; iii < obv->size(); iii++) //will modify osuBeatmap
	{
		copyFile(obv->at(iii).MusicLocation, a.getArgumentString(n_output) + justTheFile(obv->at(iii).MusicLocation)); //copies each and every file
		obv->at(iii).MusicLocation = a.getArgumentString(n_output) + justTheFile(obv->at(iii).MusicLocation); //sets the osubeatmap again.

		//GUI output
		*pt << static_cast<int>((static_cast<double>(iii)/static_cast<double>(obv->size()*2)) * static_cast<double>(100));
		*pt << std::string("Working on: ") + obv->at(iii).BeatmapName;
	}

	//Tag the audio
	for (unsigned int iii = 0; iii < obv->size(); iii++) //will *not* modify osuBeatmap
	{
		TagAgent ta;
		ta.autoTag(obv->at(iii)); //tags the files

		//GUI output
		*pt << static_cast<int>(((static_cast<double>(obv->size()) + static_cast<double>(iii)) / static_cast<double>(obv->size()*2)) * static_cast<double>(100)); //adds on to the previous progress value
		*pt << std::string("Tagging file: ") + obv->at(iii).BeatmapName;
	}

	*pt << 100; //fully complete

	//Memory management
	delete obv;
}

//Tests if files are MP3 files.
void Commands::testIfFileMP3(ProgressTracker* pt, Arguments a)
{
	for (int iii = 0; iii < a.size(); iii++)
	{
		if (osuBeatmapFunctions::isMusicMp3(a[iii]))
		{
			*pt << std::string("Music file (MP3) found at: ") + a[iii]; //a mp3 file has been file!
			break;
		}
	}
}

//Clears the textbox
void Commands::clear(ProgressTracker *pt, Arguments a)
{ pt->clear(); /*clears the progress tracker*/ }

//placeholder, launchGUI is to be implemented in the main thread, not at the command subthread
void Commands::launchGUI(ProgressTracker *pt, Arguments a)
{
	//handled locally in the console
	*pt << "Error! launchGUI is to be launched only from the console!"; //if it somehow reaches here, error.
	return;
}

//placeholder, launchConsole is to be implemented in the main thread, not at the command subthread
void Commands::launchConsole(ProgressTracker *pt, Arguments a)
{
	//handled locally in the GUI
	*pt << "Error! launchConsole is to be launched only from the GUI!"; //if it somehow reaches here, error.
	return;
}

void Commands::testProgressBar(ProgressTracker *pt, Arguments a)
{
	//Testing the progress bar
	for (int iii = 0; iii < 100; iii++)
	{
		*pt << iii;
	}
	return;
}
