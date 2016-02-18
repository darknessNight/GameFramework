#pragma once
#include "../IOModule/GraphObject.h"
#include "Model.h"
#include "Types.h"
#include "Statistics.h"

namespace GF {
	namespace GameEngine {
		class GameEngine;
		class GameObject {
		public:
			virtual void changePos(Pos newPos);
			virtual Pos getPosition();
			virtual const Model* getModel();
		private:
			virtual void selfDestroy();
		private:
			Pos pos;
			Core::MemGuard<Model> model;
			
			bool canDestroy;
			Statistics stats;
			
			GameEngine* engine;
			void* additionalData;
		};
}}