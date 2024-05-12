// EngineTester.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "VulkanCapabilitiesDisplayer.h"
#include "VkApplication.h"
#include "VkException.h"
#include "vk_parameters.h"
#include "RHIManager.h"
#include <iostream>
#include "macros.h"


#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

struct SDLApp
{
	const std::string appName = "EngineTester";
	int windowWidth = 800;
	int windowHeight = 600;
	SDL_Window* window = nullptr;
};

bool initializeSDL(SDLApp& application)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	try
	{
		SDL_CHECK(SDL_Vulkan_LoadLibrary(nullptr))
			application.window = SDL_CreateWindow(application.appName.c_str(),
				application.windowWidth, application.windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
	}
	catch (const std::runtime_error& error)
	{
		std::cerr << error.what();
		return false;
	}
	return true;
}

void applicationRun(SDLApp& a_sdlApp, std::unique_ptr<VkApplication>&& a_vkApp, VkEngineDevicePtr a_device)
{
	bool running = true;
	while (running)
	{
		SDL_Event windowEvent;
		while (SDL_PollEvent(&windowEvent))
		{
			switch (windowEvent.type)
			{
			case SDL_EVENT_WINDOW_RESIZED:
				break;

			case SDL_EVENT_QUIT:
				running = false;
				break;
			}
		}
	}
}

int main()
{
	SDLApp sdlApp;
	if (!initializeSDL(sdlApp))
		return -1;

	// display vulkan instance capabilities
	VulkanCapabilitiesDisplayer displayer;
	VkApplication::displayInstanceCapabilities(displayer);

	// loading engine resources
	RHIManager::instance().loadConfiguration("resources");

	// create instance settings
	VKInstanceSettings settings;

	// add SDL vulkan extension
	Uint32 sdlExtCount = 0;
	char const* const* sdlExt = SDL_Vulkan_GetInstanceExtensions(&sdlExtCount);
	for (Uint32 extIndex = 0; extIndex < sdlExtCount; ++extIndex)
		settings.Extensions.emplace_back(sdlExt[extIndex]);

	// setup vulkan engine
	std::unique_ptr<VkApplication> app;
	VkEngineDevicePtr device;
	try
	{
		// create engine application
		app = std::make_unique<VkApplication>(settings);

		// display devices capabilities
		app->displayDevicesCapabilities(displayer);

		// find compatible devices for required settings
		VKDeviceSettings devSettings;
		std::vector<VKDeviceInfo> compatibleDev;
		app->findCompatibleDevices(devSettings, compatibleDev);

		if (!compatibleDev.empty())
		{
			device = app->createDevice(devSettings, compatibleDev[0]);
		}
		else
		{
			std::cerr << "No device found" << std::endl;
		}

	}
	catch (VkException& except)
	{
		std::cerr << except.message();
		return -1;
	}

	// vulkan surface creation callback
	auto surfaceCallback = [&sdlApp](VkInstance a_instance, VkSurfaceKHR* a_surface)
		{
			SDL_Vulkan_CreateSurface(sdlApp.window, a_instance, nullptr, a_surface);
		};

	if (device)
	{
		applicationRun(sdlApp, std::move(app), device);
	}

	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
