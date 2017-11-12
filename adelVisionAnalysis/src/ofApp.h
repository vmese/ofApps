#pragma once

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFaceTracker.h"
#include "ofxOssia.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

        public:
                void setup();
                void update();
                void draw();

                void keyPressed(int key);
                void keyReleased(int key);
                void mouseMoved(int x, int y );
                void mouseDragged(int x, int y, int button);
                void mousePressed(int x, int y, int button);
                void mouseReleased(int x, int y, int button);
                void mouseEntered(int x, int y);
                void mouseExited(int x, int y);
                void windowResized(int w, int h);
                void dragEvent(ofDragInfo dragInfo);
                void gotMessage(ofMessage msg);

                ofVideoGrabber movie;

                ofxCvColorImage rgb,hsb;
                ofxCvGrayscaleImage hue,sat,bri,filtered;
                ofxCvContourFinder contours;

                ofVideoGrabber cam;
                ofxFaceTracker tracker;
                ExpressionClassifier classifier;

                int w,h, cas;
                int findHue;

        private:

                ofxOssia ossia;

                ossia::Parameter <int> x;
                ossia::Parameter <int> y;
                ossia::ParameterGroup paramControl;


};

#endif
