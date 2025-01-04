#include "GameSaver.h"
#include "GameStructure.h"
#include "MenuHelper.h"

#include <ctime>
#include <iostream>
#include <random>
#include <string.h>


namespace game {

namespace GameCondition {

const int myLastRound              = 10;
const int myPeoplePerArc           = 10;
const int myWheatConsume           = 20;
const int myArcConsumePopulation   = 10;

const double myWheatPerAcr              = 0.5;
const double myMinPopulationVelocity    = 0.0;
const double myMaxPopulationVelocity    = 50.;
const double myCriticalLossPopulation   = 0.45;

static long GetAcrPrice()
{
    return (std::rand() % 10) + 17;
}

static bool IsPlague()
{
    return std::rand() % 101 <= 15;
}

static long GetRodentHarm (long theWheat)
{
    return static_cast <long> ((std::rand() % 8) / 100. * theWheat);
}

static long GetCropPerAcr()
{
    return std::rand() % 6 + 1;
}

enum GameStatus {
    INVALID_INPUT,
    FAULT,
    PROCEDE,
    WIN
};

}

long GetNextPopulation (const PlayerStat& thePlayerState)
{
    double aDraftPopulation = thePlayerState.myDeadCount / 2. + (5. - thePlayerState.myWheatPerAcr) * (thePlayerState.myWheatCount) / 600. + 1.;
    return static_cast <long> (std::min (std::max (aDraftPopulation, GameCondition::myMinPopulationVelocity), GameCondition::myMaxPopulationVelocity));
}

bool IsValidRequest (const PlayerStat& thePlayerState, const PlayerRequest& thePlayerRequest)
{
    if (thePlayerState.myAcrPrice * thePlayerRequest.myArcCountToBuy > thePlayerState.myWheatCount) {
        return false;
    }

    if (thePlayerRequest.myArcCountToSell > thePlayerState.myAcrCount) {
        return false;
    }

    if (thePlayerRequest.myArcToSeed > thePlayerState.myWheatCount) {
        return false;
    }

    if (thePlayerRequest.myArcToSeed > thePlayerState.myAcrCount ||
        thePlayerRequest.myArcToSeed > GameCondition::myPeoplePerArc * thePlayerState.myPopulationSize ||
        thePlayerRequest.myArcToSeed > GameCondition::myWheatPerAcr * thePlayerState.myWheatCount) {
        return false;
    }

    if (thePlayerRequest.myArcToSeed + thePlayerRequest.myArcCountToSell > thePlayerState.myAcrCount) {
        return false;
    }

    if (thePlayerState.myAcrPrice * thePlayerRequest.myArcCountToBuy + thePlayerRequest.myArcToSeed * GameCondition::myWheatPerAcr > thePlayerState.myWheatCount) {
        return false;
    }

    return true;
}

GameCondition::GameStatus GameBody (PlayerStat& thePlayerState, const PlayerRequest& thePlayerRequest)
{
    if (!IsValidRequest (thePlayerState, thePlayerRequest)) {
        return GameCondition::GameStatus::INVALID_INPUT;
    }

    thePlayerState.myWheatPerAcr   = GameCondition::GetCropPerAcr();
    thePlayerState.myAcrCount   += thePlayerRequest.myArcCountToBuy - thePlayerRequest.myArcCountToSell;

    int aCropedWheatCount = thePlayerState.myWheatPerAcr * thePlayerState.myAcrCount;
    thePlayerState.myCropedWheat = thePlayerState.myWheatPerAcr * thePlayerState.myAcrCount;

    thePlayerState.myWheatCount += static_cast <long> (
            thePlayerRequest.myArcCountToSell * thePlayerState.myAcrPrice - thePlayerRequest.myArcToSeed * GameCondition::myWheatPerAcr + thePlayerState.myCropedWheat);

    thePlayerState.myLossWheat = GameCondition::GetRodentHarm (thePlayerState.myWheatCount);
    thePlayerState.myWheatCount -= thePlayerState.myLossWheat;

    int aDeadPeople = 0;
    int anEatenWheatDiff = thePlayerState.myPopulationSize * GameCondition::myWheatConsume - thePlayerRequest.myWheatToEat;
    if (anEatenWheatDiff > 0) {
        aDeadPeople = anEatenWheatDiff / GameCondition::myWheatConsume + (anEatenWheatDiff % GameCondition::myWheatConsume != 0);
    }

    thePlayerState.myRelativeCemetry += aDeadPeople / thePlayerState.myPopulationSize;
    thePlayerState.myDeadCount = aDeadPeople;
    if (aDeadPeople > 0.45 * thePlayerState.myPopulationSize) {
        return GameCondition::GameStatus::FAULT;
    }
    thePlayerState.myPopulationSize -= aDeadPeople;
    thePlayerState.myPopulationSize += GetNextPopulation (thePlayerState);

    if (thePlayerState.myIsPlugue = GameCondition::IsPlague()) {
        thePlayerState.myPopulationSize /= 2;
    }

    thePlayerState.myAcrPrice = GameCondition::GetAcrPrice();

    return ++thePlayerState.myRound == GameCondition::myLastRound ? GameCondition::GameStatus::WIN : GameCondition::GameStatus::PROCEDE;
}

}

int main()
{
    std::srand (std::time (nullptr));

    game::PlayerStat aPlayerState;
    game::PlayerRequest aRequest;

    bool anIsNewGame = true;
    do {
        if (anIsNewGame && game::LoadProgress (aPlayerState) && game::WantToProcede()) {
            
            std::cout << "... from previous session:" << std::endl;
            PrintStat (aPlayerState);
        } else if (anIsNewGame) {
            aPlayerState = game::PlayerStat();
            aPlayerState.myAcrPrice = game::GameCondition::GetAcrPrice();
            PrintStat (aPlayerState);
        }
        anIsNewGame = false;

        if (game::WantToClose()) {
            break;
        }

        game::GameCondition::GameStatus aStrideResult = game::GameCondition::PROCEDE;
        do {
            if (aStrideResult == game::GameCondition::INVALID_INPUT) {
                std::cout << "God save us! Our tsar can't math!" << std::endl;
            }

            MakeRequest (aRequest);
            aStrideResult = game::GameBody (aPlayerState, aRequest);
        } while (aStrideResult == game::GameCondition::INVALID_INPUT);

        if (aStrideResult == game::GameCondition::FAULT) {
            std::cout << "You lose empire Tsar! Half of empire is dead. Guitarists are left only!" << std::endl;
            break;
        }

        if (aStrideResult == game::GameCondition::WIN) {
            double aR = aPlayerState.myRelativeCemetry / static_cast <double> (aPlayerState.myRound);
            double aL = aPlayerState.myAcrCount / aPlayerState.myPopulationSize;

            game::PrintFinishResult (aR, aL);
            game::RemoveProgress();
            break;
        }

        PrintStat (aPlayerState);
        game::SaveProgress (aPlayerState);

    } while (true);
    return 0;
}