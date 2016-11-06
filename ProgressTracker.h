#ifndef ProgressTrackerHEADER
#define ProgressTrackerHEADER

#include <wx/richtext/richtextctrl.h>

#include <iostream>
#include <sstream>
#include <string>
#include <ostream>

class ProgressTracker
{
public:
	ProgressTracker(); //constructor
	ProgressTracker(wxRichTextCtrl *w); //another possible constructor

	friend std::ostream& operator<<(ProgressTracker& pt, std::ostream &os) //ADL detection
	{
		if(pt.consoleOutput != 0) //if an consoleOutput exist
			{
				std::ostringstream ss_stream; //defines string stream

				ss_stream << os.rdbuf(); //take from output stream

				pt.consoleOutput->Newline(); //adds a new line
				pt.consoleOutput->WriteText(ss_stream.str()); //adds the text
			}
			return os; //returns the istream
	}

	friend void operator<<(ProgressTracker& pt, const char *os) //ADL detection
	{
		if(pt.consoleOutput != 0) //if an consoleOutput exist
			{
				if (os != '\0')
					pt.consoleOutput->Newline(); //adds a new line

				pt.consoleOutput->WriteText(os); //adds the text
			}
	}

	friend void operator<<(ProgressTracker& pt, std::string os) //ADL detection, again.
	{
		if (pt.consoleOutput != 0) //if an consoleOutput exist
		{
			if (os != '\0')
				pt.consoleOutput->Newline(); //adds a new line

			pt.consoleOutput->WriteText(os);
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
	}

	void initializeConsole(wxRichTextCtrl*); //initializeeeee
	void initializeGUI(); //intializeeeee v2
	bool hasGUIHandler(); //checks if GUI exists in current instance of progress tracker
	bool hasConsoleHandler(); //checks if console exists in current instance of progress tracker
	void clear(); //clears the text (not really to track progress, but I figured I might as well put it here)
	//void initialize(ProgressGuage*); soon, but not now.

	virtual ~ProgressTracker(); //virtual destructor
protected:
public:
	/*Console objects*/
	wxRichTextCtrl *consoleOutput = 0;

	/*GUI objects*/
};

#endif
