#ifndef SHOOTABLESYSTEM_H_INCLUDED
#define SHOOTABLESYSTEM_H_INCLUDED

#include "BulletCollidableComponent.h"
#include "RectangleComponent.h"
#include "RectangleComponent.h"

class BulletCollisionSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<BulletCollidableComponent> collMapper;
		artemis::ComponentMapper<RectangleComponent> rectMapper;
		artemis::ComponentMapper<PositionComponent> posMapper;

		artemis::ImmutableBag<artemis::Entity*> *bullets;
		int bulletShatterCount;



		void createParticles(float explosionX, float explosionY, int size) {

			explosionX += ofRandom(-4,4);
			explosionY += ofRandom(-4,4);
			for (int i = 0; i < 3; i++) {
				artemis::Entity &em = world->createEntity();

				float rad = ofRandom(0, 6.28);
				float velX = cos(rad);
				float velY = sin(rad);
				float offset = ofRandom(2, 4);
				float speed = ofRandom(1,3);

				em.addComponent(new PositionComponent(
					explosionX + (velX * offset),
					explosionY + (velY * offset)
				));
				em.addComponent(new RectangleComponent(-1, -1, 2, 2, 0xffffff, 0));
				em.addComponent(new VelocityComponent(velX * speed, velY * speed));
				em.addComponent(new RemoveEntityConditionComponent(ofRandom(10,60), false));
				em.refresh();

			}


		}




	public:


		BulletCollisionSystem():bulletShatterCount(0) {
			addComponentType<BulletCollidableComponent>();
			addComponentType<RectangleComponent>();
			addComponentType<PositionComponent>();
		}
		~BulletCollisionSystem() {}



		virtual void begin() {
			bullets = world->getGroupManager()->getEntities("bullet");
			//std::cout << "Number of bullets: " << bullets->getCount() << std::endl;
		}

		virtual void end() {
			bullets = NULL;
		}

		virtual void initialize() {
			collMapper.init(*world);
			rectMapper.init(*world);
			posMapper.init(*world);
		}

	protected:
		bool collision(float myX, float myOffX, float myY, float myOffY, float myWidth, float myHeight, float bulletX, float bulletY) {
			float mx = myX + myOffX;
			float my = myY + myOffY;

			if (bulletX >= mx && bulletX <= mx+myWidth) {
				if (bulletY >= my && bulletY <= my+myHeight) {
					return true;
				}
			}
			return false;
		}

		virtual void processEntity(artemis::Entity &e) {

			if (bullets == NULL || bullets->getCount() == 0) {return;}

			BulletCollidableComponent *coll = collMapper.get(e);
			RectangleComponent *rect = rectMapper.get(e);
			PositionComponent *pos = posMapper.get(e);

			for (int i = 0; i < bullets->getCount(); i++) {
				artemis::Entity *b = bullets->get(i);
				PositionComponent *bp = (PositionComponent*)b->getComponent<PositionComponent>();

				if (bp == NULL) { continue; }

				// collision?
				if (collision(pos->posX, rect->x, pos->posY, rect->y, rect->width, rect->height, bp->posX, bp->posY)) {
					world->deleteEntity(*b);
					coll->hit = true;
					coll->hp -= 1;

					if (coll->hp <= 0) {
						world->deleteEntity(e);
					} else {
						// small bullet praticle
						//if (bulletShatterCount++ > 2) {
						//	bulletShatterCount = 0;
							createParticles(bp->posX, bp->posY, 1);
						//}
					}
				}
			}


			//RemoveEntityConditionComponent *r = removeMapper.get(e);
		}

};

#endif // SHOOTABLESYSTEM_H_INCLUDED
