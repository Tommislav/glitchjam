#ifndef REMOVEENTITIESCONDITIONSYSTEM_H
#define REMOVEENTITIESCONDITIONSYSTEM_H

class RemoveEntitiesConditionSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<RemoveEntityConditionComponent> removeMapper;
		//CameraComponent *camera;
		/*
		bool insideCamera(int x, int y, int w, int h) {
			if (x+w >= 0 && x <= camera->cameraW) { // inside in x-axis
				if (y+h >= 0 && y <= camera->cameraH) { // inside in y-axis
					return true;
				}
			}
			return false;
		}
		*/

	public:
		RemoveEntitiesConditionSystem() {
			addComponentType<RemoveEntityConditionComponent>();
		}
		~RemoveEntitiesConditionSystem() {}

		virtual void initialize() {
			removeMapper.init(*world);
		}

	protected:
		virtual void processEntity(artemis::Entity &e) {
			RemoveEntityConditionComponent *r = removeMapper.get(e);

			if (r->life <= 0) {
				world->getEntityManager()->remove(e);
			}
			r->life--;
		}

};

#endif // REMOVEENTITIESCONDITIONSYSTEM_H
