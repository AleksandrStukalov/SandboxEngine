#include "SandboxEngine.h"

#include <iostream>


struct App : SE::Application
{
    void onUpdate() override
    {
        SE::Log::info({ "Works" });
    }
};

int main()
{
    App().update();
}