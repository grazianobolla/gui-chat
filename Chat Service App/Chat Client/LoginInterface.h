#pragma once
#define WIN32

#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_ask.H>

class LoginInterface : public Fl_Double_Window {
	Fl_Return_Button * login_button;
	Fl_Button * register_button;
public:
	Fl_Input * username_input;
	Fl_Secret_Input * password_input;

	LoginInterface(void *);
};

void LoginButtonCallback(Fl_Widget *, void *);
void OpenRegisterWindowButtonCallback(Fl_Widget *, void *);
void CloseLoginWindowCallback(Fl_Widget *, void *);
