#pragma once

#include "syati.h"

class BlueCoinDataStorage : public BinaryDataChunkBase {
public:
    BlueCoinDataStorage();
    virtual ~BlueCoinDataStorage();
    virtual u32 makeHeaderHashCode() const;
    virtual u32 getSignature() const;
    virtual u32 serialize(u8* pPosition, u32 u) const;
    virtual u32 deserialize(const u8* pPosition, u32 size);
    virtual void initializeData();

    MR::BitArray* mCollectionData; // Blue Coins
    MR::BitArray* mFlags; // Blue Coin Flags (Example: Board)
    u32 mCollectionBytes; // Num Coins / 8
    u32 mFlagsBytes; // Num Flags / 8
    u16 mSpentData; // Spent
    bool mHasSeenTextBox; // Do I really
    bool mIsUpdateLocked; // Update?
};

namespace BlueCoinDataUtil {
    BlueCoinDataStorage* getBlueCoinDataStorage();
};