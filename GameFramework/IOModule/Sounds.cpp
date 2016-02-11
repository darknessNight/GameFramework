#include "Sounds.h"

float GF::IOModule::Sounds::Effect::volume = 100;
float GF::IOModule::Sounds::Music::volume = 100;
float GF::IOModule::Sounds::Voice::volume = 100;

void GF::IOModule::Sounds::Effect::play()
{
	sf::Sound::play();
}

void GF::IOModule::Sounds::Effect::pause()
{
	sf::Sound::pause();
}

void GF::IOModule::Sounds::Effect::stop()
{
	sf::Sound::stop();
}

void GF::IOModule::Sounds::Effect::setVolume(float val)
{
	sf::Sound::setVolume(val);
}

sf::Sound::Status GF::IOModule::Sounds::Effect::getStatus()
{
	return sf::Sound::getStatus();
}

GF::IOModule::Sounds::Effect::Effect()
{
	setVolume(volume);
	setBuffer(sound);
}

inline void GF::IOModule::Sounds::Effect::copyFormRecorder(const Recorder & rec)
{
	sound = rec.getBuffer();
}

inline bool GF::IOModule::Sounds::Effect::loadFromFile(const std::string & filename)
{
	return sound.loadFromFile(filename);
}

inline bool GF::IOModule::Sounds::Effect::loadFromMemory(const void * data, std::size_t sizeInBytes)
{
	return sound.loadFromMemory(data, sizeInBytes);
}

inline bool GF::IOModule::Sounds::Effect::loadFromStream(sf::InputStream & stream)
{
	return sound.loadFromStream(stream);
}

inline bool GF::IOModule::Sounds::Effect::loadFromSamples(const short * samples, long long sampleCount, unsigned int channelCount, unsigned int sampleRate)
{
	return sound.loadFromSamples(samples, sampleCount, channelCount, sampleRate);
}

inline bool GF::IOModule::Sounds::Effect::saveToFile(const std::string & filename) const
{
	return sound.saveToFile(filename);
}

inline const short* GF::IOModule::Sounds::Effect::getSamples() const
{
	return sound.getSamples();
}

inline long long GF::IOModule::Sounds::Effect::getSampleCount() const
{
	return sound.getSampleCount();
}

inline unsigned int GF::IOModule::Sounds::Effect::getSampleRate() const
{
	return sound.getSampleRate();
}

inline unsigned int GF::IOModule::Sounds::Effect::getChannelCount() const
{
	return sound.getChannelCount();
}

inline GF::IOModule::Time GF::IOModule::Sounds::Effect::getDuration() const
{
	return sound.getDuration();
}
