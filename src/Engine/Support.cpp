#include "Support.h"

namespace Engine::Support
{
	//Initialize static variabless
	bool Config::s_audioEnabled = true;
	bool Config::s_controllerEnabled = true;

	//getters and setters for audio
	bool Config::isAudioEnabled()
	{
		return s_audioEnabled;
	}

	void Config::setAudioEnabled(bool enabled)
	{
		s_audioEnabled = enabled;
	}

	//getters and setters for controller
	bool Config::isControllerEnabled()
	{
		return s_controllerEnabled;
	}

	void Config::setControllerEnabled(bool enabled)
	{
		s_controllerEnabled = enabled;
	}
}