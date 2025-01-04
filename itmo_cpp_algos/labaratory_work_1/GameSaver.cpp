#include "GameSaver.h"
#include "GameStructure.h"

#include <filesystem>
#include <fstream>


using namespace std;

namespace game {

namespace {

static const string SaveDir  = std::filesystem::temp_directory_path().string() + "/settings";
static const string FilePath = SaveDir + "/save.bin";

}

bool LoadProgress (PlayerStat& thePlayerState)
{
    fstream aFile (FilePath, std::ios::binary | std::ios::in);
    if (!aFile.is_open()) {
        return false;
    }

    char* aBuffer = reinterpret_cast <char*> (&thePlayerState);
    aFile.read (aBuffer, sizeof (thePlayerState));

    return true;
}

bool SaveProgress (const PlayerStat& thePlayerState)
{
    std::filesystem::create_directories (SaveDir);
    fstream aFile (FilePath, std::ios::binary | std::ios::out);
    if (!aFile.is_open()) {
        return false;
    }

    aFile.write (reinterpret_cast <const char*> (&thePlayerState), sizeof (thePlayerState));

    return true;
}

void RemoveProgress()
{
    std::remove (FilePath.c_str());
}

}
