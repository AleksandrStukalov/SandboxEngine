#include "SandboxEngine.h"
#include "SandboxEngine/Window.h"
#include <iostream>


class App : public SE::Application
{
    void onUpdate() override
    {

    }
};

int main()
{
    App app;
    app.update();
}