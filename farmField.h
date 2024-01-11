#pragma once

#include "gameObject.h"
#include "farmTile.h"

class FarmField : public GameObject 
{
private:
    FarmTile* tiles;
    int width, height;

public:
    FarmField(int width, int height) : width(width), height(height) {
        tiles = new FarmTile[width * height];
    }

    ~FarmField() {
        delete[] tiles;
    }

    void Init();
    void Uninit();
    void Update();
    void Draw();

};


