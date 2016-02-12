/*Checking playlists
*/
#pragma once
#include "../IOModule/Window.h"
#include "../IOModule/Sound.h"

std::string Test6() {
	char ret;
	std::string result;
	using namespace GF::IOModule;
	using namespace std::literals;
	GF::Core::MemGuard<Sounds::Music> m1, m2, m3, m4, m5;
	m1 = m2 = m3 = m4 = GF::Core::make_ptr(new Sounds::Music);
	m5 = GF::Core::make_ptr(new Sounds::Music);

	Sounds::PlaylistSound p1;
	p1.append(m1);
	p1.append(m2);
	p1.append(m3);
	p1.append(m4);
	p1.append(m5);
	p1.remove(m5);
	p1.remove(m5);
	p1.remove(2);
	if (p1.size() != 3)result += "Not add element to playlist p1:" + std::to_string(p1.size())+"\n";


	Sounds::PlaylistFile p2;
	p2.append("./Tests/tmusic1.ogg");
	p2.append("./Tests/tmusic2.ogg");
	p2.append("./Tests/tmusic3.ogg");

	if (p2.size() != 3)result += "Not add element to playlist p2:" + std::to_string(p1.size()) + "\n";
	
 	p2.play();
	std::this_thread::sleep_for(10s);
	p2.next();
	std::this_thread::sleep_for(10s);
	p2.next();
	std::this_thread::sleep_for(10s);

	std::clog << "Do you hear three songs?(Y/N)\n";
	std::cin >> ret;
	if (ret != 'y'&& ret != 'Y') {
		result += "Playing not working";
	}
	p2.stop();

	SoundCore::setMusicVolume(30);

	Sounds::PlaylistSound p3;
	GF::Core::MemGuard<Sounds::Music> e1, e2, e3;
	e1 = new Sounds::Music;
	e2 = new Sounds::Music;
	e3 = new Sounds::Music;
	e1->openFromFile("./Tests/tmusic1.ogg");
	e2->openFromFile("./Tests/tmusic2.ogg");
	e3->openFromFile("./Tests/tmusic3.ogg");

	GF::Core::MemGuard<Sounds::SoundBase> sb1;
	sb1 = e1;
	sb1->setVolume(10);

	p3.append(e1);
	p3.append(e2);
	p3.append(e3);

	p3.play();
	e1->setPlayingOffset(sf::seconds(4*60+20));

	std::this_thread::sleep_for(10s);
	e2->setPlayingOffset(sf::seconds(5 * 60));
	std::this_thread::sleep_for(10s);

	std::clog << "Do you hear three songs?(Y/N)\n";
	ret;
	std::cin >> ret;
	if (ret != 'y'&& ret != 'Y') {
		result += "Not autoswitching";
	}

	return result;
}