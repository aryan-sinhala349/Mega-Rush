#pragma once

int main(int argc, char** argv);

namespace MegaRush
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

	private:
		friend int ::main(int argc, char** argv);
		void Run();
	};

	Application* CreateApplication();
}