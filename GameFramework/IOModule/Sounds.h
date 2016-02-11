#pragma once
#include <SFML/Audio.hpp>
#include "../stdafx.h"
#include "../Core/Types.h"
#include "Types.h"

namespace GF {
	namespace IOModule {
		class SoundCore;
		namespace Sounds {
			class SoundBase {
			public:
				typedef sf::Sound::Status Status;
				virtual void play()=0;
				virtual void pause()=0;
				virtual void stop()=0;
				virtual void setVolume(float)=0;
				virtual Status getStatus()=0;
			};

			template <bool voice> class Sound :public sf::Music, public SoundBase {
				friend SoundCore;
			public:
				bool operator==(const Sound<!voice> &rhs) {
					return *(sf::Music*)(this) == *(sf::Music*)&rhs;
				}

				void play()override { sf::Music::play(); }
				void pause()override { sf::Music::pause(); };
				void stop()override { sf::Music::stop(); };
				void setVolume(float val)override { sf::Music::setVolume(val); }
				SoundBase::Status getStatus()override { return sf::Music::getStatus(); }

				Sound() {
					setVolume(volume);
				}
			private:
				static float volume;
			};

			typedef Sound<false> Music;
			typedef Sound<true> Voice;

			typedef sf::SoundBufferRecorder Recorder;

			class Effect : sf::Sound, public SoundBase {
				friend SoundCore;
			public:
				void play()override;
				void pause()override;
				void stop()override;
				void setVolume(float val)override;
				SoundBase::Status getStatus()override;
				Effect();
				Effect& getCopy();
				void copyFormRecorder(const Recorder& rec);
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

				using sf::Sound::setBuffer;
				using sf::Sound::getBuffer;

			private:
				static float volume;
				sf::SoundBuffer sound;
			};
		}
	}
}