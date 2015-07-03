#include "NetworkManager.hpp"
#include "CurrentRedistSystem.hpp"

NetworkManager::NetworkManager(entityx::EntityManager &entityManager,
	entityx::EventManager &eventManager)
	: _entityManager(entityManager),
	_eventManager(eventManager)
{
	// Add CurrentRedistSystem for handling OverCurrent events
	add<CurrentRedistSystem>();
}

template <typename S>
void NetworkManager::add(std::shared_ptr<S> system)
{
	_systems.insert(std::make_pair(S::family(), system));
}

template <typename S, typename ... Args>
std::shared_ptr<S> NetworkManager::add(Args && ... args)
{
	std::shared_ptr<S> s(new S(std::forward<Args>(args) ...));
    add(s);
    return s;
}

template <typename S>
std::shared_ptr<S> NetworkManager::system()
{
	auto it = _systems.find(S::family());
    assert(it != _systems.end());
    return it == _systems.end()
        ? std::shared_ptr<S>()
        : std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
}

template <typename S>
void NetworkManager::update(entityx::TimeDelta dt)
{
	assert(_initialized && "NetworkManager::configure() not called");
    std::shared_ptr<S> s = system<S>();
    s->update(_entityManager, _eventManager, dt);
}

void NetworkManager::updateAll(entityx::TimeDelta dt)
{
	assert(_initialized && "NetworkManager::configure() not called");

	// Clear the update stacks and begin update from the start of the network.
	_pendingUpdate.clear();
	_completedUpdate.clear();
	for (auto &pair : _systems) 
	{
		_pendingUpdate.push_back(pair.second);

    	pair.second->update(_entityManager, _eventManager, dt);
  	}
}

void NetworkManager::configure()
{
	// Subscribe to OverCurrentEvent
	_eventManager.subscribe<OverCurrentEvent>(*this);

	for (auto &pair : _systems) 
	{
    	pair.second->configure(_entityManager, _eventManager);
  	}
  	_initialized = true;
}

void NetworkManager::receive(const OverCurrentEvent &overCurrentEvent)
{
	// Push currently executing system to for update after the CurrentRedistSystem
	// has updated.
	_pendingUpdate.push_back(_updating);
	// Push the CurrentRedistSystem to the update stack so that it executes next.
	auto it = _systems.find(CurrentRedistSystem::family());
	_pendingUpdate.push_back(std::shared_ptr<entityx::BaseSystem>(it->second));
}