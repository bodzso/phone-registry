/**
* \file csomag.hpp
* Csomag osztály
* Ügyfelek tartozásainak számolásához
*/
#ifndef CSOMAG_H_INCLUDED
#define CSOMAG_H_INCLUDED

#include <string>
#include <iostream>
#include "memtrace.h"

///Csomag osztály
class Csomag
{
protected:
    ///Csomag neve
    std::string nev;
    ///Csomag perc díja
    size_t perc_dij;
    ///Csomag sms díja
    size_t sms_dij;
public:
    /**
    *@param n - Csomag neve
    *@param p - Csomag percdíja
    *@param s - Csomag smsdíja
    */
    Csomag(std::string n, size_t p, size_t s) : nev(n), perc_dij(p), sms_dij(s) {}

    ///@return Csomag neve
    std::string getNev()
    {
        return nev;
    }
    ///@return Csomag percdíja
    size_t getPerc_dij()
    {
        return perc_dij;
    }
    ///@return Csomag smsdíja
    size_t getSms_dij()
    {
        return sms_dij;
    }
    /**
    *@brief Csomag árat számító függvény
    *@param perc - Csomag percdíja
    *@param sms - Csomag smsdíja
    */
    virtual size_t dij(size_t perc, size_t sms) = 0;
    virtual ~Csomag() {}
};
///Alap Csomag
class Alap : public Csomag
{
public:
    /**
    *@param n - Csomag neve
    *@param p - Csomag percdíja
    *@param s - Csomag smsdíja
    */
    Alap(std::string n = "Alap", size_t p = 20, size_t s = 5) : Csomag(n, p, s) {}

    /**
    *@brief csomag árat számító függvény
    *@param perc - Ugyfel lebeszélt percei
    *@param sms - Ugyfel által küldött sms szám
    *@return Fizetendő összeg
    */
    size_t dij(size_t perc, size_t sms);
};
///MobiNet Csomag, ingyen sms opció
class MobiNet : public Csomag
{
    ///Ingyen sms max száma
    size_t ingyen_sms;
public:
    /**
    *@param n - Csomag neve
    *@param p - Csomag percdíja
    *@param s - Csomag smsdíja
    *@param is – ingyen sms max száma
    */
    MobiNet(std::string n = "MobiNet", size_t p = 30, size_t s = 5, size_t is = 5) : Csomag(n, p, s), ingyen_sms(is) {}

    /**
    *@brief Csomag árat számító függvény
    *@param perc - Ugyfel lebeszélt percei
    *@param sms - Ugyfel által küldött sms szám
    *@return Fizetendő összeg
    */
    size_t dij(size_t perc, size_t sms);
};
///SMSMax, Csomag kedvezményes sms
class SMSMax : public Csomag
{
public:
    /**
    *@param n - Csomag neve
    *@param p - Csomag percdíja
    *@param s - Csomag smsdíja
    */
    SMSMax(std::string n = "SMSMax", size_t p = 50, size_t s = 2) : Csomag(n, p, s) {}
    /**
    *@brief Csomag árat számító függvény
    *@param perc - Ugyfel lebeszélt percei
    *@param sms - Ugyfel által küldött sms szám
    *@return Fizetendő összeg
    */
    size_t dij(size_t perc, size_t sms);
};

#endif // CSOMAG_H_INCLUDED
