#pragma once
#include <wx/wx.h>
#include <string>
#include "LoginFrame.h"
#include "Variables.h"
class RegisterFrame : public wxFrame
{
public:
	RegisterFrame(const wxString& title, LoginFrame* loginFrame);
private:
	LoginFrame* loginFrame;

	wxTextCtrl* firstNameFill;
	wxTextCtrl* lastNameFill;
	wxTextCtrl* userIDFill;
	wxTextCtrl* passwordFill;
	wxTextCtrl* confirmPasswordFill;
	wxCheckBox* adminCheckBox;

	void onRegisterButtonClicked(wxCommandEvent& evt);
	void writeFile(const std::string& firstName,const std::string& lastName,const std::string& userID,const std::string& password,const bool& admin);
	void OnClose(const wxCloseEvent& evt);
	bool checkDuplicate(std::string ID);
};

