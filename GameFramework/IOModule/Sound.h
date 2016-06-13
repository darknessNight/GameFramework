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

			static void applyMusic(Core::shared_ptr<Sounds::Music>);
			static void applyVoice(Core::shared_ptr<Sounds::Voice>);
			static void applyEffect(Core::shared_ptr<Sounds::Effect>);

			static void removeMusic(Core::shared_ptr<Sounds::Music>);
			static void removeVoice(Core::shared_ptr<Sounds::Voice>);
			static void removeEffect(Core::shared_ptr<Sounds::Effect>);

			static Core::shared_ptr<Sounds::Music> createMusic();
			static Core::shared_ptr<Sounds::Voice> createVoice();
			static Core::shared_ptr<Sounds::Effect> createEffect();
		protected:
			static std::vector < Core::shared_ptr<Sounds::Music>> musics;
			static std::vector < Core::shared_ptr<Sounds::Voice>> voices;
			static std::vector < Core::shared_ptr<Sounds::Effect>> effects;
			static float volume;
		};
	}
}