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

#define CONTOUR_LLEN 2.0

class charShape {

  
  public:
		//----------------------------------------------------

	vector<ofxVec2f> shape;
	ofTrueTypeFont *font;
	
	
		//----------------------------------------------------	
	
	charShape(ofTrueTypeFont *tfont){
        cout<<"Setup font"<<endl;
		font = tfont;
	}
	
	void loadChar(char c){
        ofLog(OF_LOG_NOTICE, "Loading char");

		ofTTFCharacter mchar = font->getCharacterAsPoints(c);
		
		vector<ofTTFContour> contour=mchar.contours; 
		
		for(int j = 0 ; j < contour.size(); j++){
			for(int i = 0; i < contour[j].pts.size()-1; i++){
				ofxVec2f p1 = ofxVec2f(contour[j].pts[i].x, contour[j].pts[i].y);
				ofxVec2f p2 = ofxVec2f(contour[j].pts[i+1].x, contour[j].pts[i+1].y);
                ofxVec2f angle = (p2 - p1).normalize() * CONTOUR_LLEN;

				while((p2-p1).length() > CONTOUR_LLEN){
					shape.push_back( p1 );
                    p1 += angle; 
			    }

                //shape.push_back(p2);
                //p1 += (p2-p1).normalize() * CONTOUR_LLEN;
                //shape.push_back(p1);


			}
		}
	}
		
		
	
	void draw(int x, int y){
		
		glBegin(GL_POINTS);
		for(vector<ofxVec2f>::iterator it=shape.begin(); it != shape.end(); it++){
			glVertex2f(it->x+x, it->y+y);
			//ofCircle(it->x + x , it->y + y, 4);
			//cout<<it->x<<" "<<it->y<<endl;
		}
		glEnd();
	}


  private:


};


#endif
