#include "osemainui.h"

wxBEGIN_EVENT_TABLE(OSEMainUI, wxFrame)
	EVT_CLOSE(OSEMainUI::OnClose)
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

	gaugemain		= new wxGauge(this, ID_MainGauge, 100); //creates a gauge

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
	SetBackgroundColour(*wxWHITE); //makes the background white

	/*Sizer tweaks*/
	mainsizer->AddGrowableCol(0);
	horizontal1->AddGrowableCol(1);
	horizontal2->AddGrowableCol(1);
	horizontal4->AddGrowableCol(0);

	/*Sets the sizer*/
	this->SetSizer(mainsizer); //sets the sizer
}

void OSEMainUI::OnClose(wxCloseEvent& event)
{
	if(GetParent() != NULL) //the only parent in this case would be consoleScreen
		GetParent()->Show();

	Destroy(); //releases memory
}

OSEMainUI::~OSEMainUI()
{/*trigger(massExtinction)*/}
