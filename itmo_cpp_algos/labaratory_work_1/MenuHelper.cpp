#include "MenuHelper.h"
#include "GameStructure.h"

#include <iostream>


namespace game {

namespace {

bool DoWantTo (const char* theString)
{
    char aRequest [4];
    std::cout << theString << std::endl;
    std::cin >> aRequest;

    int anIsYes = strcmp (aRequest, "yes");
    while (anIsYes != 0 && strcmp (aRequest, "no") != 0) {
        std::cin >> aRequest;
        anIsYes = strcmp (aRequest, "yes");
    }

    return strcmp (aRequest, "yes") == 0;
}

}

bool WantToClose()
{
    return DoWantTo ("Do you want to suspend? (yes/no)");
}

bool WantToProcede()
{
    return DoWantTo ("Do you want to procede? (yes/no)");
}

void MakeRequest (PlayerRequest& theRequest)
{
    bool anIsFirstIter = true;
    do {
        if (anIsFirstIter) {
            anIsFirstIter = false;
        } else {
            std::cout << "Negative number was entered! Try again" << std::endl;
        }

        std::cout << "Hi Tsar, fill this sheet" << std::endl;

        std::cout << "How many arc you want to buy?" << std::endl;
        std::cin >> theRequest.myArcCountToBuy;

        std::cout << "How many arc you want to sell?" << std::endl;
        std::cin >> theRequest.myArcCountToSell;

        std::cout << "How many arc you want to be seeded?" << std::endl;
        std::cin >> theRequest.myArcToSeed;

        std::cout << "How many wheat you want to be eaten?" << std::endl;
        std::cin >> theRequest.myWheatToEat;

    } while (theRequest.myArcCountToBuy < 0 || theRequest.myArcCountToSell < 0 || theRequest.myArcToSeed < 0 || theRequest.myWheatToEat < 0);
}

void PrintStat (const PlayerStat& theStat)
{
    std::cout << std::endl << "Tsar! Our empire is choked your beneficence" << std::endl;

    std::cout << "In the year " << theStat.myRound << std::endl;

    if (theStat.myDeadCount) {
        std::cout << "We lost " << theStat.myDeadCount << " mans. God help them" << std::endl;
    }

    if (theStat.myRookieCount) {
        std::cout << "We have new subjects. " << theStat.myDeadCount << " mans exactly." << std::endl;
    }

    {
        const auto aStr = theStat.myIsPlugue ? "Plague kills half of population!" : "We avert a plague!";
        std::cout << aStr << std::endl;
    }

    std::cout << "Our population is " << theStat.myPopulationSize << " now" << std::endl;

    std::cout << "We croped " << theStat.myCropedWheat << " bushels. " << theStat.myWheatPerAcr << " per acr." << std::endl;

    std::cout << "Rodents decimate " << theStat.myLossWheat << " bushels. Now we have " << theStat.myWheatCount << " in stores" << std::endl;

    std::cout << "Our town occupies " << theStat.myAcrCount << " acrs." << std::endl;

    std::cout << "Capitalism, my Tsar! Price for acr is " << theStat.myAcrPrice << std::endl;
}

void PrintFinishResult (double theP, double theL)
{
    if (theP > 0.33 && theL < 7) {
        std::cout << "It's implosible to dwell without brain... until now it was a fact. Now it's not because of you." << std::endl;
        std::cout << "There's a place reserved for you on St. Helena island. " << std::endl;
    } else if (theP > 0.1 && theL < 9) {
        std::cout << "You weren't shit, but you didn't make it to the top... Like Totenham" << std::endl;
        std::cout << "Train you reign skills on somewho else, not us, please" << std::endl;
    } else if (theP > 0.03 && theL < 10) {
        std::cout << "Good job commrade! Like a Stalin in the best years!" << std::endl;
        std::cout << "Time to get 147% on the commin election" << std::endl;
    } else {
        std::cout << "Wow! Now our empire is immense and we border with Russia, USA and China..." << std::endl;
        std::cout << "It's time to prepare to any other \'operations\' LMAO" << std::endl;
    }
}
}