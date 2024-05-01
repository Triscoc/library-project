#include "RegisterFrame.h"
#include "LoginFrame.h"
#include <wx/msgdlg.h>
#include <wx/wx.h>
#include <fstream>
#include <sstream>

RegisterFrame::RegisterFrame(const wxString& title, LoginFrame* loginFrame) : wxFrame(nullptr, wxID_ANY, title), loginFrame(loginFrame)
{
	wxPanel* panel = new wxPanel(this);

	wxStaticText* registerText = new wxStaticText(panel, wxID_ANY, "Register", wxPoint(60, 65), wxSize(80, -1));
	wxStaticText* firstNameText = new wxStaticText(panel, wxID_ANY, "First Name", wxPoint(120, 160), wxSize(120, -1));
	wxStaticText* lastNameText = new wxStaticText(panel, wxID_ANY, "Last Name", wxPoint(120, 200), wxSize(120, -1));
	wxStaticText* userIDText = new wxStaticText(panel, wxID_ANY, "User ID", wxPoint(120, 240), wxSize(120, -1));
	wxStaticText* passwordText = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(120, 280), wxSize(120, -1));
	wxStaticText* confirmPasswordText = new wxStaticText(panel, wxID_ANY, "Confirm Password", wxPoint(120, 320), wxSize(120, -1));

	firstNameFill = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(240, 160), wxSize(120, -1), wxTE_PROCESS_ENTER);
	lastNameFill = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(240, 200), wxSize(120, -1), wxTE_PROCESS_ENTER);
	userIDFill = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(240, 240), wxSize(120, -1), wxTE_PROCESS_ENTER);
	passwordFill = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(240, 280), wxSize(120, -1), wxTE_PASSWORD | wxTE_PROCESS_ENTER);
	confirmPasswordFill = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(240, 320), wxSize(120, -1), wxTE_PASSWORD | wxTE_PROCESS_ENTER);
	adminCheckBox = new wxCheckBox(panel, wxID_ANY,"Admin", wxPoint(120, 360), wxDefaultSize);

	wxButton* registerButton = new wxButton(panel, wxID_ANY, "Register", wxPoint(120, 400), wxSize(120,-1));
	registerButton->Bind(wxEVT_BUTTON, &RegisterFrame::onRegisterButtonClicked, this);
	firstNameFill->Bind(wxEVT_TEXT_ENTER, &RegisterFrame::onRegisterButtonClicked, this);
	lastNameFill->Bind(wxEVT_TEXT_ENTER, &RegisterFrame::onRegisterButtonClicked, this);
	userIDFill->Bind(wxEVT_TEXT_ENTER, &RegisterFrame::onRegisterButtonClicked, this);
	passwordFill->Bind(wxEVT_TEXT_ENTER, &RegisterFrame::onRegisterButtonClicked, this);
	confirmPasswordFill->Bind(wxEVT_TEXT_ENTER, &RegisterFrame::onRegisterButtonClicked, this);

	Bind(wxEVT_CLOSE_WINDOW, &RegisterFrame::OnClose, this);

}

void RegisterFrame::onRegisterButtonClicked(wxCommandEvent& evt)
{
	wxString firstName = firstNameFill->GetValue();
	wxString lastName = lastNameFill->GetValue();
	wxString userID = userIDFill->GetValue();
	wxString password = passwordFill->GetValue();
	wxString confirmPassword = confirmPasswordFill->GetValue();
	bool admin = adminCheckBox->GetValue();


	if (password != confirmPassword) {
		wxMessageBox("Password and confirm password did not match. Please re-enter.", "Error", wxOK | wxICON_ERROR, this);
	}
	else if(checkDuplicate(userID.ToStdString())){
		wxMessageBox("ID already existed. Please re-enter.", "Error", wxOK | wxICON_ERROR, this);
	}
	else {
		writeFile(firstName.ToStdString(), lastName.ToStdString(), userID.ToStdString(), password.ToStdString(), admin);
		Destroy();
		loginFrame->Show();
	}
}

void RegisterFrame::writeFile(const std::string& firstName,const std::string& lastName,const std::string& userID,const std::string& password,const bool& admin)
{
	std::ofstream outFile(idPass, std::ios::app);
	if (!outFile.is_open()) {
		wxMessageBox("Failed to open file.", "Error", wxOK | wxICON_ERROR, this);
	}
	else {
		if (admin) {
			outFile << firstName << " " << lastName << " " << userID << " " << password << " 1" << std::endl;
		}
		else {
			outFile << firstName << " " << lastName << " " << userID << " " << password << " 0" << std::endl;
		}
		outFile.close();
	}
}



void RegisterFrame::OnClose(const wxCloseEvent& evt)
{
	Destroy();
	//Hide()
	loginFrame->Show();
}

bool RegisterFrame::checkDuplicate(std::string ID) {

	std::ifstream inFile(idPass);
	if (!inFile.is_open()) {
		wxMessageBox("Failed to open file", "Error", wxOK | wxICON_ERROR, this);
		return false;
	}
	else {
		std::string line;
		while (std::getline(inFile, line)) {
			std::istringstream iss(line);
			std::string firstName, lastName, userID, password, authority;
			iss >> firstName >> lastName >> userID >> password >> authority;
			if (userID == ID) {
				return true;
			}
		}
		return false;
	}
}
