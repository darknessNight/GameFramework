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

			virtual void selfDestroy();

			virtual void changePos(Pos newPos);

		public:
			IOModule::GraphObject2D* graphicObject;
			Model* model;
			Pos pos;
			bool canDestroy;
			Statistics stats;
			GameEngine *myEngine;
		};
}}