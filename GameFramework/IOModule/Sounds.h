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
				virtual void start();
				virtual void stop();
			};

			template <bool voice> class Sound :public sf::Music, public SoundBase{
				friend SoundCore;
			public:
				Sound() {
					setVolume(volume);
				}
			private:
				static int volume;
			};

			typedef Sound<false> Music;
			typedef Sound<true> Voice;

			typedef sf::SoundBufferRecorder Recorder;

			class Effect: sf::Sound, public SoundBase {
				friend SoundCore;
			public:
				Effect();
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
				static int volume;
				sf::SoundBuffer sound;
			};


			class Playlist {//TODO add automatic go to next
			public:
				void play();
				void stop();
				void next();
				void prev();
				unsigned size();
				void select(unsigned);
				void clear();
				void setLoop(bool);
				bool getLoop();
				void append(std::string path);
				void remove(std::string);
				void remove(unsigned);
				void setVolume(unsigned);
			private:
				std::thread th;
				std::vector<std::string> list;
				int current = 0;
				sf::Music music;
				bool loop = true;
			};
		}
	}
}