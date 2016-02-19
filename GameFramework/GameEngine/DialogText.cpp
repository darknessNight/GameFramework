#include "DialogText.h"

void GF::GameEngine::DialogText::show()
{
	if (draw) draw(text, time);
	playSound.play();
	Core::EventArgs args;
	ShowStart(this, args);
	std::this_thread::sleep_for(std::chrono::microseconds(time));
	playSound.stop();
	ShowEnd(this, args);
	
}
