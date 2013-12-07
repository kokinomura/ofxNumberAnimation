ofxNumberAnimation
======================
ofxNumberAnimation is an addon to add an animation of numbers. First it shows random  
numbers at high speed, then reveals each digit from right to left (or left to right) with  
certain delay time. This is useful to show numbers such as score or price dramatically.  

Current version is based on version 0.8.0.

Usage
--------------------------------------------

* testApp.h

        class testApp : public ofBaseApp{

            /* definitions */

            ofxNumberAnimation ani;
        };

* testApp.cpp

        void testApp::draw(){
            ani.draw(400, 400);
        }

        void testApp::keyPressed(int key){
            ani.startAnimation(1452);  // It starts the animation.
        }

Methods (Required)
--------------------------------------------
###void draw(float x, float y)###
Specifies a position you will draw.
###void draw()###
If you set position to draw by setPosition(), you can simply call draw().  
Calling setPosition(x, y) and draw() does exactly same as draw(x, y).
###void startAnimation(int num)###
The argument is a number you want to draw.

    
Methods (Optional)
--------------------------------------------
###void hide()###
###void setNDigits(int n)###
You can set the number of digits. When you draw a number which has less digits, zeros are  
filled automatically.  

###void setPosition(float x, float y)###
###void setColor(ofColor color)###
###void setAnimationTime(float timeMs)###
    
###void loadFont(string fontName, int fontSize)###
###void setLetterSpacing(float spacing)###
By default, spacing is 1.0.  
When you set spacing = 2.0, spaces between numbers will be two times wider.

###void setModeFromRight()###
This is set by default.  
After it draws an animation of random numbers, it shows the numbers    
from right digit to left.
###void setModeFromLeft()###
Same as setModeFromRight, but from left to right.
###void setModeAtOnce()###
After a random animation, it shows all numbers at once.

###void addThousandsSeparator(bool b)###
You can choose whether you draw thousands separators or not.  
e.g. 1234567 -> 1,234,567
###void setThousandsSeparatorComma()###
###void setThousandsSeparatorPeriod()###
###void setThousandsSeparatorSpace()###
For various locales, you can choose comma, period or space as thousands separator.
1,234,567   1.234.567   1 234 567

Default Values
--------------------------------------------
Letter spacing: 1.0  
  
Color: ofColor(0)  
Animation time: 1000 ms (1 sec)  
  
Mode: fromRight  
Position: ofVec2f(0, 0)  


License
-------------------------------------------
ofxNumberAnimation is distributed under the MIT License. This gives everyone the freedoms 
to use ofxNumberAnimation in any context: commercial or non-commercial, public or private, 
open or closed source.

Please see License.txt for details.

