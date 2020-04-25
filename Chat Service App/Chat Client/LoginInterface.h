#pragma once
#define WIN32
#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Double_Window.H>

class LoginInterface : public Fl_Double_Window {
public:
	Fl_Input * server_address;
	Fl_Input * username_input;
	Fl_Input * password_input;

	Fl_Return_Button * login_button;
	Fl_Button * register_button;

	LoginInterface(void *);
};

void LoginButtonCallback(Fl_Widget *, void *);
void RegisterButtonCallback(Fl_Widget *, void *);