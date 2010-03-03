//-------------------------------------------------------------------------------------
//
// \file char_shape.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 

#ifndef _char_SHAPE_
#define _char_SHAPE_

#include "ofxVectorMath.h"
#include "ofxVec2f.h"



class charShape {

  
  public:
		//----------------------------------------------------

	vector<ofxVec2f> shape;
	ofTrueTypeFont *font;
	
	
		//----------------------------------------------------	
	
	charShape(ofTrueTypeFont *font){
		font = font;
	}
	
	void loadChar(char c){
		ofTTFCharacter mchar = font->getCharacterAsPoints(c);
		
		vector<ofTTFContour> contour=mchar.contours; 
		
		for(int j = 0 ; j < contour.size(); j++){
			for(int i = 0; i < contour[j].pts.size()-1; i++){
				ofxVec2f p1 = ofxVec2f(contour[j].pts[i].x, contour[j].pts[i].y);
				ofxVec2f p2 = ofxVec2f(contour[j].pts[i+1].x, contour[j].pts[i+1].y);
				while((p1-p2).length() > 1){
					shape.push_back( (p2-p1).normalize());
					p1 += (p2-p1).normalize();
				}
			}
		}
	}
		
		
	
	void draw(int x, int y){
		
		//glBegin(GL_POINTS);
		for(vector<ofxVec2f>::iterator it=shape.begin(); it != shape.end(); it++){
			//glVertex2f(it->x, it->y);
			ofCircle(it->x, it->y, 4);
			cout<<it->x<<" "<<it->y<<endl;
			
		}
		//glEnd();

	}


  private:


};


#endif
