#include <cassert>
#include "Source.hpp"

Source::Source(entityx::Entity::Id inConnectionId)
{
	assert(inConnectionId == entityx::Entity::INVALID);
	connectionId = inConnectionId;
}