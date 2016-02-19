#include "Equipment.h"

bool GF::GameEngine::Equipment::operator==(const Equipment & rhs)
{
	return rhs.name==name&&additionalData==rhs.additionalData;
}
