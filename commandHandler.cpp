#include "commandHandler.h"

/* Needed to make the whole file work (Declaration of Commands) */
namespace Commands
{
	std::map<std::string, commandFunction> commandsAvailable = 
	{ /*List of commands here*/
		std::pair<std::string, commandFunction>("lc", printAllCommands), //print all commands
		std::pair<std::string, commandFunction>("printArgs", printArguments) //print all arguments
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
		if (buffer[n_lastPosition + 1] != ' ')
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
	n_lastPosition = buffer.find(" ", 0); //reuse used integer
	
	(buffer.find(" ", 0) != std::string::npos) ? (lastArgumentBuffer = buffer.substr(buffer.find(" ", n_lastPosition) + 1, buffer.length() - buffer.find(" ", n_lastPosition))) : (lastArgumentBuffer = buffer);
	if (removeAllSpaces(lastArgumentBuffer) != "")
	{
		v_Arguments.push_back(removeAllSpaces(lastArgumentBuffer));
	}

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

int Arguments::size()
{ return v_Arguments.size(); }

/* Commands */
void Commands::printAllCommands(ProgressTracker* pt, Arguments)
{
	for (std::map<std::string, commandFunction>::iterator it = commandsAvailable.begin(); it != commandsAvailable.end(); ++it)
	{
		*pt << it->first.c_str(); //prints the commands
	}
}

void Commands::printArguments(ProgressTracker* pt, Arguments a)
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