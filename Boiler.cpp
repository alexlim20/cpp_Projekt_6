#include "Boiler.h"
#include <iostream>
#include "WinAdapt.h"
#include <cstdio>
#include <sstream>

ExceptionBoilerOverheating::ExceptionBoilerOverheating(Boiler* Kess, double KesselTemperatur, double KesselInhalt, double AddedHeat)
: FailingBoiler(Kess), BoilerTemperature(KesselTemperatur), BoilerContent(KesselInhalt), AddedHeat(AddedHeat)
{
    std::stringstream ss;
    ss << FailingBoiler->getName() << " with temperature of " << BoilerTemperature << " and volume of " << BoilerContent << " cannot be added with energy of " << AddedHeat;
    s = ss.str();
}

const char* ExceptionBoilerOverheating::what() const noexcept
{
    return s.c_str();
}

Boiler::Boiler(const char* Name, int X, int Y, int Width, int Height, double ContainedVolume, double ContentTemperature)
: XPosition(X), YPosition(Y), Width(Width), Height(Height), ContainedVolume(ContainedVolume), ContentTemperature(ContentTemperature)
{
    char *NewName = new char[40];
    strcpy(NewName, Name);
    this->Name = NewName;

    /*
    const char *NewName = new char[40];
    NewName = Name;
    this->Name= Name; ->falsch */
}

Boiler::~Boiler()
{
    /*delete[]Name;*/
}

void Boiler::addContent(double MediaTemperature, double MediaAmount)
{
    double temp = ((ContainedVolume*ContentTemperature) + (MediaAmount*MediaTemperature))/(ContainedVolume+MediaAmount);
    ContainedVolume += MediaAmount;
    ContentTemperature = temp;
}

void Boiler::show()
{
    char TextBuffer[128];
    char TextBuffer1[128];
    char TextBuffer2[128];
    Rect(XPosition, YPosition, XPosition+Width, YPosition+Height);
    Text(XPosition+10, YPosition+10, Name);
    sprintf(TextBuffer, "%.2f Liter\n", ContainedVolume);
    sprintf(TextBuffer1, "%.2f Celsius", ContentTemperature);
    sprintf(TextBuffer2, "%.2f Joule", calculateEnergy());
    Text(XPosition+10, YPosition+50, TextBuffer);
    Text(XPosition+10, YPosition+80, TextBuffer1);
    Text(XPosition+10, YPosition+110, TextBuffer2);
}

double Boiler::calculateEnergy()
{

    double mass = 998.0*ContainedVolume*0.001*4200.0*ContentTemperature;
    return mass;
}

void Boiler::addHeat(double Amount)
{
    ExceptionBoilerOverheating ex = ExceptionBoilerOverheating(this, ContentTemperature, ContainedVolume, Amount);
    double temp = (Amount)/(4.2*ContainedVolume);
    if((ContentTemperature+temp) >= 3000.0)
    {
        throw ex;
    }
    ContentTemperature += temp;

}

void Boiler::ExtractMedium(double AmountRequested, double& AmountDelivered, double& Temperature)
{
    if(AmountRequested <= ContainedVolume)
    {
        ContainedVolume -= AmountRequested;
        AmountDelivered = AmountRequested;
    }
    Temperature = ContentTemperature;
}

int Boiler::getXPosition()
{
    return XPosition;
}

int Boiler::getYPosition()
{
    return YPosition;
}

int Boiler::getWidth()
{
    return Width;
}

int Boiler::getHeight()
{
    return Height;
}

const char* Boiler::getName() const
{
    return Name;
}

double Boiler::getContainedVolume()
{
    return ContainedVolume;
}
