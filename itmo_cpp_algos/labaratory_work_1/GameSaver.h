#pragma once

namespace game {

struct PlayerStat;

bool LoadProgress (PlayerStat& thePlayerState);
bool SaveProgress (const PlayerStat& thePlayerState);
void RemoveProgress();

}

