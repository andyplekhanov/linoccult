//------------------------------------------------------------------------------
//
// File:    apsangle.cc
//
// Purpose: Functions to work with angles.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 09.10.2005
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
#include <cstdlib>

#include "apsangle.h"

namespace aps {

  namespace apsmathlib {

double Frac( const double x )
{
   return( x - floor( x ) );
}

double Modulo( const double x, const double y )
{
   return( y * Frac( x / y ) );
}

//------------------------------------------------------------------------------
//
// Ddd: Conversion of angular degrees, minutes and seconds of arc to decimal
//   representation of an angle 
//
// Input:
//
//   D        Angular degrees
//   M        Minutes of arc
//   S        Seconds of arc
//
// <return>:  Angle in decimal representation
//
//------------------------------------------------------------------------------

double Ddd( const int D, const int M, const double S )
{
  double sign;

  if( ( D < 0 ) || ( M < 0 ) || ( S < 0 ) ) sign = -1.0; else sign = 1.0;
    
  return( sign * ( abs( D ) + abs( M ) / 60.0 + fabs( S ) / 3600.0 ) );
}


//------------------------------------------------------------------------------
//
// DMS: Finds degrees, minutes and seconds of arc for a given angle 
//
// Input:
//
//   Dd        Angle in degrees in decimal representation
//
// Output:
//
//   D         Angular degrees
//   M         Minutes of arc
//   S         Seconds of arc
//
//------------------------------------------------------------------------------

void DMS( const double Dd, int & D, int & M, double & S)
{
  double x;

  x = fabs( Dd );
  D = int( x );
  x = ( x - D ) * 60.0;
  M = int( x );
  S = ( x - M ) * 60.0;
  
  if( Dd < 0.0 ) {
    if( D != 0 ) {
      D*=-1;
    }
    else {
      if( M != 0 ) {
        M*=-1;
      }
      else {
        S*=-1.0;
      }
    }
  }
}

//=============================== APSAngle =====================

APSAngle::APSAngle( const double alpha, const APSAngleFormat Format )
 : m_angle( alpha ), m_Format( Format )
{
}

void APSAngle::Set( const APSAngleFormat Format )
{
  m_Format = Format;
}

std::ostream& operator << ( std::ostream& os, const APSAngle & alpha )
{
  int    D,M;       // degrees, minutes
  double S;         // seconds

#ifdef __GNUC__
#if __GNUC__ < 3
  long   flags;     // output stream format flags
#else
  std::_Ios_Fmtflags   flags;     // output stream format flags
#endif
#else
  long   flags;     // output stream format flags
#endif

  int    w,p,sp;    // width, precision, showpos
  double fac;       // factor for rounding
  double DegRound;  // rounded value (positive)

    
  flags = os.flags(); // output stream format flags

  w  = static_cast<int>(os.width());      // total field width
  p  = static_cast<int>(os.precision());  // precision (digits)
  sp = flags & std::ios::showpos;         // flag for positive sign

  os << std::noshowpos << std::right;

  switch (alpha.m_Format) {

    case Dd:      // decimal output

      os << std::fixed;
      os << alpha.m_angle;
      
      break;

    case DMM:     // round to 1 arcmin

      DegRound = floor(60.0*fabs(alpha.m_angle)+0.5)/60.0+0.00001;

      DMS (DegRound, D, M, S);

      if (alpha.m_angle<0.0) 
        os << std::setw(1) << "-" << std::setw(w-4);
      else if (sp)
        os << std::setw(1) << "+" << std::setw(w-4);
      else 
        os << std::setw(w-3);
      os  << D << " "  << std::setfill('0') << std::setw(2) << M << std::setfill(' ');

      break;

    case DMMm:    // round to output precision (10^-p arcmins)
      
      fac = 60.0*pow(10.0,p);

      DegRound = floor(fac*fabs(alpha.m_angle)+0.5)/fac+0.1/fac;

      DMS (DegRound, D, M,S);

      if (alpha.m_angle<0.0) 
        os << std::setw(1) << "-" << std::setw(w-5-p);
      else if (sp)
        os << std::setw(1) << "+" << std::setw(w-5-p);
      else
        os << std::setw(w-4-p);
      os << D << " "  << std::setfill('0') << std::fixed 
         << std::setw(3+p) << M+S/60.0 << std::setfill(' ');   

      break;

    case DMMSS:   // round to 1 arcsec

      DegRound = floor(3600.0*fabs(alpha.m_angle)+0.5)/3600.0+0.00001;

      DMS (DegRound, D, M, S);

      if (alpha.m_angle<0.0) 
        os << std::setw(1) << "-" << std::setw(w-7);
      else if (sp)
        os << std::setw(1) << "+" << std::setw(w-7);
      else 
        os << std::setw(w-6);
      os  << D << " "  << std::setfill('0') << std::setw(2) 
          << M << " " << std::setw(2) << int(S) << std::setfill(' ');

      break;

    case DMMSSs:  // round to output precision (10^-p arcsecs)
      
      fac = 3600.0*pow(10.0,p);

      DegRound = floor(fac*fabs(alpha.m_angle)+0.5)/fac+0.1/fac;

      DMS (DegRound, D, M, S);

      if (alpha.m_angle<0.0) 
        os << std::setw(1) << "-" << std::setw(w-8-p);
      else if (sp)
        os << std::setw(1) << "+" << std::setw(w-8-p);
      else
        os << std::setw(w-7-p);
      os << D << " "  << std::setfill('0') << std::setw(2) << M << " "
         << std::fixed << std::setw(3+p) << S << std::setfill(' ');

      break;
  }
   
  os.setf(flags); // restore output stream format flags

  return os;
}

}}

//---------------------------- End of file ---------------------------
