#pragma once
#include "Sounds.h"

namespace GF {
	namespace IOModule {
		class SoundCore {
			static int mainVolume;
		public:
			static void setMusicVolume(unsigned);
			static void setVoiceVolume(unsigned);
			static void setEffectVolume(unsigned);
			static void setMainVolume(unsigned);

			static void getMusicVolume(unsigned);
			static void getVoiceVolume(unsigned);
			static void getEffectVolume(unsigned);
			static void getMainVolume(unsigned);
		};
	}
}