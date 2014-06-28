#ifndef SHOOTABLESYSTEM_H_INCLUDED
#define SHOOTABLESYSTEM_H_INCLUDED

class ShootableSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<BulletCollidableComponent> collMapper;
		artemis::ComponentMapper<RectangleComponent> rectMapper;

	public:

		ShootableSystem() {
			addComponentType<BulletCollidableComponent>();
			addComponentType<RectangleComponent>();
		}
		~ShootableSystem() {}



		virtual void begin() {
			world->getGroupManager()->getEntities("bullet");
		}

		virtual void end() {}

		virtual void initialize() {
			collMapper.init(*world);
			rectMapper.init(*world);
		}

	protected:
		virtual void processEntity(artemis::Entity &e) {
			//RemoveEntityConditionComponent *r = removeMapper.get(e);
		}

};

#endif // SHOOTABLESYSTEM_H_INCLUDED
