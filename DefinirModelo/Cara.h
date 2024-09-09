#pragma once
class Cara {
public:
    int vertexIndices[3];
public:
    Cara(int v1, int v2, int v3) {
        vertexIndices[0] = v1;
        vertexIndices[1] = v2;
        vertexIndices[2] = v3;
    }
};

