//
// Created by Miquel �ngel Soler on 15/12/15.
//

#include "PMRibbonPainter.h"

static const int POS_MARGIN = 1;

#define DRAW_PATH false

PMRibbonPainter::PMRibbonPainter(ofColor _color, float _dx, float _dy, float _div, float _ease,unsigned int size, PMUICanvasRibbonRenderer *_gui)
{
    color = ofColor(_color.r, _color.g, _color.b, _color.a);

    dx = _dx; dy = _dy;
    ax = ay = 0.0f;
    div = _div;
    ease = _ease;
    
    setSize(size);

    isNewPath = true;

    gui = _gui;

    xMin = POS_MARGIN;
    xMax = ofGetWidth() - POS_MARGIN - 1;
    yMin = POS_MARGIN;
    yMax = ofGetHeight() - POS_MARGIN - 1;
    
    vec.setColor(255, 255, 0);
    vec.noFill();
    for(int i=0;i<4;i++)
    {
        points.push_back(ofPoint(ofGetWidth()/2,ofGetHeight()/2,0));
    }
    vec.enableDraw();

}

void PMRibbonPainter::setup()
{
    isNewPath = true;
}

void PMRibbonPainter::update()
{
    
//    if ((dx != targetPos.x) && (dy != targetPos.y))
//    {
//        if (isNewPath) return;
//
//        dx -= ax = (ax + (dx - targetPos.x) * div) * ease;
//        dy -= ay = (ay + (dy - targetPos.y) * div) * ease;
    
        
//        dx = targetPos.x;
//        dy = targetPos.y;

        
        // Clean-up path vertices in case its size is higher than the allowed maximum.
        {
//            int maxNumVertices = gui->getPathNumVertices();
//            vector<ofPoint> vertices = path.getVertices();
//            //if (vertices.size() > maxNumVertices)
//            if(false)
//            {
//                path.clear();
//                path.addVertex(vertices[vertices.size()-1]);
//            }
//            cout << "Ribbon Clear // vSize = " << vertices.size() << "  __ maxNum " << maxNumVertices;
        }

        //polyline.curveTo(dx, dy,20);

//        cout << "T Pos:   (" << targetPos.x << ", " << targetPos.y << ")" << endl;
//        cout << "(dx,dy): (" << dx << ", " << dy << ")" << endl;
//    }
    
}

void PMRibbonPainter::draw()
{
    //if (isNewPath) return;

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetLineWidth(size);

#if (DRAW_PATH == true)
    polyline.draw();
    
    vertices = polyline.getVertices();
    cout << "Riboon : vertices = "<< vertices.size() << endl;

    if (vertices.size() > 1)
    {
//        polyline.clear();
//        polyline.addVertex(vertices[vertices.size()-1]);
    }

#else
    
    /*
    vertices = polyline.getVertices();
    
    if (vertices.size() > 1)
    {
        glPointSize(size);
        for (int i=0; i<vertices.size()-1; ++i)
        {
            ofDrawLine(vertices[i], vertices[i+1]);
//            ofSetColor(color);
            glBegin(GL_POINTS);
            glVertex2f(vertices[i].x,vertices[i].y);
            glEnd();
            
            
        }

        cout << "Riboon : vertices = "<< vertices.size() << endl;
//        ofSetColor(255,0,0);
//        ofSetColor(color);
//        for (int i=0; i<vertices.size()-1; ++i)
//        {
//            ofDrawLine(vertices[i], vertices[i+1]);
//        }
        
        polyline.clear();
        polyline.addVertex(vertices[vertices.size()-1]);
    }
    */
    if(points.size()>3)
    {
        ofPoint pLast3 = points[3];
        ofPoint pLast2 = points[2];
        ofPoint pLast1 = points[1];
        
        ofNoFill();
        ofSetColor(color);
        vec.curve(points[0].x,points[0].y,points[1].x,points[1].y,points[2].x,points[2].y,points[3].x,points[3].y);

        points.clear();
        points.push_back(pLast1);
        points.push_back(pLast2);
        points.push_back(pLast3);
    }

    
#endif
    
    
    //ofDisableBlendMode();
    
}

void PMRibbonPainter::setOrigin(PMPainterOrigin _origin)
{
    origin = _origin;

    switch (origin)
    {
        case PAINTER_LEFT:
        {
            setX(xMin);
            setY(ofGetHeight() / 2);
            break;
        }
        case PAINTER_RIGHT:
        {
            setX(xMax);
            setY(ofGetHeight() / 2);
            break;
        }
        case PAINTER_UP:
        {
            setX(ofGetWidth() / 2);
            setY(yMin);
            break;
        }
        case PAINTER_DOWN:
        {
            setX(ofGetWidth() / 2);
            setY(yMax);
            break;
        }
        case PAINTER_CENTER:
        {
            setX(ofGetWidth() / 2);
            setY(ofGetHeight() / 2);
            break;
        }
        default: break;
    }
     
}

void PMRibbonPainter::setPosition(int x, int y)
{
    float delta = gui->getNextPositionDelta();
    ofPoint newPoint = ofPoint(x,y);
    
    targetPos = ( newPoint * (1.0 - delta)) + (lastPoint*(delta));

    //    targetPos = ofPoint(x, y);

//    if (isNewPath)
//    {
////        cout << "Change dx, dy" << endl;
//        dx = targetPos.x;
//        dy = targetPos.y;
//        isNewPath = false;
//        return;
//    }
    
    dx -= ax = (ax + (dx - targetPos.x) * div) * ease;
    dy -= ay = (ay + (dy - targetPos.y) * div) * ease;

    
    //cout << "dx = " << dx << " ___ dy = " << dy << "   __ targetPos = " << targetPos.x << " , " << targetPos.y << endl;
    
    if ((dx != targetPos.x) && (dy != targetPos.y))
    {
        ofPoint p = ofPoint(dx,dy);
        //ofPoint p = ofPoint(x,y); // no easing option
        points.push_back(p);
        
    }
    

    lastPoint = targetPos;
    //cout << "Painter : setPosition at " << ofGetElapsedTimef()  << endl;
    
}

void PMRibbonPainter::setX(int x)
{
    setPosition(x, int(targetPos.y));
}

void PMRibbonPainter::setY(int y)
{
    setPosition(int(targetPos.x), y);
}

void PMRibbonPainter::setColor(ofColor _color)
{
    color = ofColor(_color.r, _color.g, _color.b, _color.a);
}

void PMRibbonPainter::setSize(unsigned int _size)
{
    size = _size;
}

void PMRibbonPainter::clear()
{
    polyline.clear();
    polyline = ofPolyline();

    isNewPath = true;
}
