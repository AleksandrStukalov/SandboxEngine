#pragma once

#include "OctreeApp.h"



int main()
{
    OctreeApp* app = new OctreeApp();
    app->update();

    delete app;
}