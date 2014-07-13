#ifndef SWARMCOMPONENT_H
#define SWARMCOMPONENT_H

class SwarmComponent : public artemis::Component {
	public:
		bool isMother;
		bool hasMother;
		artemis::Entity *mother; // can be NULL
		int swarmId;

		bool usePathOffset;
		int pathOffset;

		float motherOffX;
		float motherOffY;
		float motherOffRad;
		float motherOffDist;
		float rotationSpeed;
		float rotationFriction;

		SwarmComponent(int swarmId) : swarmId(swarmId){}
		~SwarmComponent(){}
};

#endif // SWARMCOMPONENT_H
