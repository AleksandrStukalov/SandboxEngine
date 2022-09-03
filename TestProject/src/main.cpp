#pragma once

#include "Quadtree.h"
#include "Octree.h"

int main()
{
    //OctreeApp* app = new OctreeApp();
    QuadtreeApp* app = new QuadtreeApp();
    app->update();

    delete app;
}