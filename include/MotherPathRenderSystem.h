#ifndef MOTHERPATHRENDERSYSTEM_H_INCLUDED
#define MOTHERPATHRENDERSYSTEM_H_INCLUDED

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include "CameraComponent.h"
#include <vector>



class MotherPathRenderSystem : public artemis::EntityProcessingSystem
{
	private:

		int cameraX;
		int cameraY;


		artemis::ComponentMapper<MothershipComponent> motherMapper;

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
		MotherPathRenderSystem(CameraComponent &camera):camera(&camera) {
			addComponentType<MothershipComponent>();

			this->camera = &camera;
		}

		virtual void initialize() {
			motherMapper.init(*world);
		}

	protected:

		virtual void begin() {

		}


		virtual void processEntity(artemis::Entity &e) {
			MothershipComponent *mother = motherMapper.get(e);
			//PathComponent *path = e.getComponent<PathComponent>();

			//int localX = p->posX + r->x - camera->cameraX;
			//int localY = p->posY + r->y - camera->cameraY;

			//if (insideCamera(localX, localY, r->width, r->height)) {
				ofSetHexColor( 0xff0000 );
				ofSetLineWidth(4);
				ofLine(0,0,100,100);
				//ofRect(localX, localY, r->width, r->height);
			//}
		}

		virtual void end() {
		}

};

#endif // MOTHERPATHRENDERSYSTEM_H_INCLUDED
