#include "ofxNumberAnimation.h"

//--------------------------------------------------------------
ofxNumberAnimation::ofxNumberAnimation() {
    status = before;
    mode = fromRight;
    
    _nDigits = -1;
    _color = ofColor(0);
    
    _fontName = "Courier New.ttf";
    _fontSize = 10;
    font.loadFont(_fontName, _fontSize);
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
            font.drawString(numStrVec[i], xPositions[i], _y);
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

    if (_nDigits == -1) {
        _nDigits = numStr.size();
    } else if (_nDigits < numStr.size()) {
        cout << "more digits than nDigits." << endl;
        return;
    }

    int nZeros = _nDigits - numStr.size();
    for (int i=0; i<_nDigits; i++) {
        if (i < nZeros) {
            numStrVec.push_back("0");
        } else {
            numStrVec.push_back(ofToString(numStr[i-nZeros]));
        }
    }
    //-----------

    // Calculate a position of each number
    int x = _x;
    for (int i=0; i<numStrVec.size(); i++) {
        xPositions.push_back(x);
        x += font.stringWidth(numStrVec[i]) + _fontSize*0.2*_spacing;
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
void ofxNumberAnimation::setFont(string fontName) {
    _fontName = fontName;
    font.loadFont(_fontName, _fontSize);
}

//--------------------------------------------------------------
void ofxNumberAnimation::setFontSize(int fontSize) {
    _fontSize = fontSize;
    font.loadFont(_fontName, _fontSize);
}

//--------------------------------------------------------------
void ofxNumberAnimation::setFont(string fontName, int fontSize) {
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
        font.drawString(numStrVec[i], xPositions[i], _y);
    }
    
    // draw random numbers
    for (int i=n; i<_nDigits; i++) {
        int num = ofRandom(10);
        font.drawString(numbers[num], xPositions[i], _y);
    }
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawFromRight(float animatingTimeMs) {
    // draw the correct numbers
    int n = (animatingTimeMs - waitTimeMs) / waitTimePerDigitMs;
    n = ofClamp(n, 0, _nDigits);
    for (int i=_nDigits-1; i>=_nDigits-n; i--) {
        font.drawString(numStrVec[i], xPositions[i], _y);
    }
    
    // draw random numbers
    for (int i=_nDigits-n-1; i>=0; i--) {
        int num = ofRandom(10);
        font.drawString(numbers[num], xPositions[i], _y);
    }
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawAtOnce(float animatingTimeMs) {
    if (animatingTimeMs < _animationTimeMs) {
        // draw random numbers
        for (int i=0; i<_nDigits; i++) {
            int num = ofRandom(10);
            font.drawString(numbers[num], xPositions[i], _y);
        }
    } else {
        // draw the correct numbers
        for (int i=0; i<_nDigits; i++) {
            font.drawString(numStrVec[i], xPositions[i], _y);
        }
    }
}
