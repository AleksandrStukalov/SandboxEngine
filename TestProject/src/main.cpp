#pragma once

#include "Quadtree.h"
#include "Octree.h"

int main()
{
    OctreeApp* app = new OctreeApp();
    app->update();

    delete app;
}