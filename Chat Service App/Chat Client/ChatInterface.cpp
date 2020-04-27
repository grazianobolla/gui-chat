#include "ChatInterface.h"
#include "Client.h"

namespace chat_ui {
	Client * client;
}

ChatInterface::ChatInterface(void * data) : Fl_Double_Window(367, 244, "Chat Window") {
	chat_ui::client = (Client *)data;

	//Style Colors
	style_table[0] = { FL_RED, FL_COURIER, 16 };
	style_table[1] = { FL_BLUE, FL_COURIER, 16 };
	style_table[2] = { FL_DARK_YELLOW, FL_COURIER, 16 };

	message_input = new Fl_Input(70, 205, 200, 25, "Message");

	text_display = new Fl_Text_Display(10, 5, 345, 195);
	text_display_buffer = new Fl_Text_Buffer();
	text_style_buffer = new Fl_Text_Buffer();

	text_display->buffer(text_display_buffer);
	text_display->highlight_data(text_style_buffer, style_table, sizeof(style_table) / sizeof(style_table[0]), 'Z', 0, 0);

	send_button = new Fl_Return_Button(280, 205, 75, 25, "Send");
	send_button->callback(SendButtonCallback);

	this->callback(CloseWindowCallback);
	this->end();
}

void ChatInterface::PrintMessage(std::string message, char color) {
	Fl::lock();
	std::string msg = std::string(message + "\n");
	text_display_buffer->append(msg.c_str());
	text_style_buffer->append(std::string(msg.size(), color).c_str());
	Fl::unlock();
	Fl::awake();
}

void SendButtonCallback(Fl_Widget *, void * data) {
	std::string input = chat_ui::client->interface_manager->chat_interface->message_input->value();
	if (input.size() < 256) {
		if (input.size() > 0) {
			chat_ui::client->interface_manager->chat_interface->message_input->value("");
			chat_ui::client->interface_manager->chat_interface->PrintMessage("You: " + input, 'B');
			Fl::focus(chat_ui::client->interface_manager->chat_interface->message_input);
			chat_ui::client->Send(input);
		}
	}
	else fl_alert("Input message can't have more than 256 characters.");
}

void CloseWindowCallback(Fl_Widget *, void * data) {
	chat_ui::client->StopChat();
}