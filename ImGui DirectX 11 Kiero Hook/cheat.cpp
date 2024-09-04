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
    if (Menu::AimBotEnable && Menu::AimBotDraw)
    {
        ImGui::GetForegroundDrawList()->AddCircle(ImVec2(Menu::Gamewidth / 2, Menu::Gameheight / 2), Menu::FovAimBot, ImColor(Menu::AimBotColor[0], Menu::AimBotColor[1], Menu::AimBotColor[2], 1.0f), 100);

    }

    if (Menu::ESPenabled)
    {
        DrawESP();

    }


    if (Menu::showMenu) {

        if (!initialized) {
            ImGui::SetNextWindowSize(ImVec2(800, 500)); 
            initialized = true; 
            Menu::actualMenu = "General";
        }
        
        ImGui::Begin("Zykof Cheats", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 buttonSize(200, 50);
        ImVec2 LittlebuttonSize(100, 40);

        
        float buttonSpacing = 5.0f;
        float menuWidth = 200.0f;   
        float spacing = 40.0f;     


        ImGui::BeginChild("Menu", ImVec2(menuWidth, 0), true); 

        if (GradientButton("General", buttonSize, ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.3f, 0.3f, 1.0f))) {
            Menu::actualMenu = "General";
        }

        ImGui::Dummy(ImVec2(0, buttonSpacing));

        if (GradientButton("AimBot", buttonSize, ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.3f, 0.3f, 1.0f))) {
            Menu::actualMenu = "AimBot";
        }

        ImGui::Dummy(ImVec2(0, buttonSpacing)); 

        if (GradientButton("ESP", buttonSize, ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.3f, 0.3f, 1.0f))) {
            Menu::actualMenu = "ESP";
        }

        ImGui::EndChild(); 

        
        ImGui::SameLine();
        ImGui::BeginChild("MainContent", ImVec2(0, 0), true); 

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
            ImGui::Checkbox("AimBot When Aiming", &Menu::AimBotEnable);
            ImGui::Checkbox("Draw AimBot FOV", &Menu::AimBotDraw);
            ImGui::ColorEdit3("Color", Menu::AimBotColor);
            

            ImGui::SliderFloat("Fov AimBot", &Menu::FovAimBot, 10, 1000);
            ImGui::SliderFloat("Smoothing", &Menu::AimBotSmooth, 0, 10);
        }
        else if (Menu::actualMenu == "ESP")
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + menuWidth + 10);
            ImGui::Text("ESP");
            ImGui::Checkbox("ESP", &Menu::ESPenabled);
            ImGui::ColorEdit3("Color", Menu::ESPColor);
        }

        ImGui::EndChild(); 

        ImGui::End(); 

       
        style.FramePadding = ImVec2(4, 4); 
        style.ItemSpacing = ImVec2(8, 4);   
    }
}









