#include "LoginInterface.h"
#include "Mediator.h"

namespace log_ui{
     Mediator * mediator;
}

LoginInterface::LoginInterface(void * data) : Fl_Double_Window(242, 152, "Login Window") {
     log_ui::mediator = (Mediator *)data;
	server_address = new Fl_Input(100, 17, 115, 25, "Address");
	server_address->value("localHost");

	username_input = new Fl_Input(100, 49, 115, 25, "Username");
	password_input = new Fl_Secret_Input(100, 80, 115, 25, "Password");

	login_button = new Fl_Return_Button(10, 120, 100, 25, "Login");
	login_button->callback(LoginButtonCallback, data);

	register_button = new Fl_Button(145, 120, 90, 25, "Register");
	register_button->callback(RegisterButtonCallback, data);
	this->end();
	this->show();
}

void LoginButtonCallback(Fl_Widget *, void * data) {
	std::string address = log_ui::mediator->login_interface->server_address->value();
	std::string username = log_ui::mediator->login_interface->username_input->value();
	std::string password = log_ui::mediator->login_interface->password_input->value();

	if (address.size() <= 0) fl_alert("The address is too short.");
	else if (username.size() <= 6 || username.size() > 16) fl_alert("Username length must be between six and sixteen characters.");
	else if (password.size() <= 6 || username.size() > 32) fl_alert("Password length must be between six and thirty-two characters.");
	else log_ui::mediator->Login(address.c_str(), username, password);
}

void RegisterButtonCallback(Fl_Widget *, void * data) {
	log_ui::mediator->Register();
}
