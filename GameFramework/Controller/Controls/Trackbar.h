#pragma once
#include "Progressbar.h"


namespace GF {
	namespace Controller {
		namespace Controls {
			class Trackbar :public Progressbar {
			public:
				using Progressbar::Progressbar;
			protected:
				void onMousePress(Events::MouseButtonArgs&)override;
				void onMouseMove(Events::MouseMoveArgs&)override;
				virtual void calcValue(float x, float y);
			};

			class TrackbarH :public ProgressbarH {
				public:
					using ProgressbarH::ProgressbarH;
				protected:
					void onMousePress(Events::MouseButtonArgs&)override;
					void onMouseMove(Events::MouseMoveArgs&)override;
					void calcValue(float x, float y);
			};
		}
	}
}