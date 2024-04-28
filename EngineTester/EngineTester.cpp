// EngineTester.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "VulkanCapabilitiesDisplayer.h"
#include "VkApplication.h"
#include "VkException.h"
#include "vk_parameters.h"
#include "RHIManager.h"
#include <iostream>

int main()
{
    VulkanCapabilitiesDisplayer displayer;
    VkApplication::displayInstanceCapabilities(displayer);

    //RHIManager::instance().loadConfiguration("..\\..\\test_resources");
    VKInstanceSettings settings;
    settings.ApplicationName = "Engine_test";
    settings.EngineName = "Engine";
    settings.AppVersion = 1;
    settings.Layers = {"VK_LAYER_KHRONOS_validation"};
    settings.Extensions = {"VK_KHR_surface", "VK_EXT_debug_utils"};
    try
    {
        VkApplication app(settings);
        app.displayDevicesCapabilities(displayer);
    }
    catch (VkException& except)
    {
        std::cerr << except.message();
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
