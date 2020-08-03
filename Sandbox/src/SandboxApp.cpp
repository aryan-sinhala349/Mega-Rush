#include <MegaRush.h>
#include <MegaRush/Core/EntryPoint.h>

class SandboxApp : public MegaRush::Application
{
public:
	SandboxApp() : Application("Sandbox")
	{
		
	}

	~SandboxApp()
	{

	}
};

MegaRush::Application* MegaRush::CreateApplication()
{
	return new SandboxApp();
}