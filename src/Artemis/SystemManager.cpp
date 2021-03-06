#include "Artemis/SystemManager.h"
#include "Artemis/World.h"
#include "Artemis/EntitySystem.h"
#include "Artemis/SystemBitManager.h"

namespace artemis {

  SystemManager::SystemManager(World& world) {
    this->world = &world;
  }

  World* SystemManager::getWorld() { return this->world; }

  Bag<EntitySystem*> & SystemManager::getSystems() {
    return bagged;
  }

  void SystemManager::initializeAll() {
    for(int i=0; i< bagged.getCount(); i++) {
      bagged.get(i)->initialize();
    }
  }

  void SystemManager::processAll() {
	for(int i=0; i< autoProcessBag.getCount(); i++) {
      autoProcessBag.get(i)->process();
    }
  }

  EntitySystem* SystemManager::setSystem(EntitySystem* stm, bool autoProcess=true) {
    bool bitFlag = false;
    int index = 0;

    //Check if system is known.
    for(int i=0; i< bagged.getCount(); i++)
    {
      if(typeid(*stm) == typeid(*bagged.get(i))){
        bitFlag = true;
        index = i;
      }
    }

    //Check if stm pointer doesn't point to an existing system
    //Else add system to manager
    if(bagged.get(index) != stm){
      //If it doesn't point to an existing system
      //Check if the new system is already known
      if(bitFlag){
        //Delete newly made system.
        delete stm;
        //Point to existing system in bag.
        stm = bagged.get(index);
      }
      else{
        stm->setWorld(world);
        systems[&typeid(*stm)]  = stm;
        bagged.add(stm);
        stm->setSystemBit(SystemBitManager::getBitFor(typeid(*stm)));
      }
    }

    if (autoProcess) {
		autoProcessBag.add(stm);
    }

    return stm;
  }

  SystemManager::~SystemManager(){
    systems.clear();
    bagged.deleteData();
	bagged.clear();
    autoProcessBag.clear();
  }
};
