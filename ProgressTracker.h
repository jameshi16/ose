#ifndef ProgressTrackerHEADER
#define ProgressTrackerHEADER

#include <wx/richtext/richtextctrl.h>

#include <iostream>
#include <sstream>
#include <string>
#include <ostream>

#include "consoleScreen.h"
#include "osemainui.h"

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
	ProgressTracker(wxStaticText*, wxGauge*, OSEMainUI*); //another possible constructor

	friend std::ostream& operator<<(ProgressTracker& pt, std::ostream &os) //ADL detection
	{
		if(pt.hasConsoleHandler() == true) //if the progresstracker has a console
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

		if(pt.hasGUIHandler() == true) //if the progresstracker has a gui
		{
			std::ostringstream ss_stream; //defines the string stream

			ss_stream << os.rdbuf(); //take from the output stream

			wxThreadEvent *input = new wxThreadEvent; //thread event
			std::string stringInput = ss_stream.str(); //stroe the string for transport

			const std::function<void()> toMain = [&pt, stringInput]{
				pt.statuslabel->SetLabel(stringInput); //sets the value of status label
			};

			input->SetPayload<std::function<void()>>(toMain);
			pt.r_mainui->GetEventHandler()->QueueEvent(input); //queues input event
		}

			return os; //returns the istream
	}

	friend void operator<<(ProgressTracker& pt, const char *os) //ADL detection
	{
		if(pt.hasConsoleHandler() == true) //if a console exists
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

		if(pt.hasGUIHandler() == true) //if a GUI exists
		{
			wxThreadEvent *input = new wxThreadEvent; //thread event
			std::string stringInput(os); //string for transport

			const std::function<void()> toMain = [&pt, stringInput]{
				pt.statuslabel->SetLabel(stringInput); //sets the text
			};

			input->SetPayload<std::function<void()>>(toMain);
			pt.r_mainui->GetEventHandler()->QueueEvent(input); //queues input event
		}

	}

	friend void operator<<(ProgressTracker& pt, std::string os) //ADL detection, again.
	{
		if (pt.hasConsoleHandler() == true) //if an consoleOutput exist
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

		if (pt.hasGUIHandler() == true) //if a GUI exist
		{
			wxThreadEvent *input = new wxThreadEvent; //thread event

			const std::function<void()> toMain = [&pt, os]{
				pt.statuslabel->SetLabel(os);
			};

			input->SetPayload<std::function<void()>>(toMain);
			pt.r_mainui->GetEventHandler()->QueueEvent(input); //queues input event
		}
	}

	friend void operator<<(ProgressTracker& pt, int number) //ADL detection
	{
		if (pt.hasGUIHandler() == true)
		{
			wxThreadEvent *input = new wxThreadEvent; //thread event

			const std::function<void()> toMain = [&pt, number]{
				pt.progressbar->SetValue(number); //set the number
				pt.progressbar->Refresh(); //refreshes the control
				pt.progressbar->Update(); //updates the control
			};

			input->SetPayload<std::function<void()>>(toMain);
			pt.r_mainui->GetEventHandler()->QueueEvent(input); //queues input event
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
		swap(LHS.statuslabel, RHS.statuslabel);
		swap(LHS.progressbar, RHS.progressbar);
		swap(LHS.r_mainui, RHS.r_mainui);
	}

	void initializeConsole(wxRichTextCtrl*, consoleScreen*); //initializeeeee
	void initializeGUI(wxStaticText*, wxGauge*, OSEMainUI*); //intializeeeee v2
	bool hasGUIHandler(); //checks if GUI exists in current instance of progress tracker
	bool hasConsoleHandler(); //checks if console exists in current instance of progress tracker
	void clear(); //clears the text (not really to track progress, but I figured I might as well put it here)
	void SetRange(int); //sets the range
	void threadReportOperationsComplete(); //reports that operations has been completed

	virtual ~ProgressTracker(); //virtual destructor
protected:
public:
	/*Console objects*/
	wxRichTextCtrl *consoleOutput 	= 0;
	consoleScreen *r_ConsoleScreen 	= 0; //used to pass events, I swear!

	/*GUI objects*/
	wxStaticText *statuslabel 			= 0; //the status label
	wxGauge *progressbar 						= 0; //the progressbar
	OSEMainUI *r_mainui							= 0; //used to pass events

	/*Mutex (for rare cases where multi-threading might be a problem)*/
	boost::mutex ptLock;
};

#endif
