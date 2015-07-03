#ifndef __NETWORKMANAGER_HPP__
#define __NETWORKMANAGER_HPP__

#include <entityx/entityx.h>
#include <vector>
#include <unordered_map>
#include "OverCurrentEvent.hpp"

class NetworkManager 
	: entityx::help::NonCopyable, 
	public entityx::Receiver<OverCurrentEvent>
{
private:
	// Fields
	bool _initialized = false;
	entityx::EntityManager &_entityManager;
	entityx::EventManager &_eventManager;
	std::unordered_map<entityx::BaseSystem::Family, 
		std::shared_ptr<entityx::BaseSystem>> _systems;
	std::vector<std::shared_ptr<entityx::BaseSystem>> _pendingUpdate;
	std::vector<std::shared_ptr<entityx::BaseSystem>> _completedUpdate;
	std::shared_ptr<entityx::BaseSystem> _updating;	

public:
	// Constructors
	NetworkManager(entityx::EntityManager &entityManager,
		entityx::EventManager &eventManager);

	// Methods
	template <typename S>
	void add(std::shared_ptr<S> system);

	template <typename S, typename ... Args>
	std::shared_ptr<S> add(Args && ... args);

	template <typename S>
	std::shared_ptr<S> system();

	template <typename S>
	void update(entityx::TimeDelta dt);

	void updateAll(entityx::TimeDelta dt);

	void configure();	

	void receive(const OverCurrentEvent &overCurrentEvent);
};

#endif