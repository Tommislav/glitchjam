#ifndef SHAKECAMERASYSTEM_H
#define SHAKECAMERASYSTEM_H

#include "ofMath.h"
#include "RemoveEntityConditionComponent.h"


class ShakeCameraSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<CameraComponent> cameraMapper;

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


				// Create particles
				float explosionX = ofRandom(0,cam->cameraW) + cam->cameraX;
				float explosionY = ofRandom(0,cam->cameraH) + cam->cameraY;
				for (int i = 0; i < 10; i++) {
					artemis::Entity &em = world->createEntity();
					em.addComponent(new PositionComponent(
						explosionX + ofRandom(-10, 10),
						explosionY + ofRandom(-10, 10)
					));
					em.addComponent(new RectangleComponent(-5, -5, 10, 10, 0xffff00));
					em.addComponent(new VelocityComponent(ofRandom(-5, 5), ofRandom(-5, 5)));
					em.addComponent(new RemoveEntityConditionComponent(ofRandom(50,70), false));
					em.refresh();

				}

			}

		}
	protected:

};

#endif // SHAKECAMERASYSTEM_H
