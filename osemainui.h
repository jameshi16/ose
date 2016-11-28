/*headers copied and pasted from wxWidgets website*/
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#ifndef OSEMAINUI
#define OSEMAINUI

#include "boost/thread.hpp"

class ProgressTracker; //forward declaration
class CommandHandler; //forward declaration

///The UI.
class OSEMainUI : public wxFrame
{
public:
	OSEMainUI(wxWindow *const parent, const wxString& title, const wxPoint& pos, const wxSize& size);

  /*IDs of the objects*/
  enum:long
  {
    ID_LabelFrom,
    ID_LabelTo,
    ID_TexboxFrom,
    ID_TextboxTo,
    ID_ButtonFrom,
    ID_ButtonTo,
    ID_StatusLabel,
    ID_MainGauge,
    ID_StartButton,
    ID_StopButton
  };

  /*Objects*/
  wxStaticText *labelfrom;
  wxStaticText *labelto;
  wxStaticText *labelstatus;

  wxButton *buttonfrom;
  wxButton *buttonto;
  wxButton *buttonstart;
  wxButton *buttonstop;

  wxTextCtrl *textboxfrom;
  wxTextCtrl *textboxto;

  wxGauge *gaugemain;

  /*Sizers*/
  wxFlexGridSizer *mainsizer;
	wxFlexGridSizer *horizontal1; //the sizer containing from labels, buttons and textbox
	wxFlexGridSizer *horizontal2; //the sizer containing to labels, buttons and textbox
	wxFlexGridSizer *horizontal3; //the sizer containing the status label
	wxFlexGridSizer *horizontal4; //the sizer containing the gauge
	wxFlexGridSizer *horizontal5; //the sizer containing the buttons, start and cancel

	~OSEMainUI();
private:

	/*Event Handlers*/
	void OnThread(wxThreadEvent&);
	void OnClose(wxCloseEvent&);
	void OnStartClick(wxCommandEvent&);
	void OnStopClick(wxCommandEvent&);
	void OnFromClick(wxCommandEvent&);
	void OnToClick(wxCommandEvent&);

	/*Extra functions*/
	void UndoThread(); //called by sub thread to free the thread

	/*Variables*/
	boost::thread *commandThread							= 0;
	ProgressTracker *currentProgressTracker		= 0;
	CommandHandler *currentCommandHandler			= 0;


	//Necessary wxWidgets thing
	wxDECLARE_EVENT_TABLE();
};

#endif //header guards
