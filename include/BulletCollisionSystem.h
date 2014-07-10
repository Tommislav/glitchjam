#ifndef SHOOTABLESYSTEM_H_INCLUDED
#define SHOOTABLESYSTEM_H_INCLUDED

#include "Settings.h"
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

		ofSoundPlayer explosion;
		bool soundLoaded;


		void createParticles(float explosionX, float explosionY, int s) {
			//int foo [5] = { 16, 2, 77, 40, 12071 };
			float startOffset[2] 	= {4,2};
			float numParticles[2] 	= {3,30};
			float minSpeed[2] 		= {1,2};
			float maxSpeed[2] 		= {3,3};
			float minRadOffset[2] 	= {2,11};
			float maxRadOffset[2] 	= {4,12};
			int sizeX[2] 			= {-1,-4};
			int sizeW[2] 			= {2,8};
			int color[2] 			= {0xffffff, 0xffff00};
			float minLife[2] 		= {10,40};
			float maxLife[2] 		= {60,50};



			explosionX += ofRandom(-startOffset[s],startOffset[s]);
			explosionY += ofRandom(-startOffset[s],startOffset[s]);
			for (int i = 0; i < numParticles[s]; i++) {
				artemis::Entity &em = world->createEntity();

				float rad = ofRandom(0, 6.28);
				float velX = cos(rad);
				float velY = sin(rad);
				float radOffset = ofRandom(minRadOffset[s], maxRadOffset[s]);
				float speed = ofRandom(minSpeed[s],maxSpeed[s]);

				em.addComponent(new PositionComponent(
					explosionX + (velX * radOffset),
					explosionY + (velY * radOffset)
				));
				em.addComponent(new RectangleComponent(sizeX[s], sizeX[s], sizeW[s], sizeW[s], color[s], 0));
				em.addComponent(new VelocityComponent(velX * speed, velY * speed));
				em.addComponent(new RemoveEntityConditionComponent(ofRandom(minLife[s],maxLife[s]), false));
				em.refresh();

			}
		}

		void shakeScreen(int length, float str) {
			artemis::Entity &sys = world->getTagManager()->getEntity("system");
			CameraComponent *cam = (CameraComponent*)sys.getComponent<CameraComponent>();
			cam->quakeCount = length;
			cam->quakeSize = str;
		}


		void playExplosionSound() {
			if (!soundLoaded) {
				explosion.loadSound("Explosion1.wav");
			}
			explosion.play();
		}



	public:


		BulletCollisionSystem():bulletShatterCount(0),soundLoaded(false){
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

				if (bp == NULL || (pos == bp)) { continue; }

				// collision?
				if (collision(pos->posX, rect->x, pos->posY, rect->y, rect->width, rect->height, bp->posX, bp->posY)) {
					world->deleteEntity(*b);
					coll->hit = true;
					coll->hp -= 1;

					if (coll->hp <= 0) {
						world->deleteEntity(e);
						createParticles(bp->posX, bp->posY,1);
						shakeScreen(10, 8);
						if (USE_SOUNDS) {
							playExplosionSound();
						}
					} else {
						createParticles(bp->posX, bp->posY,0);
					}
				}
			}


			//RemoveEntityConditionComponent *r = removeMapper.get(e);
		}

};

#endif // SHOOTABLESYSTEM_H_INCLUDED
