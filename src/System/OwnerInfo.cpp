#include "System/Memory.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_ownerInfo.c: the owner's settings, from the copy of the NVRAM's user settings that the system
// makes at 0x027ffc80

// The NitroSDK's NVRAMConfig, only what's used here
struct UserSettings
{
    unsigned char version; // 0
    unsigned char unknown_1;
    unsigned char favoriteColor : 4; // 2
    unsigned char birthdayMonth; // 3
    unsigned char birthdayDay; // 4
    unsigned char unknown_5;
    unsigned short nickname[10]; // 6
    unsigned char nicknameLength; // 1a
    unsigned short comment[26]; // 1c
    unsigned char commentLength; // 50
    char unknown_51[0x64 - 0x51];
    unsigned short language : 3; // 64
};

#define USER_SETTINGS ((UserSettings*)0x027ffc80)
// The Wi-Fi's MAC address, after the user settings
#define MAC_ADDRESS ((unsigned char*)0x027ffcf4)

#define NICKNAME_LENGTH 10
#define COMMENT_LENGTH 26

// The NitroSDK's OSOwnerInfo
struct OwnerInfo
{
    unsigned char language; // 0
    unsigned char favoriteColor; // 1
    unsigned char birthdayMonth; // 2
    unsigned char birthdayDay; // 3
    unsigned short nickname[NICKNAME_LENGTH + 1]; // 4
    unsigned short nicknameLength; // 1a
    unsigned short comment[COMMENT_LENGTH + 1]; // 1c
    unsigned short commentLength; // 52
};

extern "C"
{
    // usa: func_020ca3b8
    // MIi_CpuCopy16
    void func_020ca3b8(const void* src, void* dst, unsigned int length);

    // usa: func_020c99ac
    // OS_GetMacAddress
    void func_020c99ac(unsigned char* macAddress)
    {
        VectorizedInvertedMemcpy(MAC_ADDRESS, macAddress, 6);
    }

    // usa: func_020c99c8
    // OS_GetOwnerInfo
    void func_020c99c8(OwnerInfo* info)
    {
        UserSettings* settings = USER_SETTINGS;

        info->language = (unsigned char)settings->language;
        info->favoriteColor = (unsigned char)settings->favoriteColor;
        info->birthdayMonth = settings->birthdayMonth;
        info->birthdayDay = settings->birthdayDay;
        info->nicknameLength = settings->nicknameLength;
        info->commentLength = settings->commentLength;
        func_020ca3b8(settings->nickname, info->nickname, NICKNAME_LENGTH * sizeof(unsigned short));
        func_020ca3b8(settings->comment, info->comment, COMMENT_LENGTH * sizeof(unsigned short));
        info->nickname[NICKNAME_LENGTH] = 0;
        info->comment[COMMENT_LENGTH] = 0;
    }
}
