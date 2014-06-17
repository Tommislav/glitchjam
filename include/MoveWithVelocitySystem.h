#ifndef MOVEWITHVELOCITYSYSTEM_H
#define MOVEWITHVELOCITYSYSTEM_H

class MoveWithVelocitySystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<VelocityComponent> velMapper;
		artemis::ComponentMapper<PositionComponent> posMapper;

	public:
		MoveWithVelocitySystem() {
			addComponentType<VelocityComponent>();
			addComponentType<PositionComponent>();
		}

		virtual ~MoveWithVelocitySystem() {}

		virtual void initialize() {
			posMapper.init(*world);
			velMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e) {
			PositionComponent *p = posMapper.get(e);
			VelocityComponent *v = velMapper.get(e);
			p->posX += v->vX;
			p->posY += v->vY;
		}
};

#endif // MOVEWITHVELOCITYSYSTEM_H
