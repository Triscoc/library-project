#include "App.h"
#include "MainFrame.h"
#include "LoginFrame.h"
#include <wx/wx.h>

bool App::OnInit() {
	LoginFrame* loginFrame = new LoginFrame("Library Management System");
	loginFrame->SetClientSize(800, 600);
	loginFrame->Center();
	loginFrame->Show();
	return true;
}