/*headers copied and pasted from wxWidgets website*/
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#ifndef consoleScreenHEADER
#define consoleScreenHEADER

#include <wx/richtext/richtextctrl.h>
#include <wx/sizer.h>

class consoleScreen : public wxFrame
{
public:
	consoleScreen();
	~consoleScreen();

	//Member UI elements represented in IDs (also, anonymous enum, so it can be accessed anywhere)
	enum:long
	{
		ID_MainSizer,
		ID_RichTextCtrl1
	};

	//Member UI elements
	wxFlexGridSizer *mainSizer;
	wxRichTextCtrl *richTextCtrl1;

protected:
private:
	//necessary wxWidgets thing
	wxDECLARE_EVENT_TABLE();
};

#endif