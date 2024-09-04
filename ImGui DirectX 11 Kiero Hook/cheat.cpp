#include "includes.h"
#include "./kiero/minhook/include/MinHook.h"
#include "./Cheats/Hooks.h"
#include "./Utils/Variable.h"
#include <algorithm>
#include "Cheats/AimBot.h"
#include "Cheats/ESP.h"
#include "Cheats/Fov.h"




uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");







void HookFunction() {
	if (MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + Offsets::playerSart), &PlayerStart_hook, (LPVOID*)&PlayerStart_o) != MH_OK) {
		std::cout << "failed hook a function";
	}
	MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + Offsets::playerSart));

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + Offsets::playerdestroy), &PlayerDestroy_hook, (LPVOID*)&PlayerDestroy_o) != MH_OK) {
		std::cout << "failed hook a function";
	}
	MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + Offsets::playerdestroy));



    /// function hook test
    if (MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + Offsets::functionTest), &function_hook, (LPVOID*)&function_o) != MH_OK) {
        std::cout << "failed hook a function";
    }
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + Offsets::functionTest));

}




void CheatMain() {

	if (GetAsyncKeyState(VK_DELETE) & 1) {
		Menu::showMenu = !Menu::showMenu;
		Sleep(50);
	}
    

    if (Variable::LocalPlayer == NULL)
    {
        return;
    }


    if (Menu::AimBotEnable)
    {
        AimBot();
    }


    Fov();

	


}


bool GradientButton(const char* label, const ImVec2& size, const ImVec4& color1, const ImVec4& color2)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);  
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);


    bool clicked = ImGui::InvisibleButton(label, size);
    ImVec2 p = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilledMultiColor(p, p_max,
        ImGui::GetColorU32(color1),
        ImGui::GetColorU32(color2),
        ImGui::GetColorU32(color2),
        ImGui::GetColorU32(color1));
    ImVec2 textSize = ImGui::CalcTextSize(label);
    ImVec2 textPos = ImVec2(
        p.x + (size.x - textSize.x) / 2.0f,
        p.y + (size.y - textSize.y) / 2.0f
    );
    draw_list->AddText(textPos, ImGui::GetColorU32(ImGuiCol_Text), label);
    ImGui::PopStyleVar(2);
    return clicked;
}






static bool initialized = false;

void ImguiWindow() {
    if (Menu::AimBotEnable)
    {
        ImGui::GetForegroundDrawList()->AddCircle(ImVec2(Menu::Gamewidth / 2, Menu::Gameheight / 2), Menu::FovAimBot, ImColor(255, 255, 255, 255),100);

    }

    if (Menu::ESPenabled)
    {
        DrawESP();

    }


    if (Menu::showMenu) {

        if (!initialized) {
            ImGui::SetNextWindowSize(ImVec2(800, 500)); // Taille initiale de la fenêtre
            initialized = true; // Marque comme initialisé pour ne plus redéfinir la taille
            Menu::actualMenu = "General";
        }
        // Définir la fenêtre principale
        ImGui::Begin("Zykof Cheats", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        // Modifier le style des boutons pour ajuster les espacements
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 buttonSize(200, 50);
        ImVec2 LittlebuttonSize(100, 40);

        // Définir l'espacement entre les boutons
        float buttonSpacing = 5.0f; // Ajustez cette valeur pour ajouter plus ou moins d'espace
        float menuWidth = 200.0f;   // Largeur fixe du menu
        float spacing = 40.0f;      // Espacement entre le menu et le contenu principal

        // Menu à gauche
        ImGui::BeginChild("Menu", ImVec2(menuWidth, 0), true); // Largeur fixe, hauteur automatique

        if (GradientButton("General", buttonSize, ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.3f, 0.3f, 1.0f))) {
            Menu::actualMenu = "General";
        }

        ImGui::Dummy(ImVec2(0, buttonSpacing)); // Ajoute un espace vertical entre les boutons

        if (GradientButton("AimBot", buttonSize, ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.3f, 0.3f, 1.0f))) {
            Menu::actualMenu = "AimBot";
        }

        ImGui::Dummy(ImVec2(0, buttonSpacing)); // Ajoute un espace vertical entre les boutons

        if (GradientButton("ESP", buttonSize, ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.3f, 0.3f, 1.0f))) {
            Menu::actualMenu = "ESP";
        }

        ImGui::EndChild(); // Fin du groupe pour le menu à gauche

        // Aligner le contenu principal à côté du menu
        ImGui::SameLine();
        ImGui::BeginChild("MainContent", ImVec2(0, 0), true); // Largeur et hauteur automatiques

        if (Menu::actualMenu == "General")
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + menuWidth + 10);
            ImGui::Text("General");
            ImGui::Dummy(ImVec2(0, buttonSpacing));
            ImGui::SliderInt("FOV Cam", &Variable::FOVCam, 80, 180);
            ImGui::SliderInt("FOV Gun", &Variable::FOVGun, 60, 180);
        }
        else if (Menu::actualMenu == "AimBot")
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + menuWidth + 10);
            ImGui::Text("AimBot");            
            ImGui::Dummy(ImVec2(0, buttonSpacing));
            ImGui::Checkbox("AimBot", &Menu::AimBotEnable);

            ImGui::SliderFloat("Fov AimBot", &Menu::FovAimBot, 10, 1000);
            ImGui::SliderFloat("Smoothing", &Menu::AimBotSmooth, 0, 10);
        }
        else if (Menu::actualMenu == "ESP")
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + menuWidth + 10);
            ImGui::Text("ESP");
            ImGui::Checkbox("ESP", &Menu::ESPenabled);
        }

        ImGui::EndChild(); // Fin du groupe pour le contenu principal

        ImGui::End(); // Fin de la fenêtre principale

        // Réinitialiser le style après usage pour éviter les effets indésirables ailleurs
        style.FramePadding = ImVec2(4, 4);  // Réinitialiser le padding
        style.ItemSpacing = ImVec2(8, 4);   // Réinitialiser l'espacement
    }
}









