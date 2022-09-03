#pragma once

#include "Quadtree.h"

int main()
{
    QuadtreeApp* app = new QuadtreeApp();
    app->update();

    delete app;
}