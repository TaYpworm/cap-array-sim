#include "source.hpp"
#include <cassert>

Source::Source(entityx::Entity::Id inConnectionId)
{
	assert(inConnectionId == entityx::Entity::INVALID);
	connectionId = inConnectionId;
}