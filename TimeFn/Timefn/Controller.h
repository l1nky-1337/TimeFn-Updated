
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <winternl.h>
#include <atomic>
#include <mutex>
#include <TlHelp32.h>

#include <dwmapi.h>
#include <xmmintrin.h>
#include <array>
#include <vector>

#include <cstdlib>
#include <random>
#include <direct.h>
#include <fstream>
#include <string>
#include <sstream>


#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "dwmapi.lib")

#include <XInput.h>
#pragma comment(lib, "XInput.lib")

namespace Controller
{
    class XboxController
    {
    private:
        XINPUT_STATE _controllerState;
        int _controllerNum;
    public:
        XboxController(int playerNumber);
        XINPUT_STATE GetControllerState();
        bool CheckConnection();
    };

    XboxController::XboxController(int playerNumber)
    {
        // Set the Controller Number
        _controllerNum = playerNumber - 1;
    }

    XINPUT_STATE XboxController::GetControllerState()
    {
        // Zeroise the state
        RtlSecureZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

        // Get the state
        XInputGetState(_controllerNum, &_controllerState);

        return _controllerState;
    }

    bool XboxController::CheckConnection()
    {
        // Zeroise the state
        RtlSecureZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

        // Get the state
        DWORD Result = XInputGetState(_controllerNum, &_controllerState);

        if (Result == ERROR_SUCCESS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}



