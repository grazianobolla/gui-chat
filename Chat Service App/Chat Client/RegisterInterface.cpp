#include "RegisterInterface.h"
#include "Client.h"

namespace register_ui {
	Client * client;
}

RegisterInterface::RegisterInterface(void * data) : Fl_Double_Window(315, 166, "Register Window") {
	register_ui::client = (Client *)data;

	username_input = new Fl_Input(130, 19, 155, 25, "Username");
	password_input = new Fl_Input(130, 52, 155, 25, "Password");
	repeat_password_input = new Fl_Input(130, 85, 155, 25, "Repeat Password");

	register_button = new Fl_Return_Button(97, 130, 120, 25, "Register");
	register_button->callback(RegisterButtonCallback);

	this->callback(CloseRegisterWindowCallback);
	this->end();
}

void RegisterButtonCallback(Fl_Widget *, void *) {
	std::string username = register_ui::client->interface_manager->register_interface->username_input->value();
	std::string password = register_ui::client->interface_manager->register_interface->password_input->value();
	std::string repeat_password = register_ui::client->interface_manager->register_interface->repeat_password_input->value();

	if (repeat_password != password) fl_alert("The passwords do not match.");
	else if (username.size() <= 4 || username.size() > 16) fl_alert("Username length must be between four and sixteen characters.");
	else if (password.size() <= 6 || username.size() > 32) fl_alert("Password length must be between six and thirty-two characters.");
	else {
		register_ui::client->Register(username, password);
	}
}

void CloseRegisterWindowCallback(Fl_Widget *, void *) {
	register_ui::client->interface_manager->ShowLoginWindow();
}