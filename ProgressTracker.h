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

	friend std::ostream& operator<<(std::ostream &os, ProgressTracker& pt) //ADL detection
	{
		if(pt.r_object != 0) //if an r_object exist
			{
				std::ostringstream ss_stream; //defines string stream

				ss_stream << os.rdbuf(); //take from output stream

				pt.r_object->Newline(); //adds a new line
				pt.r_object->AppendText(ss_stream.str()); //adds the text
			}
			return os; //returns the istream
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
		swap(LHS.r_object, RHS.r_object);
	}

	void initialize(wxRichTextCtrl*); //initializeeeee
	//void initialize(ProgressGuage*); soon, but not now.

	virtual ~ProgressTracker(); //virtual destructor, in case I actually need to change this
protected:
public:
	//ToDo: add progress guage/bar here
	wxRichTextCtrl *r_object = 0;
};

#endif