#include "ProgressTracker.h"

ProgressTracker::ProgressTracker() : consoleOutput(0)
{} //default constructor

ProgressTracker::ProgressTracker(wxRichTextCtrl* w)
{
	initializeConsole(w); //initializes with given pointer
}

void ProgressTracker::initializeConsole(wxRichTextCtrl* init)
{
	consoleOutput = init; //makes consoleOutput initialized.
}

void ProgressTracker::initializeGUI(){}

bool ProgressTracker::hasGUIHandler()
{
	return false; //to be implemented
}

bool ProgressTracker::hasConsoleHandler()
{
	if (consoleOutput != 0)
		{
			return true; //valid console handler exist
		}
	return false; //valid console handler does not exist
}

void ProgressTracker::clear()
{
	//For now, send bare signal to clear object (should not be doing this)
	consoleOutput->Clear(); //clears the paragraph
}

ProgressTracker::~ProgressTracker()
{
	//Deallocate pointers
	consoleOutput = 0; //points consoleOutput to 0
}
