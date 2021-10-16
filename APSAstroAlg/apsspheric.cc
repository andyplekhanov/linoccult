//------------------------------------------------------------------------------
//
// File:    apsspheric.cc
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

#include <cmath>

#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsspheric.h"
#include "apsvec3d.h"
#include "apsmat3d.h"

namespace aps {

  namespace apsastroalg {

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

double obleq( const double T )
{
  return( ( 23.43929111-(46.8150+(0.00059-0.001813*T)*T)*T/3600.0 ) * apsmathlib::Rad );
}

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

APSMat3d Equ2EclMatrix( const double T )
{   
  return apsmathlib::R_x( obleq( T ) );
}

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

APSMat3d Ecl2EquMatrix( const double T )
{
  return Transp(Equ2EclMatrix(T));
}

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
// Output:
//
//   h         Altitude
//   Az        Azimuth
//
// Note: all parameters in [rad]
//
//------------------------------------------------------------------------------

void Equ2Hor( const double Dec, const double tau, const double lat, 
              double& h, double& Az )
{ 
  APSVec3d e_equ = APSVec3d( apsmathlib::Polar( tau, Dec ) ); // unit vector in horizontal system
  APSVec3d e_hor = apsmathlib::R_y( apsmathlib::pi / 2.0 - lat ) * e_equ; // unit vector in equatorial system

  Az = e_hor[ apsmathlib::phi ];                     // polar angles
  h  = e_hor[ apsmathlib::theta ];
}

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
              double& Dec, double& tau )
{
  APSVec3d e_hor = APSVec3d( apsmathlib::Polar( Az, h ) );       // unit vector in horizontal system
  APSVec3d e_equ = apsmathlib::R_y( -( apsmathlib::pi / 2.0 - lat ) ) * e_hor;  // unit vector in equatorial system

  tau = e_equ[ apsmathlib::phi ];                    // polar angles
  Dec = e_equ[ apsmathlib::theta ];
}
    
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

APSVec3d Site( const double lambda, const double phi )
{
  //
  // Constants
  //
  const double f     = 1.0/298.257;   // Flattening 
  const double e_sqr = f*(2.0-f);     // Square of eccentricity
  const double cos_phi = cos(phi);    // (Co)sine of geographical latitude
  const double sin_phi = sin(phi);


  //
  // Variables
  //
  double  N = R_Earth / sqrt (1.0-e_sqr*(sin_phi*sin_phi));
      

  // Cartesian position vector [km]
  return APSVec3d ( N*cos_phi*cos(lambda),
                 N*cos_phi*sin(lambda),
                 (1.0-e_sqr)*N*sin_phi  );
}

//------------------------------------------------------------------------------
//
// StdEqu: Calculation of equatorial coordinates from standard coordinates
//         used in astrographic plate measurement
//
// Input:
//
//   RA0       Right ascension of optical axis [rad]
//   Dec0      Declination of optical axis [rad]
//   X         Standard coordinate X
//   Y         Standard coordinate Y
//
// Output:
//
//   RA        Right ascension [rad]
//   Dec       Declination [rad]
//
// Note: all angles in [rad]
//
//------------------------------------------------------------------------------

void StdEqu( const double RA0, const double Dec0, const double X, const double Y,
             double& RA, double& Dec )
{
  RA  = RA0 + atan ( -X / (cos(Dec0)-Y*sin(Dec0)) );
  Dec = asin ( (sin(Dec0)+Y*cos(Dec0))/sqrt(1.0+X*X+Y*Y) );
}

//------------------------------------------------------------------------------
//
// EquStd: Calculation of standard coordinates from equatorial coordinates
//
// Input:
//
//   RA0       Right ascension of optical axis [rad]
//   Dec0      Declination of optical axis [rad]
//   RA        Right ascension [rad]
//   Dec       Declination [rad]
//
// Output:
//
//   X         Standard coordinate X 
//   Y         Standard coordinate Y 
//
//------------------------------------------------------------------------------

void EquStd( const double RA0, const double Dec0, const double RA, const double Dec,
             double& X, double& Y ) 
{
  //
  // Constants
  //
  const double c =
    cos(Dec0)*cos(Dec)*cos(RA-RA0)+sin(Dec0)*sin(Dec);


  X = - ( cos(Dec)*sin(RA-RA0) ) / c;
  Y = - ( sin(Dec0)*cos(Dec)*cos(RA-RA0)-cos(Dec0)*sin(Dec) ) / c;
}

}}

//---------------------------- End of file ---------------------------
