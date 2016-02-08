#pragma once
#include <SFML/Audio.hpp>
#include "../stdafx.h"
#include "Types.h"

namespace GF {
	namespace IOModule {

		namespace Sounds {
			template <bool voice> class Sound :public sf::Music{
			public:
				Sound() {
					if (voice) {
						setVolume(voiceVolume);
					}
					else {
						setVolume(musicVolume);
					}
				}
			private:
				static int musicVolume;
				static int voiceVolume;
			};

			typedef Sound<false> Music;
			typedef Sound<true> Voice;

			class Effect: sf::Sound{
			public:
				Effect();
				bool loadFromFile(const std::string &filename);
				bool loadFromMemory(const void *data, std::size_t sizeInBytes);
				bool loadFromStream(sf::InputStream &stream);
				bool loadFromSamples(const short *samples, long long sampleCount, unsigned int channelCount, unsigned int sampleRate);
				bool saveToFile(const std::string &filename) const;
				const short* getSamples() const;
				long long getSampleCount() const;
				unsigned int getSampleRate() const;
				unsigned int getChannelCount() const;
				Time getDuration() const;
				
			private:
				using sf::Sound::setBuffer;
				using sf::Sound::getBuffer;
				sf::SoundBuffer sound;
			};

			class Recorder {
			public:
				static bool available();
				void record();
				void stop();
			};
		}
	}
}