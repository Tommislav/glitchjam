#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

class PlayerComponent : public artemis::Component {
	public:
		int type;

		PlayerComponent(int type): type(type) {}
		~PlayerComponent(){}
};

#endif // PLAYERCOMPONENT_H
