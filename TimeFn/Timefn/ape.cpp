#include "ape.h"
#include "driver.h"
#include "d3d9_x.h"
#include "xor.hpp"
#include <dwmapi.h>
#include <vector>
#include "Keybind.h"
#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "imgui_help.h"
ImDrawList* draw;
#include "skStr.h"
#include <WinUser.h>
#include "icons.h"
#include "iconcpp.h"
#include "font.h"
#include "imgui_help.h"
#include "xor.hpp"
#include "Connoa.h"
#include "Auth.h"
#include "offsets.h"
int segments = 25;

int
g_width,
g_height,
g_pid
;

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

using namespace KeyAuth;

std::string name = "Cheeto"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "5sJCzZ9MY1"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "db88917da0ebb45b256f05c5dd4c50a998ac70e0652a1a9f312c0ab4c8081d2c"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting

/*
	Video on what ownerid and secret are https://youtu.be/uJ0Umy_C6Fg

	Video on how to add KeyAuth to your own application https://youtu.be/GB4XW_TsHqA

	Video to use Web Loader (control loader from customer panel) https://youtu.be/9-qgmsUUCK4
*/

api KeyAuthApp(name, ownerid, secret, version, url);

bool fovcircle = false;
bool ShowMenu = true;
bool Esp = true;
bool Esp_box = false;
bool sdesp = false;
bool g_platform_esp = true;
bool cornerbox = false;
bool idktest = true;
bool Lcrosshair = false;
bool Esp_info = true;
bool Spinbot = false;
bool particles = false;
bool Esp_line = false;
bool Aimbot = true;
bool distanceesp = false;
bool squarefov = false;
bool g_skipknocked = false;
bool skeletonesp = false;
bool g_boatspeed = false;
ImFont* m_pFont;
int tabb = 1;
bool g_esp_skeleton = true;
bool idc = false;
int smooth = 3.5;
static int VisDist = 270;
int AimFOV = 300;
int darkness = 180;


int red = 0;
int green = 255;
int blue = 255;

static int aimkey = 0x02;
static int hitbox;
static int aimkeypos = 3;
static int hitboxpos = 0;
bool Filledfov = false;


bool aiminair = false;


// radar
bool radar = true;
bool rect_radar = false;
float radar_position_x{ 84.494f };
float radar_position_y{ 77.841f };
float radar_size{ 150.f };
float RadarDistance = { 700.f };

















static std::string ReadGetNameFromFName(int key) {
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = read<uint64_t>(base_address + 0xE0A9E00 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset);
	uint16_t nameEntry = read<uint16_t>(NamePoolChunk);

	int nameLength = nameEntry >> 6;

	// SOURCE MADE BY DAMAGE
	char buff[1024];
	if ((uint32_t)nameLength)
	{
		for (int x = 0; x < nameLength; ++x)
		{
			buff[x] = read<char>(NamePoolChunk + 4 + x);
		}

		char* v2 = buff;
		signed int v4 = nameLength;
		uint64_t result;
		unsigned int v5;
		unsigned int v7;
		unsigned int v8;

		v5 = 0;
		result = 22;

		if (v4)
		{
			do
			{
				++v2;
				v7 = v5++ | 0xB000;
				v8 = v7 + result;
				v7 = v8 ^ ~*(BYTE*)(v2 - 1);
				result = v8 >> 2;
				*(BYTE*)(v2 - 1) = v7;
			} while (v5 < v4);
		}
		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else {
		return "";
	}
}


static std::string GetNameFromFName(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = read<uint64_t>(base_address + 0xE0A9E00 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
	if (read<uint16_t>(NamePoolChunk) < 64)
	{
		auto a1 = read<DWORD>(NamePoolChunk + 4);
		return ReadGetNameFromFName(a1);
	}
	else
	{
		return ReadGetNameFromFName(key);
	}
}

DWORD_PTR Uworld;
DWORD_PTR LocalPawn;
DWORD_PTR PlayerState;
DWORD_PTR Localplayer;
DWORD_PTR Rootcomp;
DWORD_PTR PlayerController;
DWORD_PTR Persistentlevel;
uintptr_t PlayerCameraManager;
uintptr_t CurrentWeapon;
Vector3 localactorpos;

uint64_t TargetPawn;
int localplayerID;

RECT GameRect = { NULL };
D3DPRESENT_PARAMETERS d3dpp;

DWORD ScreenCenterX;
DWORD ScreenCenterY;
Vector3 LocalRelativeLocation; struct FBoxSphereBounds
{
	struct Vector3                                     Origin;                                                   // 0x0000(0x0018) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	struct Vector3                                     BoxExtent;                                                // 0x0018(0x0018) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             SphereRadius;                                             // 0x0030(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
};
static void xCreateWindow();
static void xInitD3d();
static void xMainLoop();
static void xShutdown();
static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static HWND Window = NULL;
IDirect3D9Ex* p_Object = NULL;
static LPDIRECT3DDEVICE9 D3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;

DWORD Menuthread(LPVOID in)
{
	while (1)
	{
		if (MouseController::GetAsyncKeyState(VK_INSERT) & 1) {
			ShowMenu = !ShowMenu;
		}
		Sleep(2);
	}
}



Vector3 GetBoneWithRotation(uintptr_t mesh, int bone_id)
{
	uintptr_t bone_array = read<uintptr_t>(mesh + OFFSETS::BoneArray);
	if (bone_array == NULL) bone_array = read<uintptr_t>(mesh + OFFSETS::BoneArray + 0x10);
	FTransform bone = read<FTransform>(bone_array + (bone_id * 0x60));
	FTransform component_to_world = read<FTransform>(mesh + OFFSETS::ComponetToWorld);
	D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), component_to_world.ToMatrixWithScale());
	return Vector3(matrix._41, matrix._42, matrix._43);
}

D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}


struct CamewaDescwipsion
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
};

CamewaDescwipsion GetViewPoint()
{
	CamewaDescwipsion ViewPoint;
	__int64 result; // rax
	__int64 v7; // rcx

	result = read<__int64>(base_address + 0xE2CED18);
	v7 = base_address + 0xE2CECD8;
	if (result)
		v7 = result;

	__int64 EncryptedData[7];
	for (int i = 0; i < 7; i++)
		EncryptedData[i] = read<__int64>(v7 + (i * 0x8));
	EncryptedData[0] ^= 0x4CF1F15DFE2D977Fi64;
	EncryptedData[1] ^= 0x4CF1F15DFE2D977Fi64;
	EncryptedData[2] ^= 0x4EF1F15DFE2D977Fi64;
	EncryptedData[3] ^= 0xAF29A7F813EFC5Ci64;
	EncryptedData[4] ^= 0xAF29A7F813EFC5Ci64;
	EncryptedData[5] ^= 0x4EF29A7E813EFC5Di64;
	EncryptedData[6] ^= 0x4E1772384C14291Fi64;

	ViewPoint.Location = {
		*(double*)(&EncryptedData[1]),
		*(double*)(&EncryptedData[0]),
		*(double*)(&EncryptedData[2])
	};
	ViewPoint.Rotation = {
		*(double*)(&EncryptedData[4]),
		*(double*)(&EncryptedData[3]),
		*(double*)(&EncryptedData[5])
	};
	ViewPoint.FieldOfView = *(float*)(&EncryptedData[6]);

	return ViewPoint;
}


Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	CamewaDescwipsion ViewPoint = GetViewPoint();
	D3DMATRIX tempMatrix = Matrix(ViewPoint.Rotation);
	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector3 vDelta = WorldLocation - ViewPoint.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;
	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}


void DrawStrokeText(int x, int y, const char* str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);

	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), utf_8_2.c_str());
}

float DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}
	return y;
}

void DrawText1(int x, int y, const char* str, RGBA* color)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}

void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

void DrawCircle(int x, int y, int radius, RGBA* color, int segments)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

void DrawBox(float X, float Y, float W, float H, RGBA* color)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}
void DrawFilledRect(int x, int y, int w, int h, ImU32 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}
void DrawNormalBox(int x, int y, int w, int h, int borderPx, ImU32 color)
{

	DrawFilledRect(x + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x + w - w + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h, color); //left 
	DrawFilledRect(x, y + h - h + borderPx * 2, borderPx, h, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w - w + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);//right 
}

ImU32 RGBtoU32(int r, int g, int b)
{
	float fr = (float)r / 255.0;
	float fg = (float)g / 255.0;
	float fb = (float)b / 255.0;

	return ImGui::GetColorU32(ImVec4(fr, fg, fb, 1));
}


void ImLine(int x1, int y1, int x2, int y2, int r, int g, int b, float t)
{
	ImGui::GetWindowDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), RGBtoU32(r, g, b), t);
}


void DrawCornerBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);


	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}


   
	void DrawSkeleton(DWORD_PTR mesh)
	{
		
		Vector3 vHeadBone = GetBoneWithRotation(mesh, 68);
		Vector3 vHip = GetBoneWithRotation(mesh, 7);
		Vector3 vNeck = GetBoneWithRotation(mesh, 67);
		Vector3 vUpperArmLeft = GetBoneWithRotation(mesh, 9);
		Vector3 vUpperArmRight = GetBoneWithRotation(mesh, 38);
		Vector3 vLeftHand = GetBoneWithRotation(mesh, 30);
		Vector3 vRightHand = GetBoneWithRotation(mesh, 58);
		Vector3 vLeftHand1 = GetBoneWithRotation(mesh, 11);
		Vector3 vRightHand1 = GetBoneWithRotation(mesh, 40);
		Vector3 vRightThigh = GetBoneWithRotation(mesh, 78);
		Vector3 vLeftThigh = GetBoneWithRotation(mesh, 71);
		Vector3 vRightCalf = GetBoneWithRotation(mesh, 79);
		Vector3 vLeftCalf = GetBoneWithRotation(mesh, 72);
		Vector3 vLeftFoot = GetBoneWithRotation(mesh, 74);
		Vector3 vRightFoot = GetBoneWithRotation(mesh, 81);
		Vector3 vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
		Vector3 vHipOut = ProjectWorldToScreen(vHip);
		Vector3 vNeckOut = ProjectWorldToScreen(vNeck);
		Vector3 vUpperArmLeftOut = ProjectWorldToScreen(vUpperArmLeft);
		Vector3 vUpperArmRightOut = ProjectWorldToScreen(vUpperArmRight);
		Vector3 vLeftHandOut = ProjectWorldToScreen(vLeftHand);
		Vector3 vRightHandOut = ProjectWorldToScreen(vRightHand);
		Vector3 vLeftHandOut1 = ProjectWorldToScreen(vLeftHand1);
		Vector3 vRightHandOut1 = ProjectWorldToScreen(vRightHand1);
		Vector3 vRightThighOut = ProjectWorldToScreen(vRightThigh);
		Vector3 vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
		Vector3 vRightCalfOut = ProjectWorldToScreen(vRightCalf);
		Vector3 vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
		Vector3 vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
		Vector3 vRightFootOut = ProjectWorldToScreen(vRightFoot);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vHipOut.x, vHipOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vLeftHandOut1.x, vLeftHandOut1.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vRightHandOut1.x, vRightHandOut1.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImVec2(vHipOut.x, vHipOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightThighOut.x, vRightThighOut.y), ImVec2(vHipOut.x, vHipOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImVec2(vRightThighOut.x, vRightThighOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftFootOut.x, vLeftFootOut.y), ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightFootOut.x, vRightFootOut.y), ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImColor(0.92f, 0.10f, 0.14f), 2.0f);
	}



typedef struct _FNlEntity
{
	uint64_t Actor;
	int ID;
	uint64_t mesh;
}FNlEntity;

std::vector<FNlEntity> entityList;


struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

static std::uint32_t _GetProcessId(std::string process_name) {
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return 0;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE) {
		if (process_name.compare(processentry.szExeFile) == 0)
			return processentry.th32ProcessID;
	}
	return 0;
}

void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}
void ReverseStealth()
{
	HWND ReverseStealth;
	AllocConsole();
	ReverseStealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(ReverseStealth, 5);
}

int main(int argc, const char* argv[])
{


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls



	io.IniFilename = nullptr;

	static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
	ImFontConfig icons_config;

	ImFontConfig CustomFont;
	CustomFont.FontDataOwnedByAtlas = false;


	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 2.5;
	icons_config.OversampleV = 2.5;

	io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 21.f, &CustomFont);
	io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &icons_config, icons_ranges);
	io.Fonts->AddFontDefault();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();







	//SetConsoleTitleA(skCrypt("Loader"));
	//std::cout << skCrypt("\n\n Connecting..");
	//system("cls");
	//KeyAuthApp.init();
	//if (!KeyAuthApp.data.success)
	//{
	//	std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
	//	Sleep(1500);
	//	exit(0);
	//}

	/*
		Optional - check if HWID or IP blacklisted

	if (KeyAuthApp.checkblack()) {
		abort();
	}
	*/



	//std::cout << skCrypt("\n\n[1] Login\n[2] Register\n\n\n Choose option: ");

	//int option;
	//std::string username;
	//std::string password;
	//std::string key;

	//std::cin >> option;
	//switch (option)
	//{
	//case 1:
	//	std::cout << skCrypt("\n\n Enter username: ");
	//	std::cin >> username;
	//	std::cout << skCrypt("\n Enter password: ");
	//	std::cin >> password;
	//	KeyAuthApp.login(username, password);
	//	break;
	//case 2:
	//	std::cout << skCrypt("\n\n Enter username: ");
	//	std::cin >> username;
	//	std::cout << skCrypt("\n Enter password: ");
	//	std::cin >> password;
	//	std::cout << skCrypt("\n Enter license: ");
	//	std::cin >> key;
	//	KeyAuthApp.regstr(username, password, key);
	//	break;

	//default:
	//	std::cout << skCrypt("\n\n Status: Failure: Invalid Selection");
	//	Sleep(3000);
	//	exit(0);
	//}

	//if (!KeyAuthApp.data.success)
	//{
	//	std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;

	//	Sleep(1500);
	//	exit(0);

	//}
	system("cls");
	menu_:
	int choice;
	system("color 3");
	printf("Loading");

	//if (CheckKey() == true) {
	//	//std::cout << "OK!" << std::endl;

	//}
	//else
	//{
	//	exit(0);
	//	return 0;
	//}
	Sleep(500);

	system("cls");
	SetConsoleTitleA("fortnite fps booster fr");
	printf("\n   MadFN Updated By SoarCheast#1337 & nikko#5550\n");
	
	printf(("\n [1] Load Cheat\n [2] Load Driver\n  \n\n > "));
	std::cin >> choice;
	switch (choice) {
	case 1:
		break;
	case 2:
		system(("cls"));
		//yes i use links for free shit stop crying
		system(("curl --silent https://cdn.discordapp.com/attachments/1151207422816424047/1151207448074522715/mapper.exe --output C:\\Windows\\System32\\Vanguardmapper.exe >nul 2>&1"));
		system(("curl --silent https://cdn.discordapp.com/attachments/1151207422816424047/1151207447491526686/driver.sys --output C:\\Windows\\System32\\Windows10Help.sys >nul 2>&1"));
		system(("cls"));
		system(("cd C:\\Windows\\System32\\"));
		system(("C:\\Windows\\System32\\Vanguardmapper.exe C:\\Windows\\System32\\Windows10Help.sys"));
		std::remove(("C:\\Windows\\System32\\Vanguardmapper.exe"));
		std::remove(("C:\\Windows\\System32\\Windows10Help.sys"));
		system("cls");
		MessageBoxA(NULL, "Loaded", "MadFN ", MB_OK);
		goto menu_;
		break;

	}

	MouseController::Init();
	CreateThread(NULL, NULL, Menuthread, NULL, NULL, NULL);
	//AttachDriver();
	system("cls");
	printf("Loaded");
	printf(skCrypt(" Waiting for Fortnite..."));
	MessageBox(NULL, skCrypt("Click OK In Lobby"), skCrypt("Information"), NULL);
	hwnd = FindWindowA(0, "Fortnite  ");
	processID = _GetProcessId("FortniteClient-Win64-Shipping.exe");
	std::cout << skCrypt("\n");

	printf(skCrypt(" "));
	GetWindowThreadProcessId(hwnd, &processID);
	Sleep(200);
	if (driver->Init(FALSE)) {
		driver->Attach(processID);
		base_address = driver->GetModuleBase(L"FortniteClient-Win64-Shipping.exe");
	};
	printf(skCrypt(" "));
	printf("[ MadFn ] Fortnites Id Base Is: %p", (void*)base_address);
	xCreateWindow();
	xInitD3d();
	xMainLoop();
	xShutdown();

	return(0);

}






void SetWindowToTarget()
{
	while (true)
	{
		if (hwnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(hwnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);

			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(Window, GameRect.left, GameRect.top, Width, Height, true);
		}
		else
		{
			exit(0);
		}
	}
}

const MARGINS Margin = { -1 };

void xCreateWindow()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	WNDCLASS windowClass = { 0 };
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hInstance = NULL;
	windowClass.lpfnWndProc = WinProc;
	windowClass.lpszClassName = "soarwazhere";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClass(&windowClass))
		std::cout << "\n\n [-] overlay failed";

	Window = CreateWindow("soarwazhere",
		"SoarCheats#1337",
		WS_POPUP,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		NULL,
		NULL);

	ShowWindow(Window, SW_SHOW);

	DwmExtendFrameIntoClientArea(Window, &Margin);
	SetWindowLong(Window, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	UpdateWindow(Window);
}






//Credits to loltf where i pasted this from lmao
// 
//all calculations 
Vector3 CalculateNewRotation(Vector3& zaz, Vector3& daz)
{
	Vector3 dalte = zaz - daz;
	Vector3 ongle;
	float hpm = sqrtf(dalte.x * dalte.x + dalte.y * dalte.y);
	ongle.y = atan(dalte.y / dalte.x) * 57.295779513082f;
	ongle.x = (atan(dalte.z / hpm) * 57.295779513082f) * -1.f;
	if (dalte.x >= 0.f) ongle.y += 180.f;
	return ongle;
}

void normalize(Vector3& in)
{
	if (in.x > 89.f) in.x -= 360.f;
	else if (in.x < -89.f) in.x += 360.f;

	while (in.y > 180)in.y -= 360;
	while (in.y < -180)in.y += 360;
	in.z = 0;
}

void RadarRange(float* x, float* y, float range)
{
	if (fabs((*x)) > range || fabs((*y)) > range)
	{
		if ((*y) > (*x))
		{
			if ((*y) > -(*x))
			{
				(*x) = range * (*x) / (*y);
				(*y) = range;
			}
			else
			{
				(*y) = -range * (*y) / (*x);
				(*x) = -range;
			}
		}
		else
		{
			if ((*y) > -(*x))
			{
				(*y) = range * (*y) / (*x);
				(*x) = range;
			}
			else
			{
				(*x) = -range * (*x) / (*y);
				(*y) = -range;
			}
		}
	}
}

void CalcRadarPoint(Vector3 vOrigin, int& screenx, int& screeny)
{
	CamewaDescwipsion vCamera = GetViewPoint();
	Vector3 vAngle = vCamera.Rotation;
	auto fYaw = vAngle.y * M_PI / 180.0f;
	float dx = vOrigin.x - vCamera.Location.x;
	float dy = vOrigin.y - vCamera.Location.y;

	float fsin_yaw = sinf(fYaw);
	float fminus_cos_yaw = -cosf(fYaw);
	
	float x = dy * fminus_cos_yaw + dx * fsin_yaw;
	x = -x;
	float y = dx * fminus_cos_yaw - dy * fsin_yaw;

	float range = (float)RadarDistance * 100.f;

	RadarRange(&x, &y, range);

	ImVec2 DrawPos = ImVec2(radar_position_x, radar_position_y);
	ImVec2 DrawSize = ImVec2(radar_size, radar_size);

	int rad_x = (int)DrawPos.x;
	int rad_y = (int)DrawPos.y;

	float r_siz_x = DrawSize.x;
	float r_siz_y = DrawSize.y;

	int x_max = (int)r_siz_x + rad_x - 5;
	int y_max = (int)r_siz_y + rad_y - 5;

	screenx = rad_x + ((int)r_siz_x / 2 + int(x / range * r_siz_x));
	screeny = rad_y + ((int)r_siz_y / 2 + int(y / range * r_siz_y));

	if (screenx > x_max)
		screenx = x_max;

	if (screenx < rad_x)
		screenx = rad_x;

	if (screeny > y_max)
		screeny = y_max;

	if (screeny < rad_y)
		screeny = rad_y;
}

void fortnite_radar(float x, float y, float size, bool rect)
{
	//if (radar)
	//{
	//	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
	//	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);
	//	static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
	//	ImGui::Begin(("##radar"), nullptr, flags);

	//	float render_size = 5;
	//	ImDrawList* drawList = ImGui::GetWindowDrawList();

	//	if (rect) {
	//		drawList->AddRectFilled(ImVec2(x, y), ImVec2(x + size, y + size), ImGui::GetColorU32({ 0.13f, 0.13f, 0.13f, 1.f }), 0.0f, 0);
	//		drawList->AddRect(ImVec2(x, y), ImVec2(x + size, y + size), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.0f, 0, 1.0f);
	//	}
	//	else {
	//		drawList->AddRectFilled(ImVec2(x, y), ImVec2(x + size, y + size), ImGui::GetColorU32({ 0.13f, 0.13f, 0.13f, 1.f }), 0.0f, 50);
	//		drawList->AddCircleFilled(ImVec2(x + size / 2, y + size / 2), render_size / 2 * sqrt(2), ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f }), 1000);
	//		drawList->AddRect(ImVec2(x, y), ImVec2(x + size, y + size), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.0f, 0, 1.0f);
	//	}

	//	ImGui::End();
	//}
}

void add_players_radar(Vector3 WorldLocation)
{
	//if (radar)
	//{
	//	static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
	//	ImGui::Begin(("##radar"), nullptr, flags);

	//	int ScreenX, ScreenY = 0;
	//	const auto& GetWindowDrawList = ImGui::GetWindowDrawList();
	//	ImDrawList* drawList = ImGui::GetWindowDrawList();

	//	CalcRadarPoint(WorldLocation, ScreenX, ScreenY);
	//	if (rect_radar) drawList->AddRectFilled(ImVec2((float)ScreenX - 4.5, (float)ScreenY - 4.5), ImVec2((float)ScreenX + 4.5, (float)ScreenY + 4.5), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }));
	//	else drawList->AddCircleFilled(ImVec2(ScreenX, ScreenY), 5, ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 12);

	//	ImGui::End();
	//}
}


void xInitD3d()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = Window;
	d3dpp.Windowed = TRUE;

	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	io.IniFilename = NULL;

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(D3dDevice);

	ImGui::StyleColorsDark();
	/*ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 0.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 0.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 0.0f;*/

	/*style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_TextDisabled] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_ChildWindowBg] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PopupBg] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_Border] = ImColor(255, 0, 255, 255);
	style->Colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_FrameBg] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(90, 90, 90, 255);
	style->Colors[ImGuiCol_TitleBg] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_MenuBarBg] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(100, 100, 100, 255);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(60, 60, 60, 255);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(80, 80, 80, 255);
	style->Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 255, 255);
	style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 255, 255);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_Button] = ImColor(50, 50, 50, 0);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
	style->Colors[ImGuiCol_Header] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_Column] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ColumnHovered] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ColumnActive] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ResizeGrip] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ResizeGripActive] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotLines] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotHistogram] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImColor(255, 255, 255, 255);*/

	

	XorS(font, "C:\\Windows\\Fonts\\verdanab.ttf");
	m_pFont = io.Fonts->AddFontFromFileTTF(font.decrypt(), 14.0f, nullptr, io.Fonts->GetGlyphRangesDefault());

}

























void aimbot(float x, float y)
{
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	int AimSpeed = smooth;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	return;
}
void AimAt(DWORD_PTR entity)
{
	uint64_t currentactormesh = read<uint64_t>(entity + OFFSETS::Mesh);
	auto rootHead = GetBoneWithRotation(currentactormesh, hitbox);
	Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

	if (rootHeadOut.y != 0 || rootHeadOut.y != 0)
	{
		aimbot(rootHeadOut.x, rootHeadOut.y);
	}
}
bool isVisible(uint64_t mesh)
{
	float bing = read<float>(mesh + OFFSETS::LastSubmitTime);
	float bong = read<float>(mesh + OFFSETS::LastRenderTimeOnScreen);
	const float tick = 0.06f;
	return bong + tick >= bing;
}
static auto DrawCircleFilled(int x, int y, int radius, RGBA* color) -> void
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}
namespace cumera
{
	Vector3 Location;
};
double GetCrossDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
void OutlinedText(int x, int y, ImColor Color, const char* text)
{
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), Color, text);
}

void DrawESP() {
	/*if (fovcircle) {

		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(AimFOV), ImColor(0, 0, 0), 100.0f, 1.5f);

	}*/


	
	if (fovcircle)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(Width / 2, Height / 2), float(AimFOV), ImColor(red, green, blue, 255), segments);
		//ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX - AimFOV, ScreenCenterY - AimFOV), ImColor(red, green, blue, 255), segments, 1.0f);
	}
	
	if (Filledfov)
	{
		ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Width / 2, Height / 2), float(AimFOV), ImColor(0, 0, 0, darkness), segments);
	}
	if (Lcrosshair)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2.01f - 14, Height / 2), ImVec2(Width / 2.01f + 1, Height / 2), ImColor(255, 255, 255, 255), 0.5f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 1.99f + 14, Height / 2), ImVec2(Width / 1.99f + 1, Height / 2), ImColor(255, 255, 255, 255), 0.5f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2.01f - 14), ImVec2(Width / 2, Height / 2.01f), ImColor(255, 255, 255, 255), 0.5f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 1.99f + 14), ImVec2(Width / 2, Height / 1.99f), ImColor(255, 255, 255, 255), 0.5f);
	}

	/*if (squarefov)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(1920 / 2, 1080 / 2), AimFOV, ImColor(red, green, blue), 0, 4, 1);
	}*/

	if (squarefov) {
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(ScreenCenterX - AimFOV, ScreenCenterY - AimFOV), ImVec2(ScreenCenterX + AimFOV, ScreenCenterY + AimFOV), ImColor(red, green, blue));
	}


	


	if (hitboxpos == 0)
	{
		hitbox = 68; //head
	}
	else if (hitboxpos == 1)
	{
		hitbox = 67; //neck
	}
	else if (hitboxpos == 2)
	{
		hitbox = 7; //chest
	}
	else if (hitboxpos == 3)
	{
		hitbox = 2; //pelvis
	}
	switch (aimkeypos) {
	case 0:
		aimkey = 0x01;//left mouse button
		break;
	case 1:
		aimkey = 0x02;//right mouse button
		break;
	case 2:
		aimkey = 0x04;//middle mouse button
		break;
	case 3:
		aimkey = 0x05;//x1 mouse button
		break;
	case 4:
		aimkey = 0x06;//x2 mouse button
		break;
	case 5:
		aimkey = 0x03;//control break processing
		break;
	case 6:
		aimkey = 0x08;//backspace
		break;
	case 7:
		aimkey = 0x09;//tab
		break;
	case 8:
		aimkey = 0x0c;//clear
		break;
	case 9:
		aimkey == 0x0D;//enter
		break;
	case 10:
		aimkey = 0x10;//shift
		break;
	case 11:
		aimkey = 0x11;//ctrl
		break;
	case 12:
		aimkey == 0x12;//alt
		break;
	case 13:
		aimkey == 0x14;//caps lock
		break;
	case 14:
		aimkey == 0x1B;//esc
		break;
	case 15:
		aimkey == 0x20;//space
		break;
	case 16:
		aimkey == 0x30;//0
		break;
	case 17:
		aimkey == 0x31;//1
		break;
	case 18:
		aimkey == 0x32;//2
		break;
	case 19:
		aimkey == 0x33;//3
		break;
	case 20:
		aimkey == 0x34;//4
		break;
	case 21:
		aimkey == 0x35;//5
		break;
	case 22:
		aimkey == 0x36;//6
		break;
	case 23:
		aimkey == 0x37;//7
		break;
	case 24:
		aimkey == 0x38;//8
		break;
	case 25:
		aimkey == 0x39;//9
		break;
	case 26:
		aimkey == 0x41;//a
		break;
	case 27:
		aimkey == 0x42;//b
		break;
	case 28:
		aimkey == 0x43;//c
		break;
	case 29:
		aimkey == 0x44;//d
		break;
	case 30:
		aimkey == 0x45;//e
		break;
	case 31:
		aimkey == 0x46;//f
		break;
	case 32:
		aimkey == 0x47;//g
		break;
	case 33:
		aimkey == 0x48;//h
		break;
	case 34:
		aimkey == 0x49;//i
		break;
	case 35:
		aimkey == 0x4A;//j
		break;
	case 36:
		aimkey == 0x4B;//k
		break;
	case 37:
		aimkey == 0x4C;//L
		break;
	case 38:
		aimkey == 0x4D;//m
		break;
	case 39:
		aimkey == 0x4E;//n
		break;
	case 40:
		aimkey == 0x4F;//o
		break;
	case 41:
		aimkey == 0x50;//p
		break;
	case 42:
		aimkey == 0x51;//q
		break;
	case 43:
		aimkey == 0x52;//r
		break;
	case 44:
		aimkey == 0x53;//s
		break;
	case 45:
		aimkey == 0x54;//t
		break;
	case 46:
		aimkey == 0x55;//u
		break;
	case 47:
		aimkey == 0x56;//v
		break;
	case 48:
		aimkey == 0x57;//w
		break;
	case 49:
		aimkey == 0x58;//x
		break;
	case 50:
		aimkey == 0x59;//y
		break;
	case 51:
		aimkey == 0x5A;//z
		break;
	case 52:
		aimkey == 0x60;//numpad 0
		break;
	case 53:
		aimkey == 0x61;//numpad 1
		break;
	case 54:
		aimkey == 0x62;//numpad 2
		break;
	case 55:
		aimkey == 0x63;//numpad 3
		break;
	case 56:
		aimkey == 0x64;//numpad 4
		break;
	case 57:
		aimkey == 0x65;//numpad 5
		break;
	case 58:
		aimkey == 0x66;//numpad 6
		break;
	case 59:
		aimkey == 0x67;//numpad 7
		break;
	case 60:
		aimkey == 0x68;//numpad 8
		break;
	case 61:
		aimkey == 0x69;//numpad 9
		break;
	case 62:
		aimkey == 0x6A;//multiply
		break;
	}
	auto entityListCopy = entityList;
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;
	Uworld = read<DWORD_PTR>(base_address + GWorld);
	DWORD_PTR Gameinstance = read<DWORD_PTR>(Uworld + OFFSETS::Gameinstance);
	DWORD_PTR LocalPlayers = read<DWORD_PTR>(Gameinstance + OFFSETS::LocalPlayers);
	Localplayer = read<DWORD_PTR>(LocalPlayers);
	PlayerController = read<DWORD_PTR>(Localplayer + OFFSETS::PlayerController);
	LocalPawn = read<DWORD_PTR>(PlayerController + OFFSETS::LocalPawn);

	PlayerState = read<DWORD_PTR>(LocalPawn + OFFSETS::PlayerState);
	Rootcomp = read<DWORD_PTR>(LocalPawn + OFFSETS::RootComponet);
	Persistentlevel = read<DWORD_PTR>(Uworld + OFFSETS::PersistentLevel);
	DWORD ActorCount = read<DWORD>(Persistentlevel + OFFSETS::ActorCount);
	DWORD_PTR AActors = read<DWORD_PTR>(Persistentlevel + OFFSETS::AActor);
	CamewaDescwipsion ViewPoint;
	for (int i = 0; i < ActorCount; i++)
	{
		uint64_t CurrentActor = read<uint64_t>(AActors + i * OFFSETS::CurrentActor);
		uint64_t CurrentActorMesh = read<uint64_t>(CurrentActor + OFFSETS::Mesh);
		if (read<float>(CurrentActor + OFFSETS::Revivefromdbnotime) != 10) continue;//changes by 10 every updated and it is importen/

		int MyTeamId = read<int>(PlayerState + OFFSETS::TeamId);
		DWORD64 otherPlayerState = read<uint64_t>(CurrentActor + OFFSETS::PlayerState);
		int ActorTeamId = read<int>(otherPlayerState + OFFSETS::ActorTeamId);

		if (MyTeamId == ActorTeamId) continue;
		if (CurrentActor == LocalPawn) continue;

		Vector3 Headpos = GetBoneWithRotation(CurrentActorMesh, 109);
		localactorpos = read<Vector3>(Rootcomp + OFFSETS::LocalActorPos);

		float distance = localactorpos.Distance(ViewPoint.Location) / 100.f;

		Vector3 bone0 = GetBoneWithRotation(CurrentActorMesh, 0);
		Vector3 bottom = ProjectWorldToScreen(bone0);
		Vector3 Headbox = ProjectWorldToScreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15));
		Vector3 w2shead = ProjectWorldToScreen(Headpos);
		auto player_screen = ProjectWorldToScreen(bone0);
		float BoxHeight = (float)(Headbox.y - bottom.y);
		float BoxWidth = BoxHeight * 0.380f;

		float LeftX = (float)Headbox.x - (BoxWidth / 1);
		float LeftY = (float)bottom.y;
		//Paste made by nigger
		float CornerHeight = abs(Headbox.y - bottom.y);
		float CornerWidth = CornerHeight * 0.550;

		if (aiminair)
		{
			write(LocalPawn + 0x4a05, true);
		}

		float boatmulti = 1.0f;
		float boatspeed = 1.0f;

		//if (g_boatspeed)
		//{
		//	uint64_t Vehicle = read<uint64_t>(g_pid, LocalPawn + 0x2260); //FortPlayerPawn::CurrentVehicle
		//	write<float>(g_pid, Vehicle + 0xca4, boatmulti);//multiplier run     AFortAthenaVehicle::CachedSpeed
		//	write<float>(g_pid, Vehicle + 0x908, boatmulti);//multiplier run     AFortAthenaVehicle::TopSpeedCurrentMultiplier
		//    write<float>(g_pid, Vehicle + 0x90c, boatmulti);//multiplier run     AFortAthenaVehicle::PushForceCurrentMultiplier
		//	write<float>(g_pid, Vehicle + 0x79c, boatspeed);//just speed         AFortAthenaVehicle::WaterEffectsVehicleMaxSpeedKmh
		//}

		int while_rotating;
		if (Spinbot)
		{

			if (GetAsyncKeyState(VK_RBUTTON))
			{
				while_rotating = true;

				if (LocalPawn)
				{
					uint64_t MeshA = read<uint64_t>(LocalPawn + 0x310);
					write<Vector3>(MeshA + 0x140, Vector3(1, 5, 1));
				}
			}
			else if (!GetAsyncKeyState(VK_RBUTTON))
			{
				if (LocalPawn)
				{
					if (while_rotating)
					{
						uint64_t MeshA = read<uint64_t>(LocalPawn + 0x310);
						write<Vector3>(MeshA + 0x140, Vector3(0, -90, 0));
						while_rotating = false;
					}
				}
			}
		}

		/*if (distance < VisDist)
		{*/
			if (Esp)
			{
				if (Esp_box)
				{
					if (isVisible(CurrentActorMesh)) {
						ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(Headbox.x - (CornerWidth / 2), Headbox.y), ImVec2(bottom.x + (CornerWidth / 2), bottom.y), ImColor(0, 0, 0, 175), 0.75f);
						//	DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, IM_COL32(255, 0, 0, 255), 1.5);

					}
					else if (!isVisible(CurrentActorMesh)) {
						//DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, IM_COL32(255, 255, 255, 255), 1.5);
						ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(Headbox.x - (CornerWidth / 2), Headbox.y), ImVec2(bottom.x + (CornerWidth / 2), bottom.y), ImColor(0, 0, 0, 175), 0.75f);
					}

				}

				



				if (skeletonesp)
				{
					
					Vector3 vHeadBone = GetBoneWithRotation(CurrentActorMesh, 109);
					Vector3 vHip = GetBoneWithRotation(CurrentActorMesh, 7);
					Vector3 vNeck = GetBoneWithRotation(CurrentActorMesh, 67);
					Vector3 vUpperArmLeft = GetBoneWithRotation(CurrentActorMesh, 9);
					Vector3 vUpperArmRight = GetBoneWithRotation(CurrentActorMesh, 38);
					Vector3 vLeftHand = GetBoneWithRotation(CurrentActorMesh, 30);
					Vector3 vRightHand = GetBoneWithRotation(CurrentActorMesh, 58);
					Vector3 vLeftHand1 = GetBoneWithRotation(CurrentActorMesh, 11);
					Vector3 vRightHand1 = GetBoneWithRotation(CurrentActorMesh, 40);
					Vector3 vRightThigh = GetBoneWithRotation(CurrentActorMesh, 78);
					Vector3 vLeftThigh = GetBoneWithRotation(CurrentActorMesh, 71);
					Vector3 vRightCalf = GetBoneWithRotation(CurrentActorMesh, 79);
					Vector3 vLeftCalf = GetBoneWithRotation(CurrentActorMesh, 72);
					Vector3 vLeftFoot = GetBoneWithRotation(CurrentActorMesh, 74);
					Vector3 vRightFoot = GetBoneWithRotation(CurrentActorMesh, 81);
					Vector3 vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
					Vector3 vHipOut = ProjectWorldToScreen(vHip);
					Vector3 vNeckOut = ProjectWorldToScreen(vNeck);
					Vector3 vUpperArmLeftOut = ProjectWorldToScreen(vUpperArmLeft);
					Vector3 vUpperArmRightOut = ProjectWorldToScreen(vUpperArmRight);
					Vector3 vLeftHandOut = ProjectWorldToScreen(vLeftHand);
					Vector3 vRightHandOut = ProjectWorldToScreen(vRightHand);
					Vector3 vLeftHandOut1 = ProjectWorldToScreen(vLeftHand1);
					Vector3 vRightHandOut1 = ProjectWorldToScreen(vRightHand1);
					Vector3 vRightThighOut = ProjectWorldToScreen(vRightThigh);
					Vector3 vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
					Vector3 vRightCalfOut = ProjectWorldToScreen(vRightCalf);
					Vector3 vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
					Vector3 vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
					Vector3 vRightFootOut = ProjectWorldToScreen(vRightFoot);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vHipOut.x, vHipOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vLeftHandOut1.x, vLeftHandOut1.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vRightHandOut1.x, vRightHandOut1.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImVec2(vHipOut.x, vHipOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightThighOut.x, vRightThighOut.y), ImVec2(vHipOut.x, vHipOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImVec2(vRightThighOut.x, vRightThighOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vLeftFootOut.x, vLeftFootOut.y), ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(vRightFootOut.x, vRightFootOut.y), ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImColor(1.0f, 1.0f, 1.0f), 2.0f);
				}
				
				
				if (radar)
				{
					fortnite_radar(radar_position_x, radar_position_y, radar_size, rect_radar);
				}

				if (distanceesp)
				{

					if (isVisible(CurrentActorMesh)) {
						XorS(dst, "[%.fm]\n");
						char dist[64];
						sprintf_s(dist, dst.decrypt(), distance);
						DrawOutlinedText(m_pFont, dist, ImVec2(Headbox.x, Headbox.y - 35), 17.0f, ImColor(red, green, blue), true);
					}
					else if (!isVisible(CurrentActorMesh)) {
						XorS(dst, "[%.fm]\n");
						char dist[64];
						sprintf_s(dist, dst.decrypt(), distance);
						DrawOutlinedText(m_pFont, dist, ImVec2(Headbox.x, Headbox.y - 35), 17.0f, ImColor(red, green, blue), true);
					}
				}
				

				
					


					if (cornerbox)
					{
						if (isVisible(CurrentActorMesh)) {
							DrawCornerBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, ImColor(red, green, blue), 2.5);
						}
						else if (!isVisible(CurrentActorMesh)) {
							DrawCornerBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, ImColor(red, green, blue), 2.5);
						}
					}
				

				if (sdesp)
				{
					if (isVisible)
						DrawNormalBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, 2.5, ImColor(red, green, blue));
					else
						DrawNormalBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, 2.5, ImColor(red, green, blue));
				}
				

				if (Esp_line)
				{
					DrawLine(Width / 2, Height, bottom.x, bottom.y, &Col.blue, 2.0);
					//DrawLine(ImVec2(Width / 2, Height - Height), ImVec2(bottom.x, bottom.y), ImColor(red, green, blue), 0.5);
				}

				
			}
		//}

		auto dx = w2shead.x - (Width / 2);
		auto dy = w2shead.y - (Height / 2);
		auto dist = sqrtf(dx * dx + dy * dy);


		if (isVisible(CurrentActorMesh)) {

			if (dist < AimFOV && dist < closestDistance) {
				closestDistance = dist;
				closestPawn = CurrentActor;

			}
		}
	}

	if (Aimbot)
	{
		if (Aimbot && closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0) {
			AimAt(closestPawn);
		}
	}

	if (radar)
	{
		fortnite_radar(radar_position_x, radar_position_y, radar_size, rect_radar);
	}
}




//Pasta made by nugga
void render() {


	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	
	DrawESP();

	
	
	//char name[64];

	if (ShowMenu)
	{

		if (particles)
		{
			static float f = 0.2f;
			static int counter = 0;



			//things you need for the background part
			ImGuiStyle& style = ImGui::GetStyle();

			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(3000, 3000));
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
			ImGui::Begin("##bg", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
			{
				//proper draw call
				draw = ImGui::GetWindowDrawList();

				ImVec2 screenSize = ImGui::GetIO().DisplaySize;
				ImGui::Particles(draw, screenSize); // it's important to define this in imgui_widgets.cpp otherwise it wouldn't work properly

			}ImGui::End();
			ImGui::PopStyleColor();
		}
		
		//background part end
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 1;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(31, 31, 31, 255)));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(ImColor(red, green, blue)));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(24, 24, 24, 255)));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(ImColor(red, green, blue)));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(ImColor(red, green, blue)));








		ImGui::SetNextWindowSize(ImVec2(650, 450.000f), ImGuiCond_Once);
		ImGui::Begin("bruh", NULL, 11);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 0, 24, 0)));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(255, 0, 24, 255)));

		//ImGui::Text("Flux [INSERT]");
		ImGui::SameLine();
		ImGui::SetCursorPosX(625);
		ImGui::SetCursorPosY(5);
		if (ImGui::Button("X", ImVec2(20, 20)))
		{
			ExitProcess(0);
		}
		ImGui::PopStyleColor(2);
		ImGui::SetCursorPos(ImVec2(0, 30));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(27, 27, 27, 255)));
		ImGui::BeginChild("##Undertitlebar", ImVec2(650, 415), false);
		ImGui::PopStyleColor();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("##categories", ImVec2(170, 405), false);

		if (ImGui::Button("Aimbot", ImVec2(165, 40)))
		{
			tabb = 1;
		}

		if (ImGui::Button("Visuals", ImVec2(165, 40)))
		{
			tabb = 2;
		}

		if (ImGui::Button("Exploits", ImVec2(165, 40)))
		{
			tabb = 3;
		}

		if (ImGui::Button("Settings", ImVec2(165, 40)))
		{
			tabb = 4;
		}
		
		/*ImGui::SetCursorPosY(370);
		ImGui::SetCursorPosX(60);
		ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(ImColor(red, green, blue)), (KeyAuthApp.data.username.c_str()));*/


		if (tabb == 1)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));


			ImGui::SetCursorPos(ImVec2(2, 0));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));


			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 2)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 45));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 3)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 90));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 4)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 130));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		// BOTTOM BAR BELOW TAB BUTTONS


		ImGui::EndChild();


		if (tabb == 1)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);
			ImGui::Text("Aimbot");
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Aimbot", &Aimbot);
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Checkbox("Square Fov", &squarefov))
			{
				fovcircle = false;
				Filledfov = false;
			}
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Checkbox("Circle Fov", &fovcircle))
			{
				squarefov = false;
			}
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Checkbox("Circle filled Fov", &Filledfov))
			{
				squarefov = false;
				fovcircle = true;
			}
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Crosshair", &Lcrosshair);
			ImGui::PopStyleColor();

			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(220, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Aimbot Config", 1, true);
			

			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Smooth", &smooth, 1, 10);
			
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Fov Size", &AimFOV, 30, 600);
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Text(("Aimkey:"));
			ImGui::SameLine();
			HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
			

			

			ImGui::EndChild();
			ImGui::PopStyleColor();

		}


		if (tabb == 2)
		{
		
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);
 
			ImGui::Text("Visuals", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("2D Box Esp", &sdesp);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Corner Box Esp", &cornerbox);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Box Filled Esp", &Esp_box);
			ImGui::Spacing();
			ImGui::Spacing();
			//ImGui::Checkbox("Skeleton Esp", &skeletonesp);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Snapline Esp", &Esp_line);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Distance Esp", &distanceesp);

			ImGui::PopStyleColor();

			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Visual Settings", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Visual Distance", &VisDist, 30, 300);
			ImGui::EndChild();
			ImGui::PopStyleColor();

		}



		

		if (tabb == 4)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);

			ImGui::Text("Settings", 1, true);
			ImGui::Separator();
			ImGui::Checkbox("BackGroud Particles", &particles);
			ImGui::PopStyleColor();

			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Color Settings", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Red", &red, 0, 255);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Green", &green, 0, 255);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Blue", &blue, 0, 255);
			
			ImGui::EndChild();
			ImGui::PopStyleColor();

		}




		ImGui::EndChild();
		ImGui::End();
	}

		


	

	DrawESP();

	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

MSG Message = { NULL };
int Loop = 0;
void xMainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = NULL;
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos(Window, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(Window);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		xShutdown();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			d3dpp.BackBufferWidth = LOWORD(lParam);
			d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = D3dDevice->Reset(&d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void xShutdown()
{
	TriBuf->Release();
	D3dDevice->Release();
	p_Object->Release();

	DestroyWindow(Window);
	UnregisterClass("soarwazhere", NULL);
}
