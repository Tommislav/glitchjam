#ifndef BULLETCOLLIDABLECOMPONENT_H
#define BULLETCOLLIDABLECOMPONENT_H

class BulletCollidableComponent : public artemis::Component {
	public:
		int hitMask;
		bool invincible;
		bool hit;

		BulletCollidableComponent(int hitMask): hitMask(hitMask), invincible(false), hit(false) {}
		~BulletCollidableComponent(){}
};

#endif // BULLETCOLLIDABLECOMPONENT_H
