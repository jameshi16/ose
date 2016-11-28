#include "ProgressTracker.h"

ProgressTracker::ProgressTracker() : consoleOutput(0)
{} //default constructor

ProgressTracker::ProgressTracker(wxRichTextCtrl* w, consoleScreen* c)
{
	initializeConsole(w, c); //initializes with given pointers
}

ProgressTracker::ProgressTracker(wxStaticText* s, wxGauge* pb, OSEMainUI *omu)
{
	initializeGUI(s, pb, omu); //initializes with given pointers
}

void ProgressTracker::initializeConsole(wxRichTextCtrl* init, consoleScreen* console)
{
	consoleOutput = init; //makes consoleOutput initialized.
	r_ConsoleScreen = console; //sets the console pointer
}

void ProgressTracker::initializeGUI(wxStaticText* s, wxGauge* pb, OSEMainUI *omu)
{
	statuslabel = s; //makes s the status label
	progressbar = pb; //makes pb the progress bar
	r_mainui 		= omu; //sets the gui pointer
}

bool ProgressTracker::hasGUIHandler()
{
	if (statuslabel != 0 && progressbar != 0 && r_mainui != 0)
		return true; //valid handler exists

	return false; //valid handler does not exist
}

bool ProgressTracker::hasConsoleHandler()
{
	if (consoleOutput != 0 && r_ConsoleScreen != 0)
			return true; //valid console handler exist

	return false; //valid console handler does not exist
}

void ProgressTracker::clear()
{
	if (hasConsoleHandler() != true)
		return;

	wxThreadEvent *input = new wxThreadEvent; //thread event
	const std::function<void()> toMain = [&]{
		consoleOutput->Clear(); //clears the paragraph
	};

	input->SetPayload<std::function<void()>>(toMain); //sets payload
	r_ConsoleScreen->GetEventHandler()->QueueEvent(input); //queues event
}

void ProgressTracker::SetRange(int theNumber)
{
	if (hasGUIHandler() != true)
		return;

	wxThreadEvent *input = new wxThreadEvent; //thread event
	const std::function<void()> toMain = [&]{
		progressbar->SetRange(theNumber); //sets the range
	};

	input->SetPayload<std::function<void()>>(toMain);
	r_mainui->GetEventHandler()->QueueEvent(input); //sets event
}

void ProgressTracker::threadReportOperationsComplete()
{
	if (hasConsoleHandler())
	{
		wxThreadEvent *input = new wxThreadEvent; //thread event
		const std::function<void()> toMain = [&]{
			r_ConsoleScreen->undoThread(); //undoes the thread
		};

		input->SetPayload<std::function<void()>>(toMain); //queues input event
		r_ConsoleScreen->GetEventHandler()->QueueEvent(input); //queues input event
	}

	if (hasGUIHandler())
	{
		wxThreadEvent *input = new wxThreadEvent; //thread event
		const std::function<void()> toMain = [&]{
			r_mainui->UndoThread(); //undoes the thread
		};

		input->SetPayload<std::function<void()>>(toMain); //queues input event
		r_mainui->GetEventHandler()->QueueEvent(input); //queues input event
	}
}

ProgressTracker::~ProgressTracker()
{
	//Deallocate pointers
	consoleOutput = 0 ; r_ConsoleScreen = 0; statuslabel = 0; progressbar = 0; r_mainui = 0;
}
