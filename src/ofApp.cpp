#include <iostream>

#include "ofApp.h"
#include "ofMath.h"
#include "World.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "PlayerInputComponent.h"
#include "RectangleComponent.h"
#include "SineOffsetComponent.h"
#include "RenderRectanglesSystem.h"
#include "MovePlayerSystem.h"
#include "InputControllableComponent.h"
#include "Artemis/EntityProcessingSystem.h"
#include "MoveSineOffsetSystem.h"
#include "ShakeCameraSystem.h"
#include "RemoveEntitiesConditionSystem.h"
#include "MoveWithVelocitySystem.h"

#define KEYCODE_UP 357
#define KEYCODE_DOWN 359
#define KEYCODE_LEFT 356
#define KEYCODE_RIGHT 358
#define KEYCODE_Z 122
#define KEYCODE_X 120



artemis::World _world;
artemis::EntitySystem *_renderSystem;

int inputBitMask(0);




//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
    ofSetWindowTitle("Glitch Jam 2014");
	ofSetFrameRate(60);



	artemis::SystemManager *sm = _world.getSystemManager();

	PlayerInputComponent *input = new PlayerInputComponent(&inputBitMask);
	CameraComponent *camera = new CameraComponent(1024, 768);
	//_world.getTagManager()->subscribe("camera", *camera);

	sm->setSystem(new MovePlayerSystem(*input), true);
	sm->setSystem(new MoveSineOffsetSystem(), true);
	sm->setSystem(new ShakeCameraSystem(*input), true);
	sm->setSystem(new RemoveEntitiesConditionSystem(), true);
	sm->setSystem(new MoveWithVelocitySystem(), true);

	_renderSystem = sm->setSystem(new RenderRectanglesSystem(*camera), false);

    artemis::EntityManager *em = _world.getEntityManager();

    artemis::Entity &sys = em->create();
    sys.addComponent(camera);
    sys.addComponent(input);
    sys.refresh();


	for (int i = 0; i < 500; i ++) {
		artemis::Entity &enemy = em->create();
		enemy.addComponent(new PositionComponent(ofRandom(0,1024), ofRandom(0,768)));
		enemy.addComponent(new RectangleComponent(0,0,10,10, 0xff0000));
		float startRad = ofRandom(0,3);
		float speed = ofRandom(0.01, 0.1);
		enemy.addComponent(new SineOffsetComponent(startRad, speed));

		enemy.refresh();
	}


    artemis::Entity &m_player = em->create();
    m_player.setTag("player");
    m_player.addComponent(new PositionComponent(50,50));
    m_player.addComponent(new RectangleComponent(0,0,40,60, 0x00ff00));
    m_player.addComponent(new VelocityComponent());
    m_player.addComponent(new InputControllableComponent());
    m_player.refresh();



	sm->initializeAll();

}

//--------------------------------------------------------------
void ofApp::update(){
_world.loopStart();
	_world.process();
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofSetColor(0, 255, 0);
	//ofRect(playerX, playerY, 10, 15);

	_renderSystem->process();
	ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == KEYCODE_UP) 		{		inputBitMask |= PlayerInputComponent::MOVE_UP;		}
	if (key == KEYCODE_DOWN) 	{		inputBitMask |= PlayerInputComponent::MOVE_DOWN;	}
	if (key == KEYCODE_LEFT) 	{		inputBitMask |= PlayerInputComponent::MOVE_LEFT;	}
	if (key == KEYCODE_RIGHT) 	{		inputBitMask |= PlayerInputComponent::MOVE_RIGHT;	}
	if (key == KEYCODE_Z) 		{		inputBitMask |= PlayerInputComponent::ATK_1;		}
	if (key == KEYCODE_X) 		{		inputBitMask |= PlayerInputComponent::ATK_2;		}

	//std::cout << "Key pressed " << key << std::endl;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == KEYCODE_UP) 		{		inputBitMask &= ~PlayerInputComponent::MOVE_UP;		}
	if (key == KEYCODE_DOWN) 	{		inputBitMask &= ~PlayerInputComponent::MOVE_DOWN;	}
	if (key == KEYCODE_LEFT) 	{		inputBitMask &= ~PlayerInputComponent::MOVE_LEFT;	}
	if (key == KEYCODE_RIGHT) 	{		inputBitMask &= ~PlayerInputComponent::MOVE_RIGHT;	}
	if (key == KEYCODE_Z) 		{		inputBitMask &= ~PlayerInputComponent::ATK_1;		}
	if (key == KEYCODE_X) 		{		inputBitMask &= ~PlayerInputComponent::ATK_2;		}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
