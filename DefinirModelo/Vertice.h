#pragma once
class Vertice {
public:
    float x, y, z, w;
public:
    Vertice() {

    }

    Vertice(float vx, float vy, float vz) {
        this->x = vx;
        this->y = vy;
        this->z = vz;
        this->w = 1;
    }
};

