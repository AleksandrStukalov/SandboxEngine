#pragma once

namespace SE
{
    class Application
    {
    public:
        Application();
        ~Application();
        void update();
    protected:
        virtual void onUpdate();
    };
}

