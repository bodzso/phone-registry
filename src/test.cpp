/**
* \file test.cpp
* Tesztelõ program
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "ugyfel.hpp"
#include "vektor.hpp"
#include "gtest_lite.h"

using namespace std;

int main()
{
    fstream ugyfelek;
    fstream dijak;
    ugyfelek.open("ugyfelek.csv", ios::in | ios::app);
    dijak.open("dijak.csv");
    if (ugyfelek.is_open() && dijak.is_open())
    {
//lekerdez--------------------------------------------------------------------------------------------------------------------------
        typedef Vektor<Ugyfel*> vect;
        size_t meret = 0;
        string tmp;
        while (getline(ugyfelek, tmp)) meret++;
        vect v(meret);
        size_t i = 0;
        TEST(Test1, Lekerdez)
        {
            string honap;
            cout << "Melyik honap? ";
            getline(cin, honap);

            ugyfelek.clear();
            ugyfelek.seekg(0, ios::beg);
            for(vect::iterator it = v.begin(); it != v.end(); it++)
            {
                Ugyfel* tmp = new Ugyfel;
                tmp->deserialize(ugyfelek);
                *it = tmp;
            }
            string s;
            size_t dij = 0;
            bool found = false;
            while(true) if(!getline(dijak, s) || (s.size() < 3 && s == honap) ) break;
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
                        Alap al;
                        MobiNet mo;
                        SMSMax sm;
                        switch(i)
                        {
                        case 0:
                            EXPECT_EQ(mo.dij(72, 16), dij);
                            break;
                        case 10:
                            EXPECT_EQ(mo.dij(243, 5), dij);
                            break;
                        case 14:
                            EXPECT_EQ(sm.dij(441, 13), dij);
                            break;
                        case 24:
                            EXPECT_EQ(al.dij(783, 19), dij);
                            break;
                        case 28:
                            EXPECT_EQ(sm.dij(6, 19), dij);
                            break;
                        }
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
        END
        string s;
        size_t cs;
        Ugyfel u;
//Ügyfél bevitel--------------------------------------------------------------------------------------------------------------------------
        TEST(Test2, Alapcsomag)
        {
            Alap a;
            cout << "Nev: ";
            getline(cin, s);
            u.setNev(s);
            cout << "Cim: ";
            getline(cin, s);
            u.setCim(s);
            cout << "Csomag: ";
            getline(cin, s);
            u.setCsomag(s);
            cs = atoi(s.c_str());
            u.setTelefon("06301018467");
            s = u.serialize(cout, cs);
            ugyfelek.clear();
            u.serialize(ugyfelek, cs);
            ugyfelek.clear();
            ugyfelek.seekg(0, ios::beg);
            EXPECT_TRUE(u.findUgyfel(ugyfelek, "06301018467"));
            EXPECT_STREQ("06301018467,0,Lucy C. May,4996 Tyler Avenue", s.c_str());
            EXPECT_STREQ("Alap", u.getCsomag()->getNev().c_str());
            EXPECT_EQ(a.dij(100, 10), u.getCsomag()->dij(100, 10));
        }
        END

        TEST(Test3, MobiNet)
        {
            MobiNet m;
            cout << "Nev: ";
            getline(cin, s);
            u.setNev(s);
            cout << "Cim: ";
            getline(cin, s);
            u.setCim(s);
            cout << "Csomag: ";
            getline(cin, s);
            u.setCsomag(s);
            cs = atoi(s.c_str());
            u.setTelefon("06471026500");
            s = u.serialize(cout, cs);
            ugyfelek.clear();
            u.serialize(ugyfelek, cs);
            ugyfelek.clear();
            ugyfelek.seekg(0, ios::beg);
            EXPECT_TRUE(u.findUgyfel(ugyfelek, "06471026500"));
            EXPECT_STREQ("06471026500,1,Ann L. McCaffrey,3664 Lakewood Drive", s.c_str());
            EXPECT_STREQ("MobiNet", u.getCsomag()->getNev().c_str());
            EXPECT_EQ(m.dij(100, 10), u.getCsomag()->dij(100, 10));
        }
        END

        TEST(Test4, SMSMax)
        {
            SMSMax sm;
            cout << "Nev: ";
            getline(cin, s);
            u.setNev(s);
            cout << "Cim: ";
            getline(cin, s);
            u.setCim(s);
            cout << "Csomag: ";
            getline(cin, s);
            u.setCsomag(s);
            cs = atoi(s.c_str());
            u.setTelefon("06301015724");
            s = u.serialize(cout, cs);
            ugyfelek.clear();
            u.serialize(ugyfelek, cs);
            ugyfelek.clear();
            ugyfelek.seekg(0, ios::beg);
            EXPECT_TRUE(u.findUgyfel(ugyfelek, "06301015724"));
            EXPECT_STREQ("06301015724,2,Martin S. Jackson,2288 Leo Street", s.c_str());
            EXPECT_STREQ("SMSMax", u.getCsomag()->getNev().c_str());
            EXPECT_EQ(sm.dij(100, 10), u.getCsomag()->dij(100, 10));
        }
        END
        TEST(Test5, RandomTelephone1)
        {
            Alap a;
            cout << "Nev: ";
            getline(cin, s);
            u.setNev(s);
            cout << "Cim: ";
            getline(cin, s);
            u.setCim(s);
            cout << "Csomag: ";
            getline(cin, s);
            u.setCsomag(s);
            cs = atoi(s.c_str());
            u.generateNumber(ugyfelek);
            cout << "Number: " << u.getTelefon() << "(" << u.getTelefon().size() << ")" << endl;
            ugyfelek.clear();
            u.serialize(ugyfelek, cs);
            ugyfelek.clear();
            ugyfelek.seekg(0, ios::beg);
            EXPECT_TRUE(u.findUgyfel(ugyfelek, u.getTelefon()));
            EXPECT_EQ((size_t)11, u.getTelefon().size());
            EXPECT_STREQ("Alap", u.getCsomag()->getNev().c_str());
            EXPECT_EQ(a.dij(100, 10), u.getCsomag()->dij(100, 10));
        }
        END
        TEST(Test6, RandomTelephone2)
        {
            Alap a;
            cout << "Nev: ";
            getline(cin, s);
            u.setNev(s);
            cout << "Cim: ";
            getline(cin, s);
            u.setCim(s);
            cout << "Csomag: ";
            getline(cin, s);
            u.setCsomag(s);
            cs = atoi(s.c_str());
            u.generateNumber(ugyfelek);
            cout << "Number: " << u.getTelefon() << "(" << u.getTelefon().size() << ")" << endl;
            ugyfelek.clear();
            u.serialize(ugyfelek, cs);
            ugyfelek.clear();
            ugyfelek.seekg(0, ios::beg);
            EXPECT_TRUE(u.findUgyfel(ugyfelek, u.getTelefon()));
            EXPECT_EQ((size_t)11, u.getTelefon().size());
            EXPECT_STREQ("Alap", u.getCsomag()->getNev().c_str());
            EXPECT_EQ(a.dij(100, 10), u.getCsomag()->dij(100, 10));
        }
        END
        TEST(Test7, RandomTelephone3)
        {
            Alap a;
            cout << "Nev: ";
            getline(cin, s);
            u.setNev(s);
            cout << "Cim: ";
            getline(cin, s);
            u.setCim(s);
            cout << "Csomag: ";
            getline(cin, s);
            u.setCsomag(s);
            cs = atoi(s.c_str());
            u.generateNumber(ugyfelek);
            cout << "Number: " << u.getTelefon() << "(" << u.getTelefon().size() << ")" << endl;
            ugyfelek.clear();
            u.serialize(ugyfelek, cs);
            ugyfelek.clear();
            ugyfelek.seekg(0, ios::beg);
            EXPECT_TRUE(u.findUgyfel(ugyfelek, u.getTelefon()));
            EXPECT_EQ((size_t)11, u.getTelefon().size());
            EXPECT_STREQ("Alap", u.getCsomag()->getNev().c_str());
            EXPECT_EQ(a.dij(100, 10), u.getCsomag()->dij(100, 10));
        }
        END
    }
    else cout << "Nem lehet megnyitni a fajlt";
    ugyfelek.close();
    dijak.close();
    return 0;
}
