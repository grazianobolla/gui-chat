#include "InterfaceManager.h"

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
	address_interface->show();
}

void InterfaceManager::ShowLoginWindow() {
	HideAll();
	login_interface->show();
}

void InterfaceManager::ShowRegisterWindow() {
	HideAll();
	register_interface->show();
}

void InterfaceManager::ShowChatWindow() {
	HideAll();
	chat_interface->show();
}