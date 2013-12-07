#include "ofxNumberAnimation.h"

//--------------------------------------------------------------
ofxNumberAnimation::ofxNumberAnimation() {
    status = before;
    mode = fromRight;
    
    _x = 0;
    _y = 0;
    
    _nDigits = -1;
    _color = ofColor(0);
    
    isFontSpecified = false;
    _fontSize = 10;
    _spacing = 1.0;
    
    _animationTimeMs = 1000;
}

//--------------------------------------------------------------
void ofxNumberAnimation::draw() {
    if (status == before) {
        return;
    } else if (status == after) {
        ofPushStyle();
        ofSetColor(_color);
        for (int i=0; i<_nDigits; i++) {
            drawString(numStrVec[i], xOffsets[i]+_x, _y);
        }
        ofPopStyle();
        return;
    }
    
    ofPushStyle();
    ofSetColor(_color);
    
    float animatingTimeMs = ofGetElapsedTimeMillis() - startTimeMs;
    if (animatingTimeMs > _animationTimeMs) {
        status = after;
        return;
    } else {
        switch (mode) {
            case fromLeft:
                drawFromLeft(animatingTimeMs);
                break;
            case fromRight:
                drawFromRight(animatingTimeMs);
                break;
            case atOnce:
                drawAtOnce(animatingTimeMs);
                break;
            default:
                break;
        }
    }    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxNumberAnimation::draw(float x, float y) {
    setPosition(x, y);
    draw();
}

//--------------------------------------------------------------
void ofxNumberAnimation::setNDigits(int n) {
    _nDigits = n;
}

//--------------------------------------------------------------
void ofxNumberAnimation::startAnimation(int num) {
    // Change number to string
    string numStr = ofToString(num);

    cout << numStr << endl;
    
    if (_nDigits == -1) {
        _nDigits = numStr.size();
    } else if (_nDigits < numStr.size()) {
        cout << "more digits than nDigits." << endl;
        return;
    }

    int nZeros = _nDigits - numStr.size();
    numStrVec.clear();
    for (int i=0; i<_nDigits; i++) {
        if (i < nZeros) {
            numStrVec.push_back("0");
        } else {
            numStrVec.push_back(ofToString(numStr[i-nZeros]));
        }
    }

    //-----------
    // Calculate a position of each number
    int x = 0;
    xOffsets.clear();
    for (int i=0; i<numStrVec.size(); i++) {
        xOffsets.push_back(x);
        x += stringWidth(numStrVec[i]) + _fontSize * 0.2 * _spacing;
    }
    //-----------

    // show random numbers for waitTime ms, then show the target numbers
    // for waitTimePerDigit ms for each number.
    waitTimeMs = _animationTimeMs * 0.5;
    waitTimePerDigitMs = (_animationTimeMs - waitTimeMs) / _nDigits;

    startTimeMs = ofGetElapsedTimeMillis();

    status = animating;
}

//--------------------------------------------------------------
void ofxNumberAnimation::setPosition(float x, float y) {
    _x = x;
    _y = y;
}

//--------------------------------------------------------------
void ofxNumberAnimation::loadFont(string fontName, int fontSize) {
    isFontSpecified = true;
    _fontName = fontName;
    _fontSize = fontSize;
    font.loadFont(_fontName, _fontSize);
}

//--------------------------------------------------------------
void ofxNumberAnimation::setLetterSpacing(float spacing) {
    _spacing = spacing;
}

void ofxNumberAnimation::setColor(ofColor color) {
    _color = color;
}

//--------------------------------------------------------------
void ofxNumberAnimation::setAnimationTime(float animationTimeMs) {
    _animationTimeMs = animationTimeMs;
}

//--------------------------------------------------------------
void ofxNumberAnimation::setModeFromLeft() {
    mode = fromLeft;
}

//--------------------------------------------------------------
void ofxNumberAnimation::setModeFromRight() {
    mode = fromRight;
}

//--------------------------------------------------------------
void ofxNumberAnimation::setModeAtOnce() {
    mode = atOnce;
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawFromLeft(float animatingTimeMs) {
    // draw the correct numbers
    int n = (animatingTimeMs - waitTimeMs) / waitTimePerDigitMs;
    n = ofClamp(n, 0, _nDigits);
    for (int i=0; i<n; i++) {
        drawString(numStrVec[i], xOffsets[i]+_x, _y);
    }
    
    // draw random numbers
    for (int i=n; i<_nDigits; i++) {
        int num = ofRandom(10);
        drawString(numbers[num], xOffsets[i]+_x, _y);
    }
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawFromRight(float animatingTimeMs) {
    // draw the correct numbers
    int n = (animatingTimeMs - waitTimeMs) / waitTimePerDigitMs;
    n = ofClamp(n, 0, _nDigits);
    for (int i=_nDigits-1; i>=_nDigits-n; i--) {
        drawString(numStrVec[i], xOffsets[i]+_x, _y);
    }
    
    // draw random numbers
    for (int i=_nDigits-n-1; i>=0; i--) {
        int num = ofRandom(10);
        drawString(numbers[num], xOffsets[i]+_x, _y);
    }
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawAtOnce(float animatingTimeMs) {
    if (animatingTimeMs < _animationTimeMs) {
        // draw random numbers
        for (int i=0; i<_nDigits; i++) {
            int num = ofRandom(10);
            drawString(numbers[num], xOffsets[i]+_x, _y);
        }
    } else {
        // draw the correct numbers
        for (int i=0; i<_nDigits; i++) {
            drawString(numStrVec[i], xOffsets[i]+_x, _y);
        }
    }
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawString(string str, float x, float y) {
    if (!isFontSpecified) {
        ofDrawBitmapString(str, x, y);
    } else {
        font.drawString(str, x, y);
    }
}

//--------------------------------------------------------------
float ofxNumberAnimation::stringWidth(string str) {
    if (!isFontSpecified) {
        float fontSize = 8.0;
        return fontSize * 0.75;
    } else {
        return font.stringWidth(str);
    }
}