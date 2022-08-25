#pragma once

#include "Octree.h"
#include "Minecraft.h"



int main()
{
    Octree* app = new Octree();
    app->update();

    delete app;
}