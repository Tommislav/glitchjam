#ifndef SHAKECAMERASYSTEM_H
#define SHAKECAMERASYSTEM_H

#include <math.h>
#include "ofMath.h"
#include "RemoveEntityConditionComponent.h"


class ShakeCameraSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<CameraComponent> cameraMapper;

	public:
		ShakeCameraSystem() {
			addComponentType<CameraComponent>();
		}
		virtual ~ShakeCameraSystem(){}

		virtual void initialize() {
			cameraMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e){

			CameraComponent *cam = (CameraComponent*) e.getComponent<CameraComponent>();
			if (cam->quakeCount > 0) {
				cam->quakeCount--;

				float qX = ofRandom(-cam->quakeSize, cam->quakeSize);
				float qY = ofRandom(-cam->quakeSize, cam->quakeSize);
				cam->cameraX = qX;
				cam->cameraY = qY;
			} else {
				cam->cameraX = 0;
				cam->cameraY = 0;
			}
		}
};

#endif // SHAKECAMERASYSTEM_H
