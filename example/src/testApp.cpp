#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255);
    ofSetFrameRate(60);
    
    ani1.setModeFromRight();
    ani2.setModeFromLeft();
    ani3.setModeAtOnce();
    
    // Please copy your font file to bin/data and change the filenames below.
    ani2.loadFont("Courier New.ttf", 32);
    ani3.loadFont("Courier New.ttf", 32);
    ani4.loadFont("Courier New.ttf", 32);
    
    ani2.setNDigits(5);
    
    ani3.setLetterSpacing(2.0);
    
    ani4.setPosition(500, 420);
    ani4.setAnimationTime(2000);
    ani4.setColor(ofColor(255, 0, 0));
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ani1.draw(500, 300);
    ani2.draw(500, 340);
    ani3.draw(500, 380);
    ani4.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    ani1.startAnimation(1452);
    ani2.startAnimation(231);
    ani3.startAnimation(750246);
    ani4.startAnimation(8033175);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}