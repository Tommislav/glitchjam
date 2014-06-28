#ifndef FIREBULLETCOMPONENT_H
#define FIREBULLETCOMPONENT_H

class FireBulletComponent : public artemis::Component {
	public:
		int shootInterval;
		int shootCountdown;
		bool friendly;
		float dirX;
		float dirY;
		int offX;
		int offY;

		FireBulletComponent(int shootInterval, bool friendly, int offX=0, int offY=0): shootInterval(shootInterval), shootCountdown(shootInterval), friendly(friendly), dirX(0), dirY(-12), offX(offX), offY(offY) {}
		~FireBulletComponent(){}
};

#endif // FIREBULLETCOMPONENT_H
