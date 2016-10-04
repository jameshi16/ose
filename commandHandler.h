#ifndef commandHandlerHEADER
#define commandHandlerHEADER

#include <wx/richtext/richtextctrl.h>
#include <map>
#include <vector>

//My own includes
#include "tagAgent.h"
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

	Arguments(Arguments& a)
	{
		//Implement copy constructor
		this->s_fullArgument 	= a.s_fullArgument;
		this->v_Arguments 		= a.v_Arguments;
	}

	Arguments(Arguments&& a) : Arguments() //I don't understand the full details, but I know this can detect rvalues (those values where there is no deeper meaning in the argument passed)
	{
		//Implement move constructor
		std::swap(*this, a); //done
	}

	Arguments& operator=(Arguments RHS)
	{
		swap(*this, RHS); //swaps
		return *this;
	}

	std::string& operator[](unsigned int iii)
	{
		return v_Arguments[iii];
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

	void removeEmptyArguments();

	int size();

protected:
private:
	std::string s_fullArgument 				= "";
	std::vector<std::string> v_Arguments 	= {};

	void splitArguments();
	std::string removeAllSpaces(std::string);
};

/* Namespace that contains commands to test the program */
namespace Commands
{
	void printAllCommands(ProgressTracker* pt, Arguments a);
	void print(ProgressTracker* pt, Arguments a);
	void testTaggingOnFile(ProgressTracker* pt, Arguments a);
	void testOsuTag(ProgressTracker* pt, Arguments a);

	typedef void (*commandFunction)(ProgressTracker*, Arguments);
	extern std::map<std::string, commandFunction> commandsAvailable;
};

#endif