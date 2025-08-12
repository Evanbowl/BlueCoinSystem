#include "Game/Screen/CounterLayoutController.h"

class BlueCoinCounter;
class CounterLayoutControllerExt : public CounterLayoutController {
public:
    CounterLayoutControllerExt();
    ~CounterLayoutControllerExt();
    s32* mGlobalLayoutHolder;
    BlueCoinCounter* mBlueCoinCounter;
};

namespace NrvPlayerLeftExt {
    NERVE(NrvDeathCounterCountUp);
};