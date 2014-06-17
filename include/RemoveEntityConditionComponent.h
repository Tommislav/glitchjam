#ifndef REMOVEENTITYCONDITIONCOMPONENT_H
#define REMOVEENTITYCONDITIONCOMPONENT_H

class RemoveEntityConditionComponent : public artemis::Component
{
	public:
		int life;
		bool removeIfOutsideScreen;

		RemoveEntityConditionComponent(int life, bool removeIfOutsideScreen):life(life), removeIfOutsideScreen(removeIfOutsideScreen) {}
		~RemoveEntityConditionComponent(){}
};

#endif // REMOVEENTITYCONDITIONCOMPONENT_H
