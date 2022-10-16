/**
* \file main.cpp
* Fõ program
*/
#ifndef CPORTA
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "ugyfel.hpp"
#include "vektor.hpp"
#include "memtrace.h"

using namespace std;

int main()
{
    typedef Vektor<Ugyfel*> vect;
    fstream ugyfelek;
    fstream dijak;
    ugyfelek.open("ugyfelek.csv", ios::in | ios::app);
    dijak.open("dijak.csv");
    if (ugyfelek.is_open() && dijak.is_open())
    {
        while(true)
        {
            cout << "XYZ Mobil KFT." << endl;
            cout << "1. lekerdez" << endl;
            cout << "2. bevitel" << endl;
            string s;
            getline(cin, s);
            cout << endl;
            if(cin.eof()) break;
            if(atoi(s.c_str()) <= 0 || atoi(s.c_str()) > 2 ) continue;

            switch(atoi(s.c_str()))
            {
            case 1:
            {
                size_t meret = 0;
                string tmp;
                ugyfelek.clear();
                ugyfelek.seekg(0, ios::beg);
                while (getline(ugyfelek, tmp)) meret++;
                vect v(meret);
                string honap;
                cout << "Melyik honap? ";
                getline(cin, honap);
                if(atoi(honap.c_str()) <= 0 || atoi(honap.c_str()) > 12 )
                {
                    cout << endl;
                    break;
                }

                ugyfelek.clear();
                ugyfelek.seekg(0, ios::beg);
                for(vect::iterator it = v.begin(); it != v.end(); it++)
                {
                    Ugyfel* tmp = new Ugyfel;
                    tmp->deserialize(ugyfelek);
                    *it = tmp;
                }

                size_t dij = 0;
                bool found = false;
                while(true) if(!getline(dijak, s) || (s.size() < 3 && s == honap) ) break;
                size_t i = 0;
                for (vect::iterator it = v.begin(); it != v.end(); it++, i++)
                {
                    cout << i << ": " << **it;
                    while (true)
                    {
                        found = false;
                        size_t perc = 0;
                        size_t sms = 0;
                        if (!getline(dijak, s)) break;
                        if ( s.size() < 3 && s != honap ) break;
                        istringstream ss(s);
                        getline(ss, s, ',');

                        if (s == (*it)->getTelefon())
                        {
                            getline(ss, s, ',');
                            perc = atoi(s.c_str());
                            getline(ss, s, ',');
                            sms = atoi(s.c_str());
                            dij = (*it)->getCsomag()->dij(perc, sms);
                            cout << dij << " Ft";
                            found = true;
                            break;
                        }
                    }
                    if(!found) cout << "0 Ft";
                    dijak.clear();
                    dijak.seekg(0, ios::beg);
                    while(true) if(!getline(dijak, s) || (s.size() < 3 && s == honap) ) break;
                    cout << endl;
                }
            }
            cout << endl;
            break;
            case 2:
            {
                string s;
                size_t cs;
                Ugyfel u;
                cout << "Nev: ";
                getline(cin, s);
                u.setNev(s);
                cout << "Cim: ";
                getline(cin, s);
                u.setCim(s);
                cout << "Csomag: ";
                getline(cin, s);
                cs = atoi(s.c_str());
                u.setCsomag(s);
                u.generateNumber(ugyfelek);
                u.serialize(cout, cs);
                ugyfelek.clear();
                u.serialize(ugyfelek, cs);
            }
            break;
            }
        }
    }
    else cout << "Nem lehet megnyitni a fajlt";
    ugyfelek.close();
    dijak.close();
    return 0;
}
#endif // CPORTA
