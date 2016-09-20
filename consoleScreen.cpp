#include "consoleScreen.h"

//Self-declared headers
#include "commandHandler.h"
#include "ProgressTracker.h"

wxBEGIN_EVENT_TABLE(consoleScreen, wxFrame)
	EVT_TEXT_ENTER(ID_TextCtrl1, consoleScreen::CommandTextCtrlEnter)
wxEND_EVENT_TABLE()


consoleScreen::consoleScreen() : wxFrame(NULL, wxID_ANY, "Console", wxDefaultPosition, wxDefaultSize)
{
	Centre(); //centers the frame
	SetMinClientSize(wxSize(800, 600)); //makes this the default size
	SetSize(GetMinClientSize()); //and also makes this the current size

	//(* Initialize objects
	mainSizer 		= new wxFlexGridSizer(2, 1, 0, 0); //rows, cols, vgap, hgap
	richTextCtrl1 	= new wxRichTextCtrl(this, ID_RichTextCtrl1, "This textbox is currently blank");
	textCtrl1 		= new wxTextCtrl(this, ID_TextCtrl1, "");
	//*)

	//(* Main Sizer configuration
	mainSizer->AddGrowableCol(0); //adds first column as growable
	mainSizer->AddGrowableRow(0); //adds first row as growable
	//*)

	//Add objects to sizer
	mainSizer->Add(richTextCtrl1, wxSizerFlags().Expand());
	mainSizer->Add(textCtrl1, wxSizerFlags().Expand());

	//（*Configure appearance of controls
	richTextCtrl1->SetBackgroundColour(*wxBLACK);
	richTextCtrl1->Disable();
	richTextCtrl1->BeginTextColour(*wxWHITE);
	richTextCtrl1->WriteText("Copyright (c) JamesLab Softwares 2016");
	richTextCtrl1->Newline();

	textCtrl1->SetHelpText("Command goes here");
	//*)
	SetSizer(mainSizer); //sets the sizer

	//Connects (only used when MACROS doesn't let me define an id ;-;)
	textCtrl1->Bind(wxEVT_KEY_DOWN, &consoleScreen::CommandTextCtrlKeyDown, this);
}

consoleScreen::~consoleScreen()
{
	//trigger(massextinction);
}

void consoleScreen::CommandTextCtrlEnter(wxCommandEvent& event)
{
	//Makes use of commandHandler
	ProgressTracker *pt = new ProgressTracker(richTextCtrl1);
	CommandHandler(textCtrl1->GetValue().ToStdString(), pt); //sends command to commandHandler
	textCtrl1->Clear(); //clears the text box
	delete pt; //deletes the pointer
}

void consoleScreen::CommandTextCtrlKeyDown(wxKeyEvent& event)
{
	//Return the event first
	event.Skip(); //"skip"

	//Detects if CTRL is held
	if (event.GetModifiers() == wxMOD_CONTROL)
	{
		switch(event.GetKeyCode())
		{
			case 'A':
				textCtrl1->SetSelection(-1, -1); //select all text!
			break;

			default:
			break;
		}
	}
}
