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

#include <fstream>
#include <cmath>

#ifdef __GNUC__   // GNU C++ adaptation
#include <float.h>
#else             // Standard C++ version
#include <limits>
#endif

#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsangle.h"
#include "apskepler.h"
#include "apsvec3d.h"
#include "apsmat3d.h"

namespace aps {

  namespace apsastroalg {

namespace // Unnamed namespace
{

  //
  // Constants
  //
  #ifdef __GNUC__   // GNU C++ adaptation
  const double eps_mach = DBL_EPSILON;
  #else             // Standard C++ version
  const double eps_mach = numeric_limits<double>::epsilon();
  #endif

  //
  // F : local function for use by FindEta()
  // F = 1 - eta +(m/eta**2)*W(m/eta**2-l)
  //
  double F( const double eta, const double m, const double l )
  {
    //
    // Constants
    //
    const double eps = 100.0 * eps_mach;

    
    //
    // Variables
    //
    double  w,W,a,n,g;

    
    w = m/(eta*eta)-l; 

    if (fabs(w)<0.1) { // Series expansion
      W = a = 4.0/3.0; n = 0.0;
      do {
        n += 1.0;  a *= w*(n+2.0)/(n+1.5);  W += a; 
      }
      while (fabs(a) >= eps);
    }
    else {
      if (w > 0.0) {
        g = 2.0*asin(sqrt(w));  
        W = (2.0*g - sin(2.0*g)) / pow(sin(g), 3);
      }
      else {
        g = 2.0*log(sqrt(-w)+sqrt(1.0-w));  // =2.0*arsinh(sqrt(-w))
        W = (sinh(2.0*g) - 2.0*g) / pow(sinh(g), 3);
      }
    }
  
    return ( 1.0 - eta + (w+l)*W );
  }   // F

} // End of unnamed namespace


//------------------------------------------------------------------------------
//
// EccAnom: computes the eccentric anomaly for elliptic orbits
//
// Input:
//
//   M        Mean anomaly in [rad]
//   e        Eccentricity of the orbit [0,1[
//
// <return>:  Eccentric anomaly in [rad]
//
//------------------------------------------------------------------------------

double EccAnom( double M, const double e, int & RetCode )
{
  //
  // Constants
  //
  const int maxit = 15;
  const double eps = 100.0*eps_mach;
  RetCode = 0;

  //
  // Variables
  //
  int    i=0;
  double E, f;


  // Starting value
  M = apsmathlib::Modulo( M, 2.0 * apsmathlib::pi );   
  if (e<0.8) E=M; else E = apsmathlib::pi;


  // Iteration
  do {
    f = E - e*sin(E) - M;
    E = E - f / ( 1.0 - e*cos(E) );
    ++i;
    if (i==maxit) {
      //std::cerr << " Convergence problems in EccAnom" << std::endl;
      RetCode = 1;
      break;
    }
  }
  while (fabs(f) > eps);

  return E;
}

//------------------------------------------------------------------------------
//
// HypAnom: computes the eccentric anomaly for hyperbolic orbits
//
// Input:
//
//   Mh       Mean anomaly in [rad]
//   e        Eccentricity of the orbit (>1)
//
// <return>:  Eccentric anomaly in [rad]
//
//------------------------------------------------------------------------------

double HypAnom( const double Mh, const double e, int & RetCode )
{
  //
  // Constants
  //
  const int maxit = 15;
  const double eps = 100.0*eps_mach;
  RetCode = 0;

  //
  // Variables
  //
  int    i=0;
  double H, f;
  
  
  // Starting value
  H = log (2.0*fabs(Mh)/e + 1.8); 
  if (Mh < 0.0)  H = -H; 


  // Iteration
  do {
    f = e*sinh(H) - H - Mh; 
    H = H - f / ( e*cosh(H) - 1.0 );
    ++i;
    if (i==maxit) {
      //std::cerr << " Convergence problems in HypAnom" << std::endl;
      RetCode = 1;
      break;
    }
  }
  while ( fabs(f) > eps*(1.0+fabs(H+Mh)) );

  return H;
}

//------------------------------------------------------------------------------
//
// Ellip: computes position and velocity vectors for elliptic orbits
//
// Input:
//
//   GM       Product of gravitational constant and centre mass [AU^3*d^-2]
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
            APSVec3d & r, APSVec3d & v )
{
  //
  // Variables
  //
  double k, E, cosE,sinE, fac, rho;
  int    RetCode = 0;

  k  = sqrt(GM/a);

  E  = EccAnom( M, e, RetCode );   

  cosE = cos(E); 
  sinE = sin(E);

  fac = sqrt ( (1.0-e)*(1.0+e) );  

  rho = 1.0 - e*cosE;

  r = APSVec3d (a*(cosE-e),  a*fac*sinE,     0.0);
  v = APSVec3d (-k*sinE/rho, k*fac*cosE/rho, 0.0);

  return( RetCode );
}

//------------------------------------------------------------------------------
//
// Hyperb: computes position and velocity vectors for elliptic orbits
//
// Input:
//
//   GM       Product of gravitational constant and centre mass [AU^3*d^-2]
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
            APSVec3d & r, APSVec3d & v )
{
  //
  // Variables
  //
  double k, Mh, H, coshH, sinhH, rho, fac;
  int    RetCode = 0;

  a  = fabs(a);
  k  = sqrt(GM/a);

  Mh = k*(t-t0)/a; 
  H  = HypAnom( Mh, e, RetCode ); 

  coshH = cosh(H); 
  sinhH = sinh(H);

  fac = sqrt ( (e+1.0)*(e-1.0) );  

  rho = e*coshH - 1.0;

  r = APSVec3d (a*(e-coshH),  a*fac*sinhH,     0.0);
  v = APSVec3d (-k*sinhH/rho, k*fac*coshH/rho, 0.0);

  return( RetCode );
}

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

void Stumpff( const double E2, double& c1, double& c2, double& c3)
{
  //
  // Constants
  //
  const double eps = 100.0*eps_mach;
  double       n, add;


  c1 = c2 = c3 = 0.0; 

  add = n = 1.0;

  do {
    c1 += add;  add /= (2.0*n);
    c2 += add;  add /= (2.0*n+1.0);
    c3 += add;  add *= -E2; 
    n += 1.0;
  }
  while (fabs(add) >= eps);
}

//------------------------------------------------------------------------------
//
// Parab: computes position and velocity vectors for parabolic and near 
//        parabolic orbits
//
// Input:
//
//   GM       Product of gravitational constant and centre mass [AU^3*d^-2]
//   t0       Time of perihelion passage
//   t        Time for calculation
//   q        Perihelion distance in [AU]
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
           APSVec3d & r, APSVec3d & v )
{
  //
  // Constants
  //
  const int maxit = 15;
  const double eps = 100.0*eps_mach;
  int    RetCode = 0;

  //
  // Variables
  //
  int     i=0;
  double  E2=0.0;
  double  E20, fac, c1, c2, c3, k, tau, A, B, u, u2, R;


  fac = 0.5*e;  

  k   = sqrt(GM / (q*(1.0+e))); 
  tau = sqrt(GM)*(t-t0);

  do {
    ++i;

    E20 = E2;

    A = 1.5*sqrt(fac/(q*q*q))*tau;  
    B = pow ( sqrt(A*A+1.0)+A, 1.0/3.0 );    

    u  = B - 1.0/B;  
    u2 = u*u;  
    E2 = u2*(1.0-e)/fac;

    Stumpff (E2, c1,c2,c3); 

    fac = 3.0*e*c3;

    if (i == maxit) {
      //std::cerr << " Convergence problems in Parab" << std::endl;
      RetCode = 1;
      break;
    }
  }
  while (fabs(E2-E20) >= eps);

  R  = q * ( 1.0 + u2*c2*e/fac ); 

  r = APSVec3d( q * ( 1.0 - u2 * c2 / fac ), q * sqrt( ( 1.0 + e ) / fac ) * u * c1, 0.0 );
  v = APSVec3d( -k * r[ apsmathlib::y ] / R, k * ( r [ apsmathlib::x ] / R + e ), 0.0 );

  return( RetCode );
}

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
//   q        Perihelion distance in [AU]
//   e        Eccentricity of the orbit
//   PQR      Transformation orbital plane -> ecliptic (Gaussian vectors)
//
// Output:
//
//   r        Heliocentric ecliptical position in [AU]
//   v        Heliocentric ecliptical velocity vector in [AU/d]
//
// Note: t0 and t in Julian centuries since J2000
//
//------------------------------------------------------------------------------

int Kepler( const double GM, const double t0, const double t, 
            const double q, const double e, const APSMat3d & PQR,
            APSVec3d & r, APSVec3d & v )
{
  //
  // Constants
  //
  const double M0  = 0.1; // [rad]
  const double eps = 0.1;
  int    RetCode = 0;

  //
  // Variables
  //
  double M, delta, tau, invax;
  APSVec3d  r_orb,v_orb;


  delta = fabs(1.0-e);

  invax = delta / q;

  tau   = sqrt(GM)*(t-t0);
  M     = tau * sqrt(invax*invax*invax);

  if ( (M < M0) && (delta < eps) )
    RetCode = Parab (GM, t0,t, q,e, r_orb, v_orb);
  else if ( e < 1.0 )
    RetCode = Ellip (GM, M, 1.0/invax, e, r_orb, v_orb);
  else
    RetCode = Hyperb (GM, t0,t, 1.0/invax, e, r_orb, v_orb);

  r = PQR*r_orb;
  v = PQR*v_orb;

  return( RetCode );
}

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
// <return>:  Transformation matrix containing the Gaussian vectors P, Q and R
//
//------------------------------------------------------------------------------

APSMat3d GaussVec( const double Omega, const double i, const double omega )
{
  return apsmathlib::R_z(-Omega) * apsmathlib::R_x(-i) * apsmathlib::R_z(-omega);
}

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
//   a        Semimajor axis of the orbit in [AU]
//   e        Eccentricity of the orbit
//   i        Inclination of the orbit to the ecliptic in [rad]
//   Omega    Longitude of the ascending node of the orbit in [rad]
//   omega    Argument of perihelion in [rad]
//   M        Mean anomaly in [rad]
//
//------------------------------------------------------------------------------

void Elements( const double GM, const APSVec3d & r, const APSVec3d & v, 
               double& a, double& e, double& i,
               double& Omega, double& omega, double& M )
{
  //
  // Variables
  //
  APSVec3d  h;
  double H, u, R, v2;
  double eCosE, eSinE, e2, E, nu;


  h = Cross(r,v);                                    // Areal velocity
  H = Norm(h);

  Omega = atan2( h[ apsmathlib::x ], -h[ apsmathlib::y ] ); // Long. ascend. node 

  i     = atan2( sqrt( h[ apsmathlib::x ] * h[ apsmathlib::x ] +
                       h[ apsmathlib::y ] * h[ apsmathlib::y ] ),
                       h[ apsmathlib::z ] );    // Inclination

  u     = atan2( r[ apsmathlib::z ] * H,
                -r[ apsmathlib::x ] * h[ apsmathlib::y ] +
                 r[ apsmathlib::y ] * h[ apsmathlib::x ] );       // Arg. of latitude   

  R  = Norm(r);                                      // Distance           
  v2 = Dot(v, v);                                    // Velocity squared   

  a = 1.0 / (2.0/R-v2/GM);                           // Semi-major axis    

  eCosE = 1.0-R/a;                                   // e*cos(E)           
  eSinE = Dot(r, v)/sqrt(GM*a);                      // e*sin(E)           

  e2 = eCosE*eCosE +eSinE*eSinE;
  e  = sqrt(e2);                                     // Eccentricity 
  E  = atan2(eSinE,eCosE);                           // Eccentric anomaly  

  M  = E - eSinE;                                    // Mean anomaly

  nu = atan2(sqrt(1.0-e2)*eSinE, eCosE-e2);          // True anomaly

  omega = u - nu;                                    // Arg. of perihelion 
 
  if( Omega < 0.0 ) Omega += 2.0 * apsmathlib::pi;
  if( omega < 0.0 ) omega += 2.0 * apsmathlib::pi;
  if( M < 0.0 ) M += 2.0 * apsmathlib::pi;
  
};

//------------------------------------------------------------------------------
//
// Elements: computes orbital elements from two given positions 
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
               double& i, double& Omega, double& omega ) 
{
  //
  // Variables
  //
  double   tau, eta, p;
  double   a, n, nu, E, M, u;
  double   s_a, s_b, s_0, fac, sinhH;
  double   cos_dnu, sin_dnu, ecos_nu, esin_nu;
  APSVec3d e_a, r_0, e_0, R;
  

  // Calculate vector r_0 (fraction of r_b perpendicular to r_a) 
  // and the magnitudes of r_a,r_b and r_0
  s_a = Norm(r_a);  e_a = r_a/s_a;
  s_b = Norm(r_b); 
  fac = Dot(r_b,e_a); r_0 = r_b-fac*e_a;
  s_0 = Norm(r_0);  e_0 = r_0/s_0;
  

  // Inclination and ascending node 
  R     = Cross(e_a,e_0);
  i     = apsmathlib::pi / 2.0 - R[ apsmathlib::theta ];
  Omega = apsmathlib::Modulo( apsmathlib::pi / 2.0 + R[ apsmathlib::phi ],
                              2.0 * apsmathlib::pi );

  if( i == 0.0 ) 
    u = atan2( r_a[ apsmathlib::y ], r_a[ apsmathlib::x ] );
  else 
    u = atan2( ( +e_0[ apsmathlib::x ] * R[ apsmathlib::y ] -
                  e_0[ apsmathlib::y ] * R[ apsmathlib::x ] ),
               ( -e_a[ apsmathlib::x ] * R[ apsmathlib::y ] +
                  e_a[ apsmathlib::y ] * R[ apsmathlib::x ] ) );
  
  // Semilatus rectum
  tau = sqrt(GM) * fabs(Mjd_b-Mjd_a);   
  eta = FindEta ( r_a, r_b, tau );
  p   = pow ( s_a*s_0*eta/tau, 2 );   


  // Eccentricity, true anomaly and argument of perihelion
  cos_dnu = fac / s_b;    
  sin_dnu = s_0 / s_b;

  ecos_nu = p / s_a - 1.0;  
  esin_nu = ( ecos_nu * cos_dnu - (p/s_b-1.0) ) / sin_dnu;

  e  = sqrt ( ecos_nu*ecos_nu + esin_nu*esin_nu );
  nu = atan2(esin_nu,ecos_nu);

  omega = apsmathlib::Modulo( u - nu, 2.0 * apsmathlib::pi );


  // Perihelion distance, semi-major axis and mean motion
  q = p/(1.0+e);
  a = q/(1.0-e);
  n = sqrt ( GM / fabs(a*a*a) );


  // Mean anomaly and time of perihelion passage
  if (e<1.0) {
    E = atan2 ( sqrt((1.0-e)*(1.0+e)) * esin_nu,  ecos_nu + e*e );
    M = E - e*sin(E);
  }
  else 
  {
    sinhH = sqrt((e-1.0)*(e+1.0)) * esin_nu / ( e + e * ecos_nu );
    M = e * sinhH - log ( sinhH + sqrt(1.0+sinhH*sinhH) );
  }

  Mjd_p = Mjd_a - M / n;
}

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
// <return>:  Sector-triangle ratio
//
//------------------------------------------------------------------------------

double FindEta( const APSVec3d & r_a, const APSVec3d & r_b, const double tau )
{
  //
  // Constants
  //
  const int maxit = 30;
  const double delta = 100.0*eps_mach;  


  //
  // Variables
  //
  int    i;
  double kappa, m, l, s_a, s_b, eta_min, eta1, eta2, F1, F2, d_eta;


  s_a = Norm(r_a);  
  s_b = Norm(r_b);  

  kappa = sqrt ( 2.0*(s_a*s_b+Dot(r_a,r_b)) );

  m = tau*tau / pow(kappa,3);   
  l = (s_a+s_b) / (2.0*kappa) - 0.5;

  eta_min = sqrt(m/(l+1.0));


  // Start with Hansen's approximation
  eta2 = ( 12.0 + 10.0*sqrt(1.0+(44.0/9.0)*m /(l+5.0/6.0)) ) / 22.0;
  eta1 = eta2 + 0.1;   


  // Secant method
  F1 = F(eta1, m, l);   
  F2 = F(eta2, m, l);  

  i = 0;

  while (fabs(F2-F1) > delta)
  {
    d_eta = -F2*(eta2-eta1)/(F2-F1);  
    eta1 = eta2; F1 = F2; 
    while (eta2+d_eta<=eta_min)  d_eta *= 0.5;
    eta2 += d_eta;  
    F2 = F(eta2,m,l); ++i;
  
    if ( i == maxit ) {
      std::cerr << " Convergence problems in FindEta" << std::endl;
      break;
    }
  }


  return eta2;
}

}}

//---------------------------- End of file ---------------------------

