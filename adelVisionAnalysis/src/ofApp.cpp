#include "ofApp.h"


using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){

        ofBackground(0,0,0);
        ofSetFrameRate(60);
        ofSetVerticalSync(true);

        // setup ofxOssia, by default it uses oscquery protocol on ports 3456 and 5678
        //ossia.setup();
        ossia.setup("OSCQuery", "ofxOssiaDevice", 6000, 9000);
        // pass a parent node to InteractiveCircle::setup() method, thus you can build hierarchy
        paramControl.setup(ossia.get_root_node(),"Control");
        x.setup(paramControl,"x",(50,0,100));
        y.setup(paramControl,"y",(50,0,100));

        w = 640;
        h = 480;

        movie.initGrabber(w, h, true);

        //reserve memory for cv images
        rgb.allocate(w, h);
        hsb.allocate(w, h);
        hue.allocate(w, h);
        sat.allocate(w, h);
        bri.allocate(w, h);
        filtered.allocate(w, h);

        tracker.setup();
        tracker.setRescale(.5);

        cas = 1;
    }

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();

    if( cas == 1){

        if (movie.isFrameNew()) {

            //copy webcam pixels to rgb image
            rgb.setFromPixels(movie.getPixels()); //, w, h,1);

            //mirror horizontal
            //rgb.mirror(false, true);

            //duplicate rgb
            hsb = rgb;

            //convert to hsb
            hsb.convertRgbToHsv();

            //store the three channels as grayscale images
            hsb.convertToGrayscalePlanarImages(hue, sat, bri);

            //filter image based on the hue value were looking for
            for (int i=0; i<w*h; i++) {
                filtered.getPixels()[i] = ofInRange(hue.getPixels()[i],findHue-8,findHue+8) ? 255 : 0;
            }

            filtered.flagImageChanged();
            //run the contour finder on the filtered image to find blobs with a certain hue
            contours.findContours(filtered, 50, w*h/2, 1, false);
        }
    }

    if( cas == 2){

        if(movie.isFrameNew()) {
                if(tracker.update(toCv(movie))) {
                        classifier.classify(tracker);
                }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);

    if( cas == 1){

        //draw all cv images
        rgb.draw(0,0); // Seul cette image m'interesse
        //hsb.draw(640,0);
        //hue.draw(0,240);
        //sat.draw(320,240);
        //bri.draw(640,240);
        //filtered.draw(0,240);   // Celle ci et la suivante sont interessante mais
        //contours.draw(0,240);   // Pas la place de la mettre pour avoir un bon rendu

        ofSetColor(255, 0, 0);
        ofFill();

        //draw red circles for found blobs
        for (int i=0; i<contours.nBlobs; i++) {
            ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 20);
            ofPoint pos = contours.blobs[i].centroid;
            float xcm = pos.x/37.795275590551;
            float ycm = pos.y/37.795275590551;

//            printf("----------PIXELS-------------------- \n");
//            printf("x = %f\n",pos.x);
//            printf("y = %f\n",pos.y);

//            printf("----------CENTIMETRE---------------- \n");
//            printf("x = %f\n",xcm);
//            printf("y = %f\n",ycm);
            //printf("z= %f\n",pos.z);


            //int val = rand() %100 -1 ;
            x.set(xcm*64);
            y.set(ycm*64);


            //1cm = 37.795275590551 pixel
        }
    }

    if( cas == 2){

        ofSetColor(255);
        movie.draw(0, 0);
        tracker.draw();

        bool headFound = tracker.getFound();

        if (headFound)
        {
            ofVec2f position = tracker.getPosition();
            float xcm2 = position.x/37.795275590551;
            float ycm2 = position.y/37.795275590551;

    //        printf("----------PIXELS--------------------\n");
    //        printf("x = %f\n",position.x);
    //        printf("y = %f\n",position.y);

    //        printf("----------CENTIMETRE----------------\n");
    //        printf("x = %f\n",xcm2);
    //        printf("y = %f\n",ycm2);



            x.set(xcm2*64);
            y.set(ycm2*64);
        }



        int w = 100, h = 12;
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(5, 10);
        int n = classifier.size();
        int primary = classifier.getPrimaryExpression();
    for(int i = 0; i < n; i++){
                ofSetColor(i == primary ? ofColor::red : ofColor::black);
                ofDrawRectangle(0, 0, w * classifier.getProbability(i) + .5, h);
                ofSetColor(255);
                ofDrawBitmapString(classifier.getDescription(i), 5, 9);
                ofTranslate(0, h + 5);
    }
        ofPopMatrix();
        ofPopStyle();

        ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
        ofDrawBitmapStringHighlight(
                string() +
                "r - reset\n" +
                "e - add expression\n" +
                "a - add sample\n" +
                "s - save expressions\n"
                "l - load expressions",
                14, ofGetHeight() - 7 * 12);

    }
    ofDrawBitmapStringHighlight(
            string() +
            "1 - suivi object\n" +
            "2 - suivi visage\n",
            ofGetWidth()-200, 14);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == '1'){
        cas = 1;
        printf("cas= %i\n",cas);
    }
    if (key == '2'){
        cas = 2;
        printf("cas= %i\n",cas);
    }

    //Cas 1 = tracking couleur, taper sur la touche 1
    if (cas == 1){
        if (key == 'r') {   //Tracking red
        findHue = 170;
        }
        if(key == 'b') {    //Tracking blue
        findHue = 100;
        }
        if(key == 'g') {    //Tracking green
            findHue = 60;
        }
        if(key == 'o') {    //Tracking orange
            findHue = 10;
        }
        if(key == 'y') {    //Tracking yellow
            findHue = 30;
        }
    }

    //Cas 2 = tracking expression; taper sur la touche 2
    if (cas == 2){

        if(key == 'r') {
                tracker.reset();
                classifier.reset();
        }
        if(key == 'e') {
                classifier.addExpression();
        }
        if(key == 'a') {
                classifier.addSample(tracker);
        }
        if(key == 's') {
                classifier.save("expressions");
        }
        if(key == 'l') {
                classifier.load("expressions");
        }

    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
