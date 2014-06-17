#ifndef SHAKECAMERASYSTEM_H
#define SHAKECAMERASYSTEM_H

#include <math.h>
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
				for (int i = 0; i < 30; i++) {
					artemis::Entity &em = world->createEntity();

					float rad = ofRandom(0, 6.28);
					float velX = cos(rad);
					float velY = sin(rad);
					float offset = ofRandom(10, 15);
					float speed = ofRandom(1,7);

					em.addComponent(new PositionComponent(
						explosionX + (velX * offset),
						explosionY + (velY * offset)
					));
					em.addComponent(new RectangleComponent(-6, -6, 12, 12, 0xffff00));
					em.addComponent(new VelocityComponent(velX * speed, velY * speed));
					em.addComponent(new RemoveEntityConditionComponent(ofRandom(50,70), false));
					em.refresh();

				}

			}

		}
	protected:

};

#endif // SHAKECAMERASYSTEM_H
