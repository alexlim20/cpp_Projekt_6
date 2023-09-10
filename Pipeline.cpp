#include "Pipeline.h"
#include "WinAdapt.h"
#include "Boiler.h"

Pipeline::Pipeline(Boiler* Source, Boiler* Target, int Pumpsize)
:Source(Source), Target(Target), Pumpsize(Pumpsize){}

void Pipeline::transferMedium(double Amount)
{
    double deliver =0.0;
    double temp = 0.0;
    if(Source->getContainedVolume()!=0)
    {
        Source->ExtractMedium(Amount, deliver, temp);
        Target->addContent(temp, deliver);
    }
}

void Pipeline::calculatePosition()
{
    startX = Source->getXPosition()+Source->getWidth()/2;
    startY = Source->getYPosition()+Source->getHeight()/2;
    endX = Target->getXPosition()+Target->getWidth()/2;
    endY = Target->getYPosition()+Target->getHeight()/2;
    midX = startX + (endX-startX)/2;
    midY = startY + (endY-startY)/2;
}

void Pipeline::show()
{
    calculatePosition();
    Line(startX, startY, endX, endY);
    Elli(midX-Pumpsize/2, midY-Pumpsize/2, midX+Pumpsize/2, midY+Pumpsize/2);

}

bool Pipeline::contains(int X, int Y)
{
    calculatePosition();
    int r = Pumpsize/2;
    if((((X-midX)*(X-midX))+((Y-midY)*(Y-midY))) < r*r)
    {
        return true;
    }else
    {
        return false;
    }
}
