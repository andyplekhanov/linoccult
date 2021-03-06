//------------------------------------------------------------------------------
//
// File:    loCalc.cc
//
// Purpose: Asteroids occultation program for Linux
//          Main calculation procedure
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 16.02.2004
// version 0.2 11.04.2004 min/max diameter has been added
// version 0.3 10.05.2004 table data representation, star and sun elevation
// version 0.4 16.05.2004 bug with star motion was fixed, shadow boundaries were added
// version 0.5 27.05.2004 bug with sun elevation was fixed. Procedure JPLSunEquPos was added.
//                        OutputType parameter was added.
// version 1.0 30.05.2004 Asteroid orbit approximation by Chebyshev polynome
// version 1.1 07.06.2004 Sun-asteroid distance, Moon-asteroid distance, Moon phase
// version 1.2 10.06.2004 Uncertainty was added
// version 1.3 10.06.2004 Duration was added
// version 1.4 10.06.2004 Output to OziExplorer was updated
// version 1.5 13.10.2004 Bug with printing extra radius header was fixed
// version 2.0 13.01.2005 NewNewNewProcessAsteroid, MySQL, kdtree
// version 2.1 23.01.2005 Output file, distance to shadow
// version 2.2 24.01.2005 ReRun was added
// version 2.3 27.01.2005 Probability was added
// version 2.4 31.01.2005 IfMySQL, ResultsFilePath were added
// version 2.5 05.02.2005 Catalog was added
// version 2.6 07.02.2005 Event data was added
// version 2.7 15.02.2005 Brightness was corrected
// version 2.8 22.02.2005 New output format. SunDist -> SunElev
// version 2.9 05.03.2005 StartSQLNumber were added.
// version 2.10 17.08.2005 JPLSunEquPos -> -JPLSunEquPos
// version 2.11 20.08.2005 Parallax processing 
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

#include <limits>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "apsmainmodule.h"
#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsvec3d.h"
#include "apsmat3d.h"
#include "apsangle.h"
#include "apsjpleph.h"
#include "apsspheric.h"
#include "apsprecnut.h"
#include "apskepler.h"
#include "apstime.h"
#include "apscheb.h"
#include "loCalc.h"
#include "loData.h"
#include "loAstOrbData.h"
#include "loStarData.h"
#include "loEventData.h"
#include "loPointEventData.h"
#include "loPosData.h"
#include "loAsteroid.h"
#include "loStar.h"
#include "loEvent.h"
#include "loPointEvent.h"
#include "loPos.h"
#include "loModuleCalc.h"
#include "loCalcSubModule.h"
#include "loAstOrbChebMaker.h"
#include "loAstOrbCalc.h"
#include "loChebMakerSubModule.h"
#include "loChebSubModule.h"
#include "loAstOrbSubModule.h"

//#define WITH_MYSQL 1

#ifdef WITH_MYSQL
#include "mysql/mysql.h"
#endif

namespace aps {

  namespace apslinoccult {

const double ANGLE_DELTA         = 2.0 * apsmathlib::Rad;
const double ANGLE_DELTA1        = 1.0 * apsmathlib::Rad / 60.0;
const double CAMERA_DIST         = 2000.0;
const double fac                 = 0.996647;     // Ratio polar/equat. Earth radius
const int    CHEB_ORDER          = 11;
const int    SAVE_CHEB_ORDER     = 11;
const double CHEB_STEP           = 1.0;          // One day
const int    OZI                 = 0;
const int    SMALL_STEP          = 60;      // 1 sec
const int    PROGRESS_POS_STEP   = 1000;

int    ShowNumber = 1;

APSVec3d       r_prev;
APSVec3d       r_old;
double         t_prev;
double         Lambda_prev;
double         Phi_prev;
int            PointNumber; // For OziExplorer

#ifdef WITH_MYSQL
MYSQL         mysql;
int           mysql_count;
#endif

double r0min  = std::numeric_limits<double>::max();
double minX   = std::numeric_limits<double>::max();
double minY   = std::numeric_limits<double>::max();
double MJDmin = 0.0;
double UTCmin = 0.0;

//======================= LOCalc ==========================

LOCalc :: LOCalc( LOCalcSubModule * pLOCalcSubModule )
{
  pModule    = new LOModuleCalc( pLOCalcSubModule );
  ephem      = 0;
  StarsCount = 0;
  EventStar  = -1;
  ChebArray  = new APSVec3d * [ pModule->GetScanStep() ];

  for( int i = 0; i < pModule->GetScanStep(); i++ ) {
    ChebArray[ i ] = new APSVec3d();
  }

  AU = 0.0;
}

LOCalc :: ~LOCalc( void )
{
  int i;

  for( i = 0; i < pModule->GetScanStep(); i++ ) {
    delete ChebArray[ i ];
  }

  delete ChebArray;
  delete pModule;
}

int LOCalc :: AddStar( const LOStar * pStar )
{
  int RetCode = 0;

  if( StarsCount < MAX_STAR_NUMBER ) {
    pLOStarsArray[ StarsCount ] = pStar;

    StarsCount++;
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

const LOStar * LOCalc :: GetStar( const unsigned int StarNumber ) const
{
  if( StarNumber < StarsCount ) {
    return( pLOStarsArray[ StarNumber ] );
  }

  return( 0 );
}

void LOCalc :: ScanStars( const LOStarData * pLOStarData, APSVec3d * r_Asteroid )
{
  unsigned int   i;
  double         RA;
  double         Dec;
  const LOStar * pLOStar;

  RA = (*r_Asteroid)[apsmathlib::phi];
  Dec = (*r_Asteroid)[apsmathlib::theta];

  ClearStarsArray();

  for( i = 0; i < pLOStarData->GetCurrentNumber(); i++ ) {
    pLOStar = pLOStarData->GetStarPtr( i );

    if( RA - ANGLE_DELTA < pLOStar->GetRA() ) {
      if( RA + ANGLE_DELTA > pLOStar->GetRA() ) {
        if( Dec - ANGLE_DELTA < pLOStar->GetDec() ) {
          if( Dec + ANGLE_DELTA > pLOStar->GetDec() ) {
            if( AddStar( pLOStar ) ) {
              std::cout << "WARNING: too many stars 1" << std::endl;
            }
          }
        }
      }
    }
  }
}

void LOCalc :: ScanStars1( const LOStarData * pLOStarData, APSVec3d * r_Asteroid1, APSVec3d * r_Asteroid2 )
{
  unsigned int   i;
  double         RA1;
  double         Dec1;
  double         RA2;
  double         Dec2;
  double         Tmp;
  const LOStar * pLOStar;

  RA1  = (*r_Asteroid1)[apsmathlib::phi];
  Dec1 = (*r_Asteroid1)[apsmathlib::theta];
  RA2  = (*r_Asteroid2)[apsmathlib::phi];
  Dec2 = (*r_Asteroid2)[apsmathlib::theta];

  if( RA1 > RA2 ) {
    Tmp = RA1;
    RA1 = RA2;
    RA2 = Tmp;
  }

  if( Dec1 > Dec2 ) {
    Tmp  = Dec1;
    Dec1 = Dec2;
    Dec2 = Tmp;
  }

  ClearStarsArray();

  for( i = 0; i < pLOStarData->GetCurrentNumber(); i++ ) {
    pLOStar = pLOStarData->GetStarPtr( i );

    if( RA1 - ANGLE_DELTA1 < pLOStar->GetRA() ) {
      if( RA2 + ANGLE_DELTA1 > pLOStar->GetRA() ) {
        if( Dec1 - ANGLE_DELTA1 < pLOStar->GetDec() ) {
          if( Dec2 + ANGLE_DELTA1 > pLOStar->GetDec() ) {

            if( AddStar( pLOStar ) ) {
              std::cout << "WARNING: too many stars 2" << std::endl;
            }
          }
        }
      }
    }
  }
}

int LOCalc :: ScanStars2( const LOStarData * pLOStarData, const int ScanStep )
{
  int            i;
  double         RA_MIN;
  double         Dec_MIN;
  double         RA_MAX;
  double         Dec_MAX;
  double         Tmp_RA;
  double         Tmp_Dec;
  const LOStar * pLOStar;
  int            RetCode;

  RetCode = 0;

  RA_MIN  = std::numeric_limits<double>::max();
  Dec_MIN = std::numeric_limits<double>::max();
  RA_MAX  = -std::numeric_limits<double>::max();
  Dec_MAX = -std::numeric_limits<double>::max();

  for( i = 0; i < ScanStep; i++ ) {
    Tmp_RA  = (*ChebArray[ i ])[apsmathlib::phi];
    Tmp_Dec = (*ChebArray[ i ])[apsmathlib::theta];
 
    if( Tmp_RA < RA_MIN ) {
      RA_MIN = Tmp_RA;
    }

    if( Tmp_Dec < Dec_MIN ) {
      Dec_MIN = Tmp_Dec;
    }

    if( Tmp_RA > RA_MAX ) {
      RA_MAX = Tmp_RA;
    }

    if( Tmp_Dec > Dec_MAX ) {
      Dec_MAX = Tmp_Dec;
    }
  }


  /*ClearStarsArray();

  for( i = 0; i < pLOStarData->GetCurrentNumber(); i++ ) {
    pLOStar = pLOStarData->GetStarPtr( i );

    if( RA_MIN - ANGLE_DELTA1 < pLOStar->GetRA() ) {
      if( RA_MAX + ANGLE_DELTA1 > pLOStar->GetRA() ) {
        if( Dec_MIN - ANGLE_DELTA1 < pLOStar->GetDec() ) {
          if( Dec_MAX + ANGLE_DELTA1 > pLOStar->GetDec() ) {

            if( AddStar( pLOStar ) ) {
              std::cout << "WARNING: too many stars 3" << std::endl;
              RetCode = 1;
            }
          }
        }
      }
    }
  }*/

const LOStar * pNewLOStarsArray[ MAX_STAR_NUMBER ];
unsigned int NewStarNumber;

NewStarNumber = MAX_STAR_NUMBER;

if( pLOStarData->FastFindStars( pNewLOStarsArray, NewStarNumber, RA_MIN - ANGLE_DELTA1, Dec_MIN - ANGLE_DELTA1,
                               RA_MAX + ANGLE_DELTA1, Dec_MAX + ANGLE_DELTA1 ) ) {
  std::cout << "WARNING: too many stars 4" << std::endl;
  //RetCode = 1;
}

ClearStarsArray();

for( unsigned int j = 0; j < NewStarNumber; j++ ) {
  pLOStar = pNewLOStarsArray[ j ];

  if( AddStar( pLOStar ) ) {
    std::cout << "WARNING: too many stars 5" << std::endl;
    //RetCode = 1;
    break;
  }
}

//printf("StarNumber = %d NewStarNumber = %d\n", StarsCount, NewStarNumber );

  return( RetCode );
}

void LOCalc :: CalcStrip( const double t_prev, const APSVec3d & r_prev, const APSVec3d & r_now,
                          const APSVec3d & eStar, const double AstRadius, double& Lambda1, double& Phi1,
                          double& Lambda2, double& Phi2 ) const
{
  APSVec3d TmpVec;
  APSVec3d r_G;
  double   VecLength;
  APSVec3d Vec1 = Cross( r_now - r_prev, eStar );
  double   T = ( t_prev - apsastroalg::MJD_J2000 ) / 36525.0;
  APSMat3d PrecMat = apsastroalg::NutMatrix( T ) * apsastroalg::PrecMatrix_Equ( apsastroalg::T_J2000, T );
  double   UT_UTC  = pModule->GetUT_UTC() + apsastroalg::equequ( T );

  Vec1 = Vec1 / Norm( Vec1 );

  Vec1 = AstRadius * Vec1;

  TmpVec = r_prev + Vec1;

  VecLength = Norm( TmpVec );

  if( VecLength < apsastroalg::R_Earth ) {
    TmpVec = TmpVec + sqrt( apsastroalg::R_Earth * apsastroalg::R_Earth - VecLength * VecLength ) * eStar;

    TmpVec = APSVec3d( TmpVec[ apsmathlib::x ], TmpVec[ apsmathlib::y ], fac * TmpVec[ apsmathlib::z ] );

//----- Precessing and nutation -------

    TmpVec = PrecMat * TmpVec;

//-------------------------------------

    r_G     = apsmathlib::R_z( apsastroalg::GMST( t_prev + UT_UTC ) ) * TmpVec;
    Lambda1 = apsmathlib::Modulo( r_G[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;
    Phi1    = r_G[ apsmathlib::theta ];
    Phi1    = Phi1 + 0.1924 * apsmathlib::Rad * sin( 2 * Phi1 );
  }

  TmpVec = r_prev - Vec1;

  VecLength = Norm( TmpVec );

  if( VecLength < apsastroalg::R_Earth ) {
    TmpVec = TmpVec + sqrt( apsastroalg::R_Earth * apsastroalg::R_Earth - VecLength * VecLength ) * eStar;

    TmpVec = APSVec3d( TmpVec[ apsmathlib::x ], TmpVec[ apsmathlib::y ], fac * TmpVec[ apsmathlib::z ] );

//----- Precessing and nutation -------

    TmpVec = PrecMat * TmpVec;

//-------------------------------------

    r_G     = apsmathlib::R_z( apsastroalg::GMST( t_prev + UT_UTC ) ) * TmpVec;
    Lambda2 = apsmathlib::Modulo( r_G[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;
    Phi2    = r_G[ apsmathlib::theta ];
    Phi2    = Phi2 + 0.1924 * apsmathlib::Rad * sin( 2 * Phi2 );
  }
}

double PosAng( const APSVec3d & r, const APSVec3d & d )
{
  //
  // Variables
  //
  APSVec3d e_1, e_2, e_3;
  double   c, s, phi;


  // Unit vectors in radial, East, North direction
  e_1 = r / Norm(r);
  e_2 = Cross ( APSVec3d(0, 0, 1), r );
  e_2 = e_2 / Norm(e_2);
  e_3 = Cross (e_1, e_2);

  // Position angle
  c = Dot(d, e_3);
  s = Dot(d, e_2);
  phi = atan2(s, c);
  
  return( apsmathlib::Modulo( phi, 2.0 * apsmathlib::pi ) );
}

double LOCalc :: CalculateBrightness( const LOAsteroid * pLOAsteroid, const APSVec3d & R_Sun,
                                      const APSVec3d & rAstAU ) const
{
  double AstDistance;
  double SunDistance;
  double Phi1;
  double Phi2;
  double beta;
  double G;
  double Brightness;

  AstDistance = sqrt( Dot( rAstAU, rAstAU ) );
  SunDistance = sqrt( Dot( ( rAstAU - R_Sun ), ( rAstAU - R_Sun ) ) );

//  beta = PosAng( rAstAU, rAstAU - R_Sun );

  beta = acos( ( SunDistance * SunDistance + AstDistance * AstDistance - Dot( R_Sun, R_Sun ) ) / ( 2.0 * SunDistance * AstDistance ) );

  Phi1 = exp( -3.33 * pow( tan( beta / 2.0 ), 0.63 ) );
  Phi2 = exp( -1.87 * pow( tan( beta / 2.0 ), 1.22 ) );

  G = pLOAsteroid->GetSlope();
//printf("G = %lf Phi1 = %lf Phi2 = %lf %lf\n", G, Phi1, Phi2, ( 1.0 - G ) * Phi1 + G * Phi2 );

  Brightness = pLOAsteroid->GetBrigteness() + 5.0 * log10( AstDistance * SunDistance ) - 2.5 * log10( ( 1.0 - G ) * Phi1 + G * Phi2 );

  return( Brightness );
}

//-------------------------------------------------------------------------------------------
    
//*********************************************************
//  TransformEpoch - transform the epoch of star's position & motion (rigorous version)
//	
//   Input:
//      Years = duration of proper motion in (Years = 365.25 days)
//		ra0   = starting RA (radians)
//		de0   = starting DE (radians)
//		plx0  = starting Parallax (mas) , NULL => unknown
//		uRAs0 = starting uRAs [proper motion in RA * cos(DE)] (mas/yr)
//		uDE0  = starting uDE [proper motion in DE (mas/yr)
//		VR0   = starting radial velocity (km/s) , NULL => unknown
//
//   Output:
//		ra   = ending RA (degrees)
//		de   = ending DE (degrees)
//		plx  = ending Parallax (mas) (0.0 => unknown)
//		uRAs = ending uRAs [proper motion in RA * cos(DE)] (mas/yr)
//		uDE  = ending uDE [proper motion in DE (mas/yr)
//		VR   = ending radial velocity (km/s) , 0.0 => unknown
//
//	 Return:
//		True if no issues
//		False if problem with input parms
//
//   notes:
//		 * if parallax = 0 or not known, this routine will use 0.0001 (10 megaparsecs) for the parallax
//       This routine uses a linear motion model that includes radial velocity. 
//       This version follows the method from secton 1.5.5 of the Hipparcos documentation
//       *** However **** The HIP documents are not clear about units: 
//			The equations require Av for the A parameter and parallaxes are in radians and proper motions are in radians/yr
//			It is possible to rework the equations to accept mas & mas/yr instead but I didn't feel like doing the math
//          and testing...
//
//**********************************************************
//
bool TransformEpoch( const double Years, const double ra0, const double de0, const double plx0,
		     const double uRAs0, const double uDE0, const double VR0, double & ra,
		     double & de, double & plx, double & uRAs, double & uDE, double & VR )
{
        const double MAS2RAD = apsmathlib::Rad / ( 3600.0 * 1000.0 );
	double	pi0;		// initial parallax (mas)		
	double	r0[3];
	double	p0[3];
	double	q0[3];
	double	mu0[3];
	double	mu0_2;
	double	zeta0;
	double	f;

	double	u[6];
	double	p[3];
	double	q[3];
	double	mu[3];
	double	zeta;

	double	cosRA;
	double	sinRA;
	double	cosDE;
	double	sinDE;

	const double Av = 4.740470446;  // units = (km yr)/s

	double	dblTmp;

		//
		//  Check parallax & radial velocity input parms
		//
	if( plx0 <= 0 ) {
	  pi0 = 0.0001;		// if plx not specified, use 1.0E-04 mas => 10 megaparsecs
	}
	else {
	  pi0 = plx0;
	}	

	/********************************************************
	 * Begin with the initial quantities: zeta0, r0, p0, q0
	 */
		//
		//  sin, cos of initial RA & DE
		//
	dblTmp = ra0;
	cosRA = cos(dblTmp);
	sinRA = sin(dblTmp);
	
	dblTmp = de0;
	cosDE = cos(dblTmp);
	sinDE = sin(dblTmp);


		//
		// zeta0 = secular acceleration at initial position
		//
	zeta0 = (VR0 * pi0 * MAS2RAD) / Av;

		//
		//  compute r0 = unit vector toward initial position (units = AU)
		//
	r0[0] = cosDE * cosRA;
	r0[1] = cosDE * sinRA;
	r0[2] = sinDE;

		//
		// compute p0 & q0 - the other two orthogonal unit vectors in the "normal triad"
		//
	p0[0] = -sinRA;
	p0[1] = cosRA;
	p0[2] = 0.0;

	q0[0] = -sinDE * cosRA;
	q0[1] = -sinDE * sinRA;
	q0[2] = cosDE;

		//
		// compute mu0 = proper motion vector
		//
	mu0[0] = p0[0] * uRAs0 + q0[0] * uDE0;
	mu0[1] = p0[1] * uRAs0 + q0[1] * uDE0;
	mu0[2] =                    q0[2] * uDE0;			// p[2] is zero...

	mu0[0] *= MAS2RAD;		// convert to radians/yr
	mu0[1] *= MAS2RAD;
	mu0[2] *= MAS2RAD;

	// compute norm of mu0
		//
	mu0_2 = mu0[0] * mu0[0] + mu0[1] * mu0[1] + mu0[2] * mu0[2];


	/*************************
	 * Now move to new epoch
	 */

		//
		// f = distance factor for new epoch
		//
	f = 1.0/sqrt(1.0 + 2.0 * zeta0 * Years + (mu0_2 + (zeta0 * zeta0)) * (Years * Years) );

		//
		// u = direction vector at new epoch
		//
	u[0] = f * ( r0[0] * (1.0 + zeta0 * Years) + mu0[0] * Years );
	u[1] = f * ( r0[1] * (1.0 + zeta0 * Years) + mu0[1] * Years );
	u[2] = f * ( r0[2] * (1.0 + zeta0 * Years) + mu0[2] * Years );

		//
		// mu = proper motion vector at new epoch
		//
	mu[0] = (f * f * f) * ( mu0[0] * (1 + (zeta0 * Years)) - r0[0] * mu0_2 * Years );
	mu[1] = (f * f * f) * ( mu0[1] * (1 + (zeta0 * Years)) - r0[1] * mu0_2 * Years );
	mu[2] = (f * f * f) * ( mu0[2] * (1 + (zeta0 * Years)) - r0[2] * mu0_2 * Years );

		//
		//  zeta = secular acceleration at new epoch
		//
	zeta = (f * f) * ( zeta0 + (mu0_2 + (zeta0 * zeta0)) * Years );

	/***************************************
	 *  Now set the output parameters
	 */

		//
		// ra, de
		//
	dblTmp = sqrt(u[0] * u[0] + u[1] * u[1]);
	
	ra = atan2(u[1],u[0]) * apsmathlib::Deg;
	if ( ra < 0.0 )
		ra += 360.0;

	de = atan2(u[2],dblTmp) * apsmathlib::Deg;
	if( de > 270.0 )
		de -= 360.0;
	else if (de > 90.0)
		de -= 180.0;

		//
		//  plx = parallax at new epoch
		//
	plx = pi0 * f;

		//
		// compute p & q - the other two orthogonal unit vectors in the "normal triad"
		//
	dblTmp = ra * apsmathlib::Rad;
	cosRA = cos(dblTmp);
	sinRA = sin(dblTmp);
	
	dblTmp = de * apsmathlib::Rad;
	cosDE = cos(dblTmp);
	sinDE = sin(dblTmp);

	p[0] = -sinRA;
	p[1] = cosRA;
	p[2] = 0.0;

	q[0] = -sinDE * cosRA;
	q[1] = -sinDE * sinRA;
	q[2] = cosDE;
		// 
		//  uRAs, uDE
		//
	uRAs = (p[0] * mu[0] + p[1] * mu[1] + p[2] * mu[2]) / MAS2RAD;
	uDE  = (q[0] * mu[0] + q[1] * mu[1] + q[2] * mu[2]) / MAS2RAD;

		//
		//  vrad
		//
	if( plx == 0.0 )
	{
		// plx should not be zero, but... if it is... I will set VR to 0.0 as well
		//
		VR = 0.0;
	}
	else
	{
		VR = (zeta * Av) / (plx * MAS2RAD);
	}


	/************
	 * done
	 */
	return( true );

} // end of Transform Epoch
  
//-------------------------------------------------------------------------------------------

void LOCalc :: CalcParallax( const LOStar * pLOStar, const double ETMjdate, const float Parallax,
                             double & ParallaxDelta, double & ParallaxAlpha ) const
{
  double sinParallaxDelta = sin( pLOStar->GetDec() );
  double cosParallaxDelta = cos( pLOStar->GetDec() );
  double sinParallaxAlpha = sin( pLOStar->GetRA() );
  double cosParallaxAlpha = cos( pLOStar->GetRA() );

  APSVec3d rEarthBary = ephem->EarthBaryEquPos( ETMjdate );

  ParallaxDelta = Parallax * ( rEarthBary[ apsmathlib::x ] * sinParallaxDelta * cosParallaxAlpha +
                               rEarthBary[ apsmathlib::y ] * sinParallaxDelta * sinParallaxAlpha -
                               rEarthBary[ apsmathlib::z ] * cosParallaxDelta );

  if( cosParallaxDelta ) {
    ParallaxAlpha = Parallax * ( rEarthBary[ apsmathlib::x ] * sinParallaxAlpha -
                                 rEarthBary[ apsmathlib::y ] * cosParallaxAlpha ) / cosParallaxDelta;
  }
}

//  AsteroidUncertainty - in km. Return in km.

double LOCalc :: CalculateTotalUncertainty( double & AngleUncertainty, const double AsteroidUncertainty,
                                            const double ETMjdate, const short StarMv, const double Distance ) const
{
  const double STAR_UNCERTAINTY1 = 60.0 / 1000.0;
  const double STAR_UNCERTAINTY2 = 7.0 / 1000.0;
  const double PROPER_MOTION_UNCERTAINTY = 2.5 / 1000.0;

  double StarUncertainty = STAR_UNCERTAINTY1;

  if( StarMv < 900 ) {
    StarUncertainty = STAR_UNCERTAINTY2;
  }

  StarUncertainty = StarUncertainty + ( ETMjdate - apsastroalg::MJD_J2016 ) * PROPER_MOTION_UNCERTAINTY / 365.25;

  StarUncertainty = StarUncertainty * apsmathlib::Rad / 3600.0;

  double AsteroidAngleUncertainty = AsteroidUncertainty / Distance;

  AngleUncertainty = sqrt( StarUncertainty * StarUncertainty + AsteroidAngleUncertainty * AsteroidAngleUncertainty );

  StarUncertainty = StarUncertainty * Distance;

  return( sqrt( AsteroidUncertainty * AsteroidUncertainty + StarUncertainty * StarUncertainty ) );
}

int LOCalc :: ProcessStar( const LOAsteroid * pLOAsteroid, const APSVec3d * r_Asteroid,
                           const double ETMjdate, const double Mjdate, const LOStar * pLOStar,
                           const int StarNumber )
{
  APSVec3d       eStar;
  APSVec3d       rAst;
  APSVec3d       rAstAU;
  APSVec3d       r_G;
  APSVec3d       r;
  double         Lambda;
  double         Phi;
  double         s0;
  double         s;
  double         eStarDist;
  double         Delta;
  double         r0;
  double         DT;
  float          Parallax;
  double         ParallaxDelta;
  double         ParallaxAlpha;
  double         AngleUncertainty;
  double         TotalUncertainty;
  double         ra;
  double         de;
  double         plx;
  double         uRAs;
  double         uDE;
  double         VR;
  int            RetCode = 0;

  ParallaxDelta = 0.0;
  ParallaxAlpha = 0.0;

  Parallax = pLOStar->GetParallax();

  DT = ( ETMjdate - pLOStar->GetEpoch() ) / 365.25;
    
  if( !TransformEpoch( DT, pLOStar->GetRA(), pLOStar->GetDec(),
		       apsmathlib::Deg * Parallax * 1000.0 * 3600.0,
		       apsmathlib::Deg * pLOStar->GetpmRA() * 1000.0 * 3600.0,
		       apsmathlib::Deg * pLOStar->GetpmDec() * 1000.0 * 3600.0,
		       pLOStar->GetVrad(),
		       ra, de, plx, uRAs, uDE, VR ) ) {
    std::ostringstream Msg;
    Msg << "ProcessStar" << std::endl;
    pModule->InfoMessage( LO_CALC_TRANSFORM_EPOCH, Msg.str() );
    std::cout << "Error returned by TransformEpoch" << std::endl;
    return( 1 );
  }

  if( Parallax ) {
    CalcParallax( pLOStar, ETMjdate, apsmathlib::Rad * apsmathlib::Ddd( 0, 0, plx / 1000.0 ), ParallaxDelta, ParallaxAlpha );
  }
  
  //std::cout << apsmathlib::APSAngle( ( ra + apsmathlib::Deg * ParallaxAlpha ) / 15, apsmathlib::DMMSSs );
  //std::cout << std::endl;	
  //std::cout << apsmathlib::APSAngle( de + apsmathlib::Deg * ParallaxDelta, apsmathlib::DMMSSs );
  //std::cout << std::endl;  

  double StarRA = apsmathlib::Rad * ra + ParallaxAlpha;
  double StarDec = apsmathlib::Rad * de + ParallaxDelta;
  
  eStar = APSVec3d( apsmathlib::Polar( StarRA, StarDec ) );

  eStar = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], eStar[ apsmathlib::z ] / fac );

  eStarDist = Norm( eStar );

  eStar = eStar / eStarDist;

  rAstAU = APSVec3d( (*r_Asteroid)[ apsmathlib::x ], (*r_Asteroid)[ apsmathlib::y ], (*r_Asteroid)[ apsmathlib::z ] / fac );

  rAst = GetAU() * rAstAU;

  s0 = -Dot( rAst, eStar );

  Delta = s0 * s0 + apsastroalg::R_Earth * apsastroalg::R_Earth - Dot( rAst, rAst );
  r0 = sqrt( apsastroalg::R_Earth * apsastroalg::R_Earth - Delta );

  if( r0 < apsastroalg::R_Earth ) {

    s = s0 + sqrt( Delta ); //s = s0 - sqrt( Delta );
    r = rAst + s * eStar;

    r = APSVec3d( r[ apsmathlib::x ], r[ apsmathlib::y ], fac * r[ apsmathlib::z ] );

//----- Precessing and nutation -------

    double T = ( ETMjdate - apsastroalg::MJD_J2000 ) / 36525.0;

    r = apsastroalg::PrecMatrix_Equ( apsastroalg::T_J2000, T ) * r;

    r = apsastroalg::NutMatrix( T ) * r;

//-------------------------------------

    r_G    = apsmathlib::R_z( apsastroalg::GMST( Mjdate + pModule->GetUT_UTC() + apsastroalg::equequ( T ) ) ) * r;                    // Greenwich coordinates
    Lambda = apsmathlib::Modulo( r_G[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;      // East longitude
    Phi    = r_G[ apsmathlib::theta ];                                 // Geocentric latitude
    Phi    = Phi + 0.1924 * apsmathlib::Rad * sin( 2 * Phi );          // Geographic latitude

/*    cout << DateTime(Mjdate,HHMMSS)
         << "  " << DateTime(ETMjdate,HHMMSS)
         << setprecision(1) << setw(12) << Angle(Deg*rAst[phi]/15.0,DMMSSs)
         << "  " << showpos << setw(9) << Angle(Deg*rAst[theta],DMMSS)
         << "  " << noshowpos << setprecision(6) << setw(11) << r0
         << "      " << setw(6) << Angle(Deg*Phi,DMM)
         << "   "    << setw(7) << Angle(Deg*Lambda,DMM)
         << endl;*/

    //cout << DateTime(Mjdate,HHMMSS) << endl;

    if( !pModule->GetIfExtraRadius() ) {
      if( GetEventStar() < 0 ) {
        SetEventStar( StarNumber );

        std::cout << "------------------------ Start event -------------------------------" << std::endl;
        std::cout << "Asteroid: " << pLOAsteroid->GetAsteroidID() << " " << pLOAsteroid->GetAsteroidNamePtr() << std::endl;
        std::cout << "Star: " << std::fixed << LOStarData :: GetCatName( pLOStar->GetCatalogue() ) << " " << std::fixed <<
	  LOStarData::GetStarName( pLOStar->GetCatalogue(), pLOStar->GetStarNumber() );  /*pLOStar->GetStarNumber()*/;
        std::cout << " Mv =" << std::fixed << std::setprecision(2) << std::setw(5) << pLOStar->GetMv() / 100.0 << std::endl;
        std::cout << " RA = " << std::fixed << std::setprecision(6) << std::setw(9);
        std::cout << apsmathlib::APSAngle( apsmathlib::Deg * StarRA / 15.0, apsmathlib::DMMSSs );
        std::cout << " Dec = " << std::fixed << std::setprecision(6) << std::setw(9);
        std::cout << apsmathlib::APSAngle( apsmathlib::Deg * StarDec, apsmathlib::DMMSSs );
        std::cout << " RA = " << std::fixed << apsmathlib::Deg * StarRA <<
	  " Dec = " << std::fixed << apsmathlib::Deg * StarDec << std::endl;
        std::cout << " RA_Catalog = ";
        std::cout << apsmathlib::APSAngle( apsmathlib::Deg * ( pLOStar->GetRA() ) / 15.0, apsmathlib::DMMSSs );
        std::cout << " Dec_Catalog = ";
        std::cout << apsmathlib::APSAngle( apsmathlib::Deg * ( pLOStar->GetDec() ), apsmathlib::DMMSSs );
        std::cout << std::fixed << std::setprecision(9) << std::setw(11) << " RA_Catalog = " << std::fixed << apsmathlib::Deg * pLOStar->GetRA() <<
                     " Dec_Catalog = " << std::fixed << apsmathlib::Deg * pLOStar->GetDec() << std::endl;
        std::cout << std::fixed << std::setprecision(2) << std::setw(4) << " pmRA = " << std::fixed << uRAs <<
	             "mas/year pmDec = " << std::fixed << uDE << "mas/year" << " Vrad = " << pLOStar->GetVrad() << std::endl;
        std::cout << " Parallax = " << std::fixed << std::setprecision(2) << std::setw(6) << plx <<
                     "mas ParallaxAlpha = " << std::fixed << std::setprecision(3) << std::setw(7) << apsmathlib::Deg * 1000.0 * 3600.0 * ParallaxAlpha <<
                     "mas ParallaxDelta = " << std::fixed << std::setprecision(3) << std::setw(7) << apsmathlib::Deg * 1000.0 * 3600.0 * ParallaxDelta << "mas" << std::endl;

APSVec3d rEarthBary = ephem->EarthBaryEquPos( ETMjdate );
std::cout << " rEarthBary[ x ] = " << std::fixed << std::setprecision(6) << std::setw(8) << rEarthBary[ apsmathlib::x ] <<
             " rEarthBary[ y ] = " << std::fixed << std::setprecision(6) << std::setw(8) << rEarthBary[ apsmathlib::y ] <<
             " rEarthBary[ z ] = " << std::fixed << std::setprecision(6) << std::setw(8) << rEarthBary[ apsmathlib::z ] << std::endl;


        APSVec3d       r_star;
        double         Lambda_star;
        double         Phi_star;

        r_star = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], fac * eStar[ apsmathlib::z ] );
        r_star = apsmathlib::R_z( apsastroalg::GMST( Mjdate ) ) * r_star;
        Lambda_star = apsmathlib::Modulo( r_star[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;
        Phi_star    = r_star[ apsmathlib::theta ];
        Phi_star    = Phi_star + 0.1924 * apsmathlib::Rad * sin( 2 * Phi_star );

        r_prev      = rAst + s0 * eStar;
        t_prev      = Mjdate;
        Lambda_prev = Lambda;
        Phi_prev    = Phi;

        double MoonPhase;
        double SunDist;
        double MoonDist;
        double Brightness;
        double BrightDelta;

        APSVec3d  R_Sun  = ephem->SunEquPos( ETMjdate );  // In AU !!!
        APSVec3d  R_Moon = ephem->MoonEquPos( ETMjdate ); // In AU !!!

        Brightness = CalculateBrightness( pLOAsteroid, R_Sun, rAstAU );

        BrightDelta = log10( pow( 2.512, pLOStar->GetMv() / 100.0 ) +
                             pow( 2.512, Brightness ) ) / log10( 2.512 ) - pLOStar->GetMv() / 100.0;

        MoonPhase = 50.0 * ( 1 + ( Dot( -R_Moon, R_Sun - R_Moon ) / ( Norm( R_Sun - R_Moon ) * Norm( R_Moon ) ) ) );

        R_Sun = R_Sun / Norm( R_Sun );

        SunDist = acos( Dot( eStar, R_Sun ) );

        R_Moon = R_Moon / Norm( R_Moon );

        MoonDist = acos( Dot( eStar, R_Moon ) );

        TotalUncertainty = CalculateTotalUncertainty( AngleUncertainty, -pLOAsteroid->GetEphemerisUncertainty() * s0,
                                                      Mjdate, pLOStar->GetMv(), -s0 );

        std::cout << "Diameter = " << std::fixed << std::setprecision(1) << std::setw(5) << pLOAsteroid->GetDiameter() <<
                     " Brightness = " << std::fixed << std::setprecision(2) << std::setw(5) << Brightness <<
                     " Delta = " << std::fixed << std::setprecision(2) << std::setw(5) << BrightDelta <<
                     " Uncertainty = " << std::fixed << std::setprecision(3) << std::setw(5) <<
                     apsmathlib::Deg * AngleUncertainty * 3600.0 <<
                     "( " << std::fixed << std::setprecision(0) << std::setw(3) <<
                      TotalUncertainty << " )" << std::endl;

        std::cout << "Sun dist = " << std::fixed << std::setprecision(1) << std::setw(5) << apsmathlib::Deg * SunDist <<
                     " Moon dist = " << std::fixed << std::setprecision(1) << std::setw(5) << apsmathlib::Deg * MoonDist <<
                     " Moon phase = " << std::fixed << std::setprecision(1) << std::setw(5) << MoonPhase << "%" << std::endl;

        std::cout << apsastroalg::DateTime( Mjdate, apsastroalg::None );

        std::cout << std::endl << std::endl;

        if( pModule->GetOutputType() ) {
          if( pModule->GetOutputType() == 1 ) {
            std::cout << "location geocentricToCartesian(<" << std::fixed << std::setprecision(6) << apsmathlib::Deg * Phi_star <<
                         ", " << std::fixed << std::setprecision(6) << apsmathlib::Deg * Lambda_star <<
                         ", " << std::fixed << std::setprecision(6) << CAMERA_DIST << ">)" << std::endl << std::endl;
          }

          if( pModule->GetOutputType() == 2 ) {
            std::cout << "LinOccult Shadow Path" << std::endl;
          }
        }
        else {
          std::cout << "     Date/Time            Long                    Lat               Star alt Sun alt   Durat" << std::endl;
        }

        PointNumber = 0;
      }
      else {
        if( GetEventStar() != StarNumber ) {
          std::cout << "WARNING: two stars event" << std::endl;
        }
      }
    }

    if( !( ShowNumber % 10 ) ) {
      if( pModule->GetOutputType() == 1 ) {
        std::cout << " TextMarker(<" << std::fixed << apsmathlib::Deg * Phi <<
                     ", " << std::fixed << apsmathlib::Deg * Lambda << ", 0>, T_White, 2.5,\"";
        std::cout << apsastroalg::DateTime( Mjdate, apsastroalg::HHMMSS );
        std::cout << "\", 0)" << std::endl;
      }
    }

    ShowNumber++;

    if( pModule->GetOutputType() ) {
      double Lambda1 = std::numeric_limits<double>::max();
      double Phi1    = std::numeric_limits<double>::max();
      double Lambda2 = std::numeric_limits<double>::max();
      double Phi2    = std::numeric_limits<double>::max();
      double Lambda3 = std::numeric_limits<double>::max();
      double Phi3    = std::numeric_limits<double>::max();
      double Lambda4 = std::numeric_limits<double>::max();
      double Phi4    = std::numeric_limits<double>::max();
      double Durat   = 0.0;

      if( t_prev != Mjdate ) {
        APSVec3d r_now = rAst + s0 * eStar;

        CalcStrip( t_prev, r_prev, r_now, eStar, pLOAsteroid->GetDiameter() / 2.0,
                   Lambda1, Phi1, Lambda2, Phi2 );

        Durat = CalcDuration( eStar, pLOAsteroid->GetDiameter(), r, r_old, Mjdate - t_prev );

        // Uncertainty

        TotalUncertainty = CalculateTotalUncertainty( AngleUncertainty, -pLOAsteroid->GetEphemerisUncertainty() * s0,
                                                      Mjdate, pLOStar->GetMv(), -s0 );

        CalcStrip( t_prev, r_prev, r_now, eStar,
                   TotalUncertainty + pLOAsteroid->GetDiameter() / 2.0,
                   Lambda3, Phi3, Lambda4, Phi4 );


        if( pModule->GetOutputType() == 1 ) {
          if( ( Phi1 != std::numeric_limits<double>::max() ) && ( Lambda1 != std::numeric_limits<double>::max() ) ) {
	    std::cout << "sphere {<0, 0, 0>, 5 texture { T_Gold_2E } putOnEarth(<" << std::fixed << apsmathlib::Deg * Phi1 <<
                         ", " << std::fixed << apsmathlib::Deg * Lambda1 << ", 0>)}" << std::endl;
          }

          if( ( Phi2 != std::numeric_limits<double>::max() ) && ( Lambda2 != std::numeric_limits<double>::max() ) ) {
	    std::cout << "sphere {<0, 0, 0>, 5 texture { T_Gold_2E } putOnEarth(<" << std::fixed << apsmathlib::Deg * Phi2 <<
                         ", " << std::fixed << apsmathlib::Deg * Lambda2 << ", 0>)}" << std::endl;
          }

          if( ( Phi3 != std::numeric_limits<double>::max() ) && ( Lambda3 != std::numeric_limits<double>::max() ) ) {
	    std::cout << "sphere {<0, 0, 0>, 5 texture { T_Gold_2E } putOnEarth(<" << std::fixed << apsmathlib::Deg * Phi3 <<
                         ", " << std::fixed << apsmathlib::Deg * Lambda3 << ", 0>)}" << std::endl;
          }

          if( ( Phi4 != std::numeric_limits<double>::max() ) && ( Lambda4 != std::numeric_limits<double>::max() ) ) {
            std::cout << "sphere {<0, 0, 0>, 5 texture { T_Gold_2E } putOnEarth(<" << std::fixed << apsmathlib::Deg * Phi4 <<
                         ", " << std::fixed << apsmathlib::Deg * Lambda4 << ", 0>)}" << std::endl;
          }
        }
        else {
          if( pModule->GetOutputType() == 2 ) {
            if( ( Phi1 != std::numeric_limits<double>::max() ) && ( Lambda1 != std::numeric_limits<double>::max() ) &&
                ( Phi2 != std::numeric_limits<double>::max() ) && ( Lambda2 != std::numeric_limits<double>::max() ) &&
                ( Phi3 != std::numeric_limits<double>::max() ) && ( Lambda3 != std::numeric_limits<double>::max() ) &&
                ( Phi4 != std::numeric_limits<double>::max() ) && ( Lambda4 != std::numeric_limits<double>::max() ) ) {
              std::cout << apsastroalg::DateTime( t_prev, apsastroalg::HHMMSS );
              std::cout << " ";
              std::cout << std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi3 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda3 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi1 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda1 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi_prev << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda_prev << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi2 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda2 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi4 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda4 << "," <<
	                   std::fixed << std::setprecision(1) << Durat << std::endl;
            }
          }
        }

        r_prev      = r_now;
        t_prev      = Mjdate;
        Lambda_prev = Lambda;
        Phi_prev    = Phi;
      }
    }
    else {
      double   StarElev;
      double   SunElev;
      double   Lambda1 = std::numeric_limits<double>::max();
      double   Phi1    = std::numeric_limits<double>::max();
      double   Lambda2 = std::numeric_limits<double>::max();
      double   Phi2    = std::numeric_limits<double>::max();
      double   Durat   = 0.0;
      APSVec3d R_Obs   = apsastroalg::Site( Lambda, Phi );
      APSVec3d R_Sun   = ephem->SunEquPos( ETMjdate );  // AU*SunEqu( ( ETMjdate - MJD_J2000 ) / 36525.0 );

      if( t_prev != Mjdate ) {
        APSVec3d r_now = rAst + s0 * eStar;

        CalcStrip( t_prev, r_prev, r_now, eStar, pLOAsteroid->GetDiameter() / 2.0,
                   Lambda1, Phi1, Lambda2, Phi2 );

        Durat = CalcDuration( eStar, pLOAsteroid->GetDiameter(), r, r_old, Mjdate - t_prev );

        r_prev = r_now;
        t_prev = Mjdate;
      }

      R_Obs = apsmathlib::R_z( -apsastroalg::GMST( Mjdate ) ) * R_Obs;

      R_Obs = R_Obs / Norm( R_Obs ); 
      
      StarElev = asin( Dot( R_Obs , eStar ) );

      R_Sun = R_Sun / Norm( R_Sun );

      SunElev = asin( Dot( R_Obs, R_Sun ) );

      if( apsmathlib::Deg * SunElev <= pModule->GetSunElev() ) {
        if( !OZI ) {
          int    D1;
          int    M1;
          double S1;
          int    D2;
          int    M2;
          double S2;
          int    Year1;
          int    Month1;
          int    Day1;
          int    Hour1;
          int    Min1;
          double Sec1;

          apsmathlib::DMS( apsmathlib::Deg * Lambda, D1, M1, S1 );
          apsmathlib::DMS( apsmathlib::Deg * Phi, D2, M2, S2 );

          apsastroalg::CalDat( Mjdate, Year1, Month1, Day1, Hour1, Min1, Sec1 );

          std::cout << Year1 << "/" << std::fixed << std::setw(2) << std::setfill( '0' ) << Month1 <<
                                "/" << std::fixed << std::setw(2) << std::setfill( '0' ) << Day1 <<
                                " " << std::fixed << std::setw(2) << std::setfill( '0' ) << Hour1 <<
                                ":" << std::fixed << std::setw(2) << std::setfill( '0' ) << Min1 <<
                                ":" << std::fixed << std::setprecision(1) << std::setw(4) << std::setfill( '0' ) << Sec1;

          std::cout << " " << std::setfill( ' ' ) << std::fixed << std::setprecision(3) << std::setw(8) << apsmathlib::Deg * Lambda <<
                       "(" << std::setw(4) << D1 << "o" <<
                              std::setw(2) << std::setfill( '0' ) << M1 << "'" <<
                              std::fixed << std::setprecision(1) << std::setw(4) << std::setfill( '0' ) << S1 << "\") " <<
                              std::setfill( ' ' ) << std::fixed <<  std::setprecision(3) << std::setw(7) << apsmathlib::Deg * Phi << "(" <<
                              std::setw(4) << D2 << "o" <<
                              std::setw(2) << std::setfill( '0' ) << M2 << "'" <<
                              std::fixed << std::setprecision(1) << std::setw(4) << std::setfill( '0' ) << S2 << "\") " <<
                              std::setfill( ' ' ) << std::fixed <<  std::setprecision(1) << std::setw(7) << apsmathlib::Deg * StarElev << " " <<
                              std::setfill( ' ' ) << std::fixed << std::setprecision(1) << std::setw(7) << apsmathlib::Deg * SunElev << "    " <<
                              std::setfill( ' ' ) << std::fixed << std::setprecision(1) << std::setw(4) << Durat << std::endl;
        }
      }

      // For OziExplorer

      if( OZI ) {
        if( ( apsmathlib::Deg * Lambda >= 37.0 ) && ( apsmathlib::Deg * Lambda <= 39.0 ) ) {
          if( ( apsmathlib::Deg * Phi >= 54.0 ) && ( apsmathlib::Deg * Phi <= 57.0 ) ) {
            PointNumber++;
            std::cout << std::setw(4) << PointNumber << "," <<
                         std::fixed << std::setprecision(6) << std::setw(14) << std::left << Mjdate << "," <<
                         std::fixed << std::setprecision(6) << std::setw(11) << std::right << apsmathlib::Deg * Phi << "," <<
                         std::fixed << std::setprecision(6) << std::setw(11) << apsmathlib::Deg * Lambda << "," <<
                         "37731.89943, 83, 1, 3,         0,     65535,                                        , 0, 0,    0,    660, 6, 0,17" << std::endl;
          }
        }
      }
    }

    r_old = r;
  }
  else {
    if( pModule->GetIfExtraRadius() ) {
      double MaxDist;

      TotalUncertainty = CalculateTotalUncertainty( AngleUncertainty, -pLOAsteroid->GetEphemerisUncertainty() * s0,
                                                    Mjdate, pLOStar->GetMv(), -s0 );

      MaxDist = TotalUncertainty + apsastroalg::R_Earth;

      if( MaxDist > pModule->GetExtraRadius() * apsastroalg::R_Earth ) {
        MaxDist = pModule->GetExtraRadius() * apsastroalg::R_Earth;
      } 

      if( r0 < MaxDist ) {

        if( GetEventStar() < 0 ) {
          SetEventStar( StarNumber );

          std::cout << "============================== Start extra event ===============================" << std::endl;

          //---------------------------------------------------------

          std::cout << "------------------------ Start event -------------------------------" << std::endl;
          std::cout << "Asteroid: " << pLOAsteroid->GetAsteroidID() << " " << pLOAsteroid->GetAsteroidNamePtr() << std::endl;
          std::cout << "Star: " << std::fixed <<
	    LOStarData::GetStarName( pLOStar->GetCatalogue(), pLOStar->GetStarNumber() ) /*pLOStar->GetStarNumber()*/;
          std::cout << " Mv=" << std::fixed << std::setprecision(2) << std::setw(5) << pLOStar->GetMv() / 100.0;
          std::cout << " RA = " << std::fixed << std::setprecision(6) << std::setw(9);
          std::cout << apsmathlib::APSAngle( apsmathlib::Deg * StarRA / 15.0, apsmathlib::DMMSSs );
          std::cout << " Dec = "  << std::fixed << std::setprecision(6) << std::setw(9);
          std::cout << apsmathlib::APSAngle( apsmathlib::Deg * StarDec, apsmathlib::DMMSSs );
          std::cout << std::fixed << " RA = " << apsmathlib::Deg * StarRA <<
                       std::fixed << " Dec = " << apsmathlib::Deg * StarDec << std::endl;

          double MoonPhase;
          double SunDist;
          double MoonDist;
          double Brightness;
          double BrightDelta;

          APSVec3d  R_Sun  = ephem->SunEquPos( ETMjdate );  // In AU !!!
          APSVec3d  R_Moon = ephem->MoonEquPos( ETMjdate ); // In AU !!!

          Brightness = CalculateBrightness( pLOAsteroid, R_Sun, rAstAU );

          BrightDelta = log10( pow( 2.512, pLOStar->GetMv() / 100.0 ) +
                               pow( 2.512, Brightness ) ) / log10( 2.512 ) - pLOStar->GetMv() / 100.0;

          MoonPhase = 50.0 * ( 1 + ( Dot( -R_Moon, R_Sun - R_Moon ) / ( Norm( R_Sun - R_Moon ) * Norm( R_Moon ) ) ) );

          R_Sun = R_Sun / Norm( R_Sun );

          SunDist = acos( Dot( eStar, R_Sun ) );

          R_Moon = R_Moon / Norm( R_Moon );

          MoonDist = acos( Dot( eStar, R_Moon ) );

          TotalUncertainty = CalculateTotalUncertainty( AngleUncertainty, -pLOAsteroid->GetEphemerisUncertainty() * s0,
                                                        Mjdate, pLOStar->GetMv(), -s0 );

          std::cout << "Diameter = " << std::fixed << pLOAsteroid->GetDiameter() <<
                       " Brightness = " << std::fixed << std::setprecision(2) << std::setw(5) << Brightness <<
                       " Delta = " << std::fixed << std::setprecision(2) << std::setw(5) << BrightDelta <<
                       " Uncertainty = " << std::fixed << std::setprecision(6) << apsmathlib::Deg * AngleUncertainty * 3600.0 <<
                       "( " << std::fixed << std::setprecision(6) << TotalUncertainty << " )" << std::endl;

          std::cout << "Sun dist = " << std::fixed << std::setprecision(1) << std::setw(5) << apsmathlib::Deg * SunDist <<
                       " Moon dist = " << std::fixed << std::setprecision(1) << std::setw(5) << apsmathlib::Deg * MoonDist <<
                       " Moon phase = " << std::fixed << std::setprecision(1) << std::setw(5) << MoonPhase << "%" << std::endl << std::endl;

          APSVec3d       r_star;
          double         Lambda_star;
          double         Phi_star;

          r_star = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], fac * eStar[ apsmathlib::z ] );
          r_star = apsmathlib::R_z( apsastroalg::GMST( Mjdate ) ) * r_star;
          Lambda_star = apsmathlib::Modulo( r_star[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;
          Phi_star    = r_star[ apsmathlib::theta ];
          Phi_star    = Phi_star + 0.1924 * apsmathlib::Rad * sin( 2 * Phi_star );

          std::cout << "location geocentricToCartesian(<" <<
                        std::fixed << std::setprecision(6) << apsmathlib::Deg * Phi_star << ", " <<
                        std::fixed << std::setprecision(6) << apsmathlib::Deg * Lambda_star << ", " <<
                        std::fixed << std::setprecision(6) << CAMERA_DIST << ">)" << std::endl << std::endl;

          //---------------------------------------------------------
        }
        else {
          if( GetEventStar() != StarNumber ) {
            std::cout << "WARNING: two stars event" << std::endl;
          }
        }

        std::cout << apsastroalg::DateTime( Mjdate, apsastroalg::HHMMSS ) << std::endl;
        std::cout << "Star: " << std::fixed <<
	  LOStarData::GetStarName( pLOStar->GetCatalogue(), pLOStar->GetStarNumber() ) /*pLOStar->GetStarNumber()*/ <<
                     " " << std::fixed << std::setprecision(6) << apsmathlib::Deg * pLOStar->GetRA() <<
                     " " << std::fixed << std::setprecision(6) << apsmathlib::Deg * pLOStar->GetDec() << std::endl;
        std::cout << "r0 = " << std::fixed << std::setprecision(6) << r0 << std::endl << std::endl;
      }
      else {
        if( GetEventStar() == StarNumber ) {
          SetEventStar( -1 );
          std::cout << "========================== End extra event ===============================" << std::endl;
        }
      }
    }
    else {
      if( GetEventStar() == StarNumber ) {
        SetEventStar( -1 );
        std::cout << "--------------------------- End event ---------------------------------" << std::endl;
      }
    }
  }

  return( RetCode );  
}

int LOCalc :: CalculateParameters( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar,
                                   const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                                   double ET_UT, const double BeginOccTime, const double EndOccTime,
                                   double & StarRA, double & StarDec,
                                   double & MoonPhase, double & SunDist, double & MoonDist,
                                   double & Brightness, double & BrightDelta, double & Uncertainty,
                                   double & AngleUncertainty ) const
{
  apsmathlib::APSCheb * pAPSCheb;
  APSVec3d              eStar;
  APSVec3d              rAstAU;
  APSVec3d              rAst;
  APSVec3d              r_equ;
  double                eStarDist;
  double                Mjdate;
  double                ETMjdate;
  double                DT;
  float                 Parallax;
  double                ParallaxDelta = 0.0;
  double                ParallaxAlpha = 0.0;
  double                s0;
  bool                  valid;
  double                ra;
  double                de;
  double                plx;
  double                uRAs;
  double                uDE;
  double                VR;
  int                   RetCode = 0;

  pAPSCheb = new apsmathlib::APSCheb( pModule->GetChebSubModulePtr(), ChebOrder, cX, cY, cZ, BeginOccTime, EndOccTime );

  Mjdate = ( BeginOccTime + EndOccTime ) / 2.0;

  if( !pAPSCheb->Value( Mjdate, r_equ ) ) {
    apsastroalg::ETminUT( ( Mjdate - apsastroalg::MJD_J2000 )/36525.0, ET_UT, valid );

    if( !valid ) {
      ET_UT = pModule->GetET_UT();
    }

    Parallax = pLOStar->GetParallax();

    ETMjdate = Mjdate + ET_UT / 86400.0;

    DT = ( ETMjdate - pLOStar->GetEpoch() ) / 365.25;

    if( !TransformEpoch( DT, pLOStar->GetRA(), pLOStar->GetDec(),
			 apsmathlib::Deg * Parallax * 1000.0 * 3600.0,
			 apsmathlib::Deg * pLOStar->GetpmRA() * 1000.0 * 3600.0,
			 apsmathlib::Deg * pLOStar->GetpmDec() * 1000.0 * 3600.0,
			 pLOStar->GetVrad(),
			 ra, de, plx, uRAs, uDE, VR ) ) {
      std::ostringstream Msg;
      Msg << "CalculateParameters" << std::endl;
      pModule->InfoMessage( LO_CALC_TRANSFORM_EPOCH, Msg.str() );
      std::cout << "Error returned by TransformEpoch" << std::endl;
      return( 1 );
    }

    if( Parallax ) {
      CalcParallax( pLOStar, ETMjdate, apsmathlib::Rad * apsmathlib::Ddd( 0, 0, plx / 1000.0 ), ParallaxDelta, ParallaxAlpha );
    }
  
    //std::cout << apsmathlib::APSAngle( ( ra + apsmathlib::Deg * ParallaxAlpha ) / 15, apsmathlib::DMMSSs );
    //std::cout << std::endl;	
    //std::cout << apsmathlib::APSAngle( de + apsmathlib::Deg * ParallaxDelta, apsmathlib::DMMSSs );
    //std::cout << std::endl;  

    StarRA = apsmathlib::Rad * ra + ParallaxAlpha;
    StarDec = apsmathlib::Rad * de + ParallaxDelta;

    eStar = APSVec3d( apsmathlib::Polar( StarRA, StarDec ) );
    eStar = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], eStar[ apsmathlib::z ] / fac );

    eStarDist = Norm( eStar );

    eStar = eStar / eStarDist;

    APSVec3d R_Sun  = ephem->SunEquPos( ETMjdate );  // In AU !!!
    APSVec3d R_Moon = ephem->MoonEquPos( ETMjdate ); // In AU !!!

    rAstAU = APSVec3d( r_equ[ apsmathlib::x ], r_equ[ apsmathlib::y ], r_equ[ apsmathlib::z ] / fac );

    Brightness = CalculateBrightness( pLOAsteroid, R_Sun, rAstAU );

    BrightDelta = log10( pow( 2.512, pLOStar->GetMv() / 100.0 ) +
                         pow( 2.512, Brightness ) ) / log10( 2.512 ) - pLOStar->GetMv() / 100.0;

    MoonPhase = 50.0 * ( 1 + ( Dot( -R_Moon, R_Sun - R_Moon ) / ( Norm( R_Sun - R_Moon ) * Norm( R_Moon ) ) ) );

    R_Sun = R_Sun / Norm( R_Sun );

    SunDist = acos( Dot( eStar, R_Sun ) );

    R_Moon = R_Moon / Norm( R_Moon );

    MoonDist = acos( Dot( eStar, R_Moon ) );

    rAst = GetAU() * rAstAU;

    s0 = -Dot( rAst, eStar );

    Uncertainty = CalculateTotalUncertainty( AngleUncertainty, -pLOAsteroid->GetEphemerisUncertainty() * s0,
                                             Mjdate, pLOStar->GetMv(), -s0 );
  }
  else {
    std::cout << "ERROR: CalculateParameters - pAPSCheb->Value1" << std::endl;
    RetCode = 1;
  }

  delete pAPSCheb;

  return( RetCode );
}

void LOCalc :: PrintHeader( const int AsteroidID, const std::string & AsteroidName,
                            const double Diameter, const double EphemerisUncertainty,
                            const unsigned char Catalog, const int StarNumber, const short Mv,
                            const double BeginOccTime, const double EndOccTime,
                            const int EarthFlag, const double MaxDuration,
                            const double StarRA, const double StarDec,
                            const double MoonPhase, const double SunDist, const double MoonDist,
                            const double Brightness, const double BrightDelta, const double Uncertainty ) const
{
  std::cout << "Asteroid: " << AsteroidID << " " << AsteroidName << std::endl;
  std::cout << "Star: " << std::fixed << LOStarData :: GetCatName( Catalog ) << " " << StarNumber;
  std::cout << " Mv=" << std::fixed << std::setprecision(2) << std::setw(5) << Mv / 100.0;
  std::cout << " RA = " << std::fixed << std::setprecision(6) << std::setw(9);
  std::cout << apsmathlib::APSAngle( apsmathlib::Deg * StarRA / 15.0, apsmathlib::DMMSSs );
  std::cout << " Dec = " << std::fixed << std::setprecision(6) << std::setw(9);
  std::cout << apsmathlib::APSAngle( apsmathlib::Deg * StarDec, apsmathlib::DMMSSs );
  std::cout << " RA = " << std::fixed << apsmathlib::Deg * StarRA <<
               " Dec = " << std::fixed << apsmathlib::Deg * StarDec << std::endl;

  std::cout << "Diameter = " << std::fixed << std::setprecision(1) << std::setw(5) << Diameter <<
               " MaxDuration = " << std::fixed << std::setprecision(1) << std::setw(4) << MaxDuration << std::endl;

  std::cout << "Brightness = " << std::fixed << std::setprecision(2) << std::setw(5) << Brightness <<
               " Delta = " << std::fixed << std::setprecision(2) << std::setw(5) << BrightDelta <<
               " Uncertainty = " << std::fixed << std::setprecision(3) << std::setw(5) << apsmathlib::Deg * EphemerisUncertainty * 3600.0 <<
               "( " << std::fixed << std::setprecision(0) << std::setw(3) << Uncertainty << " )" << std::endl;

  std::cout << "Sun dist = " << std::fixed << std::setprecision(1) << std::setw(5) << apsmathlib::Deg * SunDist <<
               " Moon dist = " << std::fixed << std::setprecision(1) << std::setw(5) << apsmathlib::Deg * MoonDist <<
               " Moon phase = " << std::fixed << std::setprecision(1) << std::setw(5) << MoonPhase << "%" << std::endl;

  std::cout << apsastroalg::DateTime( ( BeginOccTime + EndOccTime ) / 2.0, apsastroalg::None );

  std::cout << std::endl << std::endl;
}

void LOCalc :: PrintOccultationEvent( const double TimeStep, const int AsteroidID, const std::string & AsteroidName,
                                      const double Diameter, const double EphemerisUncertainty,
                                      const unsigned char Catalogue, const int StarNumber, const short Mv,
                                      const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                                      double ET_UT, const double BeginOccTime, const double EndOccTime,
                                      const int EarthFlag, const double MaxDuration,
                                      const double StarRA, const double StarDec,
                                      const double MoonPhase, const double SunDist, const double MoonDist,
                                      const double Brightness, const double BrightDelta, const double Uncertainty ) const
{
  apsmathlib::APSCheb * pAPSCheb;
  APSVec3d              r_equ;
  APSVec3d              rAst;
  APSVec3d              eStar;
  APSVec3d              r_G;
  APSVec3d              r;
  APSVec3d              r_prev;
  APSVec3d              r0_prev;
  double                Mjdate;
  double                ETMjdate;
  double                Lambda;
  double                Phi;
  double                Lambda_prev = 0;
  double                Phi_prev = 0;
  double                s;
  double                eStarDist;
  double                s0;
  double                Delta;
  double                r0;
  double                Duration;
  int                   PrevFlag;
  bool                  valid;

  std::cout << "------------------------ Start event -------------------------------" << std::endl;

  PrintHeader( AsteroidID, AsteroidName, Diameter, EphemerisUncertainty,
               Catalogue, StarNumber, Mv, BeginOccTime, EndOccTime, EarthFlag, MaxDuration,
               StarRA, StarDec, MoonPhase, SunDist, MoonDist, Brightness, BrightDelta, Uncertainty );

  pAPSCheb = new apsmathlib::APSCheb( pModule->GetChebSubModulePtr(), ChebOrder, cX, cY, cZ, BeginOccTime, EndOccTime );

  Mjdate = ( BeginOccTime + EndOccTime ) / 2.0;

  apsastroalg::ETminUT( ( Mjdate - apsastroalg::MJD_J2000 ) / 36525.0, ET_UT, valid );

  if( !valid ) {
    ET_UT = pModule->GetET_UT();
  }

  ETMjdate = Mjdate + ET_UT / 86400.0;

  eStar = APSVec3d( apsmathlib::Polar( StarRA, StarDec ) );
  eStar = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], eStar[ apsmathlib::z ] / fac );

  eStarDist = Norm( eStar );

  eStar = eStar / eStarDist;

  /*int TmpInt; Use only for 1 minute step, else - overflow int
  TmpInt = (int)(BeginOccTime / TimeStep ); 
  TmpInt++;
  Mjdate = (double)TmpInt * TimeStep;*/

  Mjdate = BeginOccTime;

  PrevFlag = 0;
  Duration = 0.0;

  double T = ( Mjdate - apsastroalg::MJD_J2000 ) / 36525.0;

  APSMat3d PrecMat = apsastroalg::NutMatrix( T ) * apsastroalg::PrecMatrix_Equ( apsastroalg::T_J2000, T );

  if( pModule->GetOutputType() == 0 ) {
    std::cout << "     Date/Time          Long                    Lat               Star alt Sun alt   Durat" << std::endl;
  }
  else {
    if( pModule->GetOutputType() == 2 ) {
      std::cout << "LinOccult Shadow Path" << std::endl;
    }
  }

  while( Mjdate <= EndOccTime ) {
    if( pAPSCheb->Value( Mjdate, r_equ ) ) {
      std::cout << "ERROR: PrintOccultationEvent - pAPSCheb->Value1" << std::endl;
      std::cout << "Mjdate = " << std::fixed << Mjdate << " BeginOccTime = " << std::fixed << BeginOccTime << std::endl;
      break;
    }

    rAst = GetAU() * APSVec3d( r_equ[ apsmathlib::x ], r_equ[ apsmathlib::y ], r_equ[ apsmathlib::z ] / fac );

    s0 = -Dot( rAst, eStar );

    Delta = s0 * s0 + apsastroalg::R_Earth * apsastroalg::R_Earth - Dot( rAst, rAst );
    r0 = sqrt( apsastroalg::R_Earth * apsastroalg::R_Earth - Delta );

    if( r0 < apsastroalg::R_Earth ) {
      s = s0 + sqrt( Delta ); //s = s0 - sqrt( Delta );
      r = rAst + s * eStar;

      r = APSVec3d( r[ apsmathlib::x ], r[ apsmathlib::y ], fac * r[ apsmathlib::z ] );

//----- Precessing and nutation -------

      r = PrecMat * r;

//-------------------------------------

      r_G    = apsmathlib::R_z( apsastroalg::GMST( Mjdate ) ) * r;                    // Greenwich coordinates
      Lambda = apsmathlib::Modulo( r_G[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;      // East longitude
      Phi    = r_G[ apsmathlib::theta ];                                 // Geocentric latitude
      Phi    = Phi + 0.1924 * apsmathlib::Rad * sin( 2 * Phi );          // Geographic latitude

      double   StarElev;
      double   SunElev;
      APSVec3d R_Obs = apsastroalg::Site( Lambda, Phi );
      APSVec3d R_Sun = ephem->SunEquPos( ETMjdate );

      R_Obs = apsmathlib::R_z( -apsastroalg::GMST( Mjdate ) ) * R_Obs;

      R_Obs = R_Obs / Norm( R_Obs ); 
      
      StarElev = asin( Dot( R_Obs , eStar ) );

      R_Sun = R_Sun / Norm( R_Sun );

      SunElev = asin( Dot( R_Obs, R_Sun ) );

      if( PrevFlag ) {
        Duration = CalcDuration( eStar, Diameter, r, r_prev, TimeStep );
      }
      else {
        Duration = 0.0;
      }

      int    D1;
      int    M1;
      double S1;
      int    D2;
      int    M2;
      double S2;

      apsmathlib::DMS( apsmathlib::Deg * Lambda, D1, M1, S1 );
      apsmathlib::DMS( apsmathlib::Deg * Phi, D2, M2, S2 );

      if( pModule->GetOutputType() == 0 ) {
        if( apsmathlib::Deg * SunElev <= pModule->GetSunElev() ) {
          std::cout << apsastroalg::DateTime( Mjdate, apsastroalg::HHMMSS );
          std::cout << " " << std::setfill( ' ' ) << std::fixed << std::setprecision(3) << std::setw(8) << apsmathlib::Deg * Lambda <<
                       "(" << std::setw(4) << D1 << "o" <<
                       std::setw(2) << std::setfill( '0' ) << M1 << "'" <<
                       std::fixed << std::setprecision(1) << std::setw(4) << std::setfill( '0' ) << S1 << "\") " <<
                       std::setfill( ' ' ) << std::fixed << std::setprecision(3) << std::setw(7) << apsmathlib::Deg * Phi << "(" <<
                       std::setw(4) << D2 << "o" <<
                       std::setw(2) << std::setfill( '0' ) << M2 << "'" <<
                       std::fixed << std::setprecision(1) << std::setw(4) << std::setfill( '0' ) << S2 << "\") " <<
                       std::setfill( ' ' ) << std::fixed << std::setprecision(1) << std::setw(7) << apsmathlib::Deg * StarElev << " " <<
                       std::setfill( ' ' ) << std::fixed << std::setprecision(1) << std::setw(7) << apsmathlib::Deg * SunElev << "    " <<
                       std::setfill( ' ' ) << std::fixed << std::setprecision(1) << std::setw(4) << Duration << std::endl; 
         }
      }
      else {
        if( pModule->GetOutputType() == 2 ) {
          double Lambda1 = std::numeric_limits<double>::max();
          double Phi1    = std::numeric_limits<double>::max();
          double Lambda2 = std::numeric_limits<double>::max();
          double Phi2    = std::numeric_limits<double>::max();
          double Lambda3 = std::numeric_limits<double>::max();
          double Phi3    = std::numeric_limits<double>::max();
          double Lambda4 = std::numeric_limits<double>::max();
          double Phi4    = std::numeric_limits<double>::max();

          APSVec3d r0_now = rAst + s0 * eStar;

          if( PrevFlag ) {
            CalcStrip( Mjdate - TimeStep, r0_prev, r0_now, eStar, Diameter / 2.0,
                       Lambda1, Phi1, Lambda2, Phi2 );

            CalcStrip( Mjdate - TimeStep, r0_prev, r0_now, eStar,
                       Uncertainty + Diameter / 2.0,
                       Lambda3, Phi3, Lambda4, Phi4 );

            if( ( Phi1 != std::numeric_limits<double>::max() ) && ( Lambda1 != std::numeric_limits<double>::max() ) &&
                ( Phi2 != std::numeric_limits<double>::max() ) && ( Lambda2 != std::numeric_limits<double>::max() ) &&
                ( Phi3 != std::numeric_limits<double>::max() ) && ( Lambda3 != std::numeric_limits<double>::max() ) &&
                ( Phi4 != std::numeric_limits<double>::max() ) && ( Lambda4 != std::numeric_limits<double>::max() ) ) {
              std::cout << apsastroalg::DateTime( Mjdate - TimeStep, apsastroalg::HHMMSS );
              std::cout << " ";
              std::cout << std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi3 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda3 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi1 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda1 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi_prev << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda_prev << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi2 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda2 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Phi4 << "," <<
                           std::fixed << std::setprecision(5) << std::setw(8) << apsmathlib::Deg * Lambda4 << "," <<
	                   std::fixed << std::setprecision(1) << Duration << std::endl;
	    }
          }

          r0_prev = r0_now;
        }
      }

      PrevFlag    = 1;
      r_prev      = r;
      Lambda_prev = Lambda;
      Phi_prev    = Phi;
    }
    else {
      PrevFlag = 0;
    }

    Mjdate = Mjdate + TimeStep;
  }

  std::cout << "--------------------------- End event ---------------------------------" << std::endl;

  delete pAPSCheb;
}

double LOCalc :: CalculateDistance( const double ObserverLongitude, const double ObserverLatitude,
                                    const double Lambda, const double Phi ) const
{
  double Distance;

  Distance = apsastroalg::R_Earth * acos( sin( ObserverLatitude ) * sin( Phi ) +
                                          cos( ObserverLatitude ) * cos( Phi ) * cos( ObserverLongitude - Lambda ) );

  return( Distance );
}

double LOCalc :: f( const double x ) const
{
  double t;

  t = x * x / 2;

  if( x < 20.0 ) { /* for underflow */
    return( exp( -t ) / sqrt( 2.0 * apsmathlib::pi ) );
  }

  return( 0.0 );
}

double LOCalc :: IntGauss( double u ) const
{
  const double b1 = 0.319381530;
  const double b2 = -0.356563782;
  const double b3 = 1.781477937;
  const double b4 = -1.821255978;
  const double b5 = 1.330274429;

  double t, Int;
  int    Negatif;

  Negatif = u < 0;

  if( Negatif ) {
    u = -u;
  }

  t = 1.0 / ( 1.0 + 0.2316419 * u );

  Int = 1 - f( u ) * ( b1 + ( b2 + ( b3 + ( b4 + b5 * t ) * t ) * t ) * t ) * t;

  if( Negatif ) {
    return( 1.0 - Int );
  }

  return( Int );
}

double LOCalc :: CalculateProbability( const double Distance, const double Diameter, const double Uncertainty ) const
{
  double x1;
  double x2;
  double g1;
  double g2;

  if( Uncertainty ) {
    x1 = ( Distance + Diameter / 2.0 ) / Uncertainty;
    x2 = ( Distance - Diameter / 2.0 ) / Uncertainty;
    g1 = 100.0 * IntGauss( x1 );
    g2 = 100.0 * IntGauss( x2 );
    return( fabs( g1 - g2 ) );
  }

  return( 0.0 );
}

double LOCalc :: CalculateAzimuty( const double ObserverLongitude, const double ObserverLatitude,
                                   const double MaxLongitude, const double MaxLatitude ) const
{
  double Az;

  if( ObserverLatitude && ( ObserverLongitude - MaxLongitude ) ) {
    Az = apsmathlib::pi / 2.0 - atan( ( ObserverLatitude - MaxLatitude ) / ( cos( ObserverLatitude ) * ( ObserverLongitude - MaxLongitude ) ) );
  }
  else {
    Az = 0;
  }

  if( MaxLongitude < ObserverLongitude ) {
    Az = apsmathlib::pi + Az;
  }

  return( Az );
}

void LOCalc :: IfDistanceCheb( const double TimeStep, const double ObserverLongitude, const double ObserverLatitude,
                               double & MaxDistance, double & MaxMjdate, double & StarElev, double & SunElev, double & MoonElev,
                               double & MaxLongitude, double & MaxLatitude,
                               const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                               const double ET_UT, const double BeginOccTime, const double EndOccTime,
                               const int EarthFlag, const double StarRA, const double StarDec ) const
{
  apsmathlib::APSCheb * pAPSCheb;
  APSVec3d              r_equ;
  APSVec3d              rAst;
  APSVec3d              eStar;
  APSVec3d              r_G;
  APSVec3d              r;
  double                Mjdate;
  double                ETMjdate;
  double                Lambda;
  double                Phi;
  double                s;
  double                eStarDist;
  double                s0;
  double                Delta;
  double                r0;
  double                Distance;

  MaxDistance = std::numeric_limits<double>::max();

  pAPSCheb = new apsmathlib::APSCheb( pModule->GetChebSubModulePtr(), ChebOrder, cX, cY, cZ, BeginOccTime, EndOccTime );

  eStar = APSVec3d( apsmathlib::Polar( StarRA, StarDec ) );
  eStar = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], eStar[ apsmathlib::z ] / fac );

  eStarDist = Norm( eStar );

  eStar = eStar / eStarDist;

  Mjdate = BeginOccTime;

  double T = ( Mjdate - apsastroalg::MJD_J2000 ) / 36525.0;

  APSMat3d PrecMat = apsastroalg::NutMatrix( T ) * apsastroalg::PrecMatrix_Equ( apsastroalg::T_J2000, T );

  while( Mjdate <= EndOccTime ) {
    if( pAPSCheb->Value( Mjdate, r_equ ) ) {
      std::cout << "ERROR: IfDistance - pAPSCheb->Value1" << std::endl;
      break;
    }

    rAst = GetAU() * APSVec3d( r_equ[ apsmathlib::x ], r_equ[ apsmathlib::y ], r_equ[ apsmathlib::z ] / fac );

    s0 = -Dot( rAst, eStar );

    Delta = s0 * s0 + apsastroalg::R_Earth * apsastroalg::R_Earth - Dot( rAst, rAst );
    r0 = sqrt( apsastroalg::R_Earth * apsastroalg::R_Earth - Delta );

    if( r0 < apsastroalg::R_Earth ) {
      s = s0 + sqrt( Delta ); //s = s0 - sqrt( Delta );
      r = rAst + s * eStar;

      r = APSVec3d( r[ apsmathlib::x ], r[ apsmathlib::y ], fac * r[ apsmathlib::z ] );

//----- Precessing and nutation -------

      r = PrecMat * r;

//-------------------------------------

      r_G    = apsmathlib::R_z( apsastroalg::GMST( Mjdate ) ) * r;                    // Greenwich coordinates
      Lambda = apsmathlib::Modulo( r_G[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;      // East longitude
      Phi    = r_G[ apsmathlib::theta ];                                 // Geocentric latitude
      Phi    = Phi + 0.1924 * apsmathlib::Rad * sin( 2 * Phi );          // Geographic latitude

      Distance = CalculateDistance( ObserverLongitude, ObserverLatitude, Lambda, Phi );

      if( Distance < MaxDistance ) {
        MaxDistance  = Distance;
        MaxMjdate    = Mjdate;
        MaxLongitude = Lambda;
        MaxLatitude  = Phi;
      }
    }

    Mjdate = Mjdate + TimeStep;
  }

  if( MaxDistance != std::numeric_limits<double>::max() ) {
    ETMjdate = MaxMjdate + ET_UT / 86400.0;

    APSVec3d R_Sun   = ephem->SunEquPos( ETMjdate );
    APSVec3d R_Moon =  ephem->MoonEquPos( ETMjdate ); // In AU !!!
    APSVec3d R_Obs   = apsastroalg::Site( ObserverLongitude, ObserverLatitude );

    R_Obs = apsmathlib::R_z( -apsastroalg::GMST( MaxMjdate ) ) * R_Obs;

    R_Obs = R_Obs / Norm( R_Obs );

    StarElev = asin( Dot( R_Obs , eStar ) );

    R_Sun = R_Sun / Norm( R_Sun );

    SunElev = asin( Dot( R_Obs, R_Sun ) );

    R_Moon = R_Moon / Norm( R_Moon );

    MoonElev = asin( Dot( R_Obs, R_Moon ) );
  }

  delete pAPSCheb;
}

void LOCalc :: IfDistance( const double TimeStep, const double ObserverLongitude, const double ObserverLatitude,
                           double & MaxDistance, double & MaxMjdate, double & StarElev, double & SunElev, double & MoonElev,
                           double & MaxLongitude, double & MaxLatitude,
                           const double ObservationEpoch, const double M, const double W, const double O,
                           const double I, const double E, const double A,
                           const double ET_UT, const double BeginOccTime, const double EndOccTime,
                           const int EarthFlag, const double StarRA, const double StarDec ) const
{
  LOAstOrbCalc * pLOAstOrbCalc;
  APSVec3d       r_equ;
  APSVec3d       rAst;
  APSVec3d       eStar;
  APSVec3d       r_G;
  APSVec3d       r;
  double         Mjdate;
  double         ETMjdate;
  double         Lambda;
  double         Phi;
  double         s;
  double         eStarDist;
  double         s0;
  double         Delta;
  double         r0;
  double         Distance;

  MaxDistance = std::numeric_limits<double>::max();

  pLOAstOrbCalc = new LOAstOrbCalc( pModule->GetAstOrbSubModulePtr(), apsastroalg::APS_INTEGRATION_DE,
                                    ephem, ObservationEpoch,
                                    M, W, O, I, E, A, ET_UT, 0.0, 0.0 );

  eStar = APSVec3d( apsmathlib::Polar( StarRA, StarDec ) );
  eStar = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], eStar[ apsmathlib::z ] / fac );

  eStarDist = Norm( eStar );

  eStar = eStar / eStarDist;

  Mjdate = BeginOccTime;

  double T = ( Mjdate - apsastroalg::MJD_J2000 ) / 36525.0;

  APSMat3d PrecMat = apsastroalg::NutMatrix( T ) * apsastroalg::PrecMatrix_Equ( apsastroalg::T_J2000, T );

  while( Mjdate <= EndOccTime ) {
    if( pLOAstOrbCalc->ProcessAsteroid( Mjdate, r_equ ) ) {
      std::cout << "ERROR: IfDistance ProcessAsteroid" << std::endl;
      break;
    }

    rAst = GetAU() * APSVec3d( r_equ[ apsmathlib::x ], r_equ[ apsmathlib::y ], r_equ[ apsmathlib::z ] / fac );

    s0 = -Dot( rAst, eStar );

    Delta = s0 * s0 + apsastroalg::R_Earth * apsastroalg::R_Earth - Dot( rAst, rAst );
    r0 = sqrt( apsastroalg::R_Earth * apsastroalg::R_Earth - Delta );

    if( r0 < apsastroalg::R_Earth ) {
      s = s0 + sqrt( Delta ); //s = s0 - sqrt( Delta );
      r = rAst + s * eStar;

      r = APSVec3d( r[ apsmathlib::x ], r[ apsmathlib::y ], fac * r[ apsmathlib::z ] );

//----- Precessing and nutation -------

      r = PrecMat * r;

//-------------------------------------

      r_G    = apsmathlib::R_z( apsastroalg::GMST( Mjdate ) ) * r;                    // Greenwich coordinates
      Lambda = apsmathlib::Modulo( r_G[ apsmathlib::phi ] + apsmathlib::pi , 2 * apsmathlib::pi ) - apsmathlib::pi;      // East longitude
      Phi    = r_G[ apsmathlib::theta ];                                 // Geocentric latitude
      Phi    = Phi + 0.1924 * apsmathlib::Rad * sin( 2 * Phi );          // Geographic latitude

      Distance = CalculateDistance( ObserverLongitude, ObserverLatitude, Lambda, Phi );

      if( Distance < MaxDistance ) {
        MaxDistance  = Distance;
        MaxMjdate    = Mjdate;
        MaxLongitude = Lambda;
        MaxLatitude  = Phi;
      }
    }

    Mjdate = Mjdate + TimeStep;
  }

  if( MaxDistance != std::numeric_limits<double>::max() ) {
    ETMjdate = MaxMjdate + ET_UT / 86400.0;

    APSVec3d R_Sun  = ephem->SunEquPos( ETMjdate );
    APSVec3d R_Moon = ephem->MoonEquPos( ETMjdate ); // In AU !!!
    APSVec3d R_Obs  = apsastroalg::Site( MaxLongitude, MaxLatitude );

    R_Obs = apsmathlib::R_z( -apsastroalg::GMST( MaxMjdate ) ) * R_Obs;

    R_Obs = R_Obs / Norm( R_Obs );

    StarElev = asin( Dot( R_Obs , eStar ) );

    R_Sun = R_Sun / Norm( R_Sun );

    SunElev = asin( Dot( R_Obs, R_Sun ) );

    R_Moon = R_Moon / Norm( R_Moon );

    MoonElev = asin( Dot( R_Obs, R_Moon ) );
  }

  delete pLOAstOrbCalc;
}

void LOCalc :: SaveOccEvent( const int AsteroidID, const std::string & AsteroidName,
                             const double Diameter, const double EphemerisUncertainty,
                             const int StarNumber, const short Mv,
                             const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                             const double ET_UT, const double BeginOccTime, const double EndOccTime,
                             const int EarthFlag, const double MaxDuration,
                             const double StarRA, const double StarDec,
                             const double MoonPhase, const double SunDist, const double MoonDist,
                             const double Brightness, const double BrightDelta, const double Uncertainty ) const
{
  std::string NewAsteroidName;
  int    Year1;
  int    Month1;
  int    Day1;
  int    Hour1;
  int    Min1;
  double Sec1;
  int    Year2;
  int    Month2;
  int    Day2;
  int    Hour2;
  int    Min2;
  double Sec2;

#ifdef WITH_MYSQL
  mysql_count++;
#endif

  apsastroalg::CalDat( BeginOccTime, Year1, Month1, Day1, Hour1, Min1, Sec1 );
  apsastroalg::CalDat( EndOccTime, Year2, Month2, Day2, Hour2, Min2, Sec2 );

  unsigned int i = 0;

  while( i < AsteroidName.length() ) {
    if( AsteroidName[ i ] == static_cast<char>( 0x27 ) ) { /* ' */
      NewAsteroidName += static_cast<char>( 0x5c ); /* \ */
    }

    NewAsteroidName += AsteroidName[ i ];

    i++;
  }

#ifdef WITH_MYSQL
  std::ostringstream MySQL_Msg;

  MySQL_Msg << std::fixed << std::setprecision(6) <<
                       "INSERT INTO occult.Events VALUES(" <<
                       mysql_count << "," <<
                       AsteroidID << "," <<
                       "'" << NewAsteroidName << "'," <<
                       Diameter << "," <<
                       EphemerisUncertainty << "," <<
                       StarNumber << "," <<
                       Mv / 100.0 << "," <<
                       "'" << Year1 << "-" <<
                       Month1 << "-" <<
                       Day1 << " " <<
                       Hour1 << ":" <<
                       Min1 << ":" <<
                       static_cast<int>( Sec1 ) << "','" <<
                       Year2 << "-" <<
                       Month2 << "-" <<
                       Day2 << " " <<
                       Hour2 << ":" <<
                       Min2 << ":" <<
                       static_cast<int>( Sec2 )  << "'," <<
                       EarthFlag << "," <<
                       MaxDuration << "," <<
                       apsmathlib::Deg * StarRA / 15.0 << "," <<
                       apsmathlib::Deg * StarDec << "," <<
                       MoonPhase << "," <<
                       apsmathlib::Deg * SunDist << "," <<
                       apsmathlib::Deg * MoonDist << "," <<
                       Brightness << "," <<
                       BrightDelta << "," <<
                       Uncertainty  << ");" << std::endl;

  if( pModule->GetIfMySQL() ) {
    if( mysql_query( &mysql, MySQL_Msg.str().c_str() ) ) {
      std::cout << "Could not insert row " << MySQL_Msg.str() << " " <<
                    mysql_errno( &mysql ) << ": " <<
                    mysql_error( &mysql ) << std::endl;
      //mysql_close( &mysql );
      //exit( 1 );
    }
  }
#endif
}

int LOCalc :: SaveOccultationEvent( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar,
                                    LOEventData * pLOEventData,
                                    const double BeginOccTime, const double EndOccTime,
                                    const int EarthFlag, const double MaxDuration, const double ET_UT ) const
{
  LOAstOrbChebMaker * pLOAstOrbChebMaker;
  double              cX[ SAVE_CHEB_ORDER + 1 ];
  double              cY[ SAVE_CHEB_ORDER + 1 ];
  double              cZ[ SAVE_CHEB_ORDER + 1 ];
  double              StarRA;
  double              StarDec;
  double              MoonPhase;
  double              SunDist;
  double              MoonDist;
  double              Brightness;
  double              BrightDelta;
  double              Uncertainty;
  double              AngleUncertainty;
  int                 RetCode = 0;

  pLOAstOrbChebMaker = new LOAstOrbChebMaker( pModule->GetChebMakerSubModulePtr(), 
                                              ephem, pLOAsteroid->GetObservationEpoch(),
                                              pLOAsteroid->GetM(), pLOAsteroid->GetW(), pLOAsteroid->GetO(),
                                              pLOAsteroid->GetI(), pLOAsteroid->GetE(), pLOAsteroid->GetA(),
                                              ET_UT, 0.0, 0.0);

  pLOAstOrbChebMaker->Create( SAVE_CHEB_ORDER, BeginOccTime, EndOccTime, cX, cY, cZ );

  delete pLOAstOrbChebMaker;

  if( !CalculateParameters( pLOAsteroid, pLOStar, SAVE_CHEB_ORDER, cX, cY, cZ,
                            ET_UT, BeginOccTime, EndOccTime,
                            StarRA, StarDec, MoonPhase, SunDist, MoonDist,
                            Brightness, BrightDelta, Uncertainty, AngleUncertainty ) ) {

    PrintOccultationEvent( 1.0 / pModule->GetScanStep(), pLOAsteroid->GetAsteroidID(), pLOAsteroid->GetAsteroidNamePtr(),
                           pLOAsteroid->GetDiameter(), AngleUncertainty,
                           pLOStar->GetCatalogue(), pLOStar->GetStarNumber(), pLOStar->GetMv(),
                           SAVE_CHEB_ORDER, cX, cY, cZ,
                           ET_UT, BeginOccTime, EndOccTime, EarthFlag, MaxDuration,
                           StarRA, StarDec, MoonPhase, SunDist, MoonDist,
                           Brightness, BrightDelta, Uncertainty );

    SaveOccEvent( pLOAsteroid->GetAsteroidID(), pLOAsteroid->GetAsteroidNamePtr(),
                  pLOAsteroid->GetDiameter(), AngleUncertainty,
                  pLOStar->GetStarNumber(), pLOStar->GetMv(),
                  SAVE_CHEB_ORDER, cX, cY, cZ,
                  ET_UT, BeginOccTime, EndOccTime, EarthFlag, MaxDuration,
                  StarRA, StarDec, MoonPhase, SunDist, MoonDist,
                  Brightness, BrightDelta, Uncertainty );

    pLOEventData->CreateEvent( pLOAsteroid->GetAsteroidID(), pLOAsteroid->GetAsteroidNamePtr(),
                               pLOAsteroid->GetDiameter(), AngleUncertainty,
                               pLOAsteroid->GetObservationEpoch(), pLOAsteroid->GetM(), pLOAsteroid->GetW(),
                               pLOAsteroid->GetO(), pLOAsteroid->GetI(), pLOAsteroid->GetE(), pLOAsteroid->GetA(),
                               pLOStar->GetCatalogue(), pLOStar->GetStarNumber(), pLOStar->GetMv(),
                               SAVE_CHEB_ORDER, cX, cY, cZ, ET_UT,
                               BeginOccTime, EndOccTime, EarthFlag, MaxDuration,
                               StarRA, StarDec, MoonPhase, SunDist, MoonDist,
                               Brightness, BrightDelta, Uncertainty );
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

double LOCalc ::  CalcDuration( const APSVec3d & eStar, const double Diameter, const APSVec3d & r,
                                const APSVec3d & r_prev, const double SmallStep ) const
{
  APSVec3d  dr;
  double    drp;
  double    Duration;

  dr = APSVec3d( r_prev[ apsmathlib::x ] - r[ apsmathlib::x ] + apsmathlib::pi2 * 1.002738 * r[ apsmathlib::y ] * SmallStep,
                 r_prev[ apsmathlib::y ] - r[ apsmathlib::y ] - apsmathlib::pi2 * 1.002738 * r[ apsmathlib::x ] * SmallStep,
                 r_prev[ apsmathlib::z ] - r[ apsmathlib::z ] );

  drp = Norm( dr - Dot( dr, eStar ) * eStar );

  if( drp ) {
    Duration = 24.0 * 3600.0 * Diameter * SmallStep / drp;
  }
  else {
    std::cout << "WARNING: drp = 0" << std::endl;
    Duration = 0.0;
  }

  return( Duration );
}

int LOCalc :: CreateOccultationEvent( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar,
                                      LOEventData * pLOEventData,
                                      const APSVec3d & eStar, double * StartMjdate, int * StartStep,
                                      const double ET_UT, const double Step, const double MaxDist ) const
{
  LOAstOrbCalc * pLOAstOrbCalc;
  int            SmallCurrentStep;
  double         SmallStep;
  double         Mjdate;
  //double         ETMjdate;
  double         LimitDate;
  APSVec3d       r_equ;
  APSVec3d       rAst;
  APSVec3d       r;
  APSVec3d       r_prev;
  double         s0;
  double         s;
  double         Delta;
  double         r0;
  double         BeginOccTime = 0.0;
  int            BeginOccFlag;
  double         EndOccTime = 0.0;
  double         MaxDuration;
  double         Duration;
  int            EarthFlag;
  int            PrevFlag;
  int            RetCode = 0;

  SmallStep = Step / SMALL_STEP;

  Mjdate = *StartMjdate;

  //ETMjdate = Mjdate + ET_UT / 86400.0;

  pLOAstOrbCalc = new LOAstOrbCalc( pModule->GetAstOrbSubModulePtr(), apsastroalg::APS_INTEGRATION_DE,
                                    ephem, pLOAsteroid->GetObservationEpoch(),
                                    pLOAsteroid->GetM(), pLOAsteroid->GetW(), pLOAsteroid->GetO(),
                                    pLOAsteroid->GetI(), pLOAsteroid->GetE(), pLOAsteroid->GetA(),
                                    ET_UT, 0.0, 0.0 );

  EarthFlag        = 0;
  PrevFlag         = 0;
  BeginOccFlag     = 0;
  SmallCurrentStep = 0;
  LimitDate        = Mjdate + 2 * Step;
  MaxDuration      = 0.0;

  // If occultation starts on previous day, do something.

  do {
    if( pLOAstOrbCalc->ProcessAsteroid( Mjdate, r_equ ) ) {
      std::cout << "ERROR: CreateOccultationEvent ProcessAsteroid" << std::endl;
      RetCode = 1;
      break;
    }

    rAst = GetAU() * APSVec3d( r_equ[ apsmathlib::x ], r_equ[ apsmathlib::y ], r_equ[ apsmathlib::z ] / fac );

    s0 = -Dot( rAst, eStar );

    r0 = sqrt( Dot( rAst, rAst ) - s0 * s0 );

    if( r0 < MaxDist ) {
      if( r0 < apsastroalg::R_Earth ) {
        EarthFlag = 1;

        Delta = s0 * s0 + apsastroalg::R_Earth * apsastroalg::R_Earth - Dot( rAst, rAst );
        s = s0 + sqrt( Delta );
        r = rAst + s * eStar;

        r = APSVec3d( r[ apsmathlib::x ], r[ apsmathlib::y ], fac * r[ apsmathlib::z ] );

        if( PrevFlag ) {
          Duration = CalcDuration( eStar, pLOAsteroid->GetDiameter(), r, r_prev, SmallStep );

          if( Duration > MaxDuration ) {
            MaxDuration = Duration;
          }
        }

        PrevFlag = 1;
        r_prev = r;
      }
      else {
        PrevFlag = 0;
      }

      if( !BeginOccFlag ) {
        BeginOccTime = Mjdate;
        BeginOccFlag = 1;
      }
    }
    else {
      if( BeginOccFlag ) {
        EndOccTime = Mjdate - SmallStep;
        break;
      }
    }

    Mjdate = Mjdate + SmallStep;

    //ETMjdate = Mjdate + ET_UT / 86400.0;

    SmallCurrentStep++;

    if( !BeginOccFlag ) {
      if( Mjdate > LimitDate ) {
        std::cout << "ERROR: Mjdate > LimitDate" << std::endl;
        std::cout << "Mjdate = " << Mjdate << " LimitDate = " << LimitDate << std::endl;
        RetCode = 2;
        break;
      }
    }
  } while( 1 );

  if( !RetCode ) {
    if( BeginOccTime < EndOccTime ) {
      RetCode = SaveOccultationEvent( pLOAsteroid, pLOStar, pLOEventData, BeginOccTime, EndOccTime, EarthFlag, MaxDuration, ET_UT );

      //cout << DateTime( BeginOccTime, HHMMSS ) << endl;
      //cout << DateTime( EndOccTime, HHMMSS ) << endl;

      if( RetCode ) {
        std::cout << "ERROR: SaveOccultationEvent" << std::endl;
      }
    }
    else {
      std::cout << "WARNING: BeginOccTime >= EndOccTime" << std::endl;
      std::cout << "BeginOccTime = " << std::fixed << BeginOccTime << " EndOccTime = " << std::fixed << EndOccTime << std::endl;
      RetCode = 3;
    }
  }

  SmallCurrentStep = SmallCurrentStep / SMALL_STEP + 1;

  *StartMjdate = *StartMjdate + Step * SmallCurrentStep;

  *StartStep = *StartStep + SmallCurrentStep;

  delete pLOAstOrbCalc;

  return( RetCode );
}

int LOCalc :: ProcessStar1( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar, LOEventData * pLOEventData,
                            const double BeginMjdate, const double EndMjdate, const double ET_UT,
                            const double Step, const int ScanStep )
{
  APSVec3d        eStar;
  APSVec3d        rAst;
  APSVec3d        rAstAU;
  int             CurrentStep;
  double          s0;
  double          eStarDist;
  double          Delta;
  double          r0;
  double          DT;
  double          Mjdate;
  double          ETMjdate;
  double          MaxDist;
  double          ExtraRadius;
  double          AngleUncertainty;
  double          TotalUncertainty;
  const LOEvent * pLOEvent;
  float           Parallax;
  double          ParallaxDelta;
  double          ParallaxAlpha;
  double          ra;
  double          de;
  double          plx;
  double          uRAs;
  double          uDE;
  double          VR;
  int             RetCode = 0;

  Mjdate = BeginMjdate;

  ETMjdate = Mjdate + ET_UT / 86400.0;

  CurrentStep = 0;

  ExtraRadius = pModule->GetExtraRadius() * apsastroalg::R_Earth; // ExtraRadius must be 3.0 by default

  ParallaxDelta = 0.0;
  ParallaxAlpha = 0.0;

  Parallax = pLOStar->GetParallax();

  // DT will be approximately the same during one day
  DT = ( ETMjdate - pLOStar->GetEpoch() ) / 365.25;

  if( !TransformEpoch( DT, pLOStar->GetRA(), pLOStar->GetDec(),
			   apsmathlib::Deg * Parallax * 1000.0 * 3600.0,
			   apsmathlib::Deg * pLOStar->GetpmRA() * 1000.0 * 3600.0,
			   apsmathlib::Deg * pLOStar->GetpmDec() * 1000.0 * 3600.0,
		           pLOStar->GetVrad(),
			   ra, de, plx, uRAs, uDE, VR ) ) {
    std::ostringstream Msg;
    Msg << "ProcessStar1" << std::endl;
    pModule->InfoMessage( LO_CALC_TRANSFORM_EPOCH, Msg.str() );
    std::cout << "Error returned by TransformEpoch" << std::endl;
    return( 1 );
  }

  if( Parallax ) {
    CalcParallax( pLOStar, ETMjdate, apsmathlib::Rad * apsmathlib::Ddd( 0, 0, plx / 1000.0 ), ParallaxDelta, ParallaxAlpha );
  }
  
  //std::cout << apsmathlib::APSAngle( ( ra + apsmathlib::Deg * ParallaxAlpha ) / 15, apsmathlib::DMMSSs );
  //std::cout << std::endl;	
  //std::cout << apsmathlib::APSAngle( de + apsmathlib::Deg * ParallaxDelta, apsmathlib::DMMSSs );
  //std::cout << std::endl;  

  double StarRA = apsmathlib::Rad * ra + ParallaxAlpha;
  double StarDec = apsmathlib::Rad * de + ParallaxDelta;
  
  eStar = APSVec3d( apsmathlib::Polar( StarRA, StarDec ) );

  eStar = APSVec3d( eStar[ apsmathlib::x ], eStar[ apsmathlib::y ], eStar[ apsmathlib::z ] / fac );

  eStarDist = Norm( eStar );

  eStar = eStar / eStarDist;

  while( Mjdate < EndMjdate ) {
    if( CurrentStep >= ScanStep ) {
      std::cout << "WARNING: ScanStep = " << std::fixed << CurrentStep << " CurrentStep = " << std::fixed << pModule->GetScanStep() << std::endl;
      break;
    }

    rAstAU = APSVec3d( (*ChebArray[ CurrentStep ])[ apsmathlib::x ], (*ChebArray[ CurrentStep ])[ apsmathlib::y ], (*ChebArray[ CurrentStep ])[ apsmathlib::z ] / fac );

    rAst = GetAU() * rAstAU;

    s0 = -Dot( rAst, eStar );

    Delta = s0 * s0 + apsastroalg::R_Earth * apsastroalg::R_Earth - Dot( rAst, rAst );
    r0 = sqrt( apsastroalg::R_Earth * apsastroalg::R_Earth - Delta );

    // Uncertainty

    TotalUncertainty = CalculateTotalUncertainty( AngleUncertainty, -pLOAsteroid->GetEphemerisUncertainty() * s0,
                                                  Mjdate, pLOStar->GetMv(), -s0 );

    MaxDist = TotalUncertainty + apsastroalg::R_Earth;

    if( MaxDist > ExtraRadius ) {
      MaxDist = ExtraRadius;
    } 

    if( r0 < MaxDist ) {
      pLOEvent = pLOEventData->FindEvent( pLOAsteroid->GetAsteroidID(), pLOStar->GetCatalogue(), pLOStar->GetStarNumber(), Mjdate );

      if( !pLOEvent ) {
        Mjdate = Mjdate - Step;
        CurrentStep--;

        RetCode = CreateOccultationEvent( pLOAsteroid, pLOStar, pLOEventData, eStar, &Mjdate, &CurrentStep, ET_UT, Step, MaxDist );

        if( RetCode ) {
          std::cout << "ERROR: CreateOccultationEvent" << std::endl;
          break;
        }
      }
      else {
        CurrentStep = static_cast<int>(( pLOEvent->GetEndOccTime() - BeginMjdate ) / Step ) + 1;
        Mjdate = BeginMjdate + CurrentStep * Step;

        /*printf("======= occultation event has been found in data base. %d %s\n",
                pLOEvent->GetAsteroidID(), pLOEvent->GetAsteroidNamePtr() );
        cout << DateTime( pLOEvent->GetBeginOccTime(), HHMMSS ) << endl;
        cout << DateTime( pLOEvent->GetEndOccTime(), HHMMSS ) << endl;*/
      }
    }

    Mjdate = Mjdate + Step;

    ETMjdate = Mjdate + ET_UT / 86400.0;

    CurrentStep++;
  }

  return( RetCode );  
}

int LOCalc :: ProcessStarData( const LOAsteroid * pLOAsteroid, const APSVec3d * r_Asteroid,
                               const double ETMjdate, const double Mjdate )
{
  unsigned int   i;
  const LOStar * pLOStar;

  for( i = 0; i < GetStarsCount(); i++ ) {
    pLOStar = GetStar( i );

    ProcessStar( pLOAsteroid, r_Asteroid, ETMjdate, Mjdate, pLOStar, pLOStar->GetStarNumber() );
  }

  return( 0 );
}

int LOCalc :: ProcessAsteroid( const LOAsteroid * pLOAsteroid, const LOStarData * pLOStarData )
{
  LOAstOrbCalc * pLOAstOrbCalc;
  double         Step;
  int            CurrentStep;
  double         CurrentMjdTime;
  APSVec3d       r_equ;
  int            RetCode = 0;

  //std::cout << "---------------- NewProcessAsteroid -------------------" << std::endl;

  std::ostringstream Msg;
  Msg << pLOAsteroid->GetAsteroidID() << " " << pLOAsteroid->GetAsteroidNamePtr() << std::endl;

  pModule->InfoMessage( LO_CALC_START_ASTEROID_PROCESSING, Msg.str() );

  SetEventStar( -1 );

  pLOAstOrbCalc = new LOAstOrbCalc( pModule->GetAstOrbSubModulePtr(), apsastroalg::APS_INTEGRATION_DE,
                                    ephem, pLOAsteroid->GetObservationEpoch(),
                                    pLOAsteroid->GetM(), pLOAsteroid->GetW(), pLOAsteroid->GetO(),
                                    pLOAsteroid->GetI(), pLOAsteroid->GetE(), pLOAsteroid->GetA(),
                                    pModule->GetET_UT(), 0.0, 0.0 );

  Step  = 1.0 / pModule->GetScanStep();

  CurrentStep = 0;

  CurrentMjdTime = MjdStart;

  while( CurrentMjdTime < MjdEnd + Step / 2 ) {
    if( pLOAstOrbCalc->ProcessAsteroid( CurrentMjdTime, r_equ ) ) {
      std::cout << "ERROR: pLOAstOrbCalc->ProcessAsteroid" << std::endl;
      RetCode = 1000;
      break;
    }

    if( !( CurrentStep % pModule->GetScanStep() ) ) {
      //std::cout << apsastroalg::DateTime( CurrentMjdTime, apsastroalg::HHh );
      ScanStars( pLOStarData, &r_equ );
      //std::cout << " Stars number: " << GetStarsCount() << std::endl;
    }

    if( ProcessStarData( pLOAsteroid, &r_equ, pLOAstOrbCalc->GetCurrentETTime(), CurrentMjdTime ) ) {
      pModule->ErrorMessage( LO_CALC_STAR_PROCESSING );    
      RetCode = LO_CALC_STAR_PROCESSING;
      break;
    }

    CurrentStep++;

    CurrentMjdTime += Step;
  } 

  delete pLOAstOrbCalc;

  return( RetCode );
}

int LOCalc :: NewNewNewProcessAsteroid( const LOAsteroid * pLOAsteroid, const LOStarData * pLOStarData,
                                        LOEventData * pLOEventData )
{
  unsigned int          i;
  LOAstOrbChebMaker   * pLOAstOrbChebMaker;
  apsmathlib::APSCheb * pAPSCheb;
  double                Step;
  int                   ScanStep;
  int                   CurrentStep;
  double                TmpMjdTime;
  double                CurrentMjdTime;
  const LOStar        * pLOStar;
  APSVec3d              r_equ;
  double                ET_UT;
  bool                  valid;
  double                cX[ CHEB_ORDER + 1 ];
  double                cY[ CHEB_ORDER + 1 ];
  double                cZ[ CHEB_ORDER + 1 ];
  int                   RetCode = 0;

  ScanStep = pModule->GetScanStep();

  Step  = CHEB_STEP / ScanStep;

  std::ostringstream Msg;
  Msg << pLOAsteroid->GetAsteroidID() << " " << pLOAsteroid->GetAsteroidNamePtr() << std::endl;

  pModule->InfoMessage( LO_CALC_START_ASTEROID_PROCESSING, Msg.str() );

  apsastroalg::ETminUT( ( MjdStart - apsastroalg::MJD_J2000 ) / 36525.0, ET_UT, valid );

  if( !valid ) {
    ET_UT = pModule->GetET_UT();
  }

  pLOAstOrbChebMaker = new LOAstOrbChebMaker( pModule->GetChebMakerSubModulePtr(), 
                                              ephem, pLOAsteroid->GetObservationEpoch(),
                                              pLOAsteroid->GetM(), pLOAsteroid->GetW(), pLOAsteroid->GetO(),
                                              pLOAsteroid->GetI(), pLOAsteroid->GetE(), pLOAsteroid->GetA(),
                                              ET_UT, 0.0, 0.0);

  for( CurrentMjdTime = MjdStart; CurrentMjdTime < MjdEnd; CurrentMjdTime += CHEB_STEP ) {
    pLOAstOrbChebMaker->Create( CHEB_ORDER, CurrentMjdTime, CurrentMjdTime + CHEB_STEP, cX, cY, cZ );

    pAPSCheb = new apsmathlib::APSCheb( pModule->GetChebSubModulePtr(), CHEB_ORDER, cX, cY, cZ, CurrentMjdTime, CurrentMjdTime + CHEB_STEP );

    TmpMjdTime = CurrentMjdTime;

    for( CurrentStep = 0; CurrentStep < ScanStep; CurrentStep++ ) {
      if( pAPSCheb->Value( TmpMjdTime, r_equ ) ) {
        std::cout << "ERROR: pAPSCheb->Value1" << std::endl;
        RetCode = 1000;
        break;
      }

      *ChebArray[ CurrentStep ] = r_equ;

      TmpMjdTime = TmpMjdTime + Step;
    }

    delete pAPSCheb;

    //cout << DateTime( CurrentMjdTime, HHh );
    ScanStars2( pLOStarData, ScanStep );
    //printf(" Stars number: %d\n", GetStarsCount() );

    for( i = 0; i < GetStarsCount(); i++ ) {
      pLOStar = GetStar( i );

      if( ProcessStar1( pLOAsteroid, pLOStar, pLOEventData, CurrentMjdTime, CurrentMjdTime + CHEB_STEP, ET_UT, Step, ScanStep ) ) {
        // We continue to process next star
        // Warning...
        //pModule->ErrorMessage( LO_CALC_STAR_PROCESSING );    
        //RetCode = LO_CALC_STAR_PROCESSING;
        //break;
      }
    }     
  }

  delete pLOAstOrbChebMaker;

  return( RetCode );
}

int LOCalc :: IfAsteroid( const LOAsteroid * pLOAsteroid ) const
{
  if( pLOAsteroid->GetA() >= pModule->GetMinA() ) {
    if( pLOAsteroid->GetA() <= pModule->GetMaxA() ) {
      if( pLOAsteroid->GetDiameter() >= pModule->GetMinDiameter() ) {
        if( pLOAsteroid->GetDiameter() <= pModule->GetMaxDiameter() ) {
          //if( pLOAsteroid->GetE() >= 0.95 ) {
            return( 1 );
          //}
        }
      }
    }
  }

  return( 0 );
}

int LOCalc :: ProcessManyAsteroids( const LOAstOrbData * pLOAstOrbData, const LOStarData * pLOStarData,
                                    LOEventData * pLOEventData )
{
  unsigned int       i;
  int                TotalAsteroids;
  const LOAsteroid * pLOAsteroid;
  int                RetCode = 0;

  TotalAsteroids = 0;

  for( i = 0; i < pLOAstOrbData->GetCurrentNumber(); i++ ) {
    pLOAsteroid = pLOAstOrbData->GetAsteroidPtr( i );

    if( IfAsteroid( pLOAsteroid ) ) {
      TotalAsteroids++;
    }
  }

  std::cout << "TotalAsteroids = " << TotalAsteroids << std::endl;

  for( i = 0; i < pLOAstOrbData->GetCurrentNumber(); i++ ) {
    pLOAsteroid = pLOAstOrbData->GetAsteroidPtr( i );

    if( IfAsteroid( pLOAsteroid ) ) {
      //RetCode = ProcessAsteroid( pLOAsteroid, pLOStarData );
      RetCode = NewNewNewProcessAsteroid( pLOAsteroid, pLOStarData, pLOEventData );

      if( RetCode ) {
        break;
      }
    }
  }

  return( RetCode );
}

int LOCalc :: Run( LOData * pLOData )
{
  const LOAstOrbData * pLOAstOrbData;
  const LOStarData   * pLOStarData;
  LOEventData        * pLOEventData;
  const LOAsteroid   * pLOAsteroid;
  int                  AsteroidNumber;
  int                  RetCode = LO_CALC_NO_ERROR;

  pModule->InfoMessage( LO_CALC_START );

  ephem = new APSJPLEph();

  if( ephem->Init( pModule->GetJPLEphemFilePath() ) != apsastrodata::APS_JPL_NO_ERROR) {
    pModule->ErrorMessage( LO_CALC_JPL_INIT );
    return( LO_CALC_JPL_INIT );
  }

  AU = ephem->GetAU();

  MjdStart = apsastroalg::Mjd( pModule->GetStartYear(), pModule->GetStartMonth(), pModule->GetStartDay() );
  MjdEnd   = apsastroalg::Mjd( pModule->GetEndYear(), pModule->GetEndMonth(), pModule->GetEndDay() ) + 1.0;

  pLOAstOrbData = pLOData->GetAstOrbDataPtr();

  pLOStarData = pLOData->GetStarDataPtr();

  pLOEventData = pLOData->GetEventDataPtr();

  AsteroidNumber = pModule->GetAsteroidNumber();

  if( AsteroidNumber > 0 ) { // Process one asteroid
    pLOAsteroid = pLOAstOrbData->GetAsteroidPtr( 0 );

    RetCode = ProcessAsteroid( pLOAsteroid, pLOStarData );
  }
  else { // Process many asteroids
#ifdef WITH_MYSQL
    if( pModule->GetIfMySQL() ) {
      if( !mysql_init( &mysql ) ) {
        std::cout << "Cannot initialize MySQL" << std::endl;
        exit( 1 );
      }

      if( !mysql_real_connect( &mysql, "localhost", "linoccult",
          "linoccult", "occult", 0, NULL, 0 ) ) {
        std::cout << mysql_errno(&mysql) << ": " << mysql_error(&mysql) << std::endl;
        exit( 1 );
      }

      mysql_count = pModule->GetStartSQLNumber();
    }
#endif

    pModule->InfoMessage( LO_CALC_START_KDTREE );

    if( !pLOData->BuildKDTree() ) {
      pModule->InfoMessage( LO_CALC_FINISH_KDTREE );

      RetCode = ProcessManyAsteroids( pLOAstOrbData, pLOStarData, pLOEventData );

      pLOEventData->Rebuild();
    }
    else {
      pModule->ErrorMessage( LO_CALC_KDTREE_BUILD_ERROR );
      RetCode = LO_CALC_KDTREE_BUILD_ERROR;
    }

#ifdef WITH_MYSQL
    if( pModule->GetIfMySQL() ) {
      mysql_close(&mysql);
    }
#endif
  }

  if( RetCode ) {
    pModule->ErrorMessage( LO_CALC_ASTEROID_ERROR );
    RetCode = LO_CALC_ASTEROID_ERROR;
  }

  pModule->InfoMessage( LO_CALC_FINISH );

  delete ephem;

  ephem = 0;

  return( RetCode );
}

int LOCalc :: ProcessOnePosition( LOPos * pLOPos, LOEventData * pLOEventData, LOPointEventData * pLOPointEventData ) const
{
  unsigned int   i;
  LOEvent      * pLOEvent;
  const LOPointEvent * pLOPointEvent;
  double         Diameter;
  //double         ObservationEpoch;
  //double         M;
  //double         W;
  //double         O;
  //double         I;
  //double         E;
  //double         A;
  short          Mv;
  short          ChebOrder;
  double         BeginOccTime;
  double         EndOccTime;
  int            EarthFlag;
  double         MaxDuration;
  double         ET_UT;
  const double * cX;
  const double * cY;
  const double * cZ;
  double         StarRA;
  double         StarDec;
  double         BrightDelta;
  double         Uncertainty;
  float          ObserverLongitude;
  float          ObserverLatitude;
  double         LimitDistance;
  float          LimitMv;
  double         LimitDuration;
  double         LimitSunElev;
  double         LimitDrop;
  double         LimitProb;
  double         LimitCenterProb;
  double         LimitStarElev;
  double         Distance;
  double         Mjdate;
  double         StarElev;
  double         SunElev;
  double         MoonElev;
  double         MaxLongitude;
  double         MaxLatitude;
  double         Probability;
  double         MaxProbability;
  double         Az;
  double         Tau;
  double         h;
  double         StarAz;
  int            RetCode = 0;

  std::cout << "Start processing position " << pLOPos->GetObsNamePtr() << std::endl;

  std::cout << "Processing " << pLOEventData->GetEventsNumber() << " event records" << std::endl;

  ObserverLongitude = pLOPos->GetObserverLongitude();
  ObserverLatitude  = pLOPos->GetObserverLatitude();
  LimitDistance     = pLOPos->GetMaxDistance();
  LimitMv           = pLOPos->GetMaxMv();
  LimitDuration     = pLOPos->GetMinDuration();
  LimitSunElev      = pLOPos->GetSunElev();
  LimitDrop         = pLOPos->GetMinDrop();
  LimitProb         = pLOPos->GetMinProb();
  LimitCenterProb   = pLOPos->GetMinCenterProb();
  LimitStarElev     = pLOPos->GetMinStarElev();

  for( i = 0; i < pLOEventData->GetEventsNumber(); i++ ) {
    pLOEvent = pLOEventData->GetEventPtr( i );

    Diameter = pLOEvent->GetDiameter();
    //ObservationEpoch = pLOEvent->GetObservationEpoch();
    //M = pLOEvent->GetM();
    //W = pLOEvent->GetW();
    //O = pLOEvent->GetO();
    //I = pLOEvent->GetI();
    //E = pLOEvent->GetE();
    //A = pLOEvent->GetA();
    Mv = pLOEvent->GetMv();
    ChebOrder = pLOEvent->GetChebOrder();
    BeginOccTime = pLOEvent->GetBeginOccTime();
    EndOccTime = pLOEvent->GetEndOccTime();
    EarthFlag = pLOEvent->GetEarthFlag();
    MaxDuration = pLOEvent->GetMaxDuration();
    ET_UT = pLOEvent->GetET_UT();
    cX = pLOEvent->GetcX();
    cY = pLOEvent->GetcY();
    cZ = pLOEvent->GetcZ();
    StarRA = pLOEvent->GetStarRA();
    StarDec = pLOEvent->GetStarDec();
    BrightDelta = pLOEvent->GetBrightDelta();
    Uncertainty = pLOEvent->GetUncertainty();

    if( ( Mv / 100.0 <= LimitMv ) && ( MaxDuration >= LimitDuration ) && ( std::fabs( BrightDelta ) >= LimitDrop ) ) {
      IfDistanceCheb( 1.0 / ( 24 * 60 * 60 ), apsmathlib::Rad * ObserverLongitude, apsmathlib::Rad * ObserverLatitude,
                      Distance, Mjdate, StarElev, SunElev, MoonElev, MaxLongitude, MaxLatitude,
                      ChebOrder, cX, cY, cZ,
                      ET_UT, BeginOccTime, EndOccTime,
                      EarthFlag, StarRA, StarDec );

      /*IfDistance( 1.0 / ( 24 * 60 * 60 ), apsmathlib::Rad * ObserverLongitude, apsmathlib::Rad * ObserverLatitude,
                    Distance, Mjdate, StarElev, SunElev, MoonElev, MaxLongitude, MaxLatitude,
                    ObservationEpoch, M, W, O, I, E, A,
                    ET_UT, BeginOccTime, EndOccTime,
                    EarthFlag, StarRA, StarDec, Uncertainty );*/

      if( Distance != std::numeric_limits<double>::max() ) {
        if( ( Distance <= LimitDistance + Diameter / 2.0 ) && ( apsmathlib::Deg * SunElev <= LimitSunElev ) &&
            ( apsmathlib::Deg * StarElev >= LimitStarElev ) ) {
          Probability = CalculateProbability( Distance, Diameter, Uncertainty );
          MaxProbability = CalculateProbability( 0.0, Diameter, Uncertainty );

          if( ( Probability >= LimitProb ) && ( MaxProbability >= LimitCenterProb ) ) {
            Az = CalculateAzimuty( apsmathlib::Rad * ObserverLongitude, apsmathlib::Rad * ObserverLatitude, MaxLongitude, MaxLatitude );

            Tau = apsastroalg::GMST( Mjdate ) + apsmathlib::Rad * ObserverLongitude - StarRA;
            apsastroalg::Equ2Hor( StarDec, Tau, apsmathlib::Rad * ObserverLatitude, h, StarAz );

            StarAz = StarAz + apsmathlib::pi;

            if( StarAz >= 2.0 * apsmathlib::pi ) {
              StarAz = StarAz - 2.0 * apsmathlib::pi;
            }

            pLOPointEvent = pLOPointEventData->CreatePointEvent( pLOPos, pLOEvent, Distance, Mjdate,
                                                                 StarElev, SunElev, MoonElev, MaxLongitude, MaxLatitude,
                                                                 Probability, MaxProbability, Az, StarAz );

            pLOPos->AddPointEvent( pLOPointEvent );
            pLOEvent->AddPointEvent( pLOPointEvent );
          }
        }
      }
    }

    if( !( i % PROGRESS_POS_STEP ) ) {
      std::cout << "*";
      std::cout.flush();
    }
  }

  std::cout << std::endl;

  return( RetCode );
}

int LOCalc :: ReRun( LOData * pLOData )
{
  unsigned int          i;
  LOEventData         * pLOEventData;
  LOEvent             * pLOEvent;
  LOPosData           * pLOPosData;
  LOPointEventData    * pLOPointEventData;
  LOPos               * pLOPos;
  int                   RetCode = 0;

//--------------

  ephem = new APSJPLEph();

  if( ephem->Init( pModule->GetJPLEphemFilePath() ) != apsastrodata::APS_JPL_NO_ERROR) {
    pModule->ErrorMessage( LO_CALC_JPL_INIT );
    return( LO_CALC_JPL_INIT );
  }

  AU = ephem->GetAU();

  pLOEventData = pLOData->GetEventDataPtr();

  /* must be in positions reader */
//  pLOData->CreatePosData();
  
  pLOPosData = pLOData->GetPosDataPtr();

  pLOPointEventData = pLOData->GetPointEventData();

  pLOEventData->Rebuild();

  pLOPosData->Rebuild();

  for( i = 0; i < pLOPosData->GetPositionsNumber(); i++ ) {
    pLOPos = pLOPosData->GetPositionPtr( i );

    if( ProcessOnePosition( pLOPos, pLOEventData, pLOPointEventData ) ) {
      std::cout << "ERROR in ProcessOnePosition" << std::endl;
      RetCode = 1;
    }
  }

  for( i = 0; i < pLOEventData->GetEventsNumber(); i++ ) {
    pLOEvent = pLOEventData->GetEventPtr( i );

    if( pLOEvent->GetFirstPointEventItem() ) {
      PrintOccultationEvent( 1.0 / pModule->GetScanStep(), pLOEvent->GetAsteroidID(), pLOEvent->GetAsteroidNamePtr(),
                             pLOEvent->GetDiameter(), pLOEvent->GetEphemerisUncertainty(),
                             pLOEvent->GetCatalog(), pLOEvent->GetStarNumber(), pLOEvent->GetMv(),
                             pLOEvent->GetChebOrder(), pLOEvent->GetcX(), pLOEvent->GetcY(), pLOEvent->GetcZ(),
                             pLOEvent->GetET_UT(), pLOEvent->GetBeginOccTime(), pLOEvent->GetEndOccTime(),
                             pLOEvent->GetEarthFlag(), pLOEvent->GetMaxDuration(),
                             pLOEvent->GetStarRA(), pLOEvent->GetStarDec(), pLOEvent->GetMoonPhase(),
                             pLOEvent->GetSunDist(), pLOEvent->GetMoonDist(),
                             pLOEvent->GetBrightness(), pLOEvent->GetBrightDelta(), pLOEvent->GetUncertainty() );
    }
  }

  delete ephem;

  ephem = 0;

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
