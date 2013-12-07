#include "ofxNumberAnimation.h"

//--------------------------------------------------------------
ofxNumberAnimation::ofxNumberAnimation() {
    status = before;
    mode = fromRight;
    
    _x = 0;
    _y = 0;
    
    _isNDigitsSet = false;
    _color = ofColor(0);
    _thousandsSeparator = false;
    
    isFontSpecified = false;
    _fontSize = 10;
    _spacing = 1.0;
    
    _animationTimeMs = 1000;
    
    separator = ",";
}

//--------------------------------------------------------------
void ofxNumberAnimation::draw() {
    if (status == before) {
        return;
    } else if (status == after) {
        drawAll();
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
    _isNDigitsSet = true;
    _nDigits = n;
}

//--------------------------------------------------------------
void ofxNumberAnimation::startAnimation(int num) {
    // Change number to string
    string numStr = ofToString(num);

    if (!_isNDigitsSet) {
        _nDigits = numStr.size();
    } else if (_nDigits < numStr.size()) {
        cout << "more digits than nDigits." << endl;
        return;
    }

    // insert zeros
    int nZeros = _nDigits - numStr.size();
    for (int i=0; i<nZeros; i++) {
        numStr.insert(numStr.begin(), '0');
    }
    
    _numModulo3 = _nDigits % 3;
    numStrVec.clear();
    if (_thousandsSeparator) {
        for (int i=0; i<_nDigits; i++) {
            if (i%3 == _numModulo3 && i!= 0) {
                numStrVec.push_back(separator);
            }
            numStrVec.push_back(ofToString(numStr[i]));
        }
    } else {
        for (int i=0; i<_nDigits; i++) {
            numStrVec.push_back(ofToString(numStr[i]));
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
void ofxNumberAnimation::addThousandsSeparator(bool b) {
    _thousandsSeparator = b;
}

//--------------------------------------------------------------
void ofxNumberAnimation::setThousandsSeparatorComma() {
    separator = ",";
}

//--------------------------------------------------------------
void ofxNumberAnimation::setThousandsSeparatorPeriod() {
    separator = ".";
}

//--------------------------------------------------------------
void ofxNumberAnimation::setThousandsSeparatorSpace() {
    separator = " ";
}
//--------------------------------------------------------------
//-private methods----------------------------------------------
//--------------------------------------------------------------
void ofxNumberAnimation::drawFromLeft(float animatingTimeMs) {
    ofPushStyle();
    ofSetColor(_color);
    // draw the correct numbers
    int nCorrect = (animatingTimeMs - waitTimeMs) / waitTimePerDigitMs;
    nCorrect = ofClamp(nCorrect, 0, _nDigits);
    
    int index = -1;
    for (int i=0, n=0; n<nCorrect; i++) {
        string s = numStrVec[i];
        drawString(s, xOffsets[i]+_x, _y);
        if (s != separator) {
            n++;
        }
        index = i;
    }
    
    // draw random numbers
    for (int i=index+1; i<numStrVec.size(); i++) {
        string s;
        if (numStrVec[i] == separator) {
            s = separator;
        } else {
            int num = ofRandom(10);
            s = numbers[num];
        }
        drawString(s, xOffsets[i]+_x, _y);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawFromRight(float animatingTimeMs) {
    ofPushStyle();
    ofSetColor(_color);
    // draw the correct numbers
    int nCorrect = (animatingTimeMs - waitTimeMs) / waitTimePerDigitMs;
    nCorrect = ofClamp(nCorrect, 0, _nDigits);
    
    int index = numStrVec.size();
    for (int i=numStrVec.size()-1, n=_nDigits-1; n>=_nDigits-nCorrect; i--) {
        string s = numStrVec[i];
        drawString(s, xOffsets[i]+_x, _y);
        if (s != separator) {
            n--;
        }
        index = i;
    }
    
    // draw random numbers
    for (int i=index-1; i>=0; i--) {
        string s;
        if (numStrVec[i] == separator) {
            s = separator;
        } else {
            int num = ofRandom(10);
            s = numbers[num];
        }
        drawString(s, xOffsets[i]+_x, _y);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawAtOnce(float animatingTimeMs) {
    ofPushStyle();
    ofSetColor(_color);
    if (animatingTimeMs < _animationTimeMs) {
        // draw random numbers
        for (int i=0; i<numStrVec.size(); i++) {
            string s;
            if (numStrVec[i] == separator) {
                s = separator;
            } else {
                int num = ofRandom(10);
                s = numbers[num];
            }
            drawString(s, xOffsets[i]+_x, _y);
        }
    } else {
        // draw the correct numbers
        for (int i=0; i<numStrVec.size(); i++) {
            drawString(numStrVec[i], xOffsets[i]+_x, _y);
        }
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxNumberAnimation::drawAll() {
    ofPushStyle();
    ofSetColor(_color);
    for (int i=0; i<numStrVec.size(); i++) {
        drawString(numStrVec[i], xOffsets[i]+_x, _y);
    }
    ofPopStyle();
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
        return str != separator ? font.stringWidth(str) : font.stringWidth(str) * 2.0;
    }
}