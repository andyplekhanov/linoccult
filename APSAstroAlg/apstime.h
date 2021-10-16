//------------------------------------------------------------------------------
//
// File:    apstime.h
//
// Purpose: Functions and classes handling time.
//          Based on Oliver Montenbruck and Thomas Pfleger code
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 22.05.2004
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//------------------------------------------------------------------------------

#ifndef APS_TIME_H
#define APS_TIME_H

#include <iostream>

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apsastrodata {
    class APSTaiUtcData;
    class APSEtUtData;
  }

  namespace apsastroalg {

const double ET_MINUS_TAI = 32.184;

// Format tag for date and time output (used by DateTime class output operator)
enum TimeFormat { 
  None,   // don't output time (date only)
  DDd,    // output time as fractional part of a day
  HHh,    // output time as hours with one decimal place
  HHMM,   // output time as hours and minutes (rounded to next minute)
  HHMMSS  // output time as hours, minutes and seconds (rounded to next s)
};

//------------------------------------------------------------------------------
//
// ETminUT: Difference ET-UT of ephemeris time and universal time
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// Output:
//
//   DTsec     ET-UT in [s]
//   valid     Flag indicating T in domain of approximation
//
// Notes: Approximation spans the years from 1825 to 2005
//
//------------------------------------------------------------------------------

void ETminUT( const double T, double& DTsec, bool& valid);

//------------------------------------------------------------------------------
//
// GMST: Greenwich mean sidereal time
//
// Input:
//
//   MJD       Time as Modified Julian Date
//
// <return>:   GMST in [rad]
//
//------------------------------------------------------------------------------

double GMST( const double MJD );

//------------------------------------------------------------------------------
//
// Mjd: Modified Julian Date from calendar date and time
//
// Input:
//
//   Year      Calendar date components
//   Month
//   Day
//   Hour      Time components (optional)
//   Min
//   Sec
//
// <return>:   Modified Julian Date
//
//------------------------------------------------------------------------------

double Mjd( int Year, int Month, const int Day, 
            const int Hour = 0, const int Min = 0, const double Sec = 0.0 );

//------------------------------------------------------------------------------
//
// CalDat: Calendar date and time from Modified Julian Date
//
// Input:
//
//   Mjd       Modified Julian Date
//
// Output:
//
//   Year      Calendar date components
//   Month
//   Day
//   Hour      Decimal hours
//
//------------------------------------------------------------------------------

void CalDat( const double Mjd,
             int& Year, int& Month, int& Day, double & Hour );

//------------------------------------------------------------------------------
//
// CalDat: Calendar date and time from Modified Julian Date
//
// Input:
//
//   Mjd       Modified Julian Date
//
// Output:
//
//   Year      Calendar date components
//   Month
//   Day
//   Hour      Time components
//   Min
//   Sec
//
//------------------------------------------------------------------------------

void CalDat( const double Mjd, 
             int& Year, int& Month, int& Day,
             int& Hour, int& Min, double& Sec );

//
// Auxiliary class for time output
//
class Time 
{
  public:
  
    // Constructors
    Time();
    Time( const double Hour, const TimeFormat Format=HHMMSS ); 
    
    // Modifiers
    void Set( const TimeFormat Format=HHMMSS );

    // Time output
    friend std::ostream& operator << (std::ostream& os, const Time& time);

  private:

    double      m_Hour;
    TimeFormat  m_Format;
};

//
// Auxiliary class for date and time output
//
class DateTime 
{
  public:
  
    // Constructors
    DateTime();
    DateTime( const double Mjd, const TimeFormat Format=None ); 
    
    // Modifiers
    void Set( const TimeFormat Format=HHMMSS );

    // Time output
    friend std::ostream& operator << (std::ostream& os, const DateTime& DT);

  private:

    double      m_Mjd;
    TimeFormat  m_Format;
};

typedef enum {
  APS_UT1 = 0,
  APS_ET,
  APS_TAI,
  APS_UTC
} APS_TIME_TYPE;

using apslib::APSSubModule;
using apsastrodata::APSTaiUtcData;
using apsastrodata::APSEtUtData;

class APSModuleTime;

class APSTime
{
  private:

    APSModuleTime * pModule;
    APSTaiUtcData * pAPSTaiUtcData;
    APSEtUtData   * pAPSEtUtData;

    int timnf( int & mjd, double & sec, const APS_TIME_TYPE scale ) const;

  public:

    APSTime( APSSubModule * pAPSSubModule );

    ~APSTime( void );

    APSTaiUtcData * GetAPSTaiUtcData( void )
      { return( pAPSTaiUtcData ); }

    APSEtUtData * GetAPSEtUtData( void )
      { return( pAPSEtUtData ); }

    int cnvtim( const int mjd1, const double sec1, const APS_TIME_TYPE scale1,
                int & mjd2, double & sec2, const APS_TIME_TYPE scale2 ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
