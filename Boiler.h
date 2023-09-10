#ifndef BOILER_H
#define BOILER_H
#include <stdexcept>
#include <sstream>

class Boiler
{
    double ContentTemperature;
    double ContainedVolume;
    int XPosition;
    int YPosition;
    int Width;
    int Height;
    const char* Name;
    public:
    Boiler(const char* Name, int X, int Y, int Width = 150, int Height = 150, double ContainedVolume = 0.0, double ContentTemperature = 0.0);
    ~Boiler();
    void addContent(double MediaTemperature, double MediaAmount);
    void show();
    double calculateEnergy();
    void addHeat(double Amount);
    void ExtractMedium(double AmountRequested, double& AmountDelivered, double& Temperature);
    int getXPosition();
    int getYPosition();
    int getWidth();
    int getHeight();
    double getContainedVolume();
    const char* getName()const;
};

class ExceptionBoilerOverheating : public std::exception
{
    double BoilerTemperature;
    double BoilerContent;
    double AddedHeat;
    Boiler* FailingBoiler;
    std::string s;
public:
    ExceptionBoilerOverheating(Boiler* Kess, double KesselTemperatur, double KesselInhalt, double AddedHeat);
    const char* what()const noexcept;
};

#endif // BOILER
