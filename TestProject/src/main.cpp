#pragma once

#include "OctreeApp.h"
#include "Minecraft.h"



int main()
{
    OctreeApp* app = new OctreeApp();
    app->update();

    delete app;
}