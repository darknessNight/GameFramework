#pragma once
#include "../Core/Types.h"
#include "Sounds.h"
#include "SoundPlaylists.h"

namespace GF {
	namespace IOModule {
		class SoundCore {
		public:
			//volumes range <0.0f,100.0f>
			static void setMusicVolume(float);
			static void setVoiceVolume(float);
			static void setEffectVolume(float);
			static void setMainVolume(float);

			static float getMusicVolume();
			static float getVoiceVolume();
			static float getEffectVolume();
			static float getMainVolume();

			static void applyMusic(Core::MemGuard<Sounds::Music>);
			static void applyVoice(Core::MemGuard<Sounds::Voice>);
			static void applyEffect(Core::MemGuard<Sounds::Effect>);

			static void removeMusic(Core::MemGuard<Sounds::Music>);
			static void removeVoice(Core::MemGuard<Sounds::Voice>);
			static void removeEffect(Core::MemGuard<Sounds::Effect>);

			static Core::MemGuard<Sounds::Music> createMusic();
			static Core::MemGuard<Sounds::Voice> createVoice();
			static Core::MemGuard<Sounds::Effect> createEffect();
		protected:
			static std::vector < Core::MemGuard<Sounds::Music>> musics;
			static std::vector < Core::MemGuard<Sounds::Voice>> voices;
			static std::vector < Core::MemGuard<Sounds::Effect>> effects;
			static float volume;
		};
	}
}