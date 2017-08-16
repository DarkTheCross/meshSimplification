//
//  meshManager.hpp
//  meshSimplification
//
//  Created by MINGXIANG FAN on 8/13/17.
//
//

#ifndef meshManager_hpp
#define meshManager_hpp

#include "cinder/TriMesh.h"
#include <vector>

class mTriangle{
public:
    mTriangle();
    size_t vertices[3];
    size_t sides[3];
    cinder::Color mColor;
    cinder::vec3 mNormal;
    size_t groupNumber;
};

class mSides{
public:
    mSides();
    size_t vertices[2];
    size_t triangles[2];
    cinder::Color mColor;
    double ridgeAngle;
};

class MeshTriangle;

class MeshEdge{
public:
    MeshEdge();
    cinder::Color edgeColor;
    double edgeAngle;
    std::shared_ptr<MeshTriangle> adjacentTriangles[2];
    std::shared_ptr<cinder::vec3> edgeVertices[2];
};

class MeshTriangle{
public:
    MeshTriangle();
    cinder::Color triangleColor;
    cinder::vec3 triangleNormal;
    size_t groupNumber;
    std::shared_ptr<MeshEdge> triangleEdges[3];
    std::shared_ptr<cinder::vec3> triangleVertices[3];
};

class meshManager{
public:
    
    meshManager();
    
    void loadSTLFile(const char* filename);
    void calculateRidgeAngles();
    void writeSTLFile(const char* filename);
    
    std::vector<mTriangle> _triangles;
    std::vector<mSides> _sides;
    std::vector<cinder::vec3> _points;
    
    std::vector<std::shared_ptr<MeshEdge> > _meshEdges;
    std::vector<std::shared_ptr<MeshTriangle> > _meshTriangles;
    std::vector<std::shared_ptr<cinder::vec3> > _meshVertices;
    
    // functions about drawing
    void drawFrame();
    void drawMeshes();
    void initTriMesh(cinder::TriMesh * tm);

    // function about paper
    void watershedSegmentation(double segmentThreshold);
    
    // divide to four, adding 3 vertices and 6 triangles
    void refineMesh(size_t triangleIndex);
    
    void flipRidge(size_t ridgeIndex);
    
    // timing
    size_t time_rec;
};





#endif /* meshManager_hpp */
