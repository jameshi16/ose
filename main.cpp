#include "main.h"
wxBEGIN_EVENT_TABLE(OSEMainUI, wxFrame)
wxEND_EVENT_TABLE()


bool OSEMainApp::OnInit()
{
	OSEMainUI *omu = new OSEMainUI("osu! Song Extractor", wxDefaultPosition, wxDefaultSize);
	omu->Show(true);
	return true;
}


OSEMainUI::OSEMainUI(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	//Insert cool code here
}

OSEMainUI::~OSEMainUI()
{
	//The entire thing disappears
}