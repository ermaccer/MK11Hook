#include "AnimationTool.h"
#include "MKCharacter.h"
#include "PlayerInfo.h"
#include "GameInfo.h"
#include "mk11.h"
#include "..\eDirectX11Hook.h"
#include "..\imgui\imgui.h"
#include "..\utils\MemoryMgr.h"
#include <algorithm>
#include "mk11menu.h"
#include <iostream>
#include <fstream>

using namespace Memory::VP;

bool AnimationTool::ms_bActive = false;
bool AnimationTool::ms_bDrawEditBox = false;
bool AnimationTool::ms_bDrawFileBox = false;
bool AnimationTool::ms_bSkipFaceBones = true;
bool AnimationTool::ms_bSave = false;
bool AnimationTool::ms_bLoad = false;
std::vector<PoseEntry> AnimationTool::plr2_pose;
std::vector<PoseEntry> AnimationTool::plr1_pose;


const char* szFaceBoneNames[] = {
	"LeftEye",
	"RightEye",
	"MouthRiggingOffset",
	"Jaw",
	"Tongue1",
	"Tongue2",
	"Tongue3",
	"Tongue4",
	"Tongue5",
	"Tongue6",
	"Chin",
	"Forehead",
	"RightLwrEyelid1",
	"RightLwrEyelid2",
	"LeftLipUpr",
	"LeftLipUprOuter",
	"NoseTip",
	"RightLipLwrCorner",
	"RightForeheadOut",
	"NoseLower",
	"LeftLipLwrOut",
	"LeftLipUprCorner",
	"LeftForeheadIn",
	"LeftLipCornerOut",
	"RightLipLwr",
	"LeftChinSide",
	"LeftUprEyelid3",
	"RightCheekInner",
	"RightNasolabialBulge",
	"RightLipLwrOuter",
	"LeftCheekLower",
	"RightNostril",
	"LeftNasolabialBulge",
	"RightUprForeheadMid",
	"LipUprOut",
	"LeftLipUprOut",
	"LeftNostril",
	"LeftNasolabialFurrow",
	"RightUprEyelid3",
	"LeftUprEyelid2",
	"RightUnderChin",
	"LeftEyelid",
	"RightUprEyelid1",
	"LeftUprForeheadMid",
	"RightNasolabialFurrow",
	"RightLipUprCorner",
	"RightUprEyelid2",
	"RightCheekLower",
	"RightForeheadMid",
	"RightLipCornerOut",
	"LeftUprEyelid1",
	"LipLwrOut",
	"LeftMasseter",
	"RightLipLwrOut",
	"UprForehead",
	"RightLwrMasseter",
	"RightCheekOuter",
	"LeftLwrMasseter",
	"LeftForeheadOut",
	"LeftForeheadMid",
	"LeftUnderChin",
	"LeftLipLwrCorner",
	"LeftUprForeheadIn",
	"RightMasseter",
	"RightLipUpr",
	"LeftLwrEyelid3",
	"LeftLipLwr",
	"RightUprEyelid4",
	"RightUprForeheadIn",
	"RightChinSide",
	"LeftLwrEyelid2",
	"LipUpr",
	"UnderChin",
	"RightEyelid",
	"RightLipUprOuter",
	"LeftLipLwrOuter",
	"LeftLwrEyelid1",
	"RightForeheadIn",
	"LeftUprEyelid4",
	"RightLipUprOut",
	"RightLwrEyelid3",
	"LipLwr",
	"LeftCheekOuter",
	"LeftCheekInner",
};


bool operator==(PoseEntry& a, PoseEntry& b)
{
	return strcmp(b.boneName, a.boneName) == 0;
}

bool cmp_pose(PoseEntry& a, PoseEntry& b)
{
	return strcmp(b.boneName, a.boneName) == 0;
}

void AnimationTool::Draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (GetObj(PLAYER1))
			{
				if (ImGui::MenuItem("Save"))
				{
					ms_bDrawFileBox = true;
					ms_bSave = true;
					ms_bLoad = false;
				}
				if (ImGui::MenuItem("Load"))
				{
					ms_bDrawFileBox = true;
					ms_bSave = false;
					ms_bLoad = true;
				}

				ImGui::Separator();
			}

			if (ImGui::MenuItem("Exit Tool"))
				TheMenu->m_bSubmenuActive[SUBMENU_ANIMATIONTOOL] = false;


			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Editing"))
		{
			if (!GetObj(PLAYER1))
			{
				ImGui::MenuItem("Only available in game.", NULL, false, false);
			}
			else
				ImGui::MenuItem("Activate", NULL, &ms_bActive);
			
			if (ms_bActive && GetObj(PLAYER1))
			{
				ImGui::MenuItem("Edit Bones", NULL, &ms_bDrawEditBox);
			}

			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Pose Tools"))
		{
			if (!GetObj(PLAYER1))
			{
				ImGui::MenuItem("Only available in game.", NULL, false, false);
			}
			else
			{
				ImGui::MenuItem("Skip Face & Head Bones (P2 transfer only)", NULL, &ms_bSkipFaceBones);
				if (ImGui::MenuItem("Store P1 Pose"))
					StorePose();

				if (ImGui::MenuItem("Store P2 Pose"))
					UseP2Pose();
				if (ImGui::MenuItem("Clear Pose"))
					ClearPose();
				if (ImGui::MenuItem("Print Pose Data"))
					PrintPose();
			}
			ImGui::EndMenu();
		}
		ImGui::Separator();
		ImGui::MenuItem(ms_bActive ? "Editing: yes" : "Editing: no", NULL, false, false);

		static char buff[256] = {};

		sprintf(buff, "Pose Info Num: %d", plr1_pose.size());
		ImGui::Separator();
		ImGui::MenuItem(buff, NULL, false, false);

		ImGui::Separator();
		ImGui::MenuItem("beta", NULL, false, false);
	}

	
	if (ms_bDrawEditBox)
		DrawEditBox();

	if (ms_bDrawFileBox)
		DrawFileBox();

}

void AnimationTool::StorePose()
{
	if (!GetObj(PLAYER1))
		return;

	USkeletalMeshComponent* skel = GetObj(PLAYER1)->GetSkeleton();
	plr1_pose.clear();
	for (int i = 0; i < skel->pose.BoneAtoms.Count; i++)
	{
		FBoneAtom atom = skel->pose.BoneAtoms.Get(i);
		FName name;
		skel->GetBoneName(name, i);

		if (name.Index >= 0)
		{
			PoseEntry ent;
			ent.atom = atom;
			sprintf(ent.boneName, GetName(name.Index));
			plr1_pose.push_back(ent);
		}
	}
}

void AnimationTool::StoreP2Pose()
{
	if (!GetObj(PLAYER1))
		return;

	USkeletalMeshComponent* skel = GetObj(PLAYER2)->GetSkeleton();
	plr2_pose.clear();
	for (int i = 0; i < skel->pose.BoneAtoms.Count; i++)
	{
		FBoneAtom atom = skel->pose.BoneAtoms.Get(i);
		FName name;
		skel->GetBoneName(name, i);

		if (name.Index >= 0)
		{
			PoseEntry ent;
			ent.atom = atom;
			sprintf(ent.boneName, GetName(name.Index));
			plr2_pose.push_back(ent);
		}
	}
}

void AnimationTool::UseP2Pose()
{
	if (!GetObj(PLAYER1))
		return;
	if (!GetObj(PLAYER2))
		return;

	plr1_pose.clear();
	// store p1 first to fix clothes and so on
	USkeletalMeshComponent* skel = GetObj(PLAYER1)->GetSkeleton();

	for (int i = 0; i < skel->pose.BoneAtoms.Count; i++)
	{
		FBoneAtom atom = skel->pose.BoneAtoms.Get(i);
		FName name;
		skel->GetBoneName(name, i);

		if (name.Index >= 0)
		{
			PoseEntry ent;
			ent.atom = atom;
			sprintf(ent.boneName, GetName(name.Index));
			plr1_pose.push_back(ent);
		}
	}

	USkeletalMeshComponent* skel_p2 = GetObj(PLAYER2)->GetSkeleton();
	for (int i = 0; i < skel_p2->pose.BoneAtoms.Count; i++)
	{
		FBoneAtom atom = skel_p2->pose.BoneAtoms.Get(i);
		FName name;
		skel_p2->GetBoneName(name, i);
		if (ms_bSkipFaceBones)
		{
			if (IsFaceBone(GetName(name.Index)))
				continue;
		}

		if (name.Index >= 0)
		{
			PoseEntry ent;
			ent.atom = atom;
			sprintf(ent.boneName, GetName(name.Index));
			plr1_pose.push_back(ent);
		}
	}

	std::sort(plr1_pose.begin(), plr1_pose.end(), cmp_pose);
	plr1_pose.erase(std::unique(plr1_pose.begin(), plr1_pose.end()), plr1_pose.end());
}

void AnimationTool::ClearPose()
{
	plr1_pose.clear();
}

void AnimationTool::ProcessPosing()
{
	if (!GetObj(PLAYER1))
		return;
	if (!GetObj(PLAYER2))
		return;

	USkeletalMeshComponent* skel = GetObj(PLAYER1)->GetSkeleton();
	USkeletalMeshComponent* skel_p2 = GetObj(PLAYER2)->GetSkeleton();


	if (ms_bActive)
	{
		for (int i = 0; i < plr1_pose.size(); i++)
		{
			int boneIdx = GetBoneID(plr1_pose[i].boneName);
			if (boneIdx >= 0)
			{
				FBoneAtom& atom = skel->pose.BoneAtoms.Get(boneIdx);
				atom = plr1_pose[i].atom;
			}
		}
		
	}
}

void AnimationTool::PrintPose()
{
	if (!GetObj(PLAYER1))
		return;

	USkeletalMeshComponent* skel = GetObj(PLAYER1)->GetSkeleton();

	for (int i = 0; i < plr1_pose.size(); i++)
	{
		PoseEntry p = plr1_pose[i];
		printf("BONE: %s POS: %f %f %f ROT: %f %f %f %f RAD: %f\n", p.boneName, p.atom.Translation.X, p.atom.Translation.Y, p.atom.Translation.Z, p.atom.Rotation.X, p.atom.Rotation.Y, p.atom.Rotation.Z, p.atom.Rotation.W, p.atom.JointRadius);
	}


}

void AnimationTool::DrawEditBox()
{

	MKCharacter* obj = GetObj(PLAYER1);
	if (!obj)
		return;

	USkeletalMeshComponent* skel = GetObj(PLAYER1)->GetSkeleton();

	if (!skel)
		return;

	static bool drawBoneName = false;
	static float sliderLimit = 30.0f;
	static char boneName[256] = {};
	static std::vector<std::string> boneList;
	int  boneID = GetBoneID(boneName);

	ImGui::Begin("EditBox");
	{
		ImGui::TextWrapped("Press Store P1 Pose if bones cant be edited.");
		ImGui::TextWrapped("Freeze player in place using speed modifier.");
		ImGui::TextWrapped("Hide P2 (if has bugged clothing) with scale modifier.");
		ImGui::Separator();
		if (plr1_pose.size() == 0)
		{
			ImGui::Text("No pose to edit!");
			ImGui::End();
			return;

		}
		ImGui::Text("Selected Bone: %s ID: %d", boneName, boneID);
		ImGui::InputFloat("Sliders Limit", &sliderLimit);
		ImGui::Separator();

		boneList.clear();
		for (int n = 0; n < skel->pose.BoneAtoms.Count; n++)
		{
			FName name;
			skel->GetBoneName(name, n);
			std::string str = GetName(name.Index);
			boneList.push_back(str);
		}
		ImGui::Text("Bone List");
		static ImGuiTextFilter filter;
		ImGui::Text("Search");
		ImGui::PushItemWidth(-FLT_MIN);
		filter.Draw("##bonelist");
		ImGui::PopItemWidth();
		ImGui::BeginChild("##list", { 0, 255.0f }, true);
		{
			static int selectID = 0;
			for (int n = 0; n < boneList.size(); n++)
			{

				if (filter.PassFilter(boneList[n].c_str()))
				{
					bool is_selected = (selectID == n);
					if (ImGui::Selectable(boneList[n].c_str(), is_selected))
					{
						selectID = n;

						char name[256] = {};
						sprintf(boneName, "%s", boneList[n].c_str());

					}
				}

			}
		}
		ImGui::EndChild();

		
	}
	if (boneID >= 0)
	{
		FBoneAtom atom = plr1_pose[boneID].atom;
		ImGui::Text("Position");
		ImGui::Separator();
		ImGui::SliderFloat("X", &plr1_pose[boneID].atom.Translation.X, -sliderLimit, sliderLimit);
		ImGui::SliderFloat("Y", &plr1_pose[boneID].atom.Translation.Y, -sliderLimit, sliderLimit);
		ImGui::SliderFloat("Z", &plr1_pose[boneID].atom.Translation.Z, -sliderLimit, sliderLimit);

		FQuat tmp = { -atom.Rotation.X, -atom.Rotation.Y, -atom.Rotation.Z, atom.Rotation.W };
		FVector tmpRot = quat2vec(tmp);
		FVector rot = {degToRad(tmpRot.X),degToRad(tmpRot.Y), degToRad(tmpRot.Z)};

		ImGui::Text("Rotation");
		ImGui::Separator();
		ImGui::SliderFloat("Pitch", &rot.X, -sliderLimit, sliderLimit);
		ImGui::SliderFloat("Yaw", &rot.Y, -sliderLimit, sliderLimit);
		ImGui::SliderFloat("Roll", &rot.Z, -sliderLimit, sliderLimit);

		tmpRot = { radToDeg(rot.X), radToDeg(rot.Y), radToDeg(rot.Z) };
		FQuat tmpQuat = vec2quat(rot);
		FQuat q = { -tmpQuat.X, -tmpQuat.Y, -tmpQuat.Z, tmpQuat.W };
		plr1_pose[boneID].atom.Rotation = q;
	}

	ImGui::End();
}

void AnimationTool::DrawFileBox()
{
	const char* title = "Save Pose";
	if (ms_bLoad)
		title = "Load Pose";

	ImGui::Begin(title, &ms_bDrawFileBox);
	{
		ImGui::Text("Write full file path (eg. \"C:\\test.pose\"). All folders must exist.");
		static char path[260];
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("", path, sizeof(path));
		ImGui::PopItemWidth();
		if (ms_bSave)
		{
			if (ImGui::Button("Save", { -FLT_MIN, 0 }))
			{
				SavePose(path);
				ms_bDrawFileBox = false;
			}

		}
		if (ms_bLoad)
		{
			if (ImGui::Button("Load", { -FLT_MIN, 0 }))
			{
				LoadPose(path);
				ms_bDrawFileBox = false;
			}

		}

	}
	ImGui::End();
}


int AnimationTool::GetBoneID(char* name)
{
	if (!GetObj(PLAYER1))
		return -1;

	int boneID = -1;

	USkeletalMeshComponent* skel = GetObj(PLAYER1)->GetSkeleton();
	for (int i = 0; i < skel->pose.BoneAtoms.Count; i++)
	{
		FBoneAtom atom = skel->pose.BoneAtoms.Get(i);
		FName n;
		skel->GetBoneName(n, i);
		if (n.Index >= 0)
		{
			if (strcmp(GetName(n.Index), name) == 0)
			{
				boneID = i;
				break;
			}
		}
	}
	return boneID;
}

bool AnimationTool::IsFaceBone(char* name)
{
	for (int i = 0; i < sizeof(szFaceBoneNames) / sizeof(szFaceBoneNames[0]); i++)
	{
		if (strcmp(szFaceBoneNames[i], name) == 0)
			return true;
	}
	return false;
}

void AnimationTool::SavePose(char* path)
{
	std::string output = path;
	if (output.empty())
		return;

	std::ofstream oFile(output, std::ofstream::binary);

	EPoseHeader hdr;
	sprintf(hdr.charName, GetCharacterName(PLAYER1));
	hdr.hdr = 'EPOS';
	hdr.game = 'MK11';
	hdr.numBones = plr1_pose.size();
	hdr.reserved = -1;

	oFile.write((char*)&hdr, sizeof(EPoseHeader));

	for (int i = 0; i < plr1_pose.size(); i++)
	{
		EPoseEntry ent;
		ent.atom = plr1_pose[i].atom;
		sprintf(ent.boneName, plr1_pose[i].boneName);
		oFile.write((char*)&ent, sizeof(EPoseEntry));
	}

}

void AnimationTool::LoadPose(char* path)
{
	std::string input = path;

	if (input.empty())
		return;

	std::ifstream pFile(input, std::ifstream::binary);

	EPoseHeader hdr;
	pFile.read((char*)&hdr, sizeof(EPoseHeader));

	if (!(hdr.hdr == 'EPOS'))
	{
		printf("%s | Not a valid pose file!\n", __FUNCTION__);
		return;
	}


	ClearPose();
	for (int i = 0; i < hdr.numBones; i++)
	{
		EPoseEntry ent;
		pFile.read((char*)&ent, sizeof(EPoseEntry));

		PoseEntry e;
		e.atom = ent.atom;
		sprintf(e.boneName, ent.boneName);
		plr1_pose.push_back(e);
	}

}


FQuat vec2quat(FVector v)
{
	float cy = cos(v.Z * 0.5);
	float sy = sin(v.Z * 0.5);
	float cp = cos(v.Y * 0.5);
	float sp = sin(v.Y * 0.5);
	float cr = cos(v.X * 0.5);
	float sr = sin(v.X * 0.5);

	FQuat q;
	q.W = cr * cp * cy + sr * sp * sy;
	q.X = sr * cp * cy - cr * sp * sy;
	q.Y = cr * sp * cy + sr * cp * sy;
	q.Z = cr * cp * sy - sr * sp * cy;



	return q;
}

FVector quat2vec(FQuat q)
{
	FVector result;

	float ysqr = q.Y * q.Y;

	float t0 = +2.0f * (q.W * q.X + q.Y * q.Z);
	float t1 = +1.0f - 2.0f * (q.X * q.X + ysqr);
	float roll = atan2(t0, t1);

	float t2 = +2.0f * (q.W * q.Y - q.Z * q.X);
	t2 = ((t2 > 1.0f) ? 1.0f : t2);
	t2 = ((t2 < -1.0f) ? -1.0f : t2);

	float pitch = asin(t2);
	float t3 = +2.0f * (q.W * q.Z + q.X * q.Y);
	float t4 = +1.0f - 2.0f * (ysqr + q.Z * q.Z);
	float yaw = atan2(t3, t4);

	result.X = roll / M_PI * 180.0f;
	result.Y = pitch / M_PI * 180.0f;
	result.Z = yaw / M_PI * 180.0f;
	return result;
}