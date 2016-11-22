/*headers copied and pasted from wxWidgets website*/
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#ifndef MAINENTRY
#define MAINENTRY

/// MainApp, entry to wxWidgets
class OSEMainApp : public wxApp
{
public:
	virtual bool OnInit();
};

//This is the entry point of the application, essentially.
wxIMPLEMENT_APP(OSEMainApp);


#endif /* This is essentially the code for main.h */
