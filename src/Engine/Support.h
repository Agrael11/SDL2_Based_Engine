#pragma once

namespace Engine::Support
{
    class Config 
    {
    public:
        //Getter And Setter for Audio
        static bool isAudioEnabled();
        static void setAudioEnabled(bool enabled);
        
        //Getter and Setter for Controller
        static bool isControllerEnabled();
        static void setControllerEnabled(bool enabled);

    private:
        static bool s_audioEnabled;
        static bool s_controllerEnabled;
    };
}