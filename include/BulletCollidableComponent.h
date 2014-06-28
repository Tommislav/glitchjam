#ifndef BULLETCOLLIDABLECOMPONENT_H
#define BULLETCOLLIDABLECOMPONENT_H

class BulletCollidableComponent : public artemis::Component {
	public:
		int hp;
		int hitMask;
		bool invincible;
		bool hit;
		int explosionSize;

		BulletCollidableComponent(int hp, int hitMask, int explosionSize): hp(hp), hitMask(hitMask), invincible(false), hit(false), explosionSize(explosionSize) {}
		~BulletCollidableComponent(){}
};

#endif // BULLETCOLLIDABLECOMPONENT_H
