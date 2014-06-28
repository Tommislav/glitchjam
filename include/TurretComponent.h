#ifndef TURRETCOMPONENT_H
#define TURRETCOMPONENT_H

class TurretComponent : public artemis::Component {
	public:
		bool attached;
		bool lockedInPlace;
		int targetX;
		int targetY;
		int offX;

		TurretComponent(int offX): attached(false), targetX(0), targetY(0), offX(offX), lockedInPlace(true) {}
		~TurretComponent(){}
};

#endif // TURRETCOMPONENT_H
