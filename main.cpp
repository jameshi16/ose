#include "main.h"

#include "consoleScreen.h"

/* Can use compiler preprocessor to do this */
#ifndef DEBUGMODE
#define DEBUGMODE 0
#endif

wxBEGIN_EVENT_TABLE(OSEMainUI, wxFrame)
wxEND_EVENT_TABLE()


bool OSEMainApp::OnInit()
{
	if (DEBUGMODE == 1) //if debug mode is on
	{
		consoleScreen *cs = new consoleScreen();
		cs->Show(true);
		return true;
	}

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