#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

class CameraComponent : public artemis::Component {
	public:
		float cameraX;
		float cameraY;
		float cameraW;
		float cameraH;

		CameraComponent(float width, float height): cameraW(width), cameraH(height){}
		~CameraComponent(){}
};

#endif // CAMERACOMPONENT_H
