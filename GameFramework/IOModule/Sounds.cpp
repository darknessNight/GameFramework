#include "Sounds.h"
GF::IOModule::Sounds::Effect::Effect()
{
	setBuffer(sound);
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
