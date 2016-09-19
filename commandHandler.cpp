#include "commandHandler.h"

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
		commandsAvailable[command]; //plays the command
		return;
	}
	if (commandsAvailable.count(command) == 0)
	{
		//report to progress tracker
		pt << "Error processing command: Command not found";
		return;
	}
	if (commandsAvailable.count(command) > 1)
	{
		//report to progress tracker
		pt << "Error processing command: Lazy programmer forgot to check code";
		return;
	}
	pt << "Error processing command: EOF reached.";
}

CommandHandler::~CommandHandler()
{
	//dtor
}