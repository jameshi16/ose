#include "main.h"

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