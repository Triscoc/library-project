#include "MainFrame.h"
#include "LoginFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <fstream>
#include <sstream>

MainFrame::MainFrame(const wxString& title, LoginFrame* loginFrame) : wxFrame(nullptr, wxID_ANY, title) {
	ID = loginFrame->getID();
	loginFrame->Destroy();

	wxPanel* panel = new wxPanel(this);
	wxStaticText* libraryText = new wxStaticText(panel, wxID_ANY, "My Library", wxPoint(10,20), wxSize(120,-1));
}


