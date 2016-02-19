#include "Dialog.h"

GF::Core::MemGuard<GF::GameEngine::Dialog> GF::GameEngine::Dialog::choice(int no)
{
	if (no >= 0 && no < options.size()) {
		for (auto el = options[no]->Texts.begin(); el != options[no]->Texts.end();el++)
		{
			el->show();
		}
		return options[no];
	}return nullptr;
}
