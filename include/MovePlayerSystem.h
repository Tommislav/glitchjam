#ifndef MOVEPLAYERSYSTEM_H
#define MOVEPLAYERSYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include "Artemis/ComponentMapper.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "PlayerInputComponent.h"
#include "InputControllableComponent.h"

class MovePlayerSystem : public artemis::EntityProcessingSystem
{
	public:
		MovePlayerSystem(PlayerInputComponent &input);
		virtual ~MovePlayerSystem();

		virtual void processEntity(artemis::Entity &e);
	protected:
	private:
		artemis::ComponentMapper<VelocityComponent> velocityMapper;
		artemis::ComponentMapper<PositionComponent> positionMapper;
		artemis::ComponentMapper<InputControllableComponent> inputMarkerMapper;

		PlayerInputComponent &input;
};

#endif // MOVEPLAYERSYSTEM_H
