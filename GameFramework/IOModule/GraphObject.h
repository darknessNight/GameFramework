#pragma once
#include <SFML\Graphics.hpp>
#include "Interfaces.h"

namespace GF {
	namespace IOModule {
		class GraphObject :public IGraphObject2D {
			friend IWindow;
		public:
			GraphObject() = delete;
			GraphObject(GraphObject&) = default;
			void setVisible(bool enabled);
			void setPos(const Posf p);
			bool getVisible();
			const Posf& getPos();
			const Size& getSize();
			virtual void LoadFromFile(std::string path) = 0;
		protected:
			virtual void render() = 0;
		public:
			Events::Event<Events::EventArgs> Render;
		protected:
			bool changed = false;
			Posf pos;
			Size size;
			bool visible;
		};
	}
}