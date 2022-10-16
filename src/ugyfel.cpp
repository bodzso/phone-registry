/**
* \file ugyfel.cpp
* Ugyfel osztály függvényeinek megvalosítása
*/
#include "ugyfel.hpp"
#include "memtrace.h"

bool Ugyfel::findUgyfel(std::fstream& is, std::string id)
{
    while (true)
    {
        std::string s;
        if (!getline(is, s)) break;
        std::istringstream ss(s);
        std::getline(ss, s, ',');

        if (s == id)
        {
            return true;
        }
    }
    return false;
}

void Ugyfel::generateNumber(std::fstream& is)
{
    std::string tmp = "06";
    switch (std::rand() % 4)
    {
    case 0:
        tmp.append("20");
        break;
    case 1:
        tmp.append("30");
        break;
    case 2:
        tmp.append("47");
        break;
    case 3:
        tmp.append("70");
        break;
    }
    std::ostringstream convert;
    int min = 1000000;
    int max = 10000000;
    while (true)
    {
        convert << std::rand() % (max - min) + min;
        if (findUgyfel(is, convert.str()))
        {
            continue;
        }
        else
        {
            break;
        }
    }
    tmp += convert.str();
    telefon = tmp;
}

Csomag* Ugyfel::getCsomag(size_t id)
{
    switch (id)
    {
    case 0:
    {
        Alap* a = new Alap;
        return a;
    }
    case 1:
    {
        MobiNet* m = new MobiNet;
        return m;
    }
    case 2:
    {
        SMSMax* s = new SMSMax;
        return s;
    }
    }
    return NULL;
}

std::string Ugyfel::serialize(std::ostream& os, size_t id)
{
    os << telefon << "," << id << "," << nev << "," << cim << std::endl;
    std::stringstream ss;
    ss << telefon << "," << id << "," << nev << "," << cim;
    return ss.str();
}

void Ugyfel::deserialize(std::istream& is)
{
    std::string s;
    if (!getline(is, s)) return;

    std::istringstream ss(s);
    std::getline(ss, s, ',');
    telefon = s;
    std::getline(ss, s, ',');
    cs = getCsomag(atoi(s.c_str()));
    std::getline(ss, s, ',');
    nev = s;
    std::getline(ss, s, ',');
    cim = s;
}
