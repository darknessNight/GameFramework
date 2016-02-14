#include "Trackbar.h"

using namespace GF::IOModule;

void GF::Controller::Controls::Trackbar::onMousePress(Events::MouseButtonArgs &args)
{
	calcValue(args.x, args.y);
	Control::onMousePress(args);
}

void GF::Controller::Controls::Trackbar::onMouseMove(Events::MouseMoveArgs &args)
{
	calcValue(args.x, args.y);
	Control::onMouseMove(args);
}

void GF::Controller::Controls::Trackbar::calcValue(float x, float y)
{
	float val = (x - getPosition().x) / getSize().x * 100;
	setCurrent(val);
}

void GF::Controller::Controls::TrackbarH::onMousePress(Events::MouseButtonArgs &args)
{
	calcValue(args.x, args.y);
	Control::onMousePress(args);
}

void GF::Controller::Controls::TrackbarH::onMouseMove(Events::MouseMoveArgs &args)
{
	calcValue(args.x, args.y);
	Control::onMouseMove(args);
}

void GF::Controller::Controls::TrackbarH::calcValue(float x, float y)
{
	float val = (y - getPosition().y) / getSize().y * 100;
	setCurrent(val);
}
