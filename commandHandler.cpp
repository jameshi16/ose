#include "commandHandler.h"

CommandHandler::CommandHandler()
{
	//ctor
}

CommandHandler::CommandHandler(std::string s, wxRichTextCtrl *c)
{
	processCommand(s, c);
}

void CommandHandler::processCommand(std::string command, wxRichTextCtrl *console)
{
	//Process Command.
}

CommandHandler::~CommandHandler()
{
	//dtor
}