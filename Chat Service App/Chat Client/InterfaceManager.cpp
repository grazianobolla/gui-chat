#include "InterfaceManager.h"


void GetCenterPos(Fl_Widget * widget, int & x, int & y) {
	Fl::get_mouse(x, y);
	x -= widget->w() / 2;
	y -= widget->h() / 2;
}

InterfaceManager::InterfaceManager(void * data) {
	address_interface = new AddressInterface(data);
	login_interface = new LoginInterface(data);
	register_interface = new RegisterInterface(data);
	chat_interface = new ChatInterface(data);
}

void InterfaceManager::HideAll() {
	address_interface->hide();
	login_interface->hide();
	register_interface->hide();
	chat_interface->hide();
}

void InterfaceManager::ShowAddressWindow() {
	HideAll();
	int x, y; GetCenterPos(address_interface, x, y);
	address_interface->position(x, y);
	address_interface->show();
}

void InterfaceManager::ShowLoginWindow() {
	HideAll();
	int x, y; GetCenterPos(address_interface, x, y);
	login_interface->position(x, y);
	login_interface->show();
}

void InterfaceManager::ShowRegisterWindow() {
	HideAll();
	int x, y; GetCenterPos(address_interface, x, y);
	register_interface->position(x, y);
	register_interface->show();
}

void InterfaceManager::ShowChatWindow() {
	HideAll();
	int x, y; GetCenterPos(address_interface, x, y);
	chat_interface->position(x, y);
	chat_interface->show();
}