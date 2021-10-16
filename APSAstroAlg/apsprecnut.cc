//------------------------------------------------------------------------------
//
// File:    apsprecnut.cc
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

#include <cmath>

#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsangle.h"
#include "apsmat3d.h"
#include "apsspheric.h"
#include "apsprecnut.h"

namespace aps {

  namespace apsastroalg {

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

APSMat3d PrecMatrix_Ecl( const double T1, const double T2 )
{
  //
  // Constants
  //
  const double dT = T2-T1;
  

  //
  // Variables
  //
  double Pi, pi, p_a;

  
  Pi  = 174.876383889*apsmathlib::Rad + 
        ( ((3289.4789+0.60622*T1)*T1) +
              ((-869.8089-0.50491*T1) + 0.03536*dT)*dT )/apsmathlib::Arcs;
  pi  = ( (47.0029-(0.06603-0.000598*T1)*T1)+
              ((-0.03302+0.000598*T1)+0.000060*dT)*dT )*dT/apsmathlib::Arcs;
  p_a = ( (5029.0966+(2.22226-0.000042*T1)*T1)+
              ((1.11113-0.000042*T1)-0.000006*dT)*dT )*dT/apsmathlib::Arcs;
    
  return apsmathlib::R_z( -( Pi + p_a ) ) * apsmathlib::R_x( pi ) * apsmathlib::R_z( Pi );
}    


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

APSMat3d PrecMatrix_Equ( const double T1, const double T2 )
{
  //
  // Constants
  //
  const double dT = T2-T1;

  
  //
  // Variables
  //
  double zeta,z,theta;


  zeta  =  ( (2306.2181+(1.39656-0.000139*T1)*T1)+
                ((0.30188-0.000344*T1)+0.017998*dT)*dT )*dT/apsmathlib::Arcs;
  z     =  zeta + ( (0.79280+0.000411*T1)+0.000205*dT)*dT*dT/apsmathlib::Arcs;
  theta =  ( (2004.3109-(0.85330+0.000217*T1)*T1)-
                ((0.42665+0.000217*T1)+0.041833*dT)*dT )*dT/apsmathlib::Arcs;

  return apsmathlib::R_z( -z ) * apsmathlib::R_y( theta ) * apsmathlib::R_z( -zeta );
}    


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

APSMat3d SimpleNutMatrix( const double T )
{
  //
  // Variables
  //
  double  ls, D, F, N;
  double  eps, dpsi, deps;

  // Mean arguments of lunar and solar motion
  ls = apsmathlib::pi2 * apsmathlib::Frac(0.993133+  99.997306*T);   // mean anomaly Sun          
  D  = apsmathlib::pi2 * apsmathlib::Frac(0.827362+1236.853087*T);   // diff. longitude Moon-Sun  
  F  = apsmathlib::pi2 * apsmathlib::Frac(0.259089+1342.227826*T);   // mean argument of latitude 
  N  = apsmathlib::pi2 * apsmathlib::Frac(0.347346-   5.372447*T);   // longit. ascending node    

  // Nutation angles
  dpsi = ( -17.200*sin(N)   - 1.319*sin(2*(F-D+N)) - 0.227*sin(2*(F+N))
           + 0.206*sin(2*N) + 0.143*sin(ls) ) / apsmathlib::Arcs;
  deps = ( + 9.203*cos(N)   + 0.574*cos(2*(F-D+N)) + 0.098*cos(2*(F+N))
           - 0.090*cos(2*N)                 ) / apsmathlib::Arcs;

  // Mean obliquity of the ecliptic 
  eps  = 0.4090928-2.2696E-4*T;

  return  apsmathlib::R_x( -eps - deps ) * apsmathlib::R_z( -dpsi ) * apsmathlib::R_x( +eps );
}

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
*  INPUT:    T      -   Time in Julian centuries since epoch J2000
*
*  OUTPUT:   DPSI   -   Nutation in longitude (arcsec)
*            DEPS   -   Nutation in obliquity (arcsec)
*/

void nutn80( const double T, double & dpsi, double & deps )
{
  const double rs = 4.84813681109536e-6;
  const double z1 = 1.0;
  const double z2 = 2.0;

  double t2 = T * T;
  double t3 = t2 * T;

/*
* Fundamental arguments (IAU 1980)
*/

  double dl = ( 485866.733 + 1717915922.633 * T + 31.310 * t2 + 0.064 * t3 ) * rs;
  double dp = ( 1287099.804 + 129596581.224 * T - 0.577 * t2 - 0.012 * t3 ) * rs;
  double df = ( 335778.877 + 1739527263.137 * T - 13.257 * t2 + 0.011 * t3 ) * rs;
  double dd = ( 1072261.307 + 1602961601.328 * T - 6.891 * t2 + 0.019 * t3 ) * rs;
  double dn = ( 450160.280 - 6962890.539 * T + 7.455 * t2 + 0.008 * t3 ) * rs;
  double l = apsmathlib::Modulo( dl, apsmathlib::pi2 );
  double p = apsmathlib::Modulo( dp, apsmathlib::pi2 );
  double x = apsmathlib::Modulo( df, apsmathlib::pi2 ) * 2.0;
  double d = apsmathlib::Modulo( dd, apsmathlib::pi2 );
  double n = apsmathlib::Modulo( dn, apsmathlib::pi2 );
  double cl = std::cos( l );
  double sl = std::sin( l );
  double cp = std::cos( p );
  double sp = std::sin( p );
  double cx = std::cos( x );
  double sx = std::sin( x );
  double cd = std::cos( d );
  double sd = std::sin( d );
  double cn = std::cos( n );
  double sn = std::sin( n );
  double cp2 = z2 * cp * cp - z1;
  double sp2 = z2 * sp * cp;
  double cd2 = z2 * cd * cd - z1;
  double sd2 = z2 * sd * cd;
  double cn2 = z2 * cn * cn - z1;
  double sn2 = z2 * sn * cn;
  double cl2 = z2 * cl * cl - z1;
  double sl2 = z2 * sl * cl;
  double ca = cx * cd2 + sx * sd2;
  double sa = sx * cd2 - cx * sd2;
  double cb = ca * cn - sa * sn;
  double sb = sa * cn + ca * sn;
  double cc = cb * cn - sb * sn;
  double sc = sb * cn + cb * sn;
  double cv = cx * cd2 - sx * sd2;
  double sv = sx * cd2 + cx * sd2;
  double ce = cv * cn - sv * sn;
  double se = sv * cn + cv * sn;
  double cf = ce * cn - se * sn;
  double sf = se * cn + ce * sn;
  double cg = cl * cd2 + sl * sd2;
  double sg = sl * cd2 - cl * sd2;
  double ch = cx * cn2 - sx * sn2;
  double sh = sx * cn2 + cx * sn2;
  double cj = ch * cl - sh * sl;
  double sj = sh * cl + ch * sl;
  double ck = cj * cl - sj * sl;
  double sk = sj * cl + cj * sl;
  double cm = cx * cl2 + sx * sl2;
  double sm = sx * cl2 - cx * sl2;
  double cq = cl * cd + sl * sd;
  double sq = sl * cd - cl * sd;
  double cr = z2 * cq * cq - z1;
  double sr = z2 * sq * cq;
  double cs = cx * cn - sx * sn;
  double ss = sx * cn + cx * sn;
  double ct = cs * cl - ss * sl;
  double st = ss * cl + cs * sl;
  double cu = cf * cl + sf * sl;
  double su = sf * cl - cf * sl;
  double cw = cp * cg - sp * sg;
  double sw = sp * cg + cp * sg;

/*
* Series for DPSI
*/

  dpsi = -( 171996.0 + 174.2 * T ) * sn + ( 2062.0 + 0.2 * T ) * sn2 + 46.0 * ( sm * cn + cm * sn )
  - 11.0 * sm - 3.0 * ( sm * cn2 + cm * sn2 ) - 3.0 * ( sq * cp - cq * sp ) - 2.0 * ( sb * cp2 - cb * sp2 )
  + ( sn * cm - cn * sm ) - ( 13187.0 + 1.6 * T ) * sc + ( 1426.0 - 3.4 * T ) * sp
  - ( 517.0 - 1.2 * T ) * ( sc * cp + cc * sp ) + ( 217.0 - 0.5 * T ) * ( sc * cp - cc * sp )
  + ( 129.0 + 0.1 * T ) * sb + 48.0 * sr - 22.0 * sa + ( 17.0 - 0.1 * T ) * sp2
  - 15.0 * ( sp * cn + cp * sn ) - ( 16.0 - 0.1 * T ) * ( sc * cp2 + cc * sp2 ) - 12.0 * ( sn * cp - cn * sp );

  dpsi = dpsi - 6.0 * ( sn * cr - cn * sr ) -5.0 * ( sb * cp - cb * sp ) + 4.0 * ( sr * cn + cr * sn )
  + 4.0 * ( sb * cp + cb * sp ) - 4.0 * sq + ( sr * cp + cr * sp ) + ( sn * ca - cn * sa )
  - ( sp * ca - cp * sa ) + ( sp * cn2 + cp * sn2 ) + ( sn * cq - cn * sq ) - ( sp * ca + cp * sa )
  - (2274.0 + 0.2 * T ) * sh + ( 712.0 + 0.1 * T ) * sl - ( 386.0 + 0.4 * T ) * ss - 301.0 * sj
  - 158.0 * sg + 123.0 * ( sh * cl - ch * sl ) + 63.0 * sd2 + ( 63.0 + 0.1 * T ) * ( sl * cn + cl * sn )
  - ( 58.0 + 0.1 * T ) * ( sn * cl - cn * sl ) - 59.0 * su - 51.0 * st - 38.0 * sf + 29.0 * sl2;

  dpsi = dpsi + 29.0 * ( sc * cl + cc * sl ) - 31.0 * sk + 26.0 * sx + 21.0 * ( ss * cl - cs * sl )
  + 16.0 * ( sn * cg - cn * sg ) - 13.0 * ( sn * cg + cn * sg ) - 10.0 * ( se * cl - ce * sl )
  - 7.0 * ( sg * cp + cg * sp ) + 7.0 * ( sh * cp + ch * sp ) - 7.0 * ( sh * cp - ch * sp )
  - 8.0 * ( sf * cl + cf * sl ) + 6.0 * ( sl * cd2 + cl * sd2 ) + 6.0 * ( sc * cl2 + cc * sl2 )
  - 6.0 * ( sn * cd2 + cn * sd2 ) - 7.0 * se + 6.0 * ( sb * cl + cb * sl ) - 5.0 * ( sn * cd2 - cn * sd2 )
  + 5.0 * ( sl * cp - cl * sp ) - 5.0 * ( ss * cl2 + cs * sl2 ) - 4.0 * ( sp * cd2 - cp * sd2 );

  dpsi = dpsi + 4.0 * ( sl * cx - cl * sx ) - 4.0 * sd - 3.0 * ( sl * cp + cl * sp )
  + 3.0 * ( sl * cx + cl * sx ) - 3.0 * ( sj * cp - cj * sp ) - 3.0 * ( su * cp - cu * sp )
  - 2.0 * ( sn * cl2 - cn * sl2 ) -3.0 * ( sk * cl + ck * sl ) - 3.0 * ( sf * cp - cf * sp )
  + 2.0 * ( sj * cp + cj * sp ) - 2.0 * ( sb * cl - cb * sl );

  dpsi = dpsi + 2.0 * ( sn * cl2 + cn * sl2 ) - 2.0 * ( sl * cn2 + cl * sn2 )
  + 2.0 * ( sl * cl2 + cl * sl2 ) +2.0 * ( sh * cd + ch * sd ) + ( sn2 * cl - cn2 * sl )
  - ( sg * cd2 - cg * sd2 ) + ( sf * cl2 - cf * sl2 ) - 2.0 * ( su * cd2 + cu * sd2 )
  - ( sr * cd2 - cr * sd2 ) + ( sw * ch + cw * sh ) - ( sl * ce + cl * se ) - ( sf * cr - cf * sr )
  + ( su * ca + cu * sa ) + ( sg * cp - cg * sp ) + ( sb * cl2 + cb * sl2 ) - ( sf * cl2 + cf * sl2 )
  - ( st * ca - ct * sa ) + ( sc * cx + cc * sx ) + ( sj * cr + cj * sr ) - ( sg * cx + cg * sx );

  dpsi = dpsi + ( sp * cs + cp * ss ) + ( sn * cw - cn * sw ) - ( sn * cx - cn * sx )
  - ( sh * cd - ch * sd ) - ( sp * cd2 + cp * sd2 ) - ( sl * cv - cl * sv ) - ( ss * cp - cs * sp )
  - ( sw * cn + cw * sn ) - ( sl * ca - cl * sa ) + ( sl2 * cd2 + cl2 * sd2 )
  - ( sf * cd2 + cf * sd2 ) + ( sp * cd + cp * sd );

/*
* Series for DEPS
*/

  deps = (92025.0 + 8.9 * T ) * cn - ( 895.0 - 0.5 * T ) * cn2 - 24.0 * ( cm * cn - sm * sn )
  + ( cm * cn2 - sm * sn2 ) + ( cb * cp2 + sb * sp2 ) + ( 5736.0 - 3.1 * T ) * cc
  + ( 54.0 - 0.1 * T ) * cp + ( 224.0 - 0.6 * T ) * ( cc * cp - sc * sp )
  - (95.0 - 0.3 * T ) * ( cc * cp + sc * sp ) - 70.0 * cb + cr + 9.0 * ( cp * cn - sp * sn )
  + 7.0 * ( cc * cp2 - sc * sp2 ) + 6.0 * ( cn * cp + sn * sp ) + 3.0 * ( cn * cr + sn * sr )
  + 3.0 * ( cb * cp + sb * sp ) -2.0 * ( cr * cn - sr * sn ) - 2.0 * ( cb * cp - sb * sp );

  deps = deps + ( 977.0 - 0.5 * T ) * ch - 7.0 * cl + 200.0 * cs + ( 129.0 - 0.1 * T ) * cj - cg
  - 53.0 * ( ch * cl + sh * sl ) - 2.0 * cd2 - 33.0 * ( cl * cn - sl * sn ) + 32.0 * ( cn * cl + sn * sl )
  + 26.0 * cu + 27.0 * ct + 16.0 * cf - cl2 - 12.0 * ( cc * cl - sc * sl ) + 13.0 * ck - cx
  - 10.0 * ( cs * cl + ss * sl ) - 8.0 * ( cn * cg + sn * sg ) + 7.0 * ( cn * cg - sn * sg )
  + 5.0 * ( ce * cl + se * sl ) - 3.0 * ( ch * cp - sh * sp ) + 3.0 * ( ch * cp + sh * sp )
  + 3.0 * ( cf * cl - sf * sl ) - 3.0 * ( cc * cl2 - sc * sl2 ) + 3.0 * ( cn * cd2 - sn * sd2 ) + 3.0 * ce;

  deps = deps - 3.0 * ( cb * cl - sb * sl ) + 3.0 * ( cn * cd2 + sn * sd2 )
  + 3.0 * ( cs * cl2 - ss * sl2 ) + ( cj * cp + sj * sp ) + ( cu * cp + su * sp )
  + ( cn * cl2 + sn * sl2 ) + ( ck * cl - sk * sl ) + ( cf * cp + sf * sp ) - ( cj * cp - sj * sp )
  + ( cb * cl + sb * sl );

  deps = deps - ( cn * cl2 - sn * sl2 ) + ( cl * cn2 - sl * sn2 ) - ( ch * cd - sh * sd )
  - ( cn2 * cl + sn2 * sl ) - ( cf * cl2 + sf * sl2 ) + ( cu * cd2 - su * sd2 ) - ( cw * ch - sw * sh )
  + ( cl * ce - sl * se ) + ( cf * cr + sf * sr ) - ( cb * cl2 - sb * sl2 );

  dpsi = dpsi * 1.0e-4;
  deps = deps * 1.0e-4;
}

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

APSMat3d NutMatrix( const double T )
{
  double epsm,epst,dpsi,deps;

  epsm = obleq( T );

  nutn80( T, dpsi, deps );

  dpsi = dpsi / apsmathlib::Arcs;

  epst = epsm + deps / apsmathlib::Arcs;

  return( apsmathlib::R_x( -epst ) * apsmathlib::R_z( -dpsi ) * apsmathlib::R_x( epsm ) );
}

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

double equequ( const double T )
{
  double oblm,dpsi,deps;

  oblm = obleq( T );

  nutn80( T, dpsi, deps );

  return( dpsi * std::cos( oblm ) / apsmathlib::Arcs );
}

}}

//---------------------------- End of file ---------------------------
