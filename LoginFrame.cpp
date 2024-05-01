#include "LoginFrame.h"
#include "MainFrame.h"
#include "RegisterFrame.h"
#include "User.h"
#include "Variables.h"
#include <wx/msgdlg.h>
#include <wx/wx.h>
#include <vector>




LoginFrame::LoginFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

	wxPanel* panel = new wxPanel(this);
	
	wxFont headerFont(wxFontInfo(15).Bold());
	wxFont smallFont(wxFontInfo(12));


	wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(150,295));
	wxButton* registerButton = new wxButton(panel, wxID_ANY, "Register", wxPoint(250,295));

	userID = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(250,160), wxSize(150,-1), wxTE_PROCESS_ENTER);
	password = new wxTextCtrl(panel, wxID_ANY, "",wxPoint(250,220), wxSize(150,-1), wxTE_PASSWORD | wxTE_PROCESS_ENTER);

	wxStaticText* loginText = new wxStaticText(panel, wxID_ANY, "Login", wxPoint(60, 65), wxSize(80, -1));
	wxStaticText* idText = new wxStaticText(panel, wxID_ANY, "User ID", wxPoint(120, 160), wxSize(80, -1));
	wxStaticText* passwordText = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(120, 220), wxSize(80, -1));

	loginText->SetFont(headerFont);

	idText->SetFont(smallFont);
	passwordText->SetFont(smallFont);
	userID->SetFont(smallFont);
	password->SetFont(smallFont);



	loginButton->Bind(wxEVT_BUTTON, &LoginFrame::onLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &LoginFrame::onRegisterButtonClicked, this);
	userID->Bind(wxEVT_TEXT_ENTER, &LoginFrame::onLoginButtonClicked, this);
	password->Bind(wxEVT_TEXT_ENTER, &LoginFrame::onLoginButtonClicked, this);
	
}

std::vector<User> LoginFrame::getUser()
{
	std::vector<User> userData = users.readFile();
	return userData;
}


void LoginFrame::onLoginButtonClicked(wxCommandEvent& evt)
{
	wxString id = userID->GetValue();
	wxString pass = password->GetValue();

	if (users.authenticate(id.ToStdString(), pass.ToStdString(), getUser())) {
		this->Hide();
		
		setID(id.ToStdString());
		MainFrame* mainFrame = new MainFrame("Library Management System", this);
		mainFrame->SetClientSize(800, 600);
		mainFrame->Center();
		mainFrame->Show();
	}
	else {
		wxMessageBox("User ID or password is wrong. Please re-enter.", "Error", wxOK | wxICON_ERROR, this);
	}
}

void LoginFrame::onRegisterButtonClicked(wxCommandEvent& evt)
{
	this->Hide();
	RegisterFrame* registerFrame = new RegisterFrame("Library Management System", this);
	registerFrame->SetClientSize(800, 600);
	registerFrame->Center();
	registerFrame->Show();
}

void LoginFrame::setID(const std::string& aID)
{
	ID = aID;
}

std::string LoginFrame::getID() {
	return ID;
}
