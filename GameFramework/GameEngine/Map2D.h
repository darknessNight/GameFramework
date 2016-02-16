
#define Mechanic Module_Map2D_h

#include <vector>

#include <Input/Output Module/Size.h>

#include "Map.h"


namespace Mechanic Module {

class Map2D : public Map {

 public:
    std::vector< bool > colisionMap;
    Input/Output Module::Size size;
};

} /* End of namespace Mechanic Module */

#endif // Mechanic Module_Map2D_h
