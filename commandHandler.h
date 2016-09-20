#ifndef commandHandlerHEADER
#define commandHandlerHEADER

#include <wx/richtext/richtextctrl.h>
#include <map>
#include <vector>

#include "ProgressTracker.h"

class CommandHandler
{
public:
	CommandHandler();
	CommandHandler(std::string, ProgressTracker*);
	~CommandHandler();

	void processCommand(std::string, ProgressTracker*);
protected:
private:
	void operator=(CommandHandler&){} //do not implement
	CommandHandler(CommandHandler&){} //do not implement
};

class Arguments
{
public:
	Arguments();
	Arguments(std::string);
	~Arguments();

	Arguments(Arguments &a)
	{*this = a;} //super fast constructor

	Arguments& operator=(Arguments RHS)
	{
		swap(*this, RHS); //swaps
		return *this;
	}

	friend void swap(Arguments& LHS, Arguments& RHS)
	{
		using std::swap; //ADL

		swap(LHS.s_fullArgument, RHS.s_fullArgument);
		swap(RHS.v_Arguments, RHS.v_Arguments);
	}

	void setFullArgument(std::string);
	std::string getFullArgument();
	std::string getArgument(int);
	void setArgument(int, std::string);

protected:
private:
	std::string s_fullArgument 				= "";
	std::vector<std::string> v_Arguments 	= {};

	void splitArguments();
};

/* Namespace that contains commands to test the program */
namespace Commands
{
	void printAllCommands(ProgressTracker* pt, Arguments a);

	typedef void (*commandFunction)(ProgressTracker*, Arguments);
	extern std::map<std::string, commandFunction> commandsAvailable;
};

#endif