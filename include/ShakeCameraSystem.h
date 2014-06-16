#ifndef SHAKECAMERASYSTEM_H
#define SHAKECAMERASYSTEM_H

#include "ofMath.h"

class ShakeCameraSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<CameraComponent> cameraMapper;
		//artemis::ComponentMapper<PositionComponent> positionMapper;
		//artemis::ComponentMapper<InputControllableComponent> inputMarkerMapper;

		PlayerInputComponent *input;
		int quakeCount;
		int qX;
		int qY;

	public:

		virtual void initialize() {
			cameraMapper.init(*world);
		}

		ShakeCameraSystem(PlayerInputComponent &input):input(&input), quakeCount(0){
			addComponentType<CameraComponent>();
		}
		virtual ~ShakeCameraSystem(){}

		virtual void processEntity(artemis::Entity &e){

			CameraComponent *cam = (CameraComponent*) e.getComponent<CameraComponent>();
			cam->cameraX -= qX;
			cam->cameraY -= qY;
			qX = 0;
			qY = 0;

			if (quakeCount > 0) {
				quakeCount--;

				int s = quakeCount / 2;

				qX = ofRandom(-s, s);
				qY = ofRandom(-s, s);

				cam->cameraX += qX;
				cam->cameraY += qY;

			} else if (input->atk1()) {
				quakeCount = 40;
			}

		}
	protected:

};

#endif // SHAKECAMERASYSTEM_H
