#pragma once

#include "Application.h"

extern MegaRush::Application* MegaRush::CreateApplication();

int main(int argc, char** argv)
{
	auto app = MegaRush::CreateApplication();

	app->Run();

	delete app;

	return 0;
}