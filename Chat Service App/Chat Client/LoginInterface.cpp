#include "LoginInterface.h"
#include "Mediator.h"

LoginInterface::LoginInterface(void * data) : Fl_Double_Window(242, 152, "Login Window") {
	server_address = new Fl_Input(100, 17, 115, 25, "Address");
	server_address->value("localHost");

	username_input = new Fl_Input(100, 49, 115, 25, "Username");
	password_input = new Fl_Input(100, 80, 115, 25, "Password");

	login_button = new Fl_Return_Button(10, 120, 100, 25, "Login");
	login_button->callback(LoginButtonCallback, data);

	register_button = new Fl_Button(145, 120, 90, 25, "Register");
	this->end();
	this->show();
}

void LoginButtonCallback(Fl_Widget *, void * data) {
	Mediator * mediator = (Mediator *)data;
	mediator->Login();
}

void RegisterButtonCallback(Fl_Widget *, void * data) {
	Mediator * mediator = (Mediator *)data;
	//mediator->Register();
}