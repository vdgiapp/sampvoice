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

#if !defined(SAMP_RU) && !defined(SAMP_EN) && !defined(SAMP_RUS)
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

#if defined(SAMP_RU)
    static constexpr auto kTitleText = "Cai dat voice chat";
    static constexpr auto kTab1TitleText = "Chung";
    static constexpr auto kTab1Desc1TitleText = "Am thanh";
    static constexpr auto kTab1Desc1EnableSoundText = "Bat tieng";
    static constexpr auto kTab1Desc1VolumeSoundText = "Am luong";
    static constexpr auto kTab1Desc2TitleText = "Hieu ung";
    static constexpr auto kTab1Desc2BalancerText = "Can bang am thanh";
    static constexpr auto kTab1Desc2FilterText = "Bo loc cao am";
    static constexpr auto kTab1Desc3TitleText = "Bieu tuong tren nguoi choi";
    static constexpr auto kTab1Desc3SpeakerIconScaleText = "Kich co";
    static constexpr auto kTab1Desc3SpeakerIconOffsetXText = "Kich co X";
    static constexpr auto kTab1Desc3SpeakerIconOffsetYText = "Kich co Y";
    static constexpr auto kTab1Desc4TitleText = "Dat lai";
    static constexpr auto kTab1Desc4ConfigResetText = "Dat lai tat ca";
    static constexpr auto kTab2TitleText = "Microphone";
    static constexpr auto kTab2Desc1TitleText = "Thiet bi";
    static constexpr auto kTab2Desc1EnableMicroText = "Bat microphone";
    static constexpr auto kTab2Desc1MicroVolumeText = "Am luong microphone";
    static constexpr auto kTab2Desc1DeviceNameText = "Thiet bi vao";
    static constexpr auto kTab2Desc1CheckDeviceText = "Kiem tra thiet bi (se bi vang)";
    static constexpr auto kTab2Desc2TitleText = "Bieu tuong microphone";
    static constexpr auto kTab2Desc2MicroIconScaleText = "Kich co";
    static constexpr auto kTab2Desc2MicroIconPositionXText = "Vi tri X";
    static constexpr auto kTab2Desc2MicroIconPositionYText = "Vi tri Y";
    static constexpr auto kTab2Desc2MicroIconMoveText = "Di chuyen";
    static constexpr auto kTab2Desc3MicroNotFoundText = "Khong co microphone kha dung";
    static constexpr auto kTab3TitleText = "Danh sach den";
    static constexpr auto kTab3Desc1TitleText = "Bo loc";
    static constexpr auto kTab3Desc1InputPlaceholderText = "Nhap id nguoi choi hoac ten...";
    static constexpr auto kTab3Desc2PlayerListText = "Nguoi choi online";
    static constexpr auto kTab3Desc3BlackListText = "Nguoi choi da chan";
#elif defined(SAMP_EN)
    static constexpr auto kTitleText = "Voice chat settings";
    static constexpr auto kTab1TitleText = "General";
    static constexpr auto kTab1Desc1TitleText = "Sound";
    static constexpr auto kTab1Desc1EnableSoundText = "Turn on sound";
    static constexpr auto kTab1Desc1VolumeSoundText = "Sound volume";
    static constexpr auto kTab1Desc2TitleText = "Effects";
    static constexpr auto kTab1Desc2BalancerText = "Volume smoothing";
    static constexpr auto kTab1Desc2FilterText = "High pass filter";
    static constexpr auto kTab1Desc3TitleText = "Icon above players";
    static constexpr auto kTab1Desc3SpeakerIconScaleText = "Scale";
    static constexpr auto kTab1Desc3SpeakerIconOffsetXText = "Offset by X";
    static constexpr auto kTab1Desc3SpeakerIconOffsetYText = "Offset by Y";
    static constexpr auto kTab1Desc4TitleText = "Reset";
    static constexpr auto kTab1Desc4ConfigResetText = "Reset all settings";
    static constexpr auto kTab2TitleText = "Microphone";
    static constexpr auto kTab2Desc1TitleText = "Device";
    static constexpr auto kTab2Desc1EnableMicroText = "Turn on microphone";
    static constexpr auto kTab2Desc1MicroVolumeText = "Microphone volume";
    static constexpr auto kTab2Desc1DeviceNameText = "Input device";
    static constexpr auto kTab2Desc1CheckDeviceText = "Check device (will be lopped echo)";
    static constexpr auto kTab2Desc2TitleText = "Microphone icon";
    static constexpr auto kTab2Desc2MicroIconScaleText = "Scale";
    static constexpr auto kTab2Desc2MicroIconPositionXText = "Position by X";
    static constexpr auto kTab2Desc2MicroIconPositionYText = "Position by Y";
    static constexpr auto kTab2Desc2MicroIconMoveText = "Move";
    static constexpr auto kTab2Desc3MicroNotFoundText = "No microphones available";
    static constexpr auto kTab3TitleText = "Black list";
    static constexpr auto kTab3Desc1TitleText = "Filter";
    static constexpr auto kTab3Desc1InputPlaceholderText = "Enter Player ID or Nickname...";
    static constexpr auto kTab3Desc2PlayerListText = "Players online";
    static constexpr auto kTab3Desc3BlackListText = "Blocked players";
#elif defined(SAMP_RUS)
    static constexpr auto kTitleText = "Настройки голосового чата";
    static constexpr auto kTab1TitleText = "Общие";
    static constexpr auto kTab1Desc1TitleText = "Звук";
    static constexpr auto kTab1Desc1EnableSoundText = "Включить звук";
    static constexpr auto kTab1Desc1VolumeSoundText = "Громкость звука";
    static constexpr auto kTab1Desc2TitleText = "Эффекты";
    static constexpr auto kTab1Desc2BalancerText = "Сглаживание громкости";
    static constexpr auto kTab1Desc2FilterText = "Фильтр высоких частот";
    static constexpr auto kTab1Desc3TitleText = "Иконка над игроками";
    static constexpr auto kTab1Desc3SpeakerIconScaleText = "Масштаб";
    static constexpr auto kTab1Desc3SpeakerIconOffsetXText = "Смещение по X";
    static constexpr auto kTab1Desc3SpeakerIconOffsetYText = "Смещение по Y";
    static constexpr auto kTab1Desc4TitleText = "Сброс";
    static constexpr auto kTab1Desc4ConfigResetText = "Сбросить все настройки";
    static constexpr auto kTab2TitleText = "Микрофон";
    static constexpr auto kTab2Desc1TitleText = "Устройство";
    static constexpr auto kTab2Desc1EnableMicroText = "Включить микрофон";
    static constexpr auto kTab2Desc1MicroVolumeText = "Громкость микрофона";
    static constexpr auto kTab2Desc1DeviceNameText = "Устройство ввода";
    static constexpr auto kTab2Desc1CheckDeviceText = "Проверить устройство (будет повторное эхо)";
    static constexpr auto kTab2Desc2TitleText = "Иконка микрофона";
    static constexpr auto kTab2Desc2MicroIconScaleText = "Масштаб";
    static constexpr auto kTab2Desc2MicroIconPositionXText = "Позиция по X";
    static constexpr auto kTab2Desc2MicroIconPositionYText = "Позиция по Y";
    static constexpr auto kTab2Desc2MicroIconMoveText = "Переместить";
    static constexpr auto kTab2Desc3MicroNotFoundText = "Нет доступных микрофонов";
    static constexpr auto kTab3TitleText = "Чёрный список";
    static constexpr auto kTab3Desc1TitleText = "Фильтр";
    static constexpr auto kTab3Desc1InputPlaceholderText = "Введите ID или Nickname игрока...";
    static constexpr auto kTab3Desc2PlayerListText = "Игроки на сервере";
    static constexpr auto kTab3Desc3BlackListText = "Заблокированные игроки";
#endif

    static constexpr float kBaseMenuWidth = 0.6f * Render::kBaseWidth;
    static constexpr float kBaseMenuHeight = 0.7f * Render::kBaseHeight;
    static constexpr float kBaseMenuPaddingX = 20.f;
    static constexpr float kBaseMenuPaddingY = 10.f;
    static constexpr float kBaseMenuFramePaddingX = 10.f;
    static constexpr float kBaseMenuFramePaddingY = 0.5f;
    static constexpr float kBaseMenuItemSpacingX = 20.f;
    static constexpr float kBaseMenuItemSpacingY = 2.f;
    static constexpr float kBaseMenuItemInnerSpacingX = 10.f;
    static constexpr float kBaseMenuItemInnerSpacingY = 10.f;
    static constexpr float kBaseMenuRounding = 10.f;
    static constexpr float kBaseFontTitleSize = 20.f;
    static constexpr float kBaseFontTabSize = 14.f;
    static constexpr float kBaseFontDescSize = 12.f;
    static constexpr float kBaseFontSize = 10.f;
    static constexpr int   kTabsCount = 3;
    static constexpr float kBaseTabPadding = 4.f;
    static constexpr float kBaseTabWidth = (kBaseMenuWidth - (2 * kBaseMenuPaddingX +
        (kTabsCount - 1) * kBaseTabPadding)) / kTabsCount;
    static constexpr float kBaseTabHeight = kBaseTabWidth / 6.f;
    static constexpr float kBlurLevelIncrement = 5.f;
    static constexpr float kBlurLevelDecrement = -5.f;

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
