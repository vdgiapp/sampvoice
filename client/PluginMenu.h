/*
    This is a SampVoice project file
    Developer: CyberMor <cyber.mor.2020@gmail.ru>

    See more here https://github.com/CyberMor/sampvoice

    Copyright (c) Daniel (CyberMor) 2020 All rights reserved
*/

#pragma once

#include <array>

#include <Windows.h>
#include <d3d9.h>

#include <imgui/imgui.h>
#include <util/Memory.hpp>
#include <util/Resource.h>
#include <util/AddressesBase.h>
#include <util/BlurEffect.h>
#include <util/Texture.h>
#include <util/Render.h>

#include "../common/common.h"

#if !defined(SAMP_VN) && !defined(SAMP_EN)
#define SAMP_EN
#endif

class PluginMenu {

    PluginMenu() = delete;
    ~PluginMenu() = delete;
    PluginMenu(const PluginMenu&) = delete;
    PluginMenu(PluginMenu&&) = delete;
    PluginMenu& operator=(const PluginMenu&) = delete;
    PluginMenu& operator=(PluginMenu&&) = delete;

private:

#if defined(SAMP_VN)
    static constexpr auto kTitleText = "Cài đặt voice chat";
    static constexpr auto kTab1TitleText = "Chung";
    static constexpr auto kTab1Desc1TitleText = "Âm thanh";
    static constexpr auto kTab1Desc1EnableSoundText = "Bật tiếng";
    static constexpr auto kTab1Desc1VolumeSoundText = "Âm lượng";
    static constexpr auto kTab1Desc2TitleText = "Hiệu ứng";
    static constexpr auto kTab1Desc2BalancerText = "Cân bằng âm thanh";
    static constexpr auto kTab1Desc2FilterText = "Bộ lọc cao âm";
    static constexpr auto kTab1Desc3TitleText = "Biểu tượng trên người chơi";
    static constexpr auto kTab1Desc3SpeakerIconScaleText = "Kích cỡ";
    static constexpr auto kTab1Desc3SpeakerIconOffsetXText = "Kích cỡ X";
    static constexpr auto kTab1Desc3SpeakerIconOffsetYText = "Kích cỡ Y";
    static constexpr auto kTab1Desc4TitleText = "Đặt lại";
    static constexpr auto kTab1Desc4ConfigResetText = "Đặt lại tất cả";
    static constexpr auto kTab2TitleText = "Microphone";
    static constexpr auto kTab2Desc1TitleText = "Thiết bị";
    static constexpr auto kTab2Desc1EnableMicroText = "Bật microphone";
    static constexpr auto kTab2Desc1MicroVolumeText = "Âm lượng microphone";
    static constexpr auto kTab2Desc1DeviceNameText = "Thiết bị vào";
    static constexpr auto kTab2Desc1CheckDeviceText = "Kiểm tra thiết bị (sẽ bị vang)";
    static constexpr auto kTab2Desc2TitleText = "Biểu tượng microphone";
    static constexpr auto kTab2Desc2MicroIconScaleText = "Kích cỡ";
    static constexpr auto kTab2Desc2MicroIconPositionXText = "Vị trí X";
    static constexpr auto kTab2Desc2MicroIconPositionYText = "Vị trí Y";
    static constexpr auto kTab2Desc2MicroIconMoveText = "Di chuyển";
    static constexpr auto kTab2Desc3MicroNotFoundText = "Không có microphone khả dụng";
    static constexpr auto kTab3TitleText = "Danh sách đen";
    static constexpr auto kTab3Desc1TitleText = "Bộ lọc";
    static constexpr auto kTab3Desc1InputPlaceholderText = "Nhập id người chơi hoặc tên...";
    static constexpr auto kTab3Desc2PlayerListText = "Người chơi online";
    static constexpr auto kTab3Desc3BlackListText = "Người chơi đã chặn";
#elif defined(SAMP_EN)
    static constexpr auto kTitleText                       = "Voice chat settings";
    static constexpr auto kTab1TitleText                   = "General";
    static constexpr auto kTab1Desc1TitleText              = "Sound";
    static constexpr auto kTab1Desc1EnableSoundText        = "Turn on sound";
    static constexpr auto kTab1Desc1VolumeSoundText        = "Sound volume";
    static constexpr auto kTab1Desc2TitleText              = "Effects";
    static constexpr auto kTab1Desc2BalancerText           = "Volume smoothing";
    static constexpr auto kTab1Desc2FilterText             = "High pass filter";
    static constexpr auto kTab1Desc3TitleText              = "Icon above players";
    static constexpr auto kTab1Desc3SpeakerIconScaleText   = "Scale";
    static constexpr auto kTab1Desc3SpeakerIconOffsetXText = "Offset by X";
    static constexpr auto kTab1Desc3SpeakerIconOffsetYText = "Offset by Y";
    static constexpr auto kTab1Desc4TitleText              = "Reset";
    static constexpr auto kTab1Desc4ConfigResetText        = "Reset all settings";
    static constexpr auto kTab2TitleText                   = "Microphone";
    static constexpr auto kTab2Desc1TitleText              = "Device";
    static constexpr auto kTab2Desc1EnableMicroText        = "Turn on microphone";
    static constexpr auto kTab2Desc1MicroVolumeText        = "Microphone volume";
    static constexpr auto kTab2Desc1DeviceNameText         = "Input device";
    static constexpr auto kTab2Desc1CheckDeviceText        = "Check device (will be lopped echo)";
    static constexpr auto kTab2Desc2TitleText              = "Microphone icon";
    static constexpr auto kTab2Desc2MicroIconScaleText     = "Scale";
    static constexpr auto kTab2Desc2MicroIconPositionXText = "Position by X";
    static constexpr auto kTab2Desc2MicroIconPositionYText = "Position by Y";
    static constexpr auto kTab2Desc2MicroIconMoveText      = "Move";
    static constexpr auto kTab2Desc3MicroNotFoundText      = "No microphones available";
    static constexpr auto kTab3TitleText                   = "Black list";
    static constexpr auto kTab3Desc1TitleText              = "Filter";
    static constexpr auto kTab3Desc1InputPlaceholderText   = "Enter Player ID or Nickname...";
    static constexpr auto kTab3Desc2PlayerListText         = "Players online";
    static constexpr auto kTab3Desc3BlackListText          = "Blocked players";
#endif

    static constexpr float kBaseMenuWidth                  = 0.6f * Render::kBaseWidth;
    static constexpr float kBaseMenuHeight                 = 0.7f * Render::kBaseHeight;
    static constexpr float kBaseMenuPaddingX               = 20.f;
    static constexpr float kBaseMenuPaddingY               = 10.f;
    static constexpr float kBaseMenuFramePaddingX          = 10.f;
    static constexpr float kBaseMenuFramePaddingY          = 0.5f;
    static constexpr float kBaseMenuItemSpacingX           = 20.f;
    static constexpr float kBaseMenuItemSpacingY           = 2.f;
    static constexpr float kBaseMenuItemInnerSpacingX      = 10.f;
    static constexpr float kBaseMenuItemInnerSpacingY      = 10.f;
    static constexpr float kBaseMenuRounding               = 10.f;
    static constexpr float kBaseFontTitleSize              = 20.f;
    static constexpr float kBaseFontTabSize                = 14.f;
    static constexpr float kBaseFontDescSize               = 12.f;
    static constexpr float kBaseFontSize                   = 10.f;
    static constexpr int   kTabsCount                      = 3;
    static constexpr float kBaseTabPadding                 = 4.f;
    static constexpr float kBaseTabWidth                   = (kBaseMenuWidth - (2 * kBaseMenuPaddingX +
                                                             (kTabsCount - 1) * kBaseTabPadding)) / kTabsCount;
    static constexpr float kBaseTabHeight                  = kBaseTabWidth / 6.f;
    static constexpr float kBlurLevelIncrement             = 5.f;
    static constexpr float kBlurLevelDecrement             = -5.f;

public:

    static bool Init(IDirect3DDevice9* pDevice, const AddressesBase& addrBase,
        const Resource& rShader, const Resource& rLogo, const Resource& rFont) noexcept;
    static void Free() noexcept;

    static bool Show() noexcept;
    static bool IsShowed() noexcept;
    static void Hide() noexcept;

    static void Render() noexcept;
    static void Update() noexcept;

    static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

private:

    static void SyncOptions() noexcept;

private:

    static bool initStatus;
    static bool showStatus;

    static float blurLevel;
    static float blurLevelDeviation;
    static BlurEffectPtr blurEffect;

    static TexturePtr tLogo;

    static ImFont* pTitleFont;
    static ImFont* pTabFont;
    static ImFont* pDescFont;
    static ImFont* pDefFont;

    static Memory::PatchPtr openChatFuncPatch;
    static Memory::PatchPtr openScoreboardFuncPatch;
    static Memory::PatchPtr switchModeFuncPatch;

    static int prevChatMode;

    // Configs
    // ------------------------------------------------------------------------------------------

    static bool soundEnable;
    static int soundVolume;
    static bool soundBalancer;
    static bool soundFilter;

    static float speakerIconScale;
    static int speakerIconOffsetX;
    static int speakerIconOffsetY;

    static bool microEnable;
    static int microVolume;
    static int deviceIndex;

    static float microIconScale;
    static int microIconPositionX;
    static int microIconPositionY;
    static D3DCOLOR microIconColor;
    static float microIconAngle;

    // Internal options
    // ------------------------------------------------------------------------------------------

    static int iSelectedMenu;
    static bool bCheckDevice;
    static bool bMicroMovement;
    static std::array<char, 64> nBuffer;

};
