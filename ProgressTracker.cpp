#include "ProgressTracker.h"

ProgressTracker::ProgressTracker() : r_object(0)
{
	//constructor
}

ProgressTracker::ProgressTracker(wxRichTextCtrl* w)
{
	initialize(w); //initializes with given pointer
}

void ProgressTracker::initialize(wxRichTextCtrl* init)
{
	//Initialize!
	r_object = init; //makes r_object initialized.
}

void ProgressTracker::clear()
{
	r_object->Clear(); //clears the paragraph
}

ProgressTracker::~ProgressTracker()
{
	//destory world
}
