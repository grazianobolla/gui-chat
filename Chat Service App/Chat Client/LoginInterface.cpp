#include "LoginInterface.h"
#include "Client.h"

namespace log_ui {
	Client * client;
}

LoginInterface::LoginInterface(void * data) : Fl_Double_Window(242, 120, "Login Window") {
	log_ui::client = (Client *)data;

	username_input = new Fl_Input(100, 20, 115, 25, "Username");
	password_input = new Fl_Secret_Input(100, 50, 115, 25, "Password");

	login_button = new Fl_Return_Button(10, 90, 100, 25, "Login");
	login_button->callback(LoginButtonCallback, data);

	register_button = new Fl_Button(145, 90, 90, 25, "Register");
	register_button->callback(OpenRegisterWindowButtonCallback, data);
	this->callback(CloseLoginWindowCallback);
	this->end();
}

void LoginButtonCallback(Fl_Widget *, void *) {
	std::string username = log_ui::client->interface_manager->login_interface->username_input->value();
	std::string password = log_ui::client->interface_manager->login_interface->password_input->value();

	if (username.size() <= 4 || username.size() > 16) fl_alert("Username length must be between four and sixteen characters.");
	else if (password.size() <= 6 || username.size() > 32) fl_alert("Password length must be between six and thirty-two characters.");
	else log_ui::client->Login(username, password);
}

void OpenRegisterWindowButtonCallback(Fl_Widget *, void *) {
	log_ui::client->interface_manager->ShowRegisterWindow();
}

void CloseLoginWindowCallback(Fl_Widget *, void *) {
	log_ui::client->interface_manager->ShowAddressWindow();
}
