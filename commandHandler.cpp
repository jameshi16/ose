#include "commandHandler.h"

namespace Commands
{
	std::map<std::string, commandFunction> commandsAvailable = 
	{ /*List of commands here*/
		std::pair<std::string, commandFunction>("exampleCommand", exampleCommand)
	}; //pretty cool, right?
}

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

	if (commandsAvailable.count(command) != 0 && commandsAvailable.count(command) == 1)
	{
		//launches the command
		commandFunction cf = commandsAvailable[command]; //gets the command
		cf(pt); //plays the command
		*pt << "";
		return;
	}
	if (commandsAvailable.count(command) == 0)
	{
		//report to progress tracker
		*pt << "Error processing command: Command not found";
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

void Commands::exampleCommand(ProgressTracker* pt)
{
	*pt << "Example!"; //returns something
}