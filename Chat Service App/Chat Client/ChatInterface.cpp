#include "ChatInterface.h"
#include "Mediator.h"

namespace chat_ui{
     Mediator * mediator;
}

ChatInterface::ChatInterface(void * data) : Fl_Double_Window(367, 244, "Chat Window") {
     chat_ui::mediator = (Mediator *)data;
	text_display = new Fl_Text_Display(10, 5, 345, 195);
	text_display_buffer = new Fl_Text_Buffer();
	text_display->buffer(text_display_buffer);

	message_input = new Fl_Input(70, 205, 200, 25, "Message");

	send_button = new Fl_Return_Button(280, 205, 75, 25, "Send");
	send_button->callback(SendButtonCallback);
	this->end();
}

void ChatInterface::PrintMessage(std::string username, std::string message){
     std::string msg = message + "\n";
     text_display_buffer->append(msg.c_str());
     message_input->value("");
     Fl::focus(message_input);
}

void SendButtonCallback(Fl_Widget *, void * data) {
     std::string input = chat_ui::mediator->chat_interface->message_input->value();
     if(input.size() > 0){
          chat_ui::mediator->Send(input);
	}
}
