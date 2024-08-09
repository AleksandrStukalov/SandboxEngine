#pragma once

//#include "Quadtree.h"
#include "Octree.h"
#include <filesystem>

int main(int argc, const char** argv)
{
    OctreeApp* app = new OctreeApp();
    //QuadtreeApp* app = new QuadtreeApp();
    app->update();

    delete app;
}