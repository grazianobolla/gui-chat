#include "AddressInterface.h"
#include "Client.h"

namespace address_ui {
	Client * client;
}

AddressInterface::AddressInterface(void * data) : Fl_Double_Window(261, 90, "Connect Window") {
	address_ui::client = (Client *)data;

	address_input = new Fl_Input(90, 15, 125, 25, "Address");
	address_input->value("localHost");

	connect_button = new Fl_Return_Button(95, 50, 90, 25, "Connect");
	connect_button->callback(ConnectButtonCallback);
	this->end();
}

void ConnectButtonCallback(Fl_Widget *, void *) {
	if (address_ui::client->Connect(address_ui::client->interface_manager->address_interface->address_input->value())) {
		address_ui::client->interface_manager->ShowLoginWindow();
	}
}