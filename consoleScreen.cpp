#include "consoleScreen.h"
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
	textCtrl1 		= new wxTextCtrl(this, ID_TextCtrl1, "Type your command");
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
	richTextCtrl1->BeginTextColour(*wxWHITE);
	richTextCtrl1->Disable();

	textCtrl1->SetHelpText("Command goes here");
	//*)
	SetSizer(mainSizer); //sets the sizer
}

consoleScreen::~consoleScreen()
{
	//trigger(massextinction);
}

void consoleScreen::CommandTextCtrlEnter(wxCommandEvent& event)
{
	//Submit something
}
