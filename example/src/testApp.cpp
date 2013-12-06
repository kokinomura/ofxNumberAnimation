#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255);
    ofSetFrameRate(60);
    
    ani1.setNDigits(4);
    ani2.setNDigits(5);
    ani3.setNDigits(6);
    
    ani1.setModeFromRight();
    ani2.setModeFromLeft();
    ani3.setModeAtOnce();
    
    ani1.setFontSize(32);
    ani2.setFontSize(32);
    ani3.setFontSize(32);
    
    ani4.setPosition(500, 400);
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
    ani2.startAnimation(62931);
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