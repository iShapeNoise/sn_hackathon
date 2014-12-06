#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
   
    
	ofBackground(255,255,255);	
	ofSetFrameRate(60);
	
	nCurveVertices = 7;
	
	curveVertices[0].x = 326;
	curveVertices[0].y = 209;
	curveVertices[1].x = 306;
	curveVertices[1].y = 279;
	curveVertices[2].x = 265;
	curveVertices[2].y = 331;
	curveVertices[3].x = 304;
	curveVertices[3].y = 383;
	curveVertices[4].x = 374;
	curveVertices[4].y = 383;
	curveVertices[5].x = 418;
	curveVertices[5].y = 309;
	curveVertices[6].x = 345;
	curveVertices[6].y = 279;
	
	for (int i = 0; i < nCurveVertices; i++){
		curveVertices[i].bOver 			= false;
		curveVertices[i].bBeingDragged 	= false;
		curveVertices[i].radius = 4;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    ofSetColor(255);
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
		ofVertex(400,135);
		ofVertex(215,135);
		ofVertex(365,25);
		ofVertex(305,200);
		ofVertex(250,25);
	ofEndShape();
	//-------------------------------------
	
	
	//------(c)--------------------------------------
	// 
	// 		draw a star dynamically
	//
	// 		use the mouse position as a pct
	//		to calc nPoints and internal point radius
	//
	float xPct = (float)(mouseX) / (float)(ofGetWidth());
	float yPct = (float)(mouseY) / (float)(ofGetHeight());
	int nTips = 5 + xPct * 60;
	int nStarPts = nTips * 2;
	float angleChangePerPt = TWO_PI / (float)nStarPts;
	float innerRadius = 0 + yPct*80;
	float outerRadius = 80;
	float origx = 525;
	float origy = 100;
	float angle = 0;
	
	ofSetHexColor(0xa16bca);
	ofBeginShape();
    
	for (int i = 0; i < nStarPts; i++){
		if (i % 2 == 0) {
			// inside point:
			float x = origx + innerRadius * cos(angle);
			float y = origy + innerRadius * sin(angle);
			ofVertex(x,y);
		} else {
			// outside point
			float x = origx + outerRadius * cos(angle);
			float y = origy + outerRadius * sin(angle);
			ofVertex(x,y);
		}
		angle += angleChangePerPt;
	}
	ofEndShape();
	//-------------------------------------

    
	
//	//------(f)--------------------------------------
//	// 
//	// 		ofCurveVertex
//	// 
//	// 		because it uses catmul rom splines, we need to repeat the first and last 
//	// 		items so the curve actually goes through those points
//	//
//
//	ofSetHexColor(0x2bdbe6);
//	ofBeginShape();
//	
//		for (int i = 0; i < nCurveVertices; i++){
//			
//			
//			// sorry about all the if/states here, but to do catmull rom curves
//			// we need to duplicate the start and end points so the curve acutally 
//			// goes through them.
//			
//			// for i == 0, we just call the vertex twice
//			// for i == nCurveVertices-1 (last point) we call vertex 0 twice
//			// otherwise just normal ofCurveVertex call
//			
//			if (i == 0){
//				ofCurveVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
//				ofCurveVertex(curveVertices[0].x, curveVertices[0].y); // we need to duplicate 0 for the curve to start at point 0
//			} else if (i == nCurveVertices-1){
//				ofCurveVertex(curveVertices[i].x, curveVertices[i].y);
//				ofCurveVertex(curveVertices[0].x, curveVertices[0].y);	// to draw a curve from pt 6 to pt 0
//				ofCurveVertex(curveVertices[0].x, curveVertices[0].y);	// we duplicate the first point twice
//			} else {
//				ofCurveVertex(curveVertices[i].x, curveVertices[i].y);
//			}
//		}
//		
//	ofEndShape();
//	
//	
//	// show a faint the non-curve version of the same polygon:
//	ofEnableAlphaBlending();
//		ofNoFill();
//		ofSetColor(0,0,0,40);
//		ofBeginShape();
//			for (int i = 0; i < nCurveVertices; i++){
//				ofVertex(curveVertices[i].x, curveVertices[i].y);
//			}
//		ofEndShape(true);
//		
//		
//		ofSetColor(0,0,0,80);
//		for (int i = 0; i < nCurveVertices; i++){
//			if (curveVertices[i].bOver == true) ofFill();
//			else ofNoFill();
//			ofCircle(curveVertices[i].x, curveVertices[i].y,4);
//		}
//	ofDisableAlphaBlending();
//	//-------------------------------------
	

	
	ofPopMatrix();

//	//-------------------------------------

//	
//	ofSetHexColor(0x000000);
//	ofDrawBitmapString("(c) dynamically\ncreated shape", 420,210);
//	

//	
//	ofSetHexColor(0x000000);
//	ofDrawBitmapString("(f) ofCurveVertex\nuses catmull rom\nto make curved shapes", 220,410);
//	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//------------- -------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	for (int i = 0; i < nCurveVertices; i++){
		float diffx = x - curveVertices[i].x;
		float diffy = y - curveVertices[i].y;
		float dist = sqrt(diffx*diffx + diffy*diffy);
		if (dist < curveVertices[i].radius){
			curveVertices[i].bOver = true;
		} else {
			curveVertices[i].bOver = false;
		}	
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	for (int i = 0; i < nCurveVertices; i++){
		if (curveVertices[i].bBeingDragged == true){
			curveVertices[i].x = x;
			curveVertices[i].y = y;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < nCurveVertices; i++){
		float diffx = x - curveVertices[i].x;
		float diffy = y - curveVertices[i].y;
		float dist = sqrt(diffx*diffx + diffy*diffy);
		if (dist < curveVertices[i].radius){
			curveVertices[i].bBeingDragged = true;
		} else {
			curveVertices[i].bBeingDragged = false;
		}	
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	for (int i = 0; i < nCurveVertices; i++){
		curveVertices[i].bBeingDragged = false;	
	}
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
