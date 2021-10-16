//------------------------------------------------------------------------------
//
// File:    apskepler.h
//
// Purpose: Computations dealing with Keplerian orbits.
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

#ifndef APS_KEPLER_H
#define APS_KEPLER_H

#include "apsvec3d.h"
#include "apsmat3d.h"

namespace aps {

  namespace apsmathlib {
    class APSVec3d;
    class APSMat3d;
  }

  namespace apsastroalg {

using apsmathlib::APSVec3d;
using apsmathlib::APSMat3d;

//------------------------------------------------------------------------------
//
// EccAnom: computes the eccentric anomaly for elliptic orbits
//
// Input:
//
//   M        Mean anomaly in [rad]
//   e        Eccentricity of the orbit [0,1[
//
// <return>   Eccentric anomaly in [rad]
//
//------------------------------------------------------------------------------

double EccAnom( double M, const double e, int & RetCode );

//------------------------------------------------------------------------------
//
// HypAnom: computes the eccentric anomaly for hyperbolic orbits
//
// Input:
//
//   Mh       Mean anomaly in [rad]
//   e        Eccentricity of the orbit (>1)
//
// <return>   Eccentric anomaly in [rad]
//
//------------------------------------------------------------------------------

double HypAnom( const double Mh, const double e );

//------------------------------------------------------------------------------
//
// Ellip: computes position and velocity vectors for elliptic orbits
//
// Input:
//
//   GM       Product of gravitational constant and centre mass in [AU^3*d^-2]
//   M        Mean anomaly in [rad]
//   a        Semi-major axis of the orbit in [AU]
//   e        Eccentricity of the orbit (<1)
//
// Output:
//
//   r        Position w.r.t. orbital plane in [AU]
//   v        Velocity w.r.t. orbital plane in [AU/d]
//
//------------------------------------------------------------------------------

int Ellip( const double GM, const double M, const double a, const double e,
           APSVec3d & r, APSVec3d & v );

//------------------------------------------------------------------------------
//
// Hyperb: computes position and velocity vectors for hyperbolic orbits
//
// Input:
//
//   GM       Product of gravitational constant and centre mass in [AU^3*d^-2]
//   t0       Time of perihelion passage
//   t        Time for calculation
//   a        Semimajor axis of the orbit in [AU]
//   e        Eccentricity of the orbit (>1)
//
// Output:
//
//   r        Position w.r.t. orbital plane in [AU]
//   v        Velocity w.r.t. orbital plane in [AU/d]
//
// Note: t0 and t in Julian centuries since J2000
//
//------------------------------------------------------------------------------

int Hyperb( const double GM, const double t0, const double t, double a, const double e,
            APSVec3d & r, APSVec3d & v );

//------------------------------------------------------------------------------
//
// Stumpff: computes values for the Stumpff functions C1, C2 and C3
//
// Input:
//
//   E2       Square of eccentric anomaly (E2=E*E) in [rad^2]
//
// Output:
//
//   c1       Value of C1 = sin(E)/E
//   c2       Value of C2 = (1-cos(E))/(E*E)
//   c3       Value of C3 = (E-sin(E))/(E^3)
//
//------------------------------------------------------------------------------

void Stumpff( const double E2, double& c1, double& c2, double& c3);


//------------------------------------------------------------------------------
//
// Parab: computes position and velocity vectors for parabolic and near 
//        parabolic orbits
//
// Input:
//
//   GM       Product of gravitational constant and centre mass in [AU^3*d^-2]
//   t0       Time of perihelion passage
//   t        Time for calculation
//   q        Perihelion distance [AU]
//   e        Eccentricity of the orbit (~1)
//
// Output:
//
//   r        Position w.r.t. orbital plane in [AU]
//   v        Velocity w.r.t. orbital plane in [AU/d]
//
// Note: t0 and t in Julian centuries since J2000
//
//------------------------------------------------------------------------------

int Parab( const double GM, const double t0, const double t, const double q, const double e,
           APSVec3d & r, APSVec3d & v );

//------------------------------------------------------------------------------
//
// Kepler: computes position and velocity vectors for Keplerian orbits w.r.t.
//         the ecliptic
//
// Input:
//
//   GM       Product of gravitational constant and centre mass [AU^3*d^-2]
//   t0       Time of perihelion passage
//   t        Time for calculation
//   q        Perihelion distance [AU]
//   e        Eccentricity of the orbit
//   PQR      Transformation orbital plane -> ecliptic (Gaussian vectors)
//
// Output:
//
//   r        Heliocentric ecliptical position in [AU]
//   v        Heliocentric ecliptical velocity in [AU/d]
//
// Note: t0 and t in Julian centuries since J2000
//
//------------------------------------------------------------------------------

int Kepler( const double GM, const double t0, const double t, 
            const double q, const double e, const APSMat3d & PQR,
            APSVec3d & r, APSVec3d & v );

//------------------------------------------------------------------------------
//
// GaussVec: computes the transformation matrix from the orbital plane 
//           coordinate system to the ecliptic
//
// Input:
//
//   Omega    Longitude of the ascending node of the orbit in [rad]
//   i        Inclination of the orbit to the ecliptic in [rad]
//   omega    Argument of perihelion in [rad]
//
// <return>   Transformation matrix containing the Gaussian vectors P, Q and R
//
//------------------------------------------------------------------------------

APSMat3d GaussVec( const double Omega, const double i, const double omega);

//------------------------------------------------------------------------------
//
// Elements:  computes the elements of an elliptical orbit from position 
//            and velocity vectors
//
// Input:
//
//   GM       Product of gravitational constant and centre mass [AU^3*d^-2]
//   r        Heliocentric ecliptical position in [AU]
//   v        Heliocentric ecliptical velocity vector in [AU/d]
//
// Output:
//
//   a        Semimajor axis of the orbit [AU]
//   e        Eccentricity of the orbit
//   i        Inclination of the orbit to the ecliptic in [rad]
//   Omega    Longitude of the ascending node of the orbit in [rad]
//   omega    Argument of perihelion in [rad]
//   M        Mean anomaly in [rad]
//
//------------------------------------------------------------------------------

void Elements( const double GM, const APSVec3d & r, const APSVec3d & v,
               double& a, double& e, double& i,
               double& Omega, double& omega, double& M );

//------------------------------------------------------------------------------
//
// Elements:  computes orbital elements from two given positions 
//
// Input:
//
//   GM       Product of gravitational constant and centre mass [AU^3*d^-2]
//   Mjd_a    Time of the passage of position A [MJD]
//   Mjd_b    Time of the passage of position B [MJD]
//   r_a      Heliocentric ecliptical position A in [AU]
//   r_b      Heliocentric ecliptical position B in [AU]
//
// Output:
//
//   Mjd_p    Time of perihelion passage
//   q        Perihelion distance in [AU]
//   e        Eccentricity of the orbit
//   i        Inclination of the orbit to the ecliptic in [rad]
//   Omega    Longitude of the ascending node of the orbit in [rad]
//   omega    Argument of perihelion in [rad]
//
//------------------------------------------------------------------------------

void Elements( const double GM, const double Mjd_a, const double Mjd_b,
               const APSVec3d & r_a, const APSVec3d & r_b,
               double& Mjd_p, double& q, double& e,
               double& i, double& Omega, double& omega );

//------------------------------------------------------------------------------
//
// FindEta: computes the sector-triangle ratio for two given positions and 
//          the time between them
//
// Input:
//
//   r_a      Position at first instant in [AU]
//   r_a      Position at second instant in [AU]
//   tau      Time between the positions r_a and r_b (kGauss * dT in [d])
//
// <return>   Sector-triangle ratio
//
//------------------------------------------------------------------------------

double FindEta( const APSVec3d & r_a, const APSVec3d & r_b, const double tau );

}}

#endif

//---------------------------- End of file ---------------------------
