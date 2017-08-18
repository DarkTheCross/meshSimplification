#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "meshManager.hpp"
#include <random>
#include <time.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class meshSimplificationApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void mouseDrag(MouseEvent event) override;
    
    CameraPersp cam;
    CameraUi cu;
    
    meshManager mm;
    TriMesh * tm;
};

void prepareSettings( meshSimplificationApp::Settings *settings )
{
    settings->setHighDensityDisplayEnabled(); // try removing this line
    settings->setMultiTouchEnabled( false );
}

void meshSimplificationApp::setup()
{
    
    //getWindow()->setSize(2000, 1000);
    //getWindow()->setBorderless(true);
    cam.setEyePoint( vec3( 0, 0, 1000) );
    cam.lookAt( vec3( 0, 0, 0 ) );
    cam.setFarClip(2000);
    cu.setCamera(&cam);
    
    /*
    auto lambert = gl::ShaderDef().lambert().color();
    auto shader = gl::getStockShader( lambert );
    shader->bind();
     */
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    mm.loadSTLFile("/Users/mingxiangfan/Documents/programming/creative/cinder_0.9.1_mac/fmx/meshSimplification/src/link_4_refined.stl");
    
    mm.calculateRidgeAngles();
    
    mm.watershedSegmentation( M_PI/180*15 );
    
    tm = new TriMesh();
    
    mm.initTriMesh(tm);

    //mm.writeSTLFile("/Users/mingxiangfan/Documents/programming/creative/cinder_0.9.1_mac/fmx/meshSimplification/src/link_4_refined.stl");

}

void meshSimplificationApp::mouseDown( MouseEvent event )
{
    cu.mouseDown(event);
}

void meshSimplificationApp::mouseDrag(MouseEvent event)
{
    cu.mouseDrag(event);
}

void meshSimplificationApp::update()
{
}

void meshSimplificationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::setMatrices(cam);

    gl::lineWidth(5);
    mm.drawMeshes();
    //mm.drawFrame();
    /*
    gl::color(1, 1, 1);
    gl::draw(*tm);
     */
}

CINDER_APP( meshSimplificationApp, RendererGl )
