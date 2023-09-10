#include "WinAdapt.h"
#include "Boiler.h"
#include "Burner.h"
#include "Pipeline.h"
#include "StorageComponentContainer.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#define MAXSIZE 4
double AmountRequested;
double TemperatureRequested;

Boiler b1("Kessel1", 10, 10, 180, 200, 10, 30);
Boiler b2("Kessel2", 10, 400, 180, 200, 10, 70);
Boiler b3("Kessel3", 400, 400, 180, 200);
Boiler b4("Kessel4", 400, 10, 180, 200);
/*std::string s1= "Burner1";
std::string s2= "Burner2";
std::string s3= "Burner3";
std::string s4= "Burner4";
Burner burner1(&b1, s1);
Burner burner2(&b2, s2);
Burner burner3(&b3, s3);
Burner burner4(&b4, s4);*/
StorageComponentContainer<Burner> BurnerList(MAXSIZE);
StorageComponentContainer<Pipeline> Pipelinelist(MAXSIZE);
StorageComponentContainer<Boiler> Boilerlist(MAXSIZE);

void VtlZyk(void)
{

}

void VtlMouse(int X, int Y)
{
    for(int i =0;i<BurnerList.getNr();i++)
    {
        if(BurnerList[i]->contains(X,Y))
        {
            try
            {
                BurnerList[i]->feedFuel(0.01);
            }catch (ExceptionBoilerOverheating &ex)
            {
                std::cout<< ex.what() << std::endl;
            }
        }
    }
    for(int i = 0; i<Pipelinelist.getNr();i++)
    {
        if(Pipelinelist[i]->contains(X,Y))
        {
            Pipelinelist[i]->transferMedium(1);
        }
    }
}

void VtlKeyHit(int key)
{
    if(key <= '9' && key >= '1')
    {
        AmountRequested = (key-'0')*10;
    }else if(key <= 'Z' && key >= 'A')
    {
        TemperatureRequested = (key- 'A'+1)*5.0;
    }else if(key <= 'd' && key >= 'a')
    {
        switch(key)
        {
            case 'a':
            b1.addContent(TemperatureRequested, AmountRequested);
            break;
            case 'b':
            b2.addContent(TemperatureRequested, AmountRequested);
            break;
            case 'c':
            b3.addContent(TemperatureRequested, AmountRequested);
            break;
            case 'd':
            b4.addContent(TemperatureRequested, AmountRequested);
            break;
        }
    }else if(key == ' ')
    {
        b1.addHeat(100.0);
    }else if(key >= 0x01 && key <= 0x04)
    {
        int temp = key - 0x01;
        try
            {
                BurnerList[temp]->feedFuel(0.01);
            }catch (ExceptionBoilerOverheating &ex)
            {
                std::cout<< ex.what() << std::endl;
            }
        /*switch(key)
        {
            case 1:
            Bu1.feedFuel(0.01);
            break;
            case 2:
            Bu2.feedFuel(0.01);
            break;
            case 3:
            Bu3.feedFuel(0.01);
            break;
            case 4:
            Bu4.feedFuel(0.01);
            break;
        }*/
    }
}

void VtlInit(void)
{
    Boiler* boi[MAXSIZE] = {&b1,&b2,&b3,&b4};
    std::string temp;
    for(int i = 0; i<MAXSIZE ; i++)
    {
        temp = "Lfd-Nr" + std::to_string(i+1);
        Burner* Bui = new Burner(boi[i], temp);
        Pipeline* pi = new Pipeline(boi[i],boi[(i+1)%4]);
        Pipelinelist.add(pi);
        BurnerList.add(Bui);
        Boilerlist.add(boi[i]);
    }
}

void VtlPaint(int xl, int yo, int xr, int yu)
{
    char Textbuffer[180];
    sprintf(Textbuffer, "%.2f Liter added\n", AmountRequested);
    Text(200, 200, Textbuffer);
    char Textbuffer1[180];
    sprintf(Textbuffer1, "%.2f Celsius added\n", TemperatureRequested);
    Text(200, 230, Textbuffer1);
    for(auto item : Pipelinelist)
    {
        item.show();
    }
    for(auto item : Boilerlist)
    {
        item.show();
    }
    /*BurnerList.begin();
    do
    {
        if(BurnerList.atEnd())
        {
            break;
        }
        BurnerList.current()->show();
    }while(BurnerList.next());*/
    for(auto item : BurnerList)
    {
        item.show();
    }
    /*Bu1.show();
    Bu2.show();
    Bu3.show();
    Bu4.show();*/
}

