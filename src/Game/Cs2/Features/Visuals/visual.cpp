#include "visual.h"


struct BoneConnection_Struct
{
	int bone1;
	int bone2;

	BoneConnection_Struct(int b1, int b2) : bone1(b1), bone2(b2) {}
};

BoneConnection_Struct boneConnections[] = {
	BoneConnection_Struct(6, 5),  // head to neck
	BoneConnection_Struct(5, 4),  // neck to spine
	BoneConnection_Struct(4, 0),  // spine to hip
	BoneConnection_Struct(4, 8), // spine to left shoulder
	BoneConnection_Struct(8, 9), // left shoulder to left arm
	BoneConnection_Struct(9, 11), // arm to hand
	BoneConnection_Struct(4, 13),
	BoneConnection_Struct(13, 14),
	BoneConnection_Struct(14, 16),
	BoneConnection_Struct(4, 2),  // spine to spine_1
	BoneConnection_Struct(0, 22), // hip to left_hip
	BoneConnection_Struct(0, 25), // hip to right_hip
	BoneConnection_Struct(22, 23), // left_hip to left_knee
	BoneConnection_Struct(23, 24), // left knee to left foot
	BoneConnection_Struct(25, 26), // right_hip to right_knee
	BoneConnection_Struct(26, 27) // right knee to right foot
};

void Visuals::Render(Entity* rawEntity) {
	entity = rawEntity;

	if (entity->Health <= 0) {
		//Logging::debug_print("health %d", entity->Health);
		return;
	}

	// tandanya ini player kita
	if (entity->Controller.currentPawn == localPlayerPawn) {
		return;
	}

	// render visual when enemy is in our screen and set the screen and headscreen global position variables
	//Vector3 HeadPosition = entity->Position + Vector3{ 0.0f,0.0f,72.0f };
	Vector3 Origin = entity->Position;
	Vector3 HeadPosition = { Origin.x , Origin.y , Origin.z + 72.f };
	/*Vector3 paddingTop = { 0.f, 0.f, 4.f };
	Vector3 topPerson = HeadPosition + paddingTop;*/


	if (!CsWorldToScreen(fromView, Origin, screenPos) && !CsWorldToScreen(fromView, HeadPosition, headScreenPos)) {
		return;
	}


	// Logging::debug_print("entity y: %f | headScreenPos.y : %f", Origin.y, headScreenPos.y);

	// old box esp 
	//Vector3 Origin = entity->Position;
	//Vector3 paddingTop = { 0.f, 0.f, 4.f };  Vector3 paddingBottom = { 0.f, 0.f, 6.f };
	//Vector3 headPos = { Origin.x , Origin.y , Origin.z + 72.f };
	//Vector2 top, bottom;
	//float h;  float w;
	//Vector3 wtsTop = headPos + paddingTop;
	//Vector3 wtsBottom = Origin + paddingBottom;
	//if (CsWorldToScreen(fromView, wtsTop, top) && CsWorldToScreen(fromView, wtsBottom, bottom)) {
	//	h = bottom.y - top.y;
	//	w = h * 0.28f;
	//	ImGui::GetBackgroundDrawList()->AddRect({ top.x - w, top.y }, { top.x + w, bottom.y }, ImColor(0, 220, 0), 0, ImDrawFlags_None, 1.f);
	//}
	Visuals::BoxEsp();
	Visuals::SkeletonEsp();
}

void Visuals::BoxEsp() {
	Vector3 corners[8];
	float boxHeight = 72.0f;
	float boxWidth = boxHeight * 0.6f;
	float boxDepth = boxWidth;

	// Calculate the corners for the 3D box
	corners[0] = entity->Position + Vector3(-boxWidth / 2, -boxDepth / 2, 0);
	corners[1] = entity->Position + Vector3(boxWidth / 2, -boxDepth / 2, 0);
	corners[2] = entity->Position + Vector3(boxWidth / 2, boxDepth / 2, 0);
	corners[3] = entity->Position + Vector3(-boxWidth / 2, boxDepth / 2, 0);

	corners[4] = corners[0] + Vector3(0, 0, boxHeight);
	corners[5] = corners[1] + Vector3(0, 0, boxHeight);
	corners[6] = corners[2] + Vector3(0, 0, boxHeight);
	corners[7] = corners[3] + Vector3(0, 0, boxHeight);

	// stil bugged for normal boxes only work proper on 3d boxes
	Vector2 topLeft(screenPos.x - boxWidth / 2, headScreenPos.y);
	Vector2 topRight(screenPos.x + boxWidth / 2 + 12.0f, headScreenPos.y);
	Vector2 bottomRight(screenPos.x + boxWidth / 2, screenPos.y);
	Logging::debug_print("screenPos y axis: %f | head y axis: %f", screenPos.y, headScreenPos.y);
	//Vector3 paddingTop = { 0.f, 0.f, 4.f };
	//Vector3 paddingBottom = { 0.f, 0.f, 6.f };

	//Vector2 top;  Vector2 bottom; float h;  float w;

	//Vector3 Origin = entity->Position;
	//Vector3 HeadPosition = { Origin.x , Origin.y , Origin.z + 72.f };

	//Vector3 topPerson = HeadPosition + paddingTop;
	//Vector3 bottomPerson = HeadPosition + paddingBottom;

	/*if (CsWorldToScreen(fromView, topPerson, top)  {*/
	
		
		/*DrawFilledBox
		(
			top,
			bottom,
			w,
			GlobalsConfig.ESP_Filled_COLOR,
			1.f,
			GlobalsConfig.ESP_PLAYER_COLOR
		);


	}*/
	//h = bottom.y - top.y;
	//w = h * 0.28f;
	if (GlobalsConfig.ESP_BoxType == 0) {
		if (GlobalsConfig.ESP_BoxFilled) {
		/*	if (CsWorldToScreen(fromView, topPerson, top) {
			}*/
			DrawFilledBox
			(
				topLeft,
				bottomRight,
				GlobalsConfig.ESP_Filled_COLOR,
				1.f,
				GlobalsConfig.ESP_PLAYER_COLOR
			);

		}
		else {
			DrawBox(
				topLeft,
				bottomRight,
				GlobalsConfig.ESP_PLAYER_COLOR,
				1.f
			);
		}
	}
	else if (GlobalsConfig.ESP_BoxType == 1) {
		Draw3D(corners, GlobalsConfig.ESP_3D_COLOR, 1.f);

	}

}
void Visuals::SkeletonEsp() {
	Vector3 head = read_mem<Vector3>(entity->BoneMatrix + BoneIndex::head * 32);
	for (int i = 0; i < sizeof(boneConnections) / sizeof(boneConnections[0]); i++) {
		int bone1 = boneConnections[i].bone1;
		int bone2 = boneConnections[i].bone2;
		Vector3 VectorBone1 = read_mem<Vector3>(entity->BoneMatrix + bone1 * 32);
		Vector3 VectorBone2 = read_mem<Vector3>(entity->BoneMatrix + bone2 * 32);
		
		Vector2 b1, b2;
		if (CsWorldToScreen(fromView, VectorBone1, b1) &&
			CsWorldToScreen(fromView, VectorBone2, b2))
		{
			float headHeight = GetHeadHeight(screenPos, headScreenPos);
			DrawLine(b1, b2, GlobalsConfig.ESP_Skeleton_COLOR, 1.f);
			//Logging::debug_print("boneMatrix addr: 0x%llx", entity->BoneMatrix);
			//DrawUtils::DrawLine(b1, b2, Config::Esp::BonesColor, Config::Esp::BonesThickness);
		}
		
	}
}