/*headers copied and pasted from wxWidgets website*/
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#ifndef OSEMAINUI
#define OSEMAINUI

/// MainApp, entry to wxWidgets
class OSEMainApp : public wxApp
{
public:
	virtual bool OnInit();
};

///The UI.
class OSEMainUI : public wxFrame
{
public:
	OSEMainUI(const wxString& title, const wxPoint& pos, const wxSize& size);

private:

	//Necessary wxWidgets thing
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(OSEMainUI, wxFrame)
wxEND_EVENT_TABLE()

//This is the entry point of the application, essentially.
wxIMPLEMENT_APP(OSEMainApp);


#endif /* This is essentially the code for main.h */