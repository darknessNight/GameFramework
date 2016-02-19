#pragma once
#include "Action.h"
#include <chrono>
namespace GF {
	namespace GameEngine {
		class Skill {
		public:
			bool canUse();
			void use();
		public:
			Core::Events::Event<Core::EventArgs> Use;
			Action action;
			int reloadTime;///<in miliseconds
			std::string name;
			void* additionalData;
		protected:
			std::chrono::high_resolution_clock::time_point lastUse=std::chrono::high_resolution_clock::time_point::min();
		};

		struct SkillEventArgs :public Core::EventArgs {
			Skill skill;
		};
	}
}