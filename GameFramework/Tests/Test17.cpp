#include "../GameEngine/RTGameEngine.h"
#include "../GameEngine/TurnGameEngine.h"
#include "../GameEngine/Map2D.h"
#include "../GameEngine/Model2D.h"
#include "../GameEngine/Mob.h"
#include "../GameEngine/StaticObject.h"
#include "../Core/Exception.h"
#include "../../GameFramework/IOModule/Window.h"
#include "../../GameFramework/IOModule/Image.h"
#include "../../GameFramework/IOModule/MultipleGraph.h"
#include "../../GameFramework/IOModule/Sound.h"
#include <fstream>

#include "Tests.h"
std::string Test17();
AutoAdd AA17(Test17, "GameEngine/IOModule", "Synch test", true);


namespace SpaceInvaders {
	class GameForm :public GF::IOModule::Window {
	public:
		void start() {
			background_ = CreateTexture({ 2560,1600 });
			if (!background_->loadFromFile("graphic/background.jpg")) {
				//TODO error 
				return;
			}
			background_->setVisible(true);
			background_->setPosition({ 0,0 });
			background_->scale({ 0.55f,0.55f });
			std::cout << (2560 * 0.55f - 1333);
			background_->setPosition({ (2560 * 0.55f - 1333),0 });
			settings.size = { 1333,768 };
			settings.fullscreen = true;
			settings.vsync = true;
			//TODO: read config from file
			this->Show();
		}
	private:
		GF::Core::shared_ptr<GF::IOModule::Texture2D> background_;
	};
}

std::string Test17() {

	std::string result;
	SpaceInvaders::GameForm form;
	form.start();
	
	return result;
}