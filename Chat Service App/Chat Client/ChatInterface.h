#pragma once
//#define WIN32
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>

class ChatInterface : public Fl_Double_Window {
public:
	Fl_Text_Display * text_display;
	Fl_Text_Buffer * text_display_buffer;

	Fl_Input * message_input;
	Fl_Button * send_button;

	ChatInterface(void *);
	void PrintMessage(std::string, std::string);
};

void SendButtonCallback(Fl_Widget *, void *);
