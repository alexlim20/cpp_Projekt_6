#ifndef BURNER_H
#define BURNER_H
#include <string>
#include "Boiler.h"
#include "WinAdapt.h"
class Burner
{
    std::string Name;
    int XPosition;
    int YPosition;
    Boiler* MyBoiler;
    double ConsumedFuel;
    int startX, startY, endX, endY;
    void calculatePosition();
    public:
    Burner(Boiler* MyBoiler, const std::string& Name, int X=-1, int Y=-1);
    void feedFuel(double Amount);
    void show();
    bool contains(int X, int Y);
};
#endif // BURNER_H
