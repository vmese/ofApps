#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "arbotixController.h"
#include "servo.h"
#include "ofxXmlSettings.h"

#include <ctime>

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "ofxKinect.h"
#include "ofxHeadPoseEstimator.h"

#include "ofxCv.h"
#include "ofxOpenCv.h"

using namespace std;
using namespace cv;

const int kNbOfServos = 5;

// kinect frame width
#define KW 480
// kinect frame height
#define KH 360
// for the average fps calculation
#define FPS_MEAN 30


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

        double diffclock(clock_t clock1, clock_t clock2);


        //Kinect head pose estimator
        void setupEstimator();
        void drawPointCloud();
        void drawPoses();
        void calcAvgFPS();
        void drawReport();
        void updateCloud();

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

        // vision
//        ofVideoGrabber movie;

        ofxCvColorImage rgb,hsb;
        ofxCvGrayscaleImage hue,sat,bri,filtered;
        ofxCvContourFinder contours;

//        ofVideoGrabber cam;
//        ofxCv::ObjectFinder faceTracker;

        int w,h, cas;
        int findHue;

        int lastObjectPositonX;
        int lastObjectPositonY;

        clock_t objectDetectionStartTime;

        boost::mutex fPosMutex;

        // kinect
        ofxKinect kinect;
        ofEasyCam easyCam;
        //Estimator parameters
        // Path to trees
        string g_treepath;
        // Number of trees
        int g_ntrees;
        // Patch width
        int g_p_width;
        // Patch height
        int g_p_height;
        //maximum distance form the sensor - used to segment the person
        int g_max_z;
        //head threshold - to classify a cluster of votes as a head
        int g_th;
        //threshold for the probability of a patch to belong to a head
        float g_prob_th;
        //threshold on the variance of the leaves
        float g_maxv;
        //stride (how densely to sample test patches - increase for higher speed)
        int g_stride;
        //radius used for clustering votes into possible heads
        float g_larger_radius_ratio;
        //radius used for mean shift
        float g_smaller_radius_ratio;
        //pointer to the actual estimator
        CRForestEstimator* g_Estimate;
        //input 3D image
        Mat g_im3D;
        // estimator trees properly loaded
        bool bTreesLoaded = false;
        //-------------------------------------------------------
        // I copied this code from the library demo code
        // this kind of nomenclature is unknown to me
        std::vector< cv::Vec<float,POSE_SIZE> > g_means; //outputs
        std::vector< std::vector< Vote > > g_clusters; //full clusters of votes
        std::vector< Vote > g_votes; //all votes returned by the forest

        //-------------------------------------------------------
        // kinect motor tilt angle
        int kTilt = 0;
        // stuff to calculate average fpg
        float kFPS = 0;
        float avgkFPS = 0;
        int frameCount = 0;
        int lastMillis = 0;
        // draw / hide poincloud
        bool bDrawCloud = true;

};
