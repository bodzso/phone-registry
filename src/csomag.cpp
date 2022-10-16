/**
* \file csomag.cpp
* Csomag osztály függvényeinek megvalosítása
*/

#include "csomag.hpp"

size_t Alap::dij(size_t perc, size_t sms)
{
    return perc_dij * perc + sms_dij * sms;
}

size_t MobiNet::dij(size_t perc, size_t sms)
{
    if(sms <= ingyen_sms)
        return perc_dij * perc;
    else
        return perc_dij * perc + sms_dij * (sms - ingyen_sms);
}

size_t SMSMax::dij(size_t perc, size_t sms)
{
    return perc_dij * perc + sms_dij * sms;
}
