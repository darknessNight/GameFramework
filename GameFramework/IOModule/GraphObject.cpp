#include "GraphObject.h"

namespace GF {
	namespace IOModule {
		void GraphObject::setVisible(bool enabled)
		{
			visible = enabled;
		}

		void GraphObject::setPos(const Posf p)
		{
			pos = p;
		}

		bool GraphObject::getVisible()
		{
			return visible;
		}
		
		const Posf& GraphObject::getPos()
		{
			return pos;
		}
		
		const Size& GraphObject::getSize()
		{
			return size;
		}
	}
}