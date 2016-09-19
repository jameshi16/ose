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
	init->Newline(); //add new line
	init->AppendText("ProgressTracker initialized for this instance."); //adds some weird matrix-like text
}

ProgressTracker::~ProgressTracker()
{
	//destory world
}

