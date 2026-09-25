#include "Wireless/WirelessManager.h"
#include "System/Cache.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_etc.c: the wireless manager's other settings (WEP, the parent's game information, the beacons'
// indications, the lifetimes) and the measure of a channel's use

// WM_WEPMODE_128BIT: the largest WEP mode
#define WEP_MODE_MAX 3
// WM_SIZE_WEPKEY
#define WEP_KEY_SIZE 80
// WM_SIZE_USER_GAMEINFO
#define USER_GAME_INFO_MAX 0x70

// The command of WM_MeasureChannel (WMMeasureChannelReq)
struct WMMeasureChannelReq
{
    unsigned short apiid;
    unsigned short ccaMode;
    unsigned short edThreshold;
    unsigned short channel;
    unsigned short measureTime;
};

// The copy of the parent's game information that the ARM7 reads: its size is rounded up to the cache lines
static unsigned long gameInfoBuf[(USER_GAME_INFO_MAX + 31) / 32 * 32 / sizeof(unsigned long)] __attribute__((aligned(32)));

extern "C"
{
    // MI_CpuCopy16
    void func_020ca3b8(const void* src, void* dst, unsigned long size);

    // WM_SetWEPKey
    int func_020d68dc(WMCallbackFunc callback, unsigned short wepmode, const unsigned short* wepkey)
    {
        int result = func_020d4204();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (wepmode > WEP_MODE_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        if (wepmode != 0)
        {
            if (wepkey == NULL)
                return WM_ERRCODE_INVALID_PARAM;
            CleanCacheRange(wepkey, WEP_KEY_SIZE);
        }
        func_020d404c(WM_APIID_SET_WEPKEY, callback);
        result = func_020d40bc(WM_APIID_SET_WEPKEY, 2, wepmode, wepkey);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_SetWEPKeyEx
    int func_020d6950(WMCallbackFunc callback, unsigned short wepmode, unsigned short wepkeyid,
                      const unsigned char* wepkey)
    {
        int result = func_020d4204();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (wepmode > WEP_MODE_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        if (wepmode != 0)
        {
            if (wepkey == NULL)
                return WM_ERRCODE_INVALID_PARAM;
            CleanCacheRange(wepkey, WEP_KEY_SIZE);
        }
        func_020d404c(WM_APIID_SET_WEPKEY_EX, callback);
        result = func_020d40bc(WM_APIID_SET_WEPKEY_EX, 3, wepmode, wepkey, wepkeyid);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_SetGameInfo: changes the game information in the parent's beacons
    int func_020d69cc(WMCallbackFunc callback, const unsigned short* userGameInfo, unsigned short userGameInfoSize,
                      unsigned long ggid, unsigned short tgid, unsigned char attr)
    {
        int result = func_020d424c(2, WM_STATE_PARENT, WM_STATE_MP_PARENT);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (userGameInfo == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (userGameInfoSize > USER_GAME_INFO_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        func_020ca3b8(userGameInfo, gameInfoBuf, userGameInfoSize);
        CleanCacheRange(gameInfoBuf, userGameInfoSize);
        func_020d404c(WM_APIID_SET_GAMEINFO, callback);
        result = func_020d40bc(WM_APIID_SET_GAMEINFO, 5, gameInfoBuf, userGameInfoSize, ggid, tgid, attr);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_SetBeaconIndication: whether the callback gets the beacons that the parent sends and the child receives
    int func_020d6a84(WMCallbackFunc callback, unsigned short flag)
    {
        int result = func_020d4204();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (flag != 0 && flag != 1)
            return WM_ERRCODE_INVALID_PARAM;
        func_020d404c(WM_APIID_SET_BEACON_IND, callback);
        result = func_020d40bc(WM_APIID_SET_BEACON_IND, 1, flag);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_SetLifeTime: how long a connection, a frame and MP communication's data last without an answer
    int func_020d6ad4(WMCallbackFunc callback, unsigned short tableNumber, unsigned short camLifeTime,
                      unsigned short frameLifeTime, unsigned short mpLifeTime)
    {
        int result = func_020d4204();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_SET_LIFETIME, callback);
        result = func_020d40bc(WM_APIID_SET_LIFETIME, 4, tableNumber, camLifeTime, frameLifeTime, mpLifeTime);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_MeasureChannel: how busy a channel is
    int func_020d6b34(WMCallbackFunc callback, unsigned short ccaMode, unsigned short edThreshold,
                      unsigned short channel, unsigned short measureTime)
    {
        int result;
        func_020d41d8();
        result = func_020d424c(1, WM_STATE_IDLE);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_MEASURE_CHANNEL, callback);
        {
            WMMeasureChannelReq req;
            req.apiid = WM_APIID_MEASURE_CHANNEL;
            req.ccaMode = ccaMode;
            req.edThreshold = edThreshold;
            req.channel = channel;
            req.measureTime = measureTime;
            result = func_020d4168(&req, sizeof(WMMeasureChannelReq));
        }
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }
}
