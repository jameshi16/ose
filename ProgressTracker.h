#ifndef ProgressTrackerHEADER
#define ProgressTrackerHEADER

#include <wx/richtext/richtextctrl.h>

#include <iostream>
#include <sstream>
#include <string>
#include <ostream>

#include "consoleScreen.h"

/**
To those asking: WHY ISN'T THIS CLASS THREAD-SAFE OMGGGGGGG
My reply: Don't worry about it, in the entire application process, there should only be 2 threads that use this class, Main and Sub.
And also:
How do I thread-safe friend functions?
*/

class ProgressTracker
{
public:
	ProgressTracker(); //constructor
	ProgressTracker(wxRichTextCtrl*,consoleScreen*); //another possible constructor

	friend std::ostream& operator<<(ProgressTracker& pt, std::ostream &os) //ADL detection
	{
		if(pt.consoleOutput != 0) //if an consoleOutput exist
			{
				std::ostringstream ss_stream; //defines string stream

				ss_stream << os.rdbuf(); //take from output stream

				wxThreadEvent *input = new wxThreadEvent; //thread event
				std::string stringInput = ss_stream.str(); //store the string for transport

				const std::function<void()> toMain = [&pt, stringInput]{
					pt.consoleOutput->Newline(); //adds a new line
					pt.consoleOutput->WriteText(stringInput); //adds the text
				};

				input->SetPayload<std::function<void()>>(toMain);
				pt.r_ConsoleScreen->GetEventHandler()->QueueEvent(input); //queues input event
			}

			return os; //returns the istream
	}

	friend void operator<<(ProgressTracker& pt, const char *os) //ADL detection
	{
		if(pt.consoleOutput != 0) //if an consoleOutput exist
			{
				wxThreadEvent *input = new wxThreadEvent; //thread event
				std::string stringInput(os); //string for transport

				const std::function<void()> toMain = [&pt, stringInput]{
					if (stringInput != '\0')
						pt.consoleOutput->Newline(); //adds a new line

					pt.consoleOutput->WriteText(stringInput); //adds the text
				};

				input->SetPayload<std::function<void()>>(toMain);
				pt.r_ConsoleScreen->GetEventHandler()->QueueEvent(input); //queues input event
			}
	}

	friend void operator<<(ProgressTracker& pt, std::string os) //ADL detection, again.
	{
		if (pt.consoleOutput != 0) //if an consoleOutput exist
		{
			wxThreadEvent *input = new wxThreadEvent; //thread event

			const std::function<void()> toMain = [&pt, os]{
				if (os != '\0')
					pt.consoleOutput->Newline(); //adds a new line

				pt.consoleOutput->WriteText(os);
			};

			input->SetPayload<std::function<void()>>(toMain);
			pt.r_ConsoleScreen->GetEventHandler()->QueueEvent(input); //queues input event
		}
	}

	ProgressTracker& operator=(ProgressTracker pt)
	{
		//Already kind of using a copy of ProgressTracker
		swap(*this, pt);
		return *this;
	}

	friend void swap(ProgressTracker& LHS, ProgressTracker& RHS)
	{
		using std::swap; //Conventions! (ADL)

		/*List of things to swap*/
		swap(LHS.consoleOutput, RHS.consoleOutput);
		swap(LHS.r_ConsoleScreen, RHS.r_ConsoleScreen);
		swap(LHS.threadIdentifier, RHS.threadIdentifier);
	}

	void initializeConsole(wxRichTextCtrl*, consoleScreen*); //initializeeeee
	void initializeGUI(); //intializeeeee v2
	bool hasGUIHandler(); //checks if GUI exists in current instance of progress tracker
	bool hasConsoleHandler(); //checks if console exists in current instance of progress tracker
	void clear(); //clears the text (not really to track progress, but I figured I might as well put it here)
	bool isWorkingThread(); //checks if the object is attached to a working thread (a.k.a not main thread)
	void setThreadPointer(boost::thread*); //sets threadIdentifier, which is used to ask main thread to join this subthread when execution is complete (if already set, doesn't change)
	void threadReportOperationsComplete(); //reports that operations has been completed

	virtual ~ProgressTracker(); //virtual destructor
protected:
public:
	/*Console objects*/
	wxRichTextCtrl *consoleOutput = 0;
	consoleScreen *r_ConsoleScreen = 0; //used to pass events, I swear!

	/*GUI objects*/

	/*Thread Identifier*/
	boost::thread *threadIdentifier = 0;

	/*Mutex (for rare cases where multi-threading might be a problem)*/
	boost::mutex ptLock;
};

#endif
