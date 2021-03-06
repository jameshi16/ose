/*headers copied and pasted from wxWidgets website*/
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#ifndef consoleScreenHEADER
#define consoleScreenHEADER

#include <vector>
#include <string>

#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/colour.h>
#include <wx/thread.h>

#include <boost/thread.hpp>

class ProgressTracker; //forward
class CommandHandler; //declaration

class consoleScreen : public wxFrame
{
public:
	consoleScreen(wxWindow* parent = NULL);
	~consoleScreen();

	//Member UI elements represented in IDs (also, anonymous enum, so it can be accessed anywhere)
	enum:long
	{
		ID_MainSizer, //not needed
		ID_RichTextCtrl1,
		ID_TextCtrl1,
		ID_Thread
	};

	//Member UI elements
	wxFlexGridSizer 	*mainSizer;
	wxRichTextCtrl 		*richTextCtrl1;
	wxTextCtrl 				*textCtrl1;

	//Mass extinction
	void undoThread();
protected:
private:
	//necessary wxWidgets thing
	wxDECLARE_EVENT_TABLE();

	//Events
	void CommandTextCtrlEnter(wxCommandEvent&);
	void CommandTextCtrlKeyDown(wxKeyEvent&);
	void outputTextCtrlTextChange(wxCommandEvent&);
	void handleThreadedEvent(wxThreadEvent&);
	void OnClose(wxCloseEvent&);

	//Variable
	std::vector<std::string> lastLines 			= {};
	int n_howManyTimesUpHasBeenPressed 			= 0;
	boost::thread *workThread 							= 0;
	ProgressTracker *activeProgressTracker 	= 0;
	CommandHandler *activeCommandHandler		= 0;
};

#endif
