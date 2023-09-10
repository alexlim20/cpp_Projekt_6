#ifndef PIPELINE_H
#define PIPELINE_H
#include "Boiler.h"

class Pipeline
{
    Boiler* Source;
    Boiler* Target;
    int Pumpsize;
    int startX, startY, endX, endY, elliRadius, midX, midY;
    void calculatePosition();
public:
    Pipeline(Boiler* Source, Boiler* Target, int Pumpsize = 75);
    void transferMedium(double Amount);
    bool contains(int X, int Y);
    void show();
};
#endif // PIPELINE_H
