#include "SandboxEngine.h"

#include <iostream>


class App : public SE::Application
{
};

int main()
{
    App app;
    app.update();
}