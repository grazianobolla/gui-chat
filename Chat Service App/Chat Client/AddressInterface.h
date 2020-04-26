#pragma once
#define WIN32

#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>

class AddressInterface : public Fl_Double_Window {
	Fl_Return_Button * connect_button;
public:
	Fl_Input * address_input;
	AddressInterface(void *);
};

void ConnectButtonCallback(Fl_Widget *, void *);