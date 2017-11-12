#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "arbotixController.h"
#include "servo.h"
#include "ofxXmlSettings.h"

#include <boost/shared_ptr.hpp>

const int kNbOfServos = 5;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();
        void standUp();
        void goToRest();

        void setupArduino(const int & version);
        void loadArbotixConfiguration(const std::string &fileName);
        void loadArduinoConfiguration(const std::string &fileName);
        void enableMotors(bool state);

        void turnOnLed(const int &pinNb);

        arbotixController *arbotix;
        ofArduino ard;
        ofxPanel _gui;

        // Ossia Params
        ofxOssia fOssia;
        ossia::ParameterGroup fOssiaAngleControl1;
        ossia::ParameterGroup fOssiaAngleControl2;
        ossia::ParameterGroup fOssiaAngleControl3;
        ossia::ParameterGroup fOssiaAngleControl4;
        ossia::ParameterGroup fOssiaAngleControl5;

        ossia::ParameterGroup fOssiaHeadPositionControl;

        ossia::Parameter <float> fOssiaAngleServo1;
        ossia::Parameter <float> fOssiaAngleServo2;
        ossia::Parameter <float> fOssiaAngleServo3;
        ossia::Parameter <float> fOssiaAngleServo4;
        ossia::Parameter <float> fOssiaAngleServo5;

        ossia::Parameter <int> fOssiaHeadPositionX;
        ossia::Parameter <int> fOssiaHeadPositionY;

        ofxXmlSettings fXMLReader;
        std::vector<std::string> fServosNames;
        std::vector<int> fServosPins;
        std::vector<int> fServosIds;
        std::vector<int> fServosMins;
        std::vector<int> fServosMax;
        std::vector<int> fServosInitialPos;

        std::string fArbotixPortName;
        int fArbotixRate;

        std::string fArduinoPortName;
        int fArduinoRate;

        float fmeanHeadPositionX;
        float fmeanHeadPositionY;

        float fInitialPosServo1;
        float fInitialPosServo2;
        float fInitialPosServo3;
        float fInitialPosServo4;
        float fInitialPosServo5;

        bool fMotorsEnabled;

        bool fTrackHead;

        //vector<boost::shared_ptr<servo> > fServosList;

        servo servo1;
        servo servo2;
        servo servo3;
        servo servo4;
        servo servo5;

        int fServo1Temp;
        int fServo2Temp;
        int fServo3Temp;
        int fServo4Temp;
        int fServo5Temp;

        std::vector <servo*> fServosList;

        ofPoint fCircleButton;
        bool fbCircleButtonClicked;
        int fCircleButtonRadius;

        ofTrueTypeFont	verdana14Font;

};
