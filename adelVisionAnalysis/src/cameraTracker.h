//
//  cameraTracker.h
//  ofxOSSIA
//
//  Created by Thomas Pachoud on 21/02/2017.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOssia.h"

class cameraTracker {
    
public :
    
//    ~cameraTracker(){
//        _colorParams.clearChild();
//        _sizeParams.clearChild();
//        _circleParams.clearChild();
//    }
    
    void setup(ossia::ParameterGroup _parent_node);
    void update();
    void draw();
    
    //inline ossia::ParameterGroup & getCircleParams() {
    //    return _circleParams;
    //}
    ossia::Parameter<ofVec2f> _position1;
    ossia::Parameter<ofVec2f> _position2;

private:


  //  ossia::Parameter<ofVec2f> _radius;

    ossia::ParameterGroup _sizeParams;
    ossia::ParameterGroup positionTracker1;
    ossia::ParameterGroup positionTracker2;
};

