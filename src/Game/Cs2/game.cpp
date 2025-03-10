#include "game.h"
#include "../globals.hpp"
#include "../../Utils/Math/math.h"

uintptr_t Cs2::client_dll;
uintptr_t Cs2::server_dll;


void Cs2::Start() {

	Logging::debug_print("starting cheetoz sir, tobi gtg bgt");
	if (!DetectGame()) {
		Logging::error_print("cant detect the game");
		return;
	}
	if (!Setup()) {
		// exiting a application
		Logging::error_print("cant setup globals cache");
		return;
	}
	Logging::info_print("game initated started succesfully");

	 Globals::EntityRenderUpdate();
}

void Cs2::Esp() {
	Matrix ViewMatrix = read_mem<Matrix>(client_dll + Sdk::offsets::client_dll::dwViewMatrix);
	/*if (!ViewMatrix) {
		return;
	}*/
	for (auto& entity : Globals::EntityList) {
		Entity* pEntity = &entity;
		if (pEntity->player.Health <= 0) {
			Logging::debug_print("player is dead");
			continue;
		}
		Vector3 Origin = pEntity->player.Position;
		Vector3 paddingTop = { 0.f, 0.f, 4.f };  Vector3 paddingBottom = { 0.f, 0.f, 6.f };
		Vector3 headPos = { Origin.x , Origin.y , Origin.z + 72.f } ;
		Vector2 top,bottom;
		float h;  float w;
		Vector3 wtsTop = headPos + paddingTop;
		Vector3 wtsBottom = Origin + paddingBottom;
		if (WorldToScreen(ViewMatrix, wtsTop, top) && WorldToScreen(ViewMatrix, wtsBottom,bottom )) {
			h = bottom.y - top.y;
			w = h * 0.28f;
			ImGui::GetBackgroundDrawList()->AddRect({ top.x - w, top.y }, { top.x + w, bottom.y }, ImColor(0, 220, 0), 0, ImDrawFlags_None, 1.f);
			// continue;
		}
	//	Vector3 HeadPosition = pEntity->player.Position + Vector3{ 0.0f,0.0f,72.0f };
	//	Vector2 screenPos, headScreenPos;

	//	//Logging::debug_print("head position x : %f, y : %f, z : %f", HeadPosition.x, HeadPosition.y, HeadPosition.z);
	//	if (!WorldToScreen(ViewMatrix, HeadPosition, screenPos))
	//	{
	//		continue;
	//	}
	//	if (!WorldToScreen(ViewMatrix, pEntity->player.Position, headScreenPos))
	//	{
	//		continue;
	//	}
	//	/*float boxHeight = std::fabs(headScreenPos.y - screenPos.y);
	//	float boxWidth = boxHeight * 0.6f;
	//	Vector2 bottomRight(screenPos.x + boxWidth / 2, screenPos.y);*/
	///*	Interact.DrawLine(ImVec2(GlobalsConfig.GameRect.right / 2.f, GlobalsConfig.GameRect.bottom), ImVec2(pBase.x, EspPart.pBottom), color, 1.f);*/
	//	Vector2 namePos(screenPos.x - 20.0f, screenPos.y);
	//	// Logging::debug_print("its in our screen with hp : %d ", pEntity->player.Health);
	//	ImColor color = GlobalsConfig.ESP_PLAYER_COLOR;
	//	Logging::debug_print("namepos x : %f, y : %f", namePos.x, namePos.y);
	//	 DrawTextWithStroke("test", namePos, color, ImColor(10, 10, 10, 255));
	/*	if (entity.player.IsDormant) {
			continue;
		}*/
		// do something
	}
}

