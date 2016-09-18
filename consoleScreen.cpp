#include "consoleScreen.h"
wxBEGIN_EVENT_TABLE(consoleScreen, wxFrame)
wxEND_EVENT_TABLE()


consoleScreen::consoleScreen() : wxFrame(NULL, wxID_ANY, "Console", wxDefaultPosition, wxDefaultSize)
{
	Centre(); //centers the frame
	richTextCtrl1 = new wxRichTextCtrl(this, ID_RichTextCtrl1, "This textbox is currently blank");
	mainSizer = new wxFlexGridSizer(1, 1, 0, 0);

	SetSizer(mainSizer); //sets the sizer
}

consoleScreen::~consoleScreen()
{
	//trigger(massextinction);
}
