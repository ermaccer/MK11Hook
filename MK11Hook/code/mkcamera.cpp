#include "mkcamera.h"
#include "mk11menu.h"
#include <iostream>
#include <Windows.h>

MKCamera* TheCamera;

void MKCamera::SetPosition(FVector * pos)
{
	TheCamera = this;
	camPos = *pos;
	((void(__fastcall*)(MKCamera*, FVector*))_addr(0x141A12830))(this, pos);
}

void MKCamera::SetRotation(FRotator * rot)
{
	TheCamera = this;
	camRot = *rot;
	((void(__fastcall*)(MKCamera*, FRotator*))_addr(0x141A13210))(this, rot);
}

void MKCamera::SetFOV(float FOV)
{
	camFov = FOV;
}

float MKCamera::GetFOV()
{
	return camFov;
}

void MKCamera::HookedSetPosition(FVector * pos)
{
	if (TheMenu->m_bCustomCameraFOV)
		SetFOV(TheMenu->camFov);
	else
		TheMenu->camFov = GetFOV();

	float oneTime = 0.0f;
	if (!TheMenu->m_bYObtained)
	{
		oneTime = pos->Y;
		TheMenu->m_bYObtained = true;
	}

	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector plrPos;
			FVector p2;
			GetCharacterPosition(&plrPos, PLAYER1);
			GetCharacterPosition(&p2, PLAYER2);
			switch (TheMenu->m_nCurrentCustomCamera)
			{
			case CAMERA_3RDPERSON:
				pos->X = 5 + TheMenu->m_fAdjustCustomCameraThirdPersonX;
				pos->Y = oneTime - 330.0f;
				pos->Y += plrPos.Y * 0.85f;
				pos->Y += TheMenu->m_fAdjustCustomCameraThirdPersonY;
				pos->Z = 210.0f + plrPos.Z;
				pos->Z += TheMenu->m_fAdjustCustomCameraThirdPersonZ;

				if (p2.Y < plrPos.Y)
				{
					pos->Y += 600.0f;
					pos->Z = 210.0f + plrPos.Z;
					pos->Z += TheMenu->m_fAdjustCustomCameraThirdPersonZ;
				}


				TheMenu->camPos = *pos;
				break;
			case CAMERA_3RDPERSON2:
				pos->X = 5;
				pos->Y = oneTime - 230.0f;
				pos->Y += plrPos.Y * 0.85f;
				pos->Z = 260.0f + plrPos.Z;;

				if (p2.Y < plrPos.Y)
				{
					pos->Y += 600.0f;
					pos->Z = 260.0f;
				}


				TheMenu->camPos = *pos;
				break;
			case CAMERA_1STPERSON:
				pos->X = TheMenu->m_fAdjustCustomCameraX;
				pos->Y = -230;
				pos->Y += plrPos.Y - pos->Y;
				if (p2.Y < plrPos.Y)
					pos->Y += TheMenu->m_fAdjustCustomCameraY * -1;
				else
					pos->Y += TheMenu->m_fAdjustCustomCameraY;

				if (GetObj(PLAYER1)->IsCrouching())
					pos->Z = TheMenu->m_fAdjustCustomCameraCrouch;
				else
					pos->Z = TheMenu->m_fAdjustCustomCameraZ + plrPos.Z;


				TheMenu->camPos = *pos;
				break;
			case CAMERA_1STPERSON_MID:
				pos->X = 16.0f;
				pos->Y = -230;
				pos->Y += plrPos.Y - pos->Y;
				if (p2.Y < plrPos.Y)
					pos->Y += 23.0f * -1;
				else
					pos->Y += 23.0f;
				pos->Z = 124.0f + plrPos.Z;


				TheMenu->camPos = *pos;
				break;
			case CAMERA_INJUSTICE_2:
				pos->X -= 120.0f;
				pos->Z -= 25.0f;

				TheMenu->camPos = *pos;
				break;
			}
		}
		
		SetPosition(pos);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraPos)
		{
			TheMenu->camPos = *pos;
			SetPosition(pos);
		}
		else
		{
			SetPosition(&TheMenu->camPos);
		}
	}

}

void MKCamera::HookedSetRotation(FRotator * rot)
{
	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector p1, p2;
			switch (TheMenu->m_nCurrentCustomCamera)
			{
			case CAMERA_3RDPERSON:
				rot->Pitch = -900;
				rot->Yaw = 16000;
				rot->Roll = 0;
				TheMenu->camRot = *rot;
				GetCharacterPosition(&p1, PLAYER1);
				GetCharacterPosition(&p2, PLAYER2);

				if (p2.Y < p1.Y)
				{
					rot->Yaw = -16000;
					rot->Pitch = -900;
				}

				TheMenu->camRot = *rot;
				break;
			case CAMERA_3RDPERSON2:
				rot->Pitch = -4000;
				rot->Yaw = 16000;
				rot->Roll = 0;
				TheMenu->camRot = *rot;
				GetCharacterPosition(&p1, PLAYER1);
				GetCharacterPosition(&p2, PLAYER2);

				if (p2.Y < p1.Y)
				{
					rot->Yaw = -16000;
					rot->Pitch = -4000;
				}

				TheMenu->camRot = *rot;
				break;
			case CAMERA_1STPERSON:
				rot->Pitch = 0;
				rot->Yaw = 16000;
				rot->Roll = 0;
				TheMenu->camRot = *rot;
				GetCharacterPosition(&p1, PLAYER1);
				GetCharacterPosition(&p2, PLAYER2);

				if (p2.Y < p1.Y)
				{
					rot->Yaw = -16000;
				}

				TheMenu->camRot = *rot;
				break;
			case CAMERA_1STPERSON_MID:
				rot->Pitch = 0;
				rot->Yaw = 16000;
				rot->Roll = 0;
				TheMenu->camRot = *rot;
				GetCharacterPosition(&p1, PLAYER1);
				GetCharacterPosition(&p2, PLAYER2);

				if (p2.Y < p1.Y)
				{
					rot->Yaw = -16000;
				}

				TheMenu->camRot = *rot;
				break;
			case CAMERA_INJUSTICE_2:
				rot->Pitch += 1228;
				TheMenu->camRot = *rot;
				break;
			}
		}
		SetRotation(rot);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			SetRotation(rot);
		}
		else
			SetRotation(&TheMenu->camRot);
	}


}


