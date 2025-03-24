#pragma once
#include "../../../Entity/entity.h"
#include "../../../../Utils/Math/math.h"
#include "../../game.h"

class Visuals {
public:
	// default vars
	uintptr_t localPlayerPawn = read_mem<uintptr_t>(Cs2::client_dll + Sdk::offsets::client_dll::dwLocalPlayerPawn);
	view_matrix fromView = read_mem<view_matrix>(Cs2::client_dll + Sdk::offsets::client_dll::dwViewMatrix);

public:
	// initialized when we call Render function to validate the correct entity that user wants
	Entity* entity;
public:
	Vector2 screenPos, headScreenPos;
public:
	void Render(Entity* rawEntity);

private:
	void SkeletonEsp();
	void BoxEsp();
private:
	// short private function here
	float GetHeadHeight(Vector2 screenPos, Vector2 headScreenPos)
	{
		return (screenPos.y - headScreenPos.y) / 8;
	}
	inline void DrawBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor color = ImColor(255, 255, 255, 255), float thickness = 2.0f) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color, 0.0f, ImDrawFlags_None, thickness);
	}
	inline void DrawFilledBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor fillColor = ImColor(255, 0, 0, 128), float borderThickness = 2.0f, ImColor borderColor = ImColor(255, 255, 255, 255)) {
	/*	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), fillColor, 0.0f, ImDrawFlags_None);*/
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), borderColor, 0.0f, ImDrawFlags_None, borderThickness);
	}
	inline void Draw3D(Vector3* corners, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f)
	{
		Vector2 screenCorners[8];

		for (int i = 0; i < 8; i++) {
			if (!CsWorldToScreen(fromView,corners[i], screenCorners[i])) {
				return;
			}

		}

		for (int i = 0; i < 4; i++) {
			int next = (i + 1) % 4;
			DrawLine(screenCorners[i], screenCorners[next], color, thickness);
			DrawLine(screenCorners[i + 4], screenCorners[next + 4], color, thickness);
			DrawLine(screenCorners[i], screenCorners[i + 4], color, thickness);
		}
	}
	inline void DrawLine(const Vector2& from, const Vector2& to, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, bool drawEndPoint = false, float endPointRadius = 3.0f, ImColor endPointColor = ImColor(255, 255, 255, 255)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);

		if (drawEndPoint) {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), endPointRadius, endPointColor);
		}
	}
};