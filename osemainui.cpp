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
  mainsizer   = new wxFlexGridSizer(6, 1, 0, 0); //creates a new flexgridsizer
	horizontal1 = new wxFlexGridSizer(1, 3, 0, 0); //creates a new flexgridsizer
	horizontal2 = new wxFlexGridSizer(1, 3, 0, 0); //creates a new flexgridsizer
	horizontal3 = new wxFlexGridSizer(1, 1, 0, 0); //creates a new flexgridsizer
	horizontal4 = new wxFlexGridSizer(1, 1, 0, 0); //creates a new flexgridsizer
	horizontal5 = new wxFlexGridSizer(1, 2, 0, 0); //creates a new flexgridsizer

  labelfrom   = new wxStaticText(this, ID_LabelFrom, "From: "); //creates a label
  labelto     = new wxStaticText(this, ID_LabelTo, "To: "); //creates a label
  labelstatus = new wxStaticText(this, ID_StatusLabel, "Done."); //creates a label

  buttonfrom  = new wxButton(this, ID_ButtonFrom, "..."); //creates a button
  buttonto    = new wxButton(this, ID_ButtonTo, "..."); //creates a button
	buttonstart = new wxButton(this, ID_StartButton, "Start"); //creates a button
	buttonstop 	= new wxButton(this, ID_StopButton, "Stop"); //creates a button

	textboxfrom = new wxTextCtrl(this, ID_TexboxFrom, wxEmptyString); //creates a textbox
	textboxto 	= new wxTextCtrl(this, ID_TextboxTo, wxEmptyString); //creates a textbox

	gaugemain		= new wxGauge(this, ID_MainGauge, 100); //creates a gauge

	/*Sizering objects*/
	mainsizer->Add(horizontal1);
	mainsizer->Add(horizontal2);
	mainsizer->Add(horizontal3);
	mainsizer->Add(horizontal4);
	mainsizer->Add(horizontal5);

	horizontal1->Add(labelfrom);
	horizontal1->Add(textboxfrom);
	horizontal1->Add(buttonfrom);

	horizontal2->Add(labelto);
	horizontal2->Add(textboxto);
	horizontal2->Add(buttonto);

	horizontal3->Add(labelstatus);

	horizontal4->Add(gaugemain);

	horizontal5->Add(buttonstart);
	horizontal5->Add(buttonstop);

	/*Tweaks*/
	buttonstop->Disable();

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
