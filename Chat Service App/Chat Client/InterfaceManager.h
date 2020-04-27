#pragma once
#include "AddressInterface.h"
#include "LoginInterface.h"
#include "RegisterInterface.h"
#include "ChatInterface.h"

class InterfaceManager {
public:
	AddressInterface * address_interface;
	LoginInterface * login_interface;
	RegisterInterface * register_interface;
	ChatInterface * chat_interface;

	InterfaceManager(void *);

	void HideAll();
	void ShowAddressWindow();
	void ShowLoginWindow();
	void ShowRegisterWindow();
	void ShowChatWindow();
};