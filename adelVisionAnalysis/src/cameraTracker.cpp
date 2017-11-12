
//  cameraTracker.cpp
//  ofxOSSIA
//
//  Created by Thomas Pachoud on 21/02/2017.
//
//

#include "cameraTracker.h"

void cameraTracker::setup(ossia::ParameterGroup _parent_node){
    
    positionTracker1.setup(_parent_node, "Position du tracker");
    
    _sizeParams.setup(positionTracker1, "sizeParams");
    //_radius.setup(_sizeParams,"radius",ofRandomf()*99+1,1.,100.);
    _position1.setup(_sizeParams,
                    "position",
                    ofVec2f(ofRandomWidth(), ofRandomHeight()),
                    ofVec2f(0., 0.), // Min
                    ofVec2f(ofGetWidth(), ofGetHeight())); // Max


    positionTracker2.setup(_parent_node, "Position du tracker");

    _sizeParams.setup(positionTracker2, "sizeParams");
    //_radius.setup(_sizeParams,"radius",ofRandomf()*99+1,1.,100.);
    _position2.setup(_sizeParams,
                    "position",
                    ofVec2f(ofRandomWidth(), ofRandomHeight()),
                    ofVec2f(0., 0.), // Min
                    ofVec2f(ofGetWidth(), ofGetHeight())); // Max

    //_fill.setup(_colorParams,"fill",false);

}

void cameraTracker::update(){
    
}

void cameraTracker::draw(){
//    if(!_fill)
//        ofNoFill();
//    else
//        ofFill();

//    ofSetColor(_color.get());
//    ofDrawCircle(_position.get(),_radius.get());
}

