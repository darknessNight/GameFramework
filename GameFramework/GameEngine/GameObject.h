#pragma once
#include "Model.h"
#include "Types.h"
#include "Statistics.h"

namespace GF {
	namespace GameEngine {
		class GameEngine;
		class GameObject;

		struct CollisionEventArgs :public Core::EventArgs {
			Core::MemGuard<GameObject> object;
		};

		class GameObject :public Core::ObjectSerialize {
			friend GameEngine;
		public:
			virtual std::vector<unsigned char> serialize() override;
			virtual bool deserialize(std::vector<unsigned char>) override;

			virtual void setPos(Pos pos);
			virtual Pos getPos();
			virtual Size getSize();
			virtual void setModel(Core::MemGuard<Model>);
			virtual void updateStats(Core::MemGuard<const Statistics>);
			virtual Model* getModel();

			virtual void setStats(Core::MemGuard<Statistics> stat);
			virtual Core::MemGuard<const Statistics> getStats();
		protected:
			virtual void selfDestroy()=0;

			virtual void onPosChagned();
			virtual void onStatsChanged();
			virtual void onDead();

		public:
			Core::Events::Event<Core::EventArgs> Dead;
			Core::Events::Event<Core::EventArgs> StatsChanged;
			Core::Events::Event<Core::EventArgs> PosChanged;
			Core::Events::Event<CollisionEventArgs> Collision;

			bool canDestroy;
			void* additionalData;
		protected:
			Core::MemGuard<Statistics> stats=nullptr;
			Core::MemGuard<Model> model=nullptr;
			GameEngine* engine=nullptr;
		};
}}