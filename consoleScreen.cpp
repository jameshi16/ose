#include "consoleScreen.h"

//Self-declared headers
#include "commandHandler.h"
#include "ProgressTracker.h"

wxBEGIN_EVENT_TABLE(consoleScreen, wxFrame)
	EVT_TEXT_ENTER(ID_TextCtrl1, consoleScreen::CommandTextCtrlEnter)
	EVT_TEXT(ID_RichTextCtrl1, consoleScreen::outputTextCtrlTextChange)
wxEND_EVENT_TABLE()


consoleScreen::consoleScreen() : wxFrame(NULL, wxID_ANY, "Console", wxDefaultPosition, wxDefaultSize)
{
	Centre(); //centers the frame
	SetMinClientSize(wxSize(800, 600)); //makes this the default size
	SetSize(GetMinClientSize()); //and also makes this the current size

	//(* Initialize objects
	mainSizer 		= new wxFlexGridSizer(2, 1, 0, 0); //rows, cols, vgap, hgap
	richTextCtrl1 	= new wxRichTextCtrl(this, ID_RichTextCtrl1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_READONLY); //sets the richtext as readonly
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
	richTextCtrl1->BeginTextColour(*wxWHITE);
	richTextCtrl1->WriteText("Copyright (c) JamesLab Softwares 2016");
	richTextCtrl1->Newline();

	textCtrl1->SetHelpText("Command goes here");
	//*)
	SetSizer(mainSizer); //sets the sizer

	//Binds (only used when MACROS doesn't let me define an id ;-;)
	textCtrl1->Bind(wxEVT_KEY_DOWN, &consoleScreen::CommandTextCtrlKeyDown, this);
	this->Bind(wxEVT_THREAD, &consoleScreen::handleThreadedEvent, this);

	//Focus
	textCtrl1->SetFocus(); //sets textctrl1 as focusable
}

consoleScreen::~consoleScreen()
{/*trigger(massextinction);*/}

void consoleScreen::CommandTextCtrlEnter(wxCommandEvent& event)
{
	activeProgressTracker = new ProgressTracker(richTextCtrl1, this); //assigns the ProgressTracker
	activeCommandHandler = new CommandHandler();
	workThread = new boost::thread(&CommandHandler::processCommand, activeCommandHandler, textCtrl1->GetValue().ToStdString(), activeProgressTracker); //prepares a thread

	lastLines.push_back(textCtrl1->GetValue().ToStdString()); //pushes back the line
	textCtrl1->Clear(); //clears the text box
	textCtrl1->Disable(); //disables the text box
	n_howManyTimesUpHasBeenPressed = 0; //sets the "last command" thingy back to 0
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
				n_howManyTimesUpHasBeenPressed = 0;
			break;
		}
	}

	//Detects if no mods are held
	if (!event.HasAnyModifiers())
	{
		if (lastLines.size() != 0)
		{
			switch(event.GetKeyCode())
			{
				case WXK_UP:
					if (static_cast<unsigned int>(n_howManyTimesUpHasBeenPressed) > (lastLines.size() - 1))
						break;

					textCtrl1->SetValue(lastLines[lastLines.size() - 1 - n_howManyTimesUpHasBeenPressed]);
					n_howManyTimesUpHasBeenPressed++;
					break;

				case WXK_DOWN:
					if (n_howManyTimesUpHasBeenPressed == 0)
						break;

					n_howManyTimesUpHasBeenPressed--;
					textCtrl1->SetValue(lastLines[lastLines.size() - 1 - n_howManyTimesUpHasBeenPressed]);
					break;

				default:
					break;
			}
		}
	}
}

void consoleScreen::outputTextCtrlTextChange(wxCommandEvent& event)
{
	event.Skip(); //pass the event to wxWidgets
	//Scroll all the way to the bottom EVERYTIME text changes.
	richTextCtrl1->ShowPosition(richTextCtrl1->GetLastPosition());
}

void consoleScreen::handleThreadedEvent(wxThreadEvent& event)
{
	std::function<void()> threadedPayload = event.GetPayload<std::function<void()>>(); //gets and runs the payload
	threadedPayload(); //runs the payload
}

void consoleScreen::undoThread()
{
	workThread->join(); //waits for the worker thread to join
	delete workThread; delete activeCommandHandler; delete activeProgressTracker; //mass deletion
	textCtrl1->Enable(); //enables the text control
}
