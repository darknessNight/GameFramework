#pragma once
#ifdef DEBUG
#include "../../MemGuard.h"
#endif
#include "../../IOModule/Image.h"

namespace GF {
	namespace Controller {
		namespace Controls {
			using namespace IOModule;
			class Control :public IOModule::Image {
			public:
				Control() = delete;
				Control(Size);
				Control(unsigned x, unsigned y);
				virtual std::wstring getText();
				virtual void setText(std::wstring t);
				virtual void setFont(Font &font);
				virtual Font getFont();
				virtual void setBackColor(Color);
				virtual Color getBackColor();
				virtual void setForeColor(Color);
				virtual Color getForeColor(Color);
				virtual void setBorderColor(Color);
				virtual Color getBordeColor(Color);
				virtual void setBackTexture(const SharedTexture&);
				virtual void setBackTexture(Texture2D&);
				virtual void setActiveBackTexture(const SharedTexture&);
				virtual void setActiveBackTexture(Texture2D&);
				virtual void setOwnDraw(bool enable = true);
				virtual void setFontSize(unsigned size);
				virtual void setActiveBackColor(Color);
				virtual void setActiveForeColor(Color);
				virtual void setActiveBorderColor(Color);
				virtual Color getActiveBackColor();
				virtual Color getActiveForeColor();
				virtual Color getActiveBorderColor();
				virtual void setBorderSize(float);
				virtual float getBorderSize();
			protected:
				void onMousePress(Events::MouseButtonArgs& args)override;
				void onMouseRelease(Events::MouseButtonArgs& args)override;
				virtual void render(sf::RenderTarget*target) = 0;
				virtual void drawBorder();
				virtual void drawText();
				virtual void drawTexture();
				virtual void drawBack();
			protected:
				Text textObj;
				std::wstring text=L"";
				Font font;
				float borderSize = 1.0f;

				Color backColor = Color(0xAA, 0xAA, 0xAA);
				Color foreColor=Color::Black;
				const SharedTexture* imgTexture=nullptr;
				Color borderColor = Color(0, 0, 0, 100);
				Color actBorderColor;
				Color actBackColor;
				Color actForeColor;
				const SharedTexture* actImgTexture = nullptr;

				bool ownDraw = false;
				bool edited = true;
				bool active = false;

				const unsigned defaultTextSize = 20;
				static Font defaultFont;
			};
		}
	}
}

