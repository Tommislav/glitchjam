#ifndef TURRETSYSTEM_H
#define TURRETSYSTEM_H

class TurretSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<PositionComponent> posMapper;
		artemis::ComponentMapper<TurretComponent> turMapper;
		PositionComponent *playerPos;

		bool valueBetween(float val, float min, float max) {
			return val > min && val < max;
		}

	public:
		TurretSystem() {
			addComponentType<PositionComponent>();
			addComponentType<TurretComponent>();
		}

		virtual ~TurretSystem() {
		}

		virtual void initialize() {
			posMapper.init(*world);
			turMapper.init(*world);
		}

		virtual void begin() {
			playerPos = (PositionComponent*) world->getTagManager()->getEntity("player").getComponent<PositionComponent>();
		}

		virtual void processEntity(artemis::Entity &e) {

			PositionComponent *p = posMapper.get(e);
			TurretComponent *t = turMapper.get(e);

			float toX;
			float toY;

			if (t->attached) {
				toX = playerPos->posX + t->offX;
				toY = playerPos->posY;
			} else {
				toX = t->targetX;
				toY = t->targetY;
			}

			if (t->lockedInPlace) {
				p->posX = toX;
				p->posY = toY;
			} else {
				float dX = toX - p->posX;
				float dY = toY - p->posY;
				float mX = dX / 6;
				float mY = dY / 6;

				p->posX += mX;
				p->posY += mY;

				float minDist = 4;
				if (valueBetween(dX, -minDist, minDist) && valueBetween(dY, -minDist, minDist)) {
					t->lockedInPlace = true;
				}
			}
		}
};

#endif // TURRETSYSTEM_H
