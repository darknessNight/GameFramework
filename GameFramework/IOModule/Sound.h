#pragma once
#include "../Core/Types.h"
#include "Sounds.h"
#include "SoundPlaylists.h"

namespace GF {
	namespace IOModule {
		class SoundCore {
		public:
			static void setMusicVolume(unsigned);
			static void setVoiceVolume(unsigned);
			static void setEffectVolume(unsigned);
			static void setMainVolume(unsigned);

			static int getMusicVolume(unsigned);
			static int getVoiceVolume(unsigned);
			static int getEffectVolume(unsigned);
			static int getMainVolume(unsigned);

			static void applyMusic(Core::MemGuard<Sounds::Music>);
			static void applyVoice(Core::MemGuard<Sounds::Voice>);
			static void applyEffect(Core::MemGuard<Sounds::Effect>);

			static void removeMusic(Core::MemGuard<Sounds::Music>);
			static void removeVoice(Core::MemGuard<Sounds::Voice>);
			static void removeEffect(Core::MemGuard<Sounds::Effect>);

			static Core::MemGuard<Sounds::Music> createMusic();
			static Core::MemGuard<Sounds::Voice> createVoice();
			static Core::MemGuard<Sounds::Effect> createEffect();
		private:
			static std::vector < Core::MemGuard<Sounds::Music>> musics;
			static std::vector < Core::MemGuard<Sounds::Voice>> voices;
			static std::vector < Core::MemGuard<Sounds::Effect>> effects;
			static float volume;
		};
	}
}