#ifndef commandHandlerHEADER
#define commandHandlerHEADER

#include <wx/richtext/richtextctrl.h>

/* Namespace that contains commands to test the program */
namespace Commands
{
	typedef void (*commandFunction)();
};

class CommandHandler
{
public:
	CommandHandler();
	CommandHandler(std::string, wxRichTextCtrl*);
	~CommandHandler();

	void processCommand(std::string, wxRichTextCtrl*);
protected:
private:
	void operator=(CommandHandler&){} //do not implement
	CommandHandler(CommandHandler&){} //do not implement
};

#endif