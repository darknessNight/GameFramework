#pragma once
#include "Sound.h"

namespace GF {
	namespace IOModule {
		namespace Sounds {
			class Playlist : public SoundBase {
			public:
				virtual void play() = 0;
				virtual void stop() = 0;
				virtual void pause() = 0;
				virtual Status getStatus() = 0;
				virtual void next();
				virtual void prev();
				virtual unsigned size() = 0;
				virtual void select(unsigned) = 0;
				virtual void clear() = 0;
				virtual void setLoop(bool);
				virtual bool getLoop();
				virtual void setVolume(float)=0;
				virtual void setCheckInterval(unsigned);//in ms
			protected:
				unsigned interval=500;//in ms
				bool playing = false;
				bool loop = true;
				int current = 0;
				std::thread th;
			};

			class PlaylistFile : public Playlist {
			public:
				~PlaylistFile();
				void play() override;
				void stop()override;
				void pause()override;
				Status getStatus() override;
				unsigned size();
				void select(unsigned);
				void clear();
				void append(std::string path);
				void remove(std::string);
				void remove(unsigned);
				void setVolume(float);
			protected:
				void checkPlaylist();
			protected:
				std::vector<std::string> list;
				sf::Music music;
			};

			class PlaylistSound : public PlaylistFile {
			public:
				~PlaylistSound();
				void play() override;
				void stop()override;
				void pause()override;
				Status getStatus() override;
				unsigned size();
				void select(unsigned);
				void clear();
				void append(Core::shared_ptr<SoundBase>);
				void remove(Core::shared_ptr<SoundBase>);
				void remove(unsigned);
				void setVolume(float);
			protected:
				void checkPlaylist();
			protected:
				float volume = 100;
				std::vector<Core::shared_ptr<SoundBase>> list;
				Core::shared_ptr<SoundBase> active;
			};
		}
	}
}