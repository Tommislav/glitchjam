#ifndef RENDERRECTANGLESSYSTEM_H
#define RENDERRECTANGLESSYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include "CameraComponent.h"



class RenderRectanglesSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<RectangleComponent> rectangleMapper;
		artemis::ComponentMapper<PositionComponent> positionMapper;
		CameraComponent *camera;

		bool insideCamera(int x, int y, int w, int h) {
			if (x+w >= 0 && x <= camera->cameraW) { // inside in x-axis
				if (y+h >= 0 && y <= camera->cameraH) { // inside in y-axis
					return true;
				}
			}
			return false;
		}

	public:
		RenderRectanglesSystem(CameraComponent &camera):camera(&camera) {
			addComponentType<RectangleComponent>();
			addComponentType<PositionComponent>();
			this->camera = &camera;
		}

		virtual void initialize() {
			rectangleMapper.init(*world);
			positionMapper.init(*world);
		}

	protected:
		virtual void processEntity(artemis::Entity &e) {
			RectangleComponent *r = rectangleMapper.get(e);
			PositionComponent *p = positionMapper.get(e);

			int localX = p->posX - camera->cameraX;
			int localY = p->posY - camera->cameraY;

			if (insideCamera(localX, localY, r->width, r->height)) {
				ofSetHexColor( r->color );
				ofRect(localX, localY, r->width, r->height);
			}
		}

};

#endif // RENDERRECTANGLESSYSTEM_H
