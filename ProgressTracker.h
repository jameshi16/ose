#ifndef ProgressTrackerHEADER
#define ProgressTrackerHEADER

#include <wx/richtext/richtextctrl.h>

#include <iostream>
#include <sstream>

class ProgressTracker
{
public:
	ProgressTracker(); //constructor

	friend std::istream& operator>>(std::istream &in, ProgressTracker& pt) //ADL detection
	{
		if(pt.r_object != 0)
			{
				char *buffer = new char[1024]; //Won't know how many bytes there will be, so a random high number will do

				in.get(buffer, 1024); //\0 automagically added!

				pt.r_object->Newline(); //adds a new line
				pt.r_object->AppendText(buffer); //adds the text
			}
			return in; //returns the istream
	}

	virtual ~ProgressTracker(); //virtual destructor, in case I actually need to change this
protected:
public:
	//ToDo: add progress guage/bar here
	wxRichTextCtrl *r_object = 0;
};

#endif