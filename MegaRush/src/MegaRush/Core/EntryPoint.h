#pragma once

#include "Application.h"

extern MegaRush::Application* MegaRush::CreateApplication();

int main(int argc, char** argv)
{
	MegaRush::Log::Init();

	auto app = MegaRush::CreateApplication();

	app->Run();

	delete app;

	return 0;
}