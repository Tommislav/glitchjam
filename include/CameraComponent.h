#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

class CameraComponent : public artemis::Component {
	public:
		float cameraX;
		float cameraY;
		float cameraW;
		float cameraH;

		float quakeSize;
		int quakeCount;

		CameraComponent(float width, float height): cameraX(0), cameraY(0), cameraW(width), cameraH(height), quakeSize(0), quakeCount(0){}
		~CameraComponent(){}
};

#endif // CAMERACOMPONENT_H
