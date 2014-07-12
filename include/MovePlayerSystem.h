#ifndef MOVEPLAYERSYSTEM_H
#define MOVEPLAYERSYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include "Artemis/ComponentMapper.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "PlayerComponent.h"

#include "ofEvents.h"
#include "Settings.h"





class MovePlayerSystem : public artemis::EntityProcessingSystem
{
	public:
		static const int MOVE_UP 			= 1 << 1;
		static const int MOVE_DOWN 			= 1 << 2;
		static const int MOVE_LEFT 			= 1 << 3;
		static const int MOVE_RIGHT 		= 1 << 4;

		static const int ATK_UP 			= 1 << 5;
		static const int ATK_DOWN 			= 1 << 6;
		static const int ATK_LEFT 			= 1 << 7;
		static const int ATK_RIGHT	 		= 1 << 8;
		static const int ATK_RESET	 		= 1 << 9;

		static const int ATK_1		 		= 1 << 10;
		static const int ATK_2		 		= 1 << 11;


		MovePlayerSystem();
		virtual ~MovePlayerSystem();

		// Needed for key listeners!
		void keyPressed(ofKeyEventArgs &args);
		void keyReleased(ofKeyEventArgs &args);


		virtual void initialize();
		virtual void begin();
		virtual void end();
		virtual void processEntity(artemis::Entity &e);
	protected:
	private:
		artemis::ComponentMapper<VelocityComponent> velocityMapper;
		artemis::ComponentMapper<PlayerComponent> playerMapper;

		bool vert;
		bool horis;
		bool up;
		bool down;
		bool left;
		bool right;

		int atkUp;
		int atkDown;
		int atkLeft;
		int atkRight;

		int inputMask;

		int turretIndex;

		bool resetTurrets;

};

#endif // MOVEPLAYERSYSTEM_H
