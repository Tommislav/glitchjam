#ifndef FIREBULLETCOMPONENT_H
#define FIREBULLETCOMPONENT_H

class FireBulletComponent : public artemis::Component {
	public:
		int shootInterval;
		int shootCountdown;
		bool friendly;
		float dirX;
		float dirY;
		int offX = 0;
		int offY = 0;

		FireBulletComponent(int shootInterval, bool friendly): shootInterval(shootInterval), shootCountdown(shootInterval), friendly(friendly), dirX(0), dirY(-1) {}
		~FireBulletComponent(){}
};

#endif // FIREBULLETCOMPONENT_H
