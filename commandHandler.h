#ifndef commandHandlerHEADER
#define commandHandlerHEADER

#include <wx/richtext/richtextctrl.h>
#include <map>

#include "ProgressTracker.h"

/* Namespace that contains commands to test the program */
namespace Commands
{
	typedef void (*commandFunction)();
	const std::map<std::string, commandFunction> commandsAvailable = {}; //pretty cool, right?
};

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

#endif