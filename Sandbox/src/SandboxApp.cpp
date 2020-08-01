#include <MegaRush.h>
#include <MegaRush/Core/EntryPoint.h>

class SandboxApp : public MegaRush::Application
{
public:
	SandboxApp()
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