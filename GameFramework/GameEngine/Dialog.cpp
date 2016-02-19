#include "Dialog.h"

GF::Core::MemGuard<GF::GameEngine::Dialog> GF::GameEngine::Dialog::choice(int no)
{
	if (no >= 0 && no < options.size()) {
		for each (auto &el in options[no]->Texts)
		{
			el.show();
		}
		return options[no];
	}return nullptr;
}
