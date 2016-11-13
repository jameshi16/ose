#include "ProgressTracker.h"

ProgressTracker::ProgressTracker() : consoleOutput(0)
{} //default constructor

ProgressTracker::ProgressTracker(wxRichTextCtrl* w, consoleScreen* c)
{
	initializeConsole(w, c); //initializes with given pointer
}

void ProgressTracker::initializeConsole(wxRichTextCtrl* init, consoleScreen* console)
{
	consoleOutput = init; //makes consoleOutput initialized.
	r_ConsoleScreen = console; //sets the console pointer
}

void ProgressTracker::initializeGUI(){}

bool ProgressTracker::hasGUIHandler()
{
	return false; //to be implemented
}

bool ProgressTracker::hasConsoleHandler()
{
	if (consoleOutput != 0 && r_ConsoleScreen != 0)
		{
			return true; //valid console handler exist
		}
	return false; //valid console handler does not exist
}

void ProgressTracker::clear()
{
	wxThreadEvent *input = new wxThreadEvent; //thread event
	const std::function<void()> toMain = [&]{
		consoleOutput->Clear(); //clears the paragraph
	};

	input->SetPayload<std::function<void()>>(toMain); //sets payload
	r_ConsoleScreen->GetEventHandler()->QueueEvent(input); //queues event
}

bool ProgressTracker::isWorkingThread()
{
	if (threadIdentifier == 0)
		return false;

	return true;
}

void ProgressTracker::setThreadPointer(boost::thread* pointer)
{
	if (isWorkingThread())
		return;

	ptLock.lock();
	threadIdentifier = pointer; //sets the pointer
	ptLock.unlock();
}

void ProgressTracker::threadReportOperationsComplete()
{
	if (hasConsoleHandler())
	{
		wxThreadEvent *input = new wxThreadEvent; //thread event
		const std::function<void()> toMain = [&]{
			r_ConsoleScreen->undoThread(); //undoes the trheads
		};

		input->SetPayload<std::function<void()>>(toMain); //queues input event
		r_ConsoleScreen->GetEventHandler()->QueueEvent(input); //queues input event
	}
}

ProgressTracker::~ProgressTracker()
{
	//Deallocate pointers
	consoleOutput = 0 ; r_ConsoleScreen = 0; threadIdentifier = 0;
}
