#ifndef BULLETCOMPONENT_H
#define BULLETCOMPONENT_H

class BulletComponent : public artemis::Component {
	public:
		int hitMask;
		bool hit;

		BulletComponent(int hitMask): hitMask(hitMask), hit(false) {}
		~BulletComponent(){}
};

#endif // BULLETCOMPONENT_H
