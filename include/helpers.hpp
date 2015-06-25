#ifndef __HELPERS_HPP__
#define __HELPERS_HPP__

#include "serialarray.hpp"
#include <entityx/entityx.h>

bool hasCap(const entityx::ComponentHandle<SerialArray>& array);

#endif