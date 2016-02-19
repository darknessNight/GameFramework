#pragma once
#include "../IOModule/GraphObject.h"
#include "Model.h"
#include "Types.h"
#include "Statistics.h"

namespace GF {
	namespace GameEngine {
		class GameEngine;
		class GameObject :public Core::ObjectSerialize {
			friend GameEngine;
		public:
			GameObject();
			virtual void setPos(Pos pos);
			virtual Pos getPos();
			virtual void setModel(Core::MemGuard<Model>);
			virtual void updateStats(Core::MemGuard<const Statistics>);
			virtual Model* getModel();

			virtual void setStats(Core::MemGuard<Statistics> stat);
			virtual Core::MemGuard<const Statistics> getStats();
		protected:
			virtual void init() = 0;
			virtual void selfDestroy()=0;

			virtual void onPosChagned();
			virtual void onStatsChanged();
			virtual void onDead();

		public:
			Core::Events::Event<Core::EventArgs> Dead;
			Core::Events::Event<Core::EventArgs> StatsChanged;
			Core::Events::Event<Core::EventArgs> PosChanged;

			bool canDestroy;
			void* additionalData;
		protected:
			Core::MemGuard<Statistics> stats;
			Pos pos;
			Core::MemGuard<Model> model;
			GameEngine* engine;
		};
}}