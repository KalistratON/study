#pragma once

namespace game {

struct PlayerRequest {
    int myArcCountToBuy  = 0;
    int myArcCountToSell = 0;
    int myWheatToEat     = 0;
    int myArcToSeed      = 0;
};

struct PlayerStat {
    bool myIsPlugue         = false;
    int myRound             = 0;
    int myDeadCount         = 0;
    int myRookieCount       = 0;
    int myPopulationSize    = 100;
    int myWheatCount        = 2800;
    int myCropedWheat       = 0;
    int myWheatPerAcr       = 0;
    int myLossWheat         = 0;
    int myAcrCount          = 1000;
    int myAcrPrice          = 0;

    int myRelativeCemetry   = 0;
};

}