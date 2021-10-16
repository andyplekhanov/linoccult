//------------------------------------------------------------------------------
//
// File:    apstime.cc
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

#include <cmath>
#include <iomanip>

#include <stdint.h>
#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsangle.h"
#include "apstaiutcdata.h"
#include "apsetutdata.h"
#include "apsmoduletime.h"
#include "apstime.h"
#include "apstimeetutsubmodule.h"
#include "apstimetaiutcsubmodule.h"

namespace aps {

  namespace apsastroalg {

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
// Notes: The approximation spans the years from 1825 to 2005
//
//------------------------------------------------------------------------------

void ETminUT( const double T, double& DTsec, bool& valid )
{
  //
  // Variables
  //
  int    i = (int) floor(T/0.25);
  double t = T-i*0.25;


  if ( (T<-1.75) || (0.05<T) ) {
    valid = false;
    DTsec = 0.0;
  }
  else {
    valid = true;
    switch (i) {
      case -7: DTsec=10.4+t*(-80.8+t*( 413.9+t*( -572.3))); break; // 1825-
      case -6: DTsec= 6.6+t*( 46.3+t*(-358.4+t*(   18.8))); break; // 1850-
      case -5: DTsec=-3.9+t*(-10.8+t*(-166.2+t*(  867.4))); break; // 1875-
      case -4: DTsec=-2.6+t*(114.1+t*( 327.5+t*(-1467.4))); break; // 1900-
      case -3: DTsec=24.2+t*( -6.3+t*(  -8.2+t*(  483.4))); break; // 1925-
      case -2: DTsec=29.3+t*( 32.5+t*(  -3.8+t*(  550.7))); break; // 1950-
      case -1: DTsec=45.3+t*(130.5+t*(-570.5+t*( 1516.7))); break; // 1975-
      case  0: t+=0.25;
               DTsec=45.3+t*(130.5+t*(-570.5+t*( 1516.7)));        // 2000-
    }                                                              // 2005
  }
}

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

double GMST( const double MJD )
{
  //
  // Constants
  //
  const double Secs = 86400.0;        // Seconds per day


  //
  // Variables
  //
  double MJD_0, UT, T_0, T, gmst;


  MJD_0 = floor ( MJD );
  UT    = Secs*(MJD-MJD_0);     // [s]
  T_0   = (MJD_0-51544.5)/36525.0; 
  T     = (MJD  -51544.5)/36525.0; 

  gmst  = 24110.54841 + 8640184.812866*T_0 + 1.0027379093*UT 
          + (0.093104-6.2e-6*T)*T*T;      // [sec]

  return  ( apsmathlib::pi2 / Secs) * apsmathlib::Modulo( gmst, Secs );   // [Rad]
}

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
            const int Hour, const int Min, const double Sec )
{
  //
  // Variables
  //
  int32_t MjdMidnight;
  double  FracOfDay;
  int     b;


  if( Month <= 2 ) { Month+=12; --Year;}
  
  if ( (10000L*Year+100L*Month+Day) <= 15821004L )
    b = -2 + ((Year+4716)/4) - 1179;     // Julian calendar 
  else
    b = (Year/400)-(Year/100)+(Year/4);  // Gregorian calendar 
    
  MjdMidnight = 365L*Year - 679004L + b + int(30.6001*(Month+1)) + Day;
  FracOfDay   = apsmathlib::Ddd(Hour,Min,Sec) / 24.0; 

  return MjdMidnight + FracOfDay;
}

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
             int& Year, int& Month, int& Day, double & Hour )
{
  //
  // Variables
  //
  int32_t a,b,c,d,e,f;
  double  FracOfDay;


  // Convert Julian day number to calendar date
  a = int32_t(Mjd+2400001.0);

  if ( a < 2299161 ) {  // Julian calendar
    b = 0;
    c = a + 1524;
  }
  else {                // Gregorian calendar
    b = int32_t((a-1867216.25)/36524.25);
    c = a +  b - (b/4) + 1525;
  }

  d     = int32_t ( (c-122.1)/365.25 );
  e     = 365*d + d/4;
  f     = int32_t ( (c-e)/30.6001 );

  Day   = c - e - int(30.6001*f);
  Month = f - 1 - 12*(f/14);
  Year  = d - 4715 - ((7+Month)/10);

  FracOfDay = Mjd - floor(Mjd);

  Hour = 24.0*FracOfDay;
}

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
             int& Hour, int& Min, double& Sec )
{
  //
  // Variables
  //
  double Hours;


  CalDat (Mjd, Year, Month, Day, Hours); 
  
  apsmathlib::DMS (Hours, Hour, Min, Sec);
}

//
// Implementation of class Time constructors and member functions
//

Time::Time ()
 : m_Hour(0.0),
   m_Format(HHMMSS)
{
}

Time::Time( const double Hour, const TimeFormat Format )
 : m_Hour(Hour),
   m_Format(Format)
{
}

void Time::Set( const TimeFormat Format )
{
  m_Format = Format;
}

std::ostream & operator << ( std::ostream & os, const Time & time )
{
  //
  // Variables
  //
  double Hour, S;
  int    H,M;


  os << std::right;

  switch ( time.m_Format ) {

    case HHh:

      os << std::fixed << std::setprecision(1);
      os << std::setw(4) << time.m_Hour;
      
      break;

    case HHMM:

      // round to 1 min
      Hour = floor(60.0*time.m_Hour+0.5)/60.0+0.00001;

      apsmathlib::DMS( Hour, H, M, S );

      os.fill('0');
      os << std::setw(2) << H << ":" << std::setw(2) << M;
      os.fill(' ');
      
      break;

    case HHMMSS:

      // round to 1 sec
      Hour = floor(3600.0*time.m_Hour+0.5)/3600.0+0.0000001;

      apsmathlib::DMS( Hour, H, M, S );

      os.fill('0');
      os << std::setw(2) << H << ":" << std::setw(2) << M << ":" << std::setw(2) << int(S);
      os.fill(' ');

    default:;
  }
   
  return os;
}

//
// Implementation of class DateTime constructors and member functions
//

DateTime::DateTime ()
 : m_Mjd(0.0),
   m_Format(None)
{
}

DateTime::DateTime( const double Mjd, const TimeFormat Format )
 : m_Mjd(Mjd),
   m_Format(Format)
{
}

void DateTime::Set( const TimeFormat Format )
{
  m_Format = Format;
}

std::ostream & operator << ( std::ostream & os, const DateTime & DT )
{
  //
  // Variables
  //
  double MjdRound, Hours, S;
  int    Year, Month, Day;
  int    H, M;


  os << std::right;

  switch ( DT.m_Format ) {

    case None:

      CalDat (DT.m_Mjd, Year, Month, Day, Hours);
      
      os.fill('0');
      os << std::setw(4) << Year  << "/" 
         << std::setw(2) << Month << "/" 
         << std::setw(2) << Day; 
      os.fill(' ');
      
      break;

    case DDd:

      CalDat (DT.m_Mjd, Year, Month, Day, Hours);
      
      os.fill('0');
      os << std::setw(4) << Year  << "/" 
         << std::setw(2) << Month << "/" 
         << std::fixed << std::setw(3+os.precision()) << Day + Hours / 24.0;
      os.fill(' ');

      break;

    case HHh:

      // round to 0.1h
      MjdRound = floor(240.0*DT.m_Mjd+0.5)/240.0+0.0001;

      CalDat (MjdRound, Year, Month, Day, Hours);
      
      os.fill('0');
      os << std::setw(4) << Year  << "/" 
         << std::setw(2) << Month << "/" 
         << std::setw(2) << Day   << " "; 

      os << std::fixed << std::setprecision(1);
      os << std::setw(4) << Hours;
      os.fill(' ');
      
      break;

    case HHMM:

      // round to 1 min
      MjdRound = floor(1440.0*DT.m_Mjd+0.5)/1440.0+0.00001;

      CalDat (MjdRound, Year, Month, Day, H, M, S);
      
      os.fill('0');
      os << std::setw(4) << Year  << "/" 
         << std::setw(2) << Month << "/" 
         << std::setw(2) << Day   << " "; 
      os << std::setw(2) << H << ":"
         << std::setw(2) << M;
      os.fill(' ');
      
      break;

    case HHMMSS:

      // round to 1 sec
      MjdRound = floor(86400.0*DT.m_Mjd+0.5)/86400.0+0.000001;

      CalDat (MjdRound, Year, Month, Day, H, M, S);
      
      os.fill('0');
      os << std::setw(4) << Year  << "/" 
         << std::setw(2) << Month << "/" 
         << std::setw(2) << Day   << " "; 
      os << std::setw(2) << H << ":" 
         << std::setw(2) << M << ":" 
         << std::setw(2) << int(S);
      os.fill(' ');
  }
   
  return os;
}

APSTime :: APSTime( APSSubModule * pAPSSubModule )
{
  pModule        = new APSModuleTime( pAPSSubModule );
  pAPSEtUtData   = new APSEtUtData( pModule->GetTimeEtUtSubModulePtr() );
  pAPSTaiUtcData = new APSTaiUtcData( pModule->GetTimeTaiUtcSubModulePtr() );
}

APSTime :: ~APSTime( void )
{
  delete pAPSTaiUtcData;
  delete pAPSEtUtData;
  delete pModule;
}

//============================= timnf ===============================

/*           MJD,SEC are normalized, namely SEC is reduced within
*           the limits 0 <= SEC < LOD, and MJD is changed accordingly;
*           LOD (length of the day) is usually 86400 s, but can be
*           different from that value in the case of UTC, due to
*           leap seconds
*/

int APSTime :: timnf( int & mjd, double & sec, const APS_TIME_TYPE scale ) const
{
  const int NITMAX = 5;
  const int NITUTC = 20;

  /* Non-trivial case: UTC (the duration of the day can be different
     from 86400 s)*/

  if( scale == APS_UTC ) {
    bool quit = false;
    int  nit = 0;

    do {
      nit++;

      if( sec < 0.0 ) {
        // Duration in seconds of the previous day
        int itaiut, itaiut_prev;

        if( pAPSTaiUtcData->GetValue( mjd, itaiut ) ) {
          break;
        }

        if( pAPSTaiUtcData->GetValue( mjd - 1, itaiut_prev ) ) {
          break;
        }

        int idur = 86400 + itaiut - itaiut_prev;
        sec = sec + idur;
        mjd = mjd - 1;
      }
      else {
        quit = true;
      }
    } while( !quit && ( nit <= NITUTC ) );

    if( !quit ) {
      pModule->ErrorMessage( APS_TIME_NITUTC );
      return( APS_TIME_NITUTC );
    }

    /* Decomposition of SEC into integer part (ISEC) + fraction (FSEC),
       where 0 <= FSEC < 1 */

    int    isec = static_cast<int>( std::floor( sec ) );
    double fsec = sec - isec;

    // Duration in seconds of today (MJD)

    quit = false;

    do {
      int itaiut_next, itaiut;

      if( pAPSTaiUtcData->GetValue( mjd + 1, itaiut_next ) ) {
        break;
      }

      if( pAPSTaiUtcData->GetValue( mjd, itaiut ) ) {
        break;
      }

      int idur = 86400 + itaiut_next - itaiut;

      if( isec >= idur) {
        // Renormalization of time

        isec = isec - idur;
        mjd = mjd + 1;
      }
      else {
        quit = true;
      }
    } while( !quit );

    if( !quit ) {
      pModule->ErrorMessage( APS_TIME_RENOM );
      return( APS_TIME_RENOM );
    }

    sec = isec + fsec;
  }
  else {

    /* Trivial case: the duration of the day is always 86400 s
     * Also this case requires iterations, due to rounding-off problems.
     * EXAMPLE: Let's suppose that the starting values are MJD=48000,
     * SEC=-1.d-14. The result of the first iteration is then:
     *    SEC --> SEC+86400 = 86400 EXACTLY (due to rounding off)
     *    MJD --> MJD-1 = 47999
     * Therefore, a second iteration is required, giving:
     *    SEC --> SEC-86400 = 0
     *    MJD --> MJD+1 = 48000 */

    bool quit = false;
    int  nit  = 0;

    do {
      nit++;

      int k = static_cast<int>( std::floor( sec / 86400.0 ) );

      if( sec < 0.0 ) {
        k = k - 1;
      }

      if( k == 0 ) {
        quit = true;
        break;
      }

      mjd = mjd + k;
      sec = sec - k * 86400.0;
    } while( nit <= NITMAX );

    if( !quit ) {
      pModule->ErrorMessage( APS_TIME_NITMAX );
      return( APS_TIME_NITMAX );
    }
  }

  return( APS_TIME_NO_ERROR );
}

//========================== cnvtim =============================

/* INPUT:   MJD1      -  Modified Julian Day (integer part)
*           SEC1      -  Seconds within day
*           SCALE1    -  Input time scale
*           SCALE2    -  Output (required) time scale
*
* OUTPUT:   MJD2      -  Modified Julian Day (integer part)
*           SEC2      -  Seconds within day
*
* Supported time scales:
*        UT1
*        TAI
*        UTC
*        ET
*/

int APSTime :: cnvtim( const int mjd1, const double sec1, const APS_TIME_TYPE scale1,
                       int & mjd2, double & sec2, const APS_TIME_TYPE scale2 ) const
{
  const int    NITMAX  = 5;
  const int    LOOPMAX = 7;
  const double EPST    = 1e-10;

  int           loops = 0;
  APS_TIME_TYPE scale = scale1;
  int           RetCode = APS_TIME_NO_ERROR;

  mjd2  = mjd1;
  sec2  = sec1;
  scale = scale1;

  do {
    loops++;

    if( timnf( mjd2, sec2, scale ) ) {
      pModule->ErrorMessage( APS_TIME_CVTTIM1 );
      RetCode = APS_TIME_CVTTIM1;
      break;
    }

    // Required timescale has been reached
    if( scale == scale2 ) {
      break;
    }

    /* Transformations are performed according to the following path:
     *
     *                 UT1 -- TDT -- TAI -- UTC
     */

    if( scale == APS_UT1 ) {
      // Conversion UT1 --> ET

      double tjm2 = mjd2 + sec2 / 86400.0;

      double dt;

      if( pAPSEtUtData->GetValue( tjm2, dt ) ) {
        pModule->ErrorMessage( APS_TIME_CVTTIM2 );
        RetCode = APS_TIME_CVTTIM2;
        break;
      }

      sec2  = sec2 + dt;
      scale = APS_ET;
    }
    else {
      if( scale == APS_ET ) {
        if( scale2 == APS_UT1 ) {

          /* Conversion TDT --> UT1 (iterative method)
           *   a) computation of DT = TDT - UT1 using (mjd2,sec2) (TDT) as an
           *      approximate value of UT1
           */

          double tjm2 = mjd2 + sec2 / 86400.0;

          double dt;

          if( pAPSEtUtData->GetValue( tjm2, dt ) ) {
            pModule->ErrorMessage( APS_TIME_CVTTIM3 );
            RetCode = APS_TIME_CVTTIM3;
            break;
          }

          /*   b) subtract DT from (mjd2,sec2), finding a first approximation
           *      for UT1
           */

          int    mjdt = mjd2;
          double sect = sec2 - dt;

          //   start iterations

          bool quit = false;
          int  nit  = 0;

          do {
            nit++;

            if( timnf( mjdt, sect, APS_UT1 ) ) {
              break;
            }

            /*   c) try to find the starting value of ET from the approximate
             *      value of UT1
             */

            double tjmt = mjdt + sect / 86400.0;

            double dt;

            if( pAPSEtUtData->GetValue( tjmt, dt ) ) {
              break;
            }

            int    mjd2r = mjdt;
            double sec2r = sect + dt;

            if( timnf( mjd2r, sec2r, APS_ET ) ) {
              break;
            }

            //   d) computation of error and correction of the approximate value

            double err = ( mjd2r - mjd2 ) * 86400.0 + sec2r - sec2;

            if( fabs( err ) > EPST ) {
              sect = sect - err;
            }
            else {
              quit = true;
            }
          } while( !quit && ( nit <= NITMAX ) );

          if( !quit ) {
            pModule->ErrorMessage( APS_TIME_CVTTIM4 );
            RetCode = APS_TIME_CVTTIM4;
            break;
          }

          mjd2  = mjdt;
          sec2  = sect;
          scale = APS_UT1;
        }
        else {
          // Conversion ET --> TAI

          sec2  = sec2 - ET_MINUS_TAI;
          scale = APS_TAI;
        }
      }
      else {
        if( scale == APS_TAI ) {
          if( scale2 == APS_UTC ) {

            /* Conversion TAI --> UTC (iterative method)
             *   a) computation of DAT = TAI - UTC using (mjd2,sec2) (TAI) as an
             *      approximate value of UTC
             */

            int    mjdt = mjd2;
            double sect = sec2;
            int    dat;

            if( pAPSTaiUtcData->GetValue( mjdt, dat ) ) {
              pModule->ErrorMessage( APS_TIME_CVTTIM5 );
              RetCode = APS_TIME_CVTTIM5;
              break;
            }

            /*   b) subtract DAT from (mjd2,sec2), finding a first approximation
             *      for UTC
             */

            sect = sec2 - dat;

            //   start iterations
            bool quit = false;
            int  nit  = 0;

            do {
              nit++;

              if( timnf( mjdt, sect, APS_UTC ) ) {
                break;
              }

              /*   c) try to find the starting value of TAI from the approximate
               *      value of UTC
               */

              int mjd2r = mjdt;
              int delta;

              if( pAPSTaiUtcData->GetValue( mjdt, delta ) ) {
                break;
              }

              double sec2r = sect + delta;

              if( timnf( mjd2r, sec2r, APS_TAI ) ) {
                break;
              }

              //   d) computation of error and correction of the approximate value

              int itaiut1, itaiut2;

              if( pAPSTaiUtcData->GetValue( mjd2r, itaiut1 ) ) {
                break;
              }

              if( pAPSTaiUtcData->GetValue( mjd2, itaiut2 ) ) {
                break;
              }

              double err = ( mjd2r - mjd2 ) * 86400.0 + sec2r - sec2 + itaiut1 - itaiut2;

              if( fabs( err ) > EPST ) {
                sect = sect - err;
              }
              else {
                quit = true;
              }
            } while( !quit && ( nit <= NITMAX ) );

            if( !quit ) {
              pModule->ErrorMessage( APS_TIME_CVTTIM6 );
              RetCode = APS_TIME_CVTTIM6;
              break;
            }

            mjd2  = mjdt;
            sec2  = sect;
            scale = APS_UTC;
          }
          else {
            // Conversion TAI --> ET

            sec2  = sec2 + ET_MINUS_TAI;
            scale = APS_ET;
          }
        }
        else {
          if( scale == APS_UTC ) {
            // Conversione UTC --> TAI

            int delta;

            if( pAPSTaiUtcData->GetValue( mjd2, delta ) ) {
              pModule->ErrorMessage( APS_TIME_CVTTIM7 );
              RetCode = APS_TIME_CVTTIM7;
              break;
            }

            sec2  = sec2 + delta;
            scale = APS_TAI;
          }
          else {
            pModule->ErrorMessage( APS_TIME_CVTTIM8 );
            RetCode = APS_TIME_CVTTIM8;
            break;
          }
        }
      }
    }
  } while( loops <= LOOPMAX );

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
