#include "osemainui.h"
#include "ProgressTracker.h"
#include "commandHandler.h"

//Boost includes
#include <boost/filesystem.hpp>

wxBEGIN_EVENT_TABLE(OSEMainUI, wxFrame)
	EVT_CLOSE(OSEMainUI::OnClose)
	EVT_BUTTON(OSEMainUI::ID_StartButton, OSEMainUI::OnStartClick)
	EVT_BUTTON(OSEMainUI::ID_StopButton, OSEMainUI::OnStopClick)
	EVT_BUTTON(OSEMainUI::ID_ButtonTo, OSEMainUI::OnToClick)
	EVT_BUTTON(OSEMainUI::ID_ButtonFrom, OSEMainUI::OnFromClick)
wxEND_EVENT_TABLE()

OSEMainUI::OSEMainUI(wxWindow *const parent, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(parent, wxID_ANY, title, pos, size)
{
	if (parent != NULL)
	{
		parent->Hide();
	}

	/*Creating objects*/
  mainsizer   = new wxFlexGridSizer(6, 1, 3, 0); //creates a new flexgridsizer
	horizontal1 = new wxFlexGridSizer(1, 3, 0, 5); //creates a new flexgridsizer
	horizontal2 = new wxFlexGridSizer(1, 3, 0, 5); //creates a new flexgridsizer
	horizontal3 = new wxFlexGridSizer(1, 1, 0, 5); //creates a new flexgridsizer
	horizontal4 = new wxFlexGridSizer(1, 1, 0, 5); //creates a new flexgridsizer
	horizontal5 = new wxFlexGridSizer(1, 2, 0, 5); //creates a new flexgridsizer

  labelfrom   = new wxStaticText(this, ID_LabelFrom, "From: "); //creates a label
  labelto     = new wxStaticText(this, ID_LabelTo, "To: "); //creates a label
  labelstatus = new wxStaticText(this, ID_StatusLabel, "Done."); //creates a label

  buttonfrom  = new wxButton(this, ID_ButtonFrom, "Browse"); //creates a button
  buttonto    = new wxButton(this, ID_ButtonTo, "Browse"); //creates a button
	buttonstart = new wxButton(this, ID_StartButton, "Start"); //creates a button
	buttonstop 	= new wxButton(this, ID_StopButton, "Stop"); //creates a button

	textboxfrom = new wxTextCtrl(this, ID_TexboxFrom, wxEmptyString); //creates a textbox
	textboxto 	= new wxTextCtrl(this, ID_TextboxTo, wxEmptyString); //creates a textbox

	gaugemain		= new wxGauge(this, ID_MainGauge, 100, wxDefaultPosition, wxDefaultSize, wxGA_SMOOTH | wxGA_PROGRESS); //creates a gauge

	/*Sizering objects*/
	mainsizer->Add(horizontal1, wxSizerFlags().Expand().Proportion(0));
	mainsizer->Add(horizontal2, wxSizerFlags().Expand().Proportion(0));
	mainsizer->Add(horizontal3, wxSizerFlags().Expand().Proportion(0));
	mainsizer->Add(horizontal4, wxSizerFlags().Expand().Proportion(0));
	mainsizer->Add(horizontal5, wxSizerFlags().Right());

	horizontal1->Add(labelfrom, wxSizerFlags().Right());
	horizontal1->Add(textboxfrom, wxSizerFlags().Expand().Proportion(0));
	horizontal1->Add(buttonfrom, wxSizerFlags().Left());

	horizontal2->Add(labelto, wxSizerFlags().Right());
	horizontal2->Add(textboxto, wxSizerFlags().Expand().Proportion(0));
	horizontal2->Add(buttonto, wxSizerFlags().Left());

	horizontal3->Add(labelstatus, wxSizerFlags().Left());

	horizontal4->Add(gaugemain, wxSizerFlags().Expand().Border(wxLEFT | wxRIGHT, 5));

	horizontal5->Add(buttonstart, wxSizerFlags().Right());
	horizontal5->Add(buttonstop, wxSizerFlags().Right());

	/*Tweaks*/
	buttonstop->Disable();
	SetMinClientSize(wxSize(300, 200)); //sets the minimum client size
	SetSize(GetMinClientSize()); //sets the current client size to the minimum client size
	SetBackgroundColour(*wxLIGHT_GREY); //makes the background white

	/*Sizer tweaks*/
	mainsizer->AddGrowableCol(0);
	horizontal1->AddGrowableCol(1);
	horizontal2->AddGrowableCol(1);
	horizontal4->AddGrowableCol(0);

	/*Sets the sizer*/
	this->SetSizer(mainsizer); //sets the sizer

	/*Binds*/
	this->Bind(wxEVT_THREAD, &OSEMainUI::OnThread, this); //declares thread event to use OnThread
}

void OSEMainUI::OnStartClick(wxCommandEvent& event)
{
	namespace fs = boost::filesystem;
	if (textboxfrom->GetLabel() == "" || textboxto->GetLabel() == "" )
		{
			wxMessageDialog msgdlg(this, "Please fill in both fields!", "Empty fields", wxOK|wxCENTRE|wxICON_EXCLAMATION);
			msgdlg.ShowModal(); //shows the dialog
			return;
		}

	if (!fs::exists(fs::path(textboxfrom->GetLabel())) || !fs::exists(fs::path(textboxto->GetLabel())))
		{
			wxMessageDialog msgdlg(this, "Directories does not exist!", "Directory does not exist", wxOK|wxCENTRE|wxICON_EXCLAMATION);
			msgdlg.ShowModal(); //shows the dialog
			return;
		}

	currentProgressTracker 	= new ProgressTracker(labelstatus, gaugemain, this); //assigns a new progress tracker
	currentCommandHandler 	= new CommandHandler(); //creates a new command handler

	commandThread 					= new boost::thread(CommandHandler::processCommand, currentCommandHandler, std::string("OsuTag -i \"") + textboxfrom->GetLabel().ToStdString() + std::string("\" -o \"") + textboxto->GetLabel().ToStdString() + std::string("\""), currentProgressTracker); //thread started

	this->DisableStuff(); //disables the whole window
}

void OSEMainUI::OnStopClick(wxCommandEvent& event){/*to be implemented*/}

void OSEMainUI::OnFromClick(wxCommandEvent& event)
{
  wxDirDialog folderdlg(this, "Find your osu! song folder", "C:/", wxDD_DIR_MUST_EXIST);
	if (folderdlg.ShowModal() == wxID_CANCEL) //if the user cancels the operation, do nothing
		return;

	textboxfrom->SetLabel(folderdlg.GetPath()); //gets the path and places it onto the textbox
}

void OSEMainUI::OnToClick(wxCommandEvent& event)
{
	wxDirDialog folderdlg(this, "Save the song to where?", "C:/", wxDD_DEFAULT_STYLE);
	if (folderdlg.ShowModal() == wxID_CANCEL) //if the user cancels the operation, do nothing
		return;

	if (!boost::filesystem::is_directory(boost::filesystem::path(folderdlg.GetPath()))) //if the path is not a directory
	{
		wxMessageDialog msgdlg(this, "There is no such directory. Create a new directory?", "Directory specified not found", wxYES_NO | wxICON_QUESTION);
		if (msgdlg.ShowModal() == wxID_YES) //if the user presses yes
		{
			boost::filesystem::create_directory(boost::filesystem::path(folderdlg.GetPath())); //creates the path
		}
	}

	textboxto->SetLabel(folderdlg.GetPath()); //gets the path and places it onto the textbox
}

void OSEMainUI::OnThread(wxThreadEvent& event)
{
	std::function<void()> toExecute = event.GetPayload<std::function<void()>>(); //gets the payload
	toExecute(); //runs the event
}

void OSEMainUI::OnClose(wxCloseEvent& event)
{
	if(GetParent() != NULL) //the only parent in this case would be consoleScreen
		GetParent()->Show();

	Destroy(); //releases memory
}

void OSEMainUI::UndoThread()
{
	if (commandThread != 0)
	{
		commandThread->join(); //waits for the joining of thread
		delete commandThread; delete currentProgressTracker; delete currentCommandHandler;
		this->EnableStuff();
		labelstatus->SetLabel("Done.");
	}
}

void OSEMainUI::EnableStuff()
{
	buttonfrom->Enable();
	buttonto->Enable();
	buttonstart->Enable();

	textboxfrom->Enable();
	textboxto->Enable();
}

void OSEMainUI::DisableStuff()
{
	buttonfrom->Disable();
	buttonto->Disable();
	buttonstart->Disable();

	textboxfrom->Disable();
	textboxto->Disable();
}

OSEMainUI::~OSEMainUI()
{/*trigger(massExtinction)*/}
