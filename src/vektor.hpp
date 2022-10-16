/**
* \file vektor.hpp
* Vektor osztály
*/
#ifndef VEKTOR_HPP_INCLUDED
#define VEKTOR_HPP_INCLUDED

#include <iostream>
#include "memtrace.h"

///@param T – adat típus
template <typename T>
///Vektor osztály tároláshoz
class Vektor
{
private:
    T * tomb; ///A vektor kezdeti címe
    size_t meret; ///A vektor maximális mérete
public:
    ///@param m – vektor max mérete
    Vektor(size_t m = 0) : meret(m)
    {
        tomb = new T[m];
        for (size_t i = 0; i < m; i++)
            tomb[i] = 0;
    }
    ///T* tomb felszabadítása
    ~Vektor()
    {
        for (size_t i = 0; i < meret; i++)
        {
            delete tomb[i];
        }
        delete[] tomb;
    }
    /**
    * @brief Tömbindexelés
    * @param i - Index
    */
    T& operator[] (size_t i)
    {
        return tomb[i];
    }
    /**
    * @brief Tömbindexelés const verzió
    * @param i - Index
    */
    T const & operator[] (size_t i) const
    {
        return tomb[i];
    }
    ///Iterátor az elemek könnyebb eléréséhez
    class iterator
    {
        T* p; ///Jelenlegi elem
    public:
        ///@param pt - Pointer vektor egy elemére
        iterator(T* pt) : p(pt) { }
        ///@return *p - Jelenlegi elem visszadása
        T& operator*()
        {
            return *p;
        }
        iterator operator++()
        {
            p++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator i = *this;
            p++;
            return i;
        }
        bool operator==(const iterator& rhs)
        {
            return p == rhs.p;
        }
        bool operator!=(const iterator& rhs)
        {
            return p != rhs.p;
        }
    };

    ///@return iterator - elejére mutató iterator
    iterator begin()
    {
        return iterator(tomb);
    }
    ///@return iterator - végére mutató iterator
    iterator end()
    {
        return iterator(tomb+meret);
    }
};

#endif // VEKTOR_HPP_INCLUDED
