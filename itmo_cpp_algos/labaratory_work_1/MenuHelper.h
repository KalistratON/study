#pragma once

namespace game {

struct PlayerStat;
struct PlayerRequest;

bool WantToClose();
bool WantToProcede();
void MakeRequest (PlayerRequest& theRequest);
void PrintStat (const PlayerStat& theStat);
void PrintFinishResult (double theP, double theL);

}

