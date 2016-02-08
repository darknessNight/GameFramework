#include "Sounds.h"
GF::IOModule::Sounds::Effect::Effect()
{
	setVolume(volume);
	setBuffer(sound);
}

void GF::IOModule::Sounds::Effect::copyFormRecorder(const Recorder & rec)
{
	sound = rec.getBuffer();
}

bool GF::IOModule::Sounds::Effect::loadFromFile(const std::string & filename)
{
	return sound.loadFromFile(filename);
}

bool GF::IOModule::Sounds::Effect::loadFromMemory(const void * data, std::size_t sizeInBytes)
{
	return sound.loadFromMemory(data, sizeInBytes);
}

bool GF::IOModule::Sounds::Effect::loadFromStream(sf::InputStream & stream)
{
	return sound.loadFromStream(stream);
}

bool GF::IOModule::Sounds::Effect::loadFromSamples(const short * samples, long long sampleCount, unsigned int channelCount, unsigned int sampleRate)
{
	return sound.loadFromSamples(samples, sampleCount, channelCount, sampleRate);
}

bool GF::IOModule::Sounds::Effect::saveToFile(const std::string & filename) const
{
	return sound.saveToFile(filename);
}

const short* GF::IOModule::Sounds::Effect::getSamples() const
{
	return sound.getSamples();
}

long long GF::IOModule::Sounds::Effect::getSampleCount() const
{
	return sound.getSampleCount();
}

unsigned int GF::IOModule::Sounds::Effect::getSampleRate() const
{
	return sound.getSampleRate();
}

unsigned int GF::IOModule::Sounds::Effect::getChannelCount() const
{
	return sound.getChannelCount();
}

GF::IOModule::Time GF::IOModule::Sounds::Effect::getDuration() const
{
	return sound.getDuration;
}

void GF::IOModule::Sounds::Playlist::play()
{
	if(list.size()>0)
		music.play();

}

void GF::IOModule::Sounds::Playlist::stop()
{
	music.stop();
}

void GF::IOModule::Sounds::Playlist::next()
{
	if(current<list.size() || loop )
	select(current + 1);
}

void GF::IOModule::Sounds::Playlist::prev()
{
	if(current!=0 || loop)
	select(current + 1);
}

unsigned GF::IOModule::Sounds::Playlist::size()
{
	return list.size();
}

void GF::IOModule::Sounds::Playlist::select(unsigned i)
{
	stop();
	if (i < list.size()) {
		if (!music.openFromFile(list[i]))
			throw std::exception("Cannot open music");
	}
	else if (list.size()>0) {
		if (!music.openFromFile(list[0]))
			throw std::exception("Cannot open music");
	}
}

void GF::IOModule::Sounds::Playlist::clear()
{
	list.clear();
}

void GF::IOModule::Sounds::Playlist::setLoop(bool enable)
{
	loop = enable;
}

bool GF::IOModule::Sounds::Playlist::getLoop()
{
	return loop;
}

void GF::IOModule::Sounds::Playlist::append(std::string path)
{
	list.push_back(path);
	if (list.size() == 1)
		select(0);
}

void GF::IOModule::Sounds::Playlist::remove(std::string path)
{
	for (auto i = list.begin(); i != list.end(); i++)
		if (path == (*i)) {
			i = list.erase(i);
			break;
		}
}

void GF::IOModule::Sounds::Playlist::remove(unsigned el)
{
	if (el > list.size())return;
	auto i = list.begin();
	i += el;
	i = list.erase(i);

}

void GF::IOModule::Sounds::Playlist::setVolume(unsigned vol)
{
	music.setVolume(vol);
}
