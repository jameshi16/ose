#ifndef commandHandlerHEADER
#define commandHandlerHEADER

#include <wx/richtext/richtextctrl.h>
#include <map>

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

/* Namespace that contains commands to test the program */
namespace Commands
{
	void exampleCommand(ProgressTracker* pt);

	typedef void (*commandFunction)(ProgressTracker*);
	extern std::map<std::string, commandFunction> commandsAvailable; 
};

#endif