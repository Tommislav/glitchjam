#include "ofApp.h"
#include "ofMath.h"
#include "World.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "PlayerInputComponent.h"
#include "RectangleComponent.h"
#include "RenderRectanglesSystem.h"
#include "Artemis/EntityProcessingSystem.h"

#define KEYCODE_UP 357
#define KEYCODE_DOWN 359
#define KEYCODE_LEFT 356
#define KEYCODE_RIGHT 358

float playerX = 0;
float playerY = 0;

artemis::World _world;
PlayerInputComponent playerInput;
artemis::EntitySystem *_renderSystem;




//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Glitch Jam 2014");
	ofSetFrameRate(60);

	artemis::SystemManager *sm = _world.getSystemManager();
	_renderSystem = sm->setSystem(new RenderRectanglesSystem());
    //MovementSystem * movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());

    artemis::EntityManager *em = _world.getEntityManager();

	for (int i = 0; i < 1000; i ++) {
		artemis::Entity &enemy = em->create();
		enemy.addComponent(new PositionComponent(ofRandom(0,1024), ofRandom(0,768)));
		enemy.addComponent(new RectangleComponent(0,0,10,10, 0xff0000));
		enemy.refresh();
	}


    artemis::Entity &m_player = em->create();
    m_player.addComponent(new PositionComponent(50,50));
    m_player.addComponent(new RectangleComponent(0,0,10,15, 0x00ff00));
    m_player.refresh();



	PositionComponent *comp = (PositionComponent*)m_player.getComponent<PositionComponent>();
	comp->posX = 30;

	sm->initializeAll();
	_world.loopStart();
}

//--------------------------------------------------------------
void ofApp::update(){

	if (playerInput.left()) {
		playerX -= 1;
	}
	if (playerInput.right()) {
		playerX += 1;
	}

	if (playerInput.up()) {
		playerY -= 1;
	}
	if (playerInput.down()) {
		playerY += 1;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofSetColor(0, 255, 0);
	//ofRect(playerX, playerY, 10, 15);

	_renderSystem->process();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == KEYCODE_UP) 		{		playerInput.movementBitMask |= PlayerInputComponent::MOVE_UP;		}
	if (key == KEYCODE_DOWN) 	{		playerInput.movementBitMask |= PlayerInputComponent::MOVE_DOWN;		}
	if (key == KEYCODE_LEFT) 	{		playerInput.movementBitMask |= PlayerInputComponent::MOVE_LEFT;		}
	if (key == KEYCODE_RIGHT) 	{		playerInput.movementBitMask |= PlayerInputComponent::MOVE_RIGHT;	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == KEYCODE_UP) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_UP;	}
	if (key == KEYCODE_DOWN) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_DOWN;	}
	if (key == KEYCODE_LEFT) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_LEFT;	}
	if (key == KEYCODE_RIGHT) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_RIGHT;	}
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
