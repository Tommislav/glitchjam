#ifndef MOTHERSHIPCOMPONENT_H
#define MOTHERSHIPCOMPONENT_H

class MothershipComponent : public artemis::Component {
	public:
		std::string swarmId;

		MothershipComponent(std::string swarmId): swarmId(swarmId) {}
		~MothershipComponent(){}
};

#endif // MOTHERSHIPCOMPONENT_H
