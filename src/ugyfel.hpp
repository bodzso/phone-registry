/**
* \file ugyfel.hpp
* Ugyfel osztály
* Az ügyfelek adatait tartalmazó osztály
*/
#ifndef UGYFEL_HPP_INCLUDED
#define UGYFEL_HPP_INCLUDED

#include <iostream>
#include <string>
#include <sstream> //fájl kezelés
#include <fstream> //fájl kezelés
#include <cstdlib> //random szám
#include <ctime> //random szám

#include "csomag.hpp"
#include "memtrace.h"
///Ugyfel osztály
class Ugyfel
{
protected:
    ///Ügyfél neve
    std::string nev;
    ///Ügyfél címe
    std::string cim;
    ///Ügyfél telefonszáma
    std::string telefon;
    ///Az ügyfél csomaga
    Csomag * cs;
public:
    /**
    *@param n - Ugyfel neve
    *@param c - Ugyfel címe
    *@param t - Ugyfel telefonszáma
    */
    Ugyfel(std::string n = "", std::string c = "", std::string t = "") : nev(n), cim(c), telefon(t), cs(NULL) {}

    ///@param u - Ugyfel objektum
    Ugyfel(Ugyfel& u)
    {
        nev = u.nev;
        cim = u.cim;
        telefon = u.telefon;
        cs = NULL;
        std::srand(std::time(NULL)); ///A telefonszám generálásához
    }
    ~Ugyfel()
    {
        delete cs;
    }
    /**
    *@brief Megkeresi, hogy egy adott azonosító(ügyfél) létezik-e a is-ben
    *@param is - input stream
    *@param id - telefonszám
    */
    bool findUgyfel(std::fstream& is, std::string id);
    /**
    *@brief Telefonszámot generál
    *@param is - input stream
    */
    void generateNumber(std::fstream& is);
    ///@return cs - Csomag objektum
    Csomag* getCsomag()
    {
        return cs;
    }
    ///Fájból kiolvasott azonosító alapján visszaad egy Csomag objektumot
    Csomag* getCsomag(size_t id);
    //getters, setters
    ///@return nev - Ugyfel neve
    std::string getNev()
    {
        return nev;
    }
    ///@return Ugyfel címe
    std::string getCim()
    {
        return cim;
    }
    ///@return Ugyfel telefonszáma
    std::string getTelefon()
    {
        return telefon;
    }
    ///@param nev - Ugyfel neve
    void setNev(std::string nev)
    {
        this->nev = nev;
    }
    ///@param cim - Ugyfel címe
    void setCim(std::string cim)
    {
        this->cim = cim;
    }
    ///@param telefon - Ugyfel telefonszáma
    void setTelefon(std::string telefon)
    {
        this->telefon = telefon;
    }
    ///@param csomag - Csomag azonosítója
    void setCsomag(std::string csomag)
    {
        if(cs) delete cs;
        cs = getCsomag(atoi(csomag.c_str()));
    }
    /**
    *@brief Ügyfél Nevét, Csomagát kiíró függvény
    *@param os - ostream
    */
    void print(std::ostream& os) const
    {
        os << nev << "(" << cs->getNev() << "): ";
    }
    /**
    *@brief Ugyfel tipushoz egyszerűbb kiírás ostreamen
    *@param os - ostream
    *@param u - Ugyfel objektum
    */
    friend std::ostream& operator<< (std::ostream& os, const Ugyfel& u)
    {
        u.print(os);
        return os;
    }
    /**
    *@brief Fájlba íráshoz
    *@param os - ostream
    *@param id - Ugyfel Csomag azonosítója
    *@return serialized Ugyfel objektum
    */
    std::string serialize(std::ostream& os, size_t id = 0);
    /**
    *@brief Fájlból olvasáshoz
    *@param is - istream
    */
    void deserialize(std::istream& is);
};

#endif // UGYFEL_HPP_INCLUDED
