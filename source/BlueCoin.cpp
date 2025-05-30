#include "BlueCoin.h"
#include "Game/MapObj/CoinHolder.h"
#include "BlueCoinLayouts.h"
#include "Game/Screen/GameSceneLayoutHolder.h"
#include "Game/Screen/CounterLayoutControllerExt.h"

BlueCoin::BlueCoin(const char* pName) : CoinBase(pName) {
    mID = 0;
    mLaunchVelocity = 25.0f;
    mIsCollected = 0;
    
    MR::addToCoinHolder(this, this);
}

void BlueCoin::init(const JMapInfoIter& rIter) {
    mCoinInfo.mExistInDarkComet = true;
    mCoinInfo.mPlaySound = false;
    mCoinInfo.mUseReadSwitchB = false;
    mCoinInfo.mIgnoreSensorScaling = true;
    mCoinInfo.mInitFunction = false;
    const char* name = "BlueCoin";
    
    if (MR::isValidInfo(rIter)) {
        MR::getJMapInfoArg0NoInit(rIter, &mID); 
        MR::getJMapInfoArg1NoInit(rIter, &mLaunchVelocity);
    }
    
    if (BlueCoinUtil::isBlueCoinGotCurrentFile(mID))
    name = "BlueCoinClear";
    
    strcpy(mCoinInfo.mMirrorActorName, name);
    if (MR::isValidInfo(rIter)) {
        MR::processInitFunction(this, rIter, name, false);
        MR::initSwitches(this, rIter, "BlueCoin", 0);
    }
    else {
        MR::processInitFunction(this, name, false);
        MR::initShadowVolumeSphere(this, 50.0f);
        MR::setShadowDropPositionPtr(this, 0, &mShadowDropPos);
        MR::setShadowDropLength(this, 0, 1000.0f);
    }

    CoinBase::init(rIter);
    
    MR::initSensors(this, "BlueCoin", 0);

    if (MR::isValidSwitchB(this))
        requestHide();
}


void BlueCoin::control() {
    if (MR::isOnSwitchB(this)) {
        if (isNerve(&NrvCoin::CoinNrvFixHide::sInstance))
            appearAndMove(mLaunchVelocity, "SE_SY_PURPLE_COIN_APPEAR");

        mLifeTime = 0x7FFFFFFF;
    }
}

bool BlueCoin::vRequestGetCoin() {
    #if defined SMG63 
        MR::emitEffect(this, "BlueCoinGet"); 
        MR::startSystemSE("SE_SY_TICO_COIN", -1, -1);
    #else
        MR::emitEffect(this, BlueCoinUtil::isBlueCoinGotCurrentFile(mID) ? "BlueCoinClearGet" : "BlueCoinGet"); 
        MR::startSystemSE("SE_SY_PURPLE_COIN", -1, -1);
    #endif

    mFlashingCtrl->end();
    setNerve(&NrvCoin::CoinNrvGot::sInstance);
    makeActorDead();
    
    if (!BlueCoinUtil::isBlueCoinGotCurrentFile(mID)) {
        BlueCoinUtil::setBlueCoinGotCurrentFile(mID);

        if (!BlueCoinUtil::hasSeenBlueCoinTextBoxCurrentFile())
            BlueCoinUtil::showTextBox();
    }

    noticeGetCoin();
    return 1;
}

/*

void BlueCoin::collect() {
    mIsCollected = true;
    setNerve(&NrvCoin::CoinNrvGot::sInstance);
    
    if (MR::isValidSwitchA(this))
        MR::onSwitchA(this);

    if (mIsInBubble) {
        MR::emitEffect(mAirBubble, "RecoveryBubbleBreak");
        mAirBubble->kill();
    }
    
    #if defined SMG63 
        MR::emitEffect(this, "BlueCoinGet"); 
        MR::startSystemSE("SE_SY_TICO_COIN", -1, -1);
    #else
        MR::emitEffect(this, BlueCoinUtil::isBlueCoinGotCurrentFile(mID) ? "BlueCoinClearGet" : "BlueCoinGet"); 
        MR::startSystemSE("SE_SY_PURPLE_COIN", -1, -1);
    #endif


    
    if (!BlueCoinUtil::isBlueCoinGotCurrentFile(mID)) {
        BlueCoinUtil::setBlueCoinGotCurrentFile(mID);

        if (!BlueCoinUtil::hasSeenBlueCoinTextBoxCurrentFile())
            BlueCoinUtil::showTextBox();
    }
    
    if (!MR::isGalaxyDarkCometAppearInCurrentStage())
        MR::incCoin(1, this);

    MR::incPlayerOxygen(mIsInBubble ? 2 : 1);
    makeActorDead();
}*/