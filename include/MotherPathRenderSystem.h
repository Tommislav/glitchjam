#ifndef MOTHERPATHRENDERSYSTEM_H_INCLUDED
#define MOTHERPATHRENDERSYSTEM_H_INCLUDED

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include "ofVec2f.h"
#include "CameraComponent.h"
#include <vector>
#include <map>



class MotherPathRenderSystem : public artemis::EntityProcessingSystem
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
		MotherPathRenderSystem(CameraComponent &camera):camera(&camera) {
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

		}


		virtual void processEntity(artemis::Entity &e) {
			MothershipComponent *mother = motherMapper.get(e);
			PathComponent *path = pathMapper.get(e);

			if (path == 0) { // invalid pointer... =/
				std::cout << "INVALID POINTER TO PATH..." << std::endl;
				return;
			}

			int start = 0;
			int end = 1;
			int max = 0;
			int steps = 0;
			int traceLength = 400;

			int index = path->id;
			if (pathIndex.find(index) != pathIndex.end()) { // exists!!!
				max = path->points.size()-1;
				start = pathIndex[index];

				steps = (start < traceLength) ? start : traceLength;
				end = start + steps;

				/*
				if (start < 20) { end+=2; }
				else { end = start + 20; }
				*/
				if (end > max) end = max;
				

			} else {
				// don't exist
				//pathIndex[index] = end;
			}
			int speed = 4;
			pathIndex[index] = (start + speed > max) ? max : start + speed;

			if (start == end == max) {
				// Done! remove!
			}

			//PathComponent *path = e.getComponent<PathComponent>();

			//int localX = p->posX + r->x - camera->cameraX;
			//int localY = p->posY + r->y - camera->cameraY;

			//ofVec2f vStart = path->points[start];
			//ofVec2f vEnd = path->points[end];

			std::cout << "start: " << start << ", end: " << end << ", max: " << max << std::endl;

			
			int color = 0xff0000;
			ofSetHexColor(color);
			ofSetLineWidth(2);

			for (int i=start; i < end; i++) {
				if (i == start) { continue; }
				
				
				

				ofVec2f last = path->points[i - 1];
				ofVec2f curr = path->points[i];
				ofLine(last.x, last.y, curr.x, curr.y);
			}
			

			//ofLine(vStart.x, vStart.y, vEnd.x, vEnd.y);
		}

		virtual void end() {
		}

};

#endif // MOTHERPATHRENDERSYSTEM_H_INCLUDED
