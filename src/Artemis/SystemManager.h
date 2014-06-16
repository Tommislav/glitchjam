#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <map>
#include "ImmutableBag.h"
#include "TypeInfoComparator.h"
#include <iostream>
namespace artemis {

	class EntitySystem;
	class Entity;
	class World;

	class SystemManager {
  public:
    SystemManager(World &world);
    ~SystemManager();
    void initializeAll();
    void processAll();
    Bag<EntitySystem*> & getSystems();
    EntitySystem* setSystem(EntitySystem * stm, bool autoProcess);

	World* getWorld();

    template<typename eSystem>
    EntitySystem* getSystem() {
      return (eSystem*)(systems[&typeid(eSystem)]);
    }

  private:
    World * world;
    std::map<const std::type_info*, EntitySystem*, type_info_comparator> systems;
    Bag<EntitySystem*> bagged;
    Bag<EntitySystem*> autoProcessBag;
	};
};
#endif // $(Guard token)
