#ifndef REMOVEENTITIESCONDITIONSYSTEM_H
#define REMOVEENTITIESCONDITIONSYSTEM_H

class RemoveEntitiesConditionSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<RemoveEntityConditionComponent> removeMapper;
		CameraComponent *camera;
		bool hasCameraRef;

		bool insideCamera(float x, float y, int &w, int &h) {

			if (!hasCameraRef) { return false; }

			if (x+w >= 0 && x <= camera->cameraW) { // inside in x-axis
				if (y+h >= 0 && y <= camera->cameraH) { // inside in y-axis
					return true;
				}
			}
			return false;
		}


	public:

		RemoveEntitiesConditionSystem() {
			addComponentType<RemoveEntityConditionComponent>();
		}
		~RemoveEntitiesConditionSystem() {}



		virtual void begin() {
			hasCameraRef = world->getTagManager()->isSubscribed("system");
			if (hasCameraRef) {
				artemis::Entity &sys = world->getTagManager()->getEntity("system");
				camera = (CameraComponent*)sys.getComponent<CameraComponent>();
			}
		}

		virtual void end() {}

		virtual void initialize() {
			removeMapper.init(*world);
		}

	protected:
		virtual void processEntity(artemis::Entity &e) {
			RemoveEntityConditionComponent *r = removeMapper.get(e);

			bool lifeEnded = r->life <= 0;
			bool onScreen = true;

			r->life--;

			if (r->removeIfOutsideScreen) {
				RectangleComponent *rect = (RectangleComponent*)e.getComponent<RectangleComponent>();
				PositionComponent *pos = (PositionComponent*)e.getComponent<PositionComponent>();
				onScreen = insideCamera((pos->posX + rect->x), (pos->posY + rect->y), rect->width, rect->height);
			}

			//std::cout << "Remove entity? life=" << (r->life) << ", onScreen=" << onScreen << " (has cameraRef:)" << hasCameraRef << std::endl;
			if (lifeEnded || !onScreen) {
				//std::cout << "Remove entity" << std::endl;

				world->getEntityManager()->remove(e);
			}
		}

};

#endif // REMOVEENTITIESCONDITIONSYSTEM_H
