#ifndef SPAWNBULLETSSYSTEM_H
#define SPAWNBULLETSSYSTEM_H

#include "FireBulletComponent.h"
#include "BulletComponent.h"

class SpawnBulletSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<FireBulletComponent> bulMapper;
		artemis::ComponentMapper<PositionComponent> posMapper;
		bool soundLoaded = false;
		ofSoundPlayer pew;

	public:
		SpawnBulletSystem() {
			addComponentType<FireBulletComponent>();
			addComponentType<PositionComponent>();
		}

		virtual ~SpawnBulletSystem() {
		}

		virtual void initialize() {
			posMapper.init(*world);
			bulMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e) {

			FireBulletComponent *b = bulMapper.get(e);

			bool shotFired = false;

			b->shootCountdown -= 1;
			if ( b->shootCountdown <= 0 ) {
				// reset bullet counter
				b->shootCountdown = b->shootInterval;

				// spawn bullet
				PositionComponent *p = posMapper.get(e);
				float x = p->posX + b->offX;
				float y = p->posY + b->offY;

				artemis::Entity &bullet = world->createEntity();
				bullet.addComponent(new PositionComponent(x + b->offX, y + b->offY));
				bullet.addComponent(new VelocityComponent(b->dirX, b->dirY));
				bullet.addComponent(new RectangleComponent(-4, -4, 8, 8, 0xffffff, 0));
				bullet.addComponent(new RemoveEntityConditionComponent(200, true));
				bullet.addComponent(new BulletComponent( (b->friendly) ? 1 : 2 ));
				bullet.refresh();

				shotFired = true;
			}

			if (shotFired) {

				if (!soundLoaded) {
					soundLoaded = true;
					pew.loadSound("Laser.wav");
					pew.setVolume(0.1f);
				}

				pew.play();
			}

		}
};


#endif // SPAWNBULLETSSYSTEM_H
