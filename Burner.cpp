#include "Burner.h"
#include "Boiler.h"
#include <iostream>
#include "WinAdapt.h"
#include <cstdio>
#include <string>

Burner::Burner(Boiler* MyBoiler, const std::string& Name, int X, int Y)
:MyBoiler(MyBoiler), Name(Name), XPosition(X), YPosition(Y)
{
    this->ConsumedFuel = 0.0;
    startX = 0;
    startY = 0;
    endX = 0;
    endY = 0;
}

void Burner::feedFuel(double Amount)
{
    double temp = Amount*0.001*34300.0;

    MyBoiler->addHeat(temp);
    ConsumedFuel += Amount;
}

void Burner::calculatePosition()
{
    if(XPosition<0 || YPosition<0)
    {
        startX = MyBoiler->getXPosition()+(0.125*MyBoiler->getWidth());
        startY = MyBoiler->getYPosition()+MyBoiler->getHeight();
        endX = MyBoiler->getXPosition()+(0.125*MyBoiler->getWidth())+XPosition+MyBoiler->getWidth()*0.75;
        endY = MyBoiler->getYPosition()+MyBoiler->getHeight()+0.25*MyBoiler->getHeight();
    }else
    {
        startX = XPosition;
        startY = YPosition;
        endX = MyBoiler->getWidth()*0.75;
        endY = MyBoiler->getHeight()*0.25;
    }
}

void Burner::show()
{
    calculatePosition();
    Rect(startX, startY, endX, endY);
    Text(startX+10, startY+10, Name.c_str());
    std::stringstream s;
    s << "Consumed Fuel: " << ConsumedFuel;
    Text(startX+10, startY+30, s.str().c_str());

}

bool Burner::contains(int X, int Y)
{
    calculatePosition();
    if(X>= startX && X<= endX && Y>= startY && Y<= endY)
    {
        return true;
    }else
    {
        return false;
    }
}
