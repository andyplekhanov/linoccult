//------------------------------------------------------------------------------
//
// File:    apsspheric.h
//
// Purpose: Transformations frequently found in spherical astronomy.
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

#ifndef APS_SPHERIC_H
#define APS_SPHERIC_H

namespace aps {

  namespace apsmathlib {
    class APSVec3d;
    class APSMat3d;
  }

  namespace apsastroalg {

using apsmathlib::APSVec3d;
using apsmathlib::APSMat3d;

//---------------------------------------------------------------------
//
//  ***************************************************************
//  *                                                             *
//  *                          O B L E Q                          *
//  *                                                             *
//  *                 Mean obliquity of ecliptic                  *
//  *                                                             *
//  *       T         Time in Julian centuries since J2000        *
//  *                                                             *
//  *       <return>: Mean obliquity of ecliptic in radians       *
//  *                                                             *
//  ***************************************************************

double obleq( const double T );

//------------------------------------------------------------------------------
//
// Equ2EclMatrix: Transformation of equatorial to ecliptical coordinates
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// <return>:   Transformation matrix
//
//------------------------------------------------------------------------------

APSMat3d Equ2EclMatrix( const double T );

//------------------------------------------------------------------------------
//
// Ecl2EquMatrix: Transformation of ecliptical to equatorial coordinates
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// <return>:   Transformation matrix
//
//------------------------------------------------------------------------------

APSMat3d Ecl2EquMatrix( const double T );

//------------------------------------------------------------------------------
//
// Equ2Hor: Transformation of equatorial coordinates to the horizon system
//
// Input:
//
//   Dec       Declination
//   tau       Hour angle
//   lat       Geographical latitude of the observer
//
// Output :
//
//   h         Altitude
//   Az        Azimuth
//
// Note: all parameters in [rad]
//
//------------------------------------------------------------------------------

void Equ2Hor( const double Dec, const double tau, const double lat, 
              double& h, double& Az );

//------------------------------------------------------------------------------
//
// Hor2Equ: Transformation of horizon system coordinates 
//          to equatorial coordinates
//
// Input:
//
//   h         Altitude
//   Az        Azimuth
//   lat       Geographical latitude of the observer
//
// Output:
//
//   Dec       Declination
//   tau       Hour angle
//
// Note: all parameters in [rad]
//
//------------------------------------------------------------------------------

void Hor2Equ( const double h, const double Az, const double lat,
              double& Dec, double& tau );

//------------------------------------------------------------------------------
//
// Site: Calculates the geocentric position of a site on the Earth's surface
//
// Input:
//
//   lambda    Geographical longitude (east positive) in [rad]
//   phi       Geographical latitude  in [rad]
//
// <return>:   Geocentric position in [km]
//
//------------------------------------------------------------------------------

APSVec3d Site( const double lambda, const double phi );

//------------------------------------------------------------------------------
//
// StdEqu: Calculation of equatorial coordinates from standard coordinates
//         used in astrographic plate measurement
//
// Input:
//
//   RA0       Right ascension of optical axis
//   Dec0      Declination of optical axis
//   X         Standard coordinate X [no dimension]
//   Y         Standard coordinate Y [no dimension]
//
// Output :
//
//   RA        Right ascension
//   Dec       Declination
//
// Note: all angles in [rad]
//
//------------------------------------------------------------------------------

void StdEqu( const double RA0, const double Dec0, const double X, const double Y,
             double& RA, double& Dec );


//------------------------------------------------------------------------------
//
// EquStd: Calculation of standard coordinates from equatorial coordinates
//
// Input:
//
//   RA0       Right ascension of optical axis
//   Dec0      Declination of optical axis
//   RA        Right ascension
//   Dec       Declination
//
// Output:
//
//   X         Standard coordinate X [no dimension]
//   Y         Standard coordinate Y [no dimension]
//
// Note: all angles in [rad]
//
//------------------------------------------------------------------------------

void EquStd( const double RA0, const double Dec0, const double RA, const double Dec,
             double& X, double& Y );

}}

#endif

//---------------------------- End of file ---------------------------
