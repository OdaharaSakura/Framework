#pragma once
#include <string>

//@ŒÍ‚ê‚½ó‘Ô‚ð’Ç‰Á‚·‚é‚©l‚¦‚é
enum FarmTileState
{
    EMPTY, 
    PLOWED,     // k‚³‚ê‚½
    PLANTED,    // Ží‚ðA‚¦‚½
    PLANTEDWATERED, // Ží‚ðA‚¦‚Ä…‚â‚è‚µ‚½
    GROWING,    // ¬’·’†
    GROWINGWATERED, // ¬’·’†‚Å…‚â‚è‚µ‚½
    HARVESTABLE, // ŽûŠn‰Â”\
    MAX_GROWTH_STAGE
};

class FarmTile 
{
private:
    FarmTileState state;
    int growthStage;
public:
    
    FarmTile() : state(EMPTY), growthStage(0) {}

    void plow() {
        if (state == EMPTY) state = PLOWED;
    }

    void plantSeed() {
        if (state == PLOWED) {
            state = PLANTED;
            growthStage = 1; // ‰Šú¬’·’iŠK
        }
    }

    void updateGrowth() {
        if (state == PLANTED || state == GROWING) {
            growthStage++;
            if (growthStage >= FarmTileState::MAX_GROWTH_STAGE) {
                state = HARVESTABLE;
            }
            else {
                state = GROWING;
            }
        }
    }
};


