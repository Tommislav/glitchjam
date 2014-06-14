#include "ofApp.h"
#include "World.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "PlayerInputComponent.h"

#define KEYCODE_UP 357
#define KEYCODE_DOWN 359
#define KEYCODE_LEFT 356 //357
#define KEYCODE_RIGHT 358 //359

float playerX = 0;
float playerY = 0;

// Use bitmask to determine which keys are being pressed and released
/*
int movementBitMask 	= 0;
const int MOVE_UP 		= 1 << 1;
const int MOVE_DOWN 	= 1 << 2;
const int MOVE_LEFT 	= 1 << 3;
const int MOVE_RIGHT 	= 1 << 4;
*/
artemis::World _world;
PositionComponent test = PositionComponent(0, 50);
PlayerInputComponent playerInput;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Glitch Jam 2014");
	ofSetFrameRate(60);

	artemis::SystemManager *sm = _world.getSystemManager();
    //MovementSystem * movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());
    artemis::EntityManager *em = _world.getEntityManager();

    artemis::Entity &player = em->create();
    player.addComponent(new PositionComponent(1,2));
    player.refresh();


	PositionComponent *comp = (PositionComponent*)player.getComponent<PositionComponent>();
	comp->posX = 3;
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
	ofSetColor(0, 255, 0);
	ofRect(playerX, playerY, 10, 15);

	test.drawSomething();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == KEYCODE_UP) {		playerInput.movementBitMask |= PlayerInputComponent::MOVE_UP;		}
	if (key == KEYCODE_DOWN) {		playerInput.movementBitMask |= PlayerInputComponent::MOVE_DOWN;	}
	if (key == KEYCODE_LEFT) {		playerInput.movementBitMask |= PlayerInputComponent::MOVE_LEFT;	}
	if (key == KEYCODE_RIGHT) {		playerInput.movementBitMask |= PlayerInputComponent::MOVE_RIGHT;	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == KEYCODE_UP) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_UP;	}
	if (key == KEYCODE_DOWN) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_DOWN;	}
	if (key == KEYCODE_LEFT) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_LEFT;	}
	if (key == KEYCODE_RIGHT) {		playerInput.movementBitMask &= ~PlayerInputComponent::MOVE_RIGHT;	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
