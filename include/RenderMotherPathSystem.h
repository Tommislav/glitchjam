#ifndef RENDERMOTHERPATHSYSTEM_H_INCLUDED
#define RENDERMOTHERPATHSYSTEM_H_INCLUDED

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include "ofVec2f.h"
#include "CameraComponent.h"
#include <vector>
#include <map>



class RenderMotherPathSystem : public artemis::EntityProcessingSystem
{
	private:

		int cameraX;
		int cameraY;
		map<int, int> pathIndex;


		artemis::ComponentMapper<MothershipComponent> motherMapper;
		artemis::ComponentMapper<PathComponent> pathMapper;

		CameraComponent *camera;

		bool insideCamera(int x, int y, int w, int h) {
			if (x+w >= 0 && x <= camera->cameraW) { // inside in x-axis
				if (y+h >= 0 && y <= camera->cameraH) { // inside in y-axis
					return true;
				}
			}
			return false;
		}

	public:
		RenderMotherPathSystem(CameraComponent &camera):camera(&camera) {
			addComponentType<MothershipComponent>();
			addComponentType<PathComponent>();

			this->camera = &camera;
		}

		virtual void initialize() {
			motherMapper.init(*world);
			pathMapper.init(*world);
		}

	protected:

		virtual void begin() {
			cameraX = camera->cameraX;
			cameraY = camera->cameraY;
		}


		virtual void processEntity(artemis::Entity &e) {
			MothershipComponent *mother = motherMapper.get(e);
			PathComponent *path = pathMapper.get(e);

			if (mother == NULL || path == NULL) {
				return;
			}

			int tail = 0;
			int head = 0;
			int max = 0;
			int steps = 0;
			int traceLength = 400;

			int index = path->id;
			if (pathIndex.find(index) != pathIndex.end()) { // exists!!!
				max = path->points.size()-1;
				head = pathIndex[index];
				tail = head - traceLength;
			} else { // don't exist
				pathIndex[index] = 0;
			}

			if (tail >= max) {
				// Done! remove!
				//std::cout << "TAIL > MAX " << tail << ", " << max << std::endl;
				return;
			}

			int speed = 4;
			pathIndex[index] = head + speed;

			
			int color = 0xff0000;
			ofSetHexColor(color);
			ofSetLineWidth(2);

			//std::cout << "tail: " << tail << ", head: " << head << ", max: " << max << std::endl;

			for (int i = (tail + 1); i < head; i++) {
				if (i < 1 || i > max) { continue; }
				
				ofVec2f last = path->points[i - 1];
				ofVec2f curr = path->points[i];
				ofLine(last.x - cameraX, last.y-cameraY, curr.x - cameraX, curr.y - cameraY);
			}
		}

		virtual void end() {
		}

};

#endif // MOTHERPATHRENDERSYSTEM_H_INCLUDED
