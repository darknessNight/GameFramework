#include "Sound.h"

namespace GF {
	namespace IOModule {
		float SoundCore::volume = 1.00;
		std::vector < Core::MemGuard<Sounds::Music>> SoundCore::musics;
		std::vector < Core::MemGuard<Sounds::Voice>> SoundCore::voices;
		std::vector < Core::MemGuard<Sounds::Effect>> SoundCore::effects;
	}
}

void GF::IOModule::SoundCore::setMusicVolume(float v)
{
	if (v <= 100) {
		Sounds::Music::volume = v*volume;
		for each(auto el in musics)
			el->setVolume(Sounds::Music::volume);
	}
}

void GF::IOModule::SoundCore::setVoiceVolume(float v)
{
	if (v <= 100) {
		Sounds::Voice::volume = v*volume;
		for each(auto el in voices)
			el->setVolume(Sounds::Voice::volume);
	}

}

void GF::IOModule::SoundCore::setEffectVolume(float v)
{
	if (v <= 100) {
		Sounds::Effect::volume = v*volume;
		for each(auto el in effects)
			el->setVolume(Sounds::Effect::volume);
	}
}

void GF::IOModule::SoundCore::setMainVolume(float v)
{
	if (v <= 100) {
		float old = v/volume;
		volume = v / 100.0f;
		Sounds::Effect::volume = Sounds::Effect::volume*old;
		Sounds::Music::volume = Sounds::Music::volume*old;
		Sounds::Voice::volume = Sounds::Voice::volume*old;
		for each(auto el in musics)
			el->setVolume(Sounds::Music::volume);
		for each(auto el in voices)
			el->setVolume(Sounds::Voice::volume);
		for each(auto el in effects)
			el->setVolume(Sounds::Effect::volume);
	}
}

float GF::IOModule::SoundCore::getMusicVolume()
{
	return Sounds::Music::volume / volume;
}

float GF::IOModule::SoundCore::getVoiceVolume()
{
	return Sounds::Voice::volume / volume;
}

float GF::IOModule::SoundCore::getEffectVolume()
{
	return Sounds::Effect::volume / volume;
}

float GF::IOModule::SoundCore::getMainVolume()
{
	return volume * 100;
}

void GF::IOModule::SoundCore::applyMusic(Core::MemGuard<Sounds::Music> m)
{
	musics.push_back(m);
}

void GF::IOModule::SoundCore::applyVoice(Core::MemGuard<Sounds::Voice> v)
{
	voices.push_back(v);
}

void GF::IOModule::SoundCore::applyEffect(Core::MemGuard<Sounds::Effect> e)
{
	effects.push_back(e);
}

void GF::IOModule::SoundCore::removeMusic(Core::MemGuard<Sounds::Music> el)
{
	for (auto i = musics.begin(); i != musics.end();i++)
		if ((*i) == el) {
			std::swap(i,musics.end());musics.pop_back();
			break;
		}
}

void GF::IOModule::SoundCore::removeVoice(Core::MemGuard<Sounds::Voice> el)
{
	for (auto i = voices.begin(); i != voices.end(); i++)
		if ((*i) == el) {
			std::swap(i,voices.end());voices.pop_back();
			break;
		}
}

void GF::IOModule::SoundCore::removeEffect(Core::MemGuard<Sounds::Effect> el)
{
	for (auto i = effects.begin(); i != effects.end(); i++)
		if ((*i) == el) {
			std::swap(i,effects.end());effects.pop_back();
			break;
		}
}

GF::Core::MemGuard<GF::IOModule::Sounds::Music> GF::IOModule::SoundCore::createMusic()
{
	return Core::MemGuard<Sounds::Music>();
}

GF::Core::MemGuard<GF::IOModule::Sounds::Voice> GF::IOModule::SoundCore::createVoice()
{
	return Core::MemGuard<Sounds::Voice>();
}

GF::Core::MemGuard<GF::IOModule::Sounds::Effect> GF::IOModule::SoundCore::createEffect()
{
	return Core::MemGuard<Sounds::Effect>();
}
