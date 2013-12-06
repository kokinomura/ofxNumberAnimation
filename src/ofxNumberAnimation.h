#pragma once

#include "ofMain.h"

class ofxNumberAnimation {
public:
    ofxNumberAnimation();
    
    void draw();
    void draw(float x, float y);
    
    void setNDigits(int n);
    void startAnimation(int num);
    void hide();
    
    void setPosition(float x, float y);
    void setColor(ofColor color);
    void setAnimationTime(float timeMs);
    
    void setFont(string fontName);
    void setFontSize(int fontSize);
    void setFont(string fontName, int fontSize);
    void setLetterSpacing(float spacing);
    
    void setModeFromLeft();
    void setModeFromRight();
    void setModeAtOnce();
    
private:
    enum {
        fromLeft,
        fromRight,
        atOnce
    } mode;
    
    enum {
        before,
        animating,
        after
    } status;
    
    int _nDigits;
    int _number;
    ofColor _color;
    float _animationTimeMs;
    float _x, _y;
    
    ofTrueTypeFont font;
    string _fontName;
    int _fontSize;
    float _spacing;
    
    // for animation
    vector<string> numStrVec;
    string numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    vector<float> xPositions;
    float startTimeMs;
    float waitTimeMs;
    float waitTimePerDigitMs;
    
    void drawFromLeft(float animatingTimeMs);
    void drawFromRight(float animatingTimeMs);
    void drawAtOnce(float animatingTimeMs);
};
