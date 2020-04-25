#include "ChatInterface.h"
#include "Mediator.h"

Fl_Input * input;
ChatInterface::ChatInterface(void * data) : Fl_Double_Window(367, 244, "Chat Window") {
	text_display = new Fl_Text_Display(10, 5, 345, 195);
	text_display_buffer = new Fl_Text_Buffer();

	message_input = new Fl_Input(70, 205, 200, 25, "Message");
	input = message_input;

	send_button = new Fl_Return_Button(280, 205, 75, 25, "Send");
	send_button->callback(SendButtonCallback, data);
	this->end();
}

void SendButtonCallback(Fl_Widget *, void * data) {
     if(input.size() > 0){
          Mediator * mediator = (Mediator *)data;
          mediator->Send(std::string(input->value()));
	}
}
