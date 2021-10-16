//------------------------------------------------------------------------------
//
// File:    apsprecnut.h
//
// Purpose: Precession and nutation routines.
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

#ifndef APS_PRECNUT_H
#define APS_PRECNUT_H

#include "apsmat3d.h"

namespace aps {

  namespace apsmathlib {
    class APSMat3d;
  }

  namespace apsastroalg {

using apsmathlib::APSMat3d;

//------------------------------------------------------------------------------
//
// PrecMatrix_Ecl: Precession of ecliptic coordinates
//
// Input:
//
//   T1        Epoch given
//   T2        Epoch to precess to
//
// <return>:   Precession transformation matrix
//
// Note: T1 and T2 in Julian centuries since J2000
//
//------------------------------------------------------------------------------

APSMat3d PrecMatrix_Ecl( const double T1, const double T2 );

//------------------------------------------------------------------------------
//
// PrecMatrix_Equ: Precession of equatorial coordinates
//
// Input:
//
//   T1        Epoch given
//   T2        Epoch to precess to
//
// <return>:   Precession transformation matrix
//
// Note: T1 and T2 in Julian centuries since J2000
//
//------------------------------------------------------------------------------

APSMat3d PrecMatrix_Equ( const double T1, const double T2 );

//------------------------------------------------------------------------------
//
// SimpleNutMatrix: Transformation from mean to true equator and equinox
//
// Input:
//
//   T         Time in Julian centuries since epoch J2000
//
// <return>:   Nutation matrix
//
//------------------------------------------------------------------------------

APSMat3d SimpleNutMatrix( const double T );

/* ---------------------------------------------------------------------
*
*  ***************************************************************
*  *                                                             *
*  *                         N U T N 8 0                         *
*  *                                                             *
*  *    Nutation angles according to Wahr (IAU 1980) theory      *
*  *                                                             *
*  ***************************************************************
*
*  INPUT:    Time in Julian centuries since epoch J2000
*
*  OUTPUT:   DPSI   -   Nutation in longitude (arcsec)
*            DEPS   -   Nutation in obliquity (arcsec)
*/

void nutn80( const double T, double & dpsi, double & deps );

/*  ***************************************************************
*  *                                                             *
*  *                         NutMatrix                           *
*  *                                                             *
*  *    Nutation matrix according to Wahr (IAU-1980) theory      *
*  *                                                             *
*  ***************************************************************
*
*  INPUT:    T           -   Time in Julian centuries since epoch J2000
*
*  OUTPUT:   <return>    -   Nutation matrix, transforming MEAN
*                            coordinates into TRUE coordinates
*                            Xtrue = RNUT Xmean
*/

APSMat3d NutMatrix( const double T );

/*  ***************************************************************
*  *                                                             *
*  *                         E Q U E Q U                         *
*  *                                                             *
*  *                 Equation of the equinoxes                   *
*  *                                                             *
*  ***************************************************************
*
*
* INPUT:    T         -  Time in Julian centuries since epoch J2000
*
* OUTPUT:   EQUEQU    -  Equation of the equinoxes (difference
*                        between apparent sidereal time and mean
*                        sidereal time) in radians
*/

double equequ( const double T );

}}

#endif

//---------------------------- End of file ---------------------------

