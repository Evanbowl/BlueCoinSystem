#pragma once
#include "syati.h"
#include "BlueCoinDataStorage.h"
class BlueCoin;
class CounterLayoutController;
class BlueCoinCounter;

class CoinBase;

// These can be customized but save files will not carry over.
// Modifying these will disable the updater.
#define COLLECTIONCOUNT 256
#define FLAGSCOUNT 32

namespace pt {
    extern void* loadArcAndFile(const char *pArc, const char *pFile, JKRHeap *pHeap);
    extern void setTextBoxArgStringNumberFontRecursive(LayoutActor* pLayout, const char* paneName, u16 num, s32 index);
}

namespace BlueCoinUtil {
    s32 getCurrentFileNum();

    void setBlueCoinGotCurrentFile(u16 id);
    bool isBlueCoinGotCurrentFile(u16 id);
   
    void setOnBlueCoinFlagCurrentFile(u16 flag);
    bool isOnBlueCoinFlagCurrentFile(u16 flag);

    bool hasSeenBlueCoinTextBoxCurrentFile();
    void setSeenBlueCoinTextBoxCurrentFile();
    bool isBlueCoinTextBoxAppeared();

    void setCounter();
    void showTextBox();  

    void spendBlueCoinCurrentFile(u16 numcoin);
    u16 getSpentBlueCoinNum(BlueCoinDataStorage* pStorage);
    u16 getSpentBlueCoinNumCurrentFile();

    s32 getTotalBlueCoinNum(BlueCoinDataStorage* pStorage, bool ignoreSpent);
    s32 getTotalBlueCoinNumCurrentFile(bool ignoreSpent);
    
    s32 getBlueCoinRange(const char* pStageName, bool minOrMax);
    s32 calcBlueCoinTotalInRange(const char* pStageName, bool collectedCoinsOnly);

    bool isBlueCoinListLayoutExist();

    CoinBase* tryCreateBlueCoinForSpawningActorActionKeeper(LiveActor* pSourceActor, const JMapInfoIter& rIter, s32 id);
    bool tryAppearBlueCoinActionKeeper(LiveActor* pSourceActor, const TVec3f& rPosition);
    bool isValidBlueCoinActionKeeper(LiveActor* pSourceActor);

    NameObj* createBlueCoin(const char* pName);
};

namespace BlueCoinReplaceTag {
    u32 appendBlueCoinString(wchar_t* pStr, u32 num);
    inline u16 getReplaceParam(const MessageEditorMessageTag& rTag);
    u32 getTotalBlueCoinNumCurrentFileForMsg(wchar_t* pStr, const MessageEditorMessageTag& rTag);
    u32 calcBlueCoinTotalInRangeForMsg(wchar_t* pStr, const MessageEditorMessageTag& rTag);
    u32 getSpentBlueCoinNumCurrentFileForMsg(wchar_t* pStr, const MessageEditorMessageTag& rTag);
};