#include <iostream>

#include "ofApp.h"
#include "ofMath.h"
#include "World.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "PositionComponent.h"
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
#include "ofSoundPlayer.h"
#include "SpawnBulletsSystem.h"
#include "FireBulletComponent.h"

// ARROW KEYS
#define KEYCODE_UP 357
#define KEYCODE_DOWN 359
#define KEYCODE_LEFT 356
#define KEYCODE_RIGHT 358

// WASD
#define KEYCODE_ATK_UP 119
#define KEYCODE_ATK_DOWN 115
#define KEYCODE_ATK_LEFT 97
#define KEYCODE_ATK_RIGHT 100

// space
#define KEYCODE_ATK_RESET 32



#define KEYCODE_Z 122
#define KEYCODE_X 120



artemis::World _world;
artemis::EntitySystem *_renderSystem = NULL;



int inputBitMask(0);




//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
    ofSetWindowTitle("Glitch Jam 2014");
	ofSetFrameRate(60);


	bgMusic.loadSound("pulseboy_demo.wav");
	bgMusic.play();


	artemis::SystemManager *sm = _world.getSystemManager();

	CameraComponent *camera = new CameraComponent(1024, 768);
	//_world.getTagManager()->subscribe("camera", *camera);

	sm->setSystem(new MovePlayerSystem(), true);
	sm->setSystem(new MoveSineOffsetSystem(), true);
	sm->setSystem(new ShakeCameraSystem(), true);
	sm->setSystem(new RemoveEntitiesConditionSystem(), true);
	sm->setSystem(new MoveWithVelocitySystem(), true);
	sm->setSystem(new SpawnBulletSystem(), true);

	_renderSystem = sm->setSystem(new RenderRectanglesSystem(*camera), false);

    artemis::EntityManager *em = _world.getEntityManager();

    artemis::Entity &sys = em->create();
    sys.addComponent(camera);
    sys.refresh();


	for (int i = 0; i < 500; i ++) {
		artemis::Entity &enemy = em->create();
		enemy.addComponent(new PositionComponent(ofRandom(0,1024), ofRandom(0,768)));
		enemy.addComponent(new RectangleComponent(0,0,10,10, 0x333333, 0));
		float startRad = ofRandom(0,3);
		float speed = ofRandom(0.01, 0.1);
		enemy.addComponent(new SineOffsetComponent(startRad, speed));

		enemy.refresh();
	}


    artemis::Entity &m_player = em->create();
    m_player.setTag("player");
    m_player.addComponent(new PositionComponent(50,50));
    m_player.addComponent(new RectangleComponent(0,0,30,30, 0x00ff00, 0));
    m_player.addComponent(new VelocityComponent());
    m_player.addComponent(new InputControllableComponent());
    m_player.addComponent(new FireBulletComponent(10, true));
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
void ofApp::keyPressed(int key){}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}

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
