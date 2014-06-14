#ifndef RENDERRECTANGLESSYSTEM_H
#define RENDERRECTANGLESSYSTEM_H

#include <Artemis/EntityProcessingSystem.h>

#include <Artemis/ComponentMapper.h>
#include <RectangleComponent.h>
#include <PositionComponent.h>


class RenderRectanglesSystem : public artemis::EntityProcessingSystem
{
	public:
		RenderRectanglesSystem();
	protected:
		virtual void processEntity(artemis::Entity &e);
	private:
		artemis::ComponentMapper<RectangleComponent> rectangleMapper;
		artemis::ComponentMapper<PositionComponent> positionMapper;
};

#endif // RENDERRECTANGLESSYSTEM_H
