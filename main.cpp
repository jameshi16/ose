#include "main.h"

#include "consoleScreen.h"
#include "osemainui.h"

/* Can use compiler preprocessor to do this */
#ifndef DEBUGMODE
#define DEBUGMODE 0
#endif

bool OSEMainApp::OnInit()
{
	if (DEBUGMODE == 1) //if debug mode is on
	{
		consoleScreen *cs = new consoleScreen();
		cs->Show(true);
		return true;
	}

	OSEMainUI *omu = new OSEMainUI(NULL, "osu! Song Extractor", wxDefaultPosition, wxDefaultSize);
	omu->Show(true);
	return true;
}
