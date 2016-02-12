#include "SoundPlaylists.h"

void GF::IOModule::Sounds::Playlist::next()
{
	select(current + 1);
}

void GF::IOModule::Sounds::Playlist::prev()
{
	select(current - 1);
}

void GF::IOModule::Sounds::Playlist::setLoop(bool enable)
{
	loop = enable;
}

bool GF::IOModule::Sounds::Playlist::getLoop()
{
	return loop;
}

void GF::IOModule::Sounds::Playlist::setCheckInterval(unsigned val)
{
	interval = val;
}

GF::IOModule::Sounds::PlaylistSound::~PlaylistSound()
{
	stop();
}

GF::IOModule::Sounds::PlaylistFile::~PlaylistFile()
{
	stop();
}
//=======
void GF::IOModule::Sounds::PlaylistFile::play()
{
	if (list.size() > 0) {
		playing = true;
		music.play();
		th = std::thread(&PlaylistFile::checkPlaylist, this);
	}
}

void GF::IOModule::Sounds::PlaylistFile::stop()
{
	if (playing) {
		playing = false;
		music.stop();
		if(th.joinable())
			th.join();
	}
}

void GF::IOModule::Sounds::PlaylistFile::pause()
{
	music.pause();
}

GF::IOModule::Sounds::SoundBase::Status GF::IOModule::Sounds::PlaylistFile::getStatus()
{
	return music.getStatus();
}

unsigned GF::IOModule::Sounds::PlaylistFile::size()
{
	return list.size();
}

void GF::IOModule::Sounds::PlaylistFile::select(unsigned i)
{
	Status s = music.getStatus();
	stop();

	//loop ckech
	if (loop) {
		if (i >= list.size()) i = 0;
		if (i < 0) i = list.size() - 1;
	}
	//loop check

	if (i < list.size() && i >= 0) {
		if (!music.openFromFile(list[i]))
			throw std::runtime_error("Cannot open music");
	}

	if (s == Status::Playing)
		play();
	current = i;
}

void GF::IOModule::Sounds::PlaylistFile::clear()
{
	list.clear();
}

void GF::IOModule::Sounds::PlaylistFile::append(std::string path)
{
	list.push_back(path);
	if (list.size() == 1)
		select(0);
}

void GF::IOModule::Sounds::PlaylistFile::remove(std::string path)
{
	for (auto i = list.begin(); i != list.end(); i++)
		if (path == (*i)) {
			i = list.erase(i);
			break;
		}
}

void GF::IOModule::Sounds::PlaylistFile::remove(unsigned el)
{
	if (el > list.size())return;
	auto i = list.begin();
	i += el;
	i = list.erase(i);

}

void GF::IOModule::Sounds::PlaylistFile::setVolume(float vol)
{
	music.setVolume(vol);
}

void GF::IOModule::Sounds::PlaylistFile::checkPlaylist()
{
	std::chrono::milliseconds sleep(interval);
	while (playing) {
		if (music.getStatus() == Status::Stopped) {
			select(current + 1);
		}
		std::this_thread::sleep_for(sleep);
	}
}
//=======
void GF::IOModule::Sounds::PlaylistSound::play()
{
	if (active == nullptr) select(0);
	if (list.size() > 0) {
		playing = true;
		active->play();
		th = std::thread(&PlaylistSound::checkPlaylist, this);
	}
}

void GF::IOModule::Sounds::PlaylistSound::stop()
{
	if (playing) {
		playing = false;
		if (active != nullptr)
			active->stop();
		if(th.joinable())
		th.join();
	}
}

void GF::IOModule::Sounds::PlaylistSound::pause()
{
	if (active != nullptr)
		active->pause();
}

GF::IOModule::Sounds::SoundBase::Status GF::IOModule::Sounds::PlaylistSound::getStatus()
{
	if (active != nullptr)
		return active->getStatus();
	else return Status::Stopped;
}

unsigned GF::IOModule::Sounds::PlaylistSound::size()
{
	return list.size();
}

void GF::IOModule::Sounds::PlaylistSound::select(unsigned i)
{
	Status s = Status::Stopped;
	if (active != nullptr) {
		s = active->getStatus();
		active->stop();
	}
	//loop ckech
	if (loop) {
		if (i >= list.size()) i = 0;
		if (i < 0) i = list.size() - 1;
	}
	//loop check

	if (i < list.size() && i >= 0 && list[i]!=nullptr) {
		active = list[i];
		void* ptr = active.getPtr();
		list[i]->setVolume(volume);
	}

	if (s == Status::Playing)
		active->play();
	current = i;
}

void GF::IOModule::Sounds::PlaylistSound::clear()
{
	list.clear();
}

void GF::IOModule::Sounds::PlaylistSound::append(Core::MemGuard<SoundBase> el)
{
	if (el != nullptr) {
		list.push_back(el);
		SoundBase* ptr = el.getPtr();
	}
}

void GF::IOModule::Sounds::PlaylistSound::remove(Core::MemGuard<SoundBase> el)
{
	for (auto i = list.begin(); i != list.end(); i++)
		if (el == (*i)) {
			i = list.erase(i);
			break;
		}
}

void GF::IOModule::Sounds::PlaylistSound::remove(unsigned el)
{
	if (el > list.size())return;
	auto i = list.begin();
	i += el;
	i = list.erase(i);
}

void GF::IOModule::Sounds::PlaylistSound::setVolume(float vol)
{
	volume = vol;
	if (active != nullptr) {
		active->setVolume(vol);
	}
}

void GF::IOModule::Sounds::PlaylistSound::checkPlaylist()
{
	std::chrono::milliseconds sleep(interval);
	while (playing) {
		if (active==nullptr || active->getStatus() == Status::Stopped) {
			select(current + 1);
			if (active != nullptr)
				active->play();
		}
		std::this_thread::sleep_for(sleep);
	}
}
