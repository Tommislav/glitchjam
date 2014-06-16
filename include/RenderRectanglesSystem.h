#ifndef RENDERRECTANGLESSYSTEM_H
#define RENDERRECTANGLESSYSTEM_H

#include <Artemis/EntityProcessingSystem.h>

#include <Artemis/ComponentMapper.h>



class RenderRectanglesSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<RectangleComponent> rectangleMapper;
		artemis::ComponentMapper<PositionComponent> positionMapper;

	public:
		RenderRectanglesSystem() {
			addComponentType<RectangleComponent>();
			addComponentType<PositionComponent>();
		}

		virtual void initialize() {
			rectangleMapper.init(*world);
			positionMapper.init(*world);
		}

	protected:
		virtual void processEntity(artemis::Entity &e) {
			RectangleComponent *r = rectangleMapper.get(e);
			PositionComponent *p = positionMapper.get(e);
			ofSetHexColor( r->color );
			ofRect(p->posX, p->posY, r->width, r->height);
		}

};

#endif // RENDERRECTANGLESSYSTEM_H
