#include "commandHandler.h"

/* Needed to make the whole file work (Declaration of Commands) */
namespace Commands
{
	std::map<std::string, commandFunction> commandsAvailable = 
	{ /*List of commands here*/
		std::pair<std::string, commandFunction>("lc", printAllCommands) //alias to entry #2
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

	//First, split the command from the arguments.
	Arguments a_arg(command.substr(command.find(" ", 0), command.length() - command.find(" ", 0)));
	command = command.substr(0, command.find(" ", 0));

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
		v_Arguments.push_back(buffer.substr(n_lastPosition, buffer.find(" ", n_lastPosition) - n_lastPosition)); //pushes back this anonymous string
		n_lastPosition = buffer.find(" ", n_lastPosition); //sets n_lastPosition to the latest position
	}

	//Done.
}

/* Commands */
void Commands::printAllCommands(ProgressTracker* pt, Arguments a)
{
	for (std::map<std::string, commandFunction>::iterator it = commandsAvailable.begin(); it != commandsAvailable.end(); ++it)
	{
		*pt << it->first.c_str(); //prints the commands
	}
}