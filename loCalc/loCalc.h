//------------------------------------------------------------------------------
//
// File:    loCalc.h
//
// Purpose: Asteroids occultation program for Linux
//          Main calculation procedure
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 16.02.2004
//         version 0.2 13.01.2005 NewNewNewProcessAsteroid, MySQL, kdtree
//         version 0.3 07.02.2005 Event data was added
//         version 0.4 15.02.2005 CalculateBrightness was added
//         version 0.5  9.02.2021 MAX_STAR_NUMBER 100000 -> 1000000
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

#ifndef LO_CALC_H
#define LO_CALC_H

#include <string>

namespace aps {

  namespace apsmathlib {
    class APSVec3d;
  }

  namespace apsastrodata {
    class APSJPLEph;
  }

  namespace apslinoccult {

using apsmathlib::APSVec3d;
using apsastrodata::APSJPLEph;

class LOData;
class LOModuleCalc;
class LOCalcSubModule;
class LOAsteroid;
class LOStarData;
class LOEventData;
class LOPointEventData;
class LOAstOrbData;
class LOStar;
class LOPos;

const unsigned int MAX_STAR_NUMBER = 1000000; // For near Earth asteroids this limit should be increased

//======================= LOCalc ==========================

class LOCalc
{
  private:

    LOModuleCalc  * pModule;
    APSJPLEph     * ephem;
    double          MjdStart;
    double          MjdEnd;
    const LOStar  * pLOStarsArray[ MAX_STAR_NUMBER ];
    unsigned int    StarsCount;
    int             EventStar;
    APSVec3d     ** ChebArray;
    double          AU;

    double GetAU( void ) const
      { return( AU ); }

    int AddStar( const LOStar * pStar );

    const LOStar * GetStar( const unsigned int StarNumber ) const;

    void ClearStarsArray( void )
      {  StarsCount = 0; }

    unsigned int GetStarsCount( void ) const
      { return( StarsCount ); }

    int GetEventStar( void ) const
      { return( EventStar ); }

    void SetEventStar( const int aEventStar )
      { EventStar = aEventStar; }

    void ScanStars( const LOStarData * pLOStarData, APSVec3d * r_Asteroid );

    void ScanStars1( const LOStarData * pLOStarData, APSVec3d * r_Asteroid1, APSVec3d * r_Asteroid2 );

    int ScanStars2( const LOStarData * pLOStarData, const int ScanStep );

    double CalculateBrightness( const LOAsteroid * pLOAsteroid, const APSVec3d & R_Sun,
                                const APSVec3d & rAstAU ) const;

    void CalcParallax( const LOStar * pLOStar, const double ETMjdate, const float Parallax,
                       double & ParallaxDelta, double & ParallaxAlpha ) const;

    void CalcStrip( const double t_prev, const APSVec3d & r_prev, const APSVec3d & r_now,
                    const APSVec3d & eStar, const double AstRadius, double & Lambda1, double & Phi1,
                    double & Lambda2, double & Phi2 ) const;

    double CalculateTotalUncertainty( double & AngleUncertainty, const double AsteroidUncertainty,
                                      const double ETMjdate, const short StarMv, const double Distance ) const;

    int ProcessStar( const LOAsteroid * pLOAsteroid, const APSVec3d * r_Asteroid,
                     const double ETMjdate, const double Mjdate,
                     const LOStar * pLOStar, const int StarNumber );

    int CalculateParameters( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar,
                             const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                             double ET_UT, const double BeginOccTime, const double EndOccTime,
                             double & StarRA, double & StarDec,
                             double & MoonPhase, double & SunDist, double & MoonDist,
                             double & Brightness, double & BrightDelta, double & Uncertainty,
                             double & AngleUncertainty ) const;

    void PrintHeader( const int AsteroidID, const std::string & AsteroidName,
                      const double Diameter, const double EphemerisUncertainty,
                      const unsigned char Catalog, const int StarNumber, const short Mv,
                      const double BeginOccTime, const double EndOccTime,
                      const int EarthFlag, const double MaxDuration,
                      const double StarRA, const double StarDec,
                      const double MoonPhase, const double SunDist, const double MoonDist,
                      const double Brightness, const double BrightDelta, const double Uncertainty ) const;

    void PrintOccultationEvent( const double TimeStep, const int AsteroidID, const std::string & AsteroidName,
                                const double Diameter, const double EphemerisUncertainty,
                                const unsigned char Catalogue, const int StarNumber, const short Mv,
                                const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                                double ET_UT, const double BeginOccTime, const double EndOccTime,
                                const int EarthFlag, const double MaxDuration,
                                const double StarRA, const double StarDec,
                                const double MoonPhase, const double SunDist, const double MoonDist,
                                const double Brightness, const double BrightDelta, const double Uncertainty ) const;

    double CalculateDistance( const double ObserverLongitude, const double ObserverLatitude,
                              const double Lambda, const double Phi ) const;

    double f( const double x ) const;

    double IntGauss( double u ) const;

    double CalculateProbability( const double Distance, const double Diameter, const double Uncertainty ) const;

    double CalculateAzimuty( const double ObserverLongitude, const double ObserverLatitude,
                             const double MaxLongitude, const double MaxLatitude ) const;

    void IfDistanceCheb( const double TimeStep, const double ObserverLongitude, const double ObserverLatitude,
                         double & MaxDistance, double & MaxMjdate, double & StarElev, double & SunElev, double & MoonElev,
                         double & MaxLongitude, double & MaxLatitude,
                         const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                         const double ET_UT, const double BeginOccTime, const double EndOccTime,
                         const int EarthFlag, const double StarRA, const double StarDec ) const;

    void IfDistance( const double TimeStep, const double ObserverLongitude, const double ObserverLatitude,
                     double & MaxDistance, double & MaxMjdate, double & StarElev, double & SunElev, double & MoonElev,
                     double & MaxLongitude, double & MaxLatitude,
                     const double ObservationEpoch, const double M, const double W, const double O,
                     const double I, const double E, const double A,
                     const double ET_UT, const double BeginOccTime, const double EndOccTime,
                     const int EarthFlag, const double StarRA, const double StarDec ) const;

    void SaveOccEvent( const int AsteroidID, const std::string & AsteroidName,
                       const double Diameter, const double EphemerisUncertainty,
                       const int StarNumber, const short Mv,
                       const int ChebOrder, const double * cX, const double * cY, const double * cZ,
                       const double ET_UT, const double BeginOccTime, const double EndOccTime,
                       const int EarthFlag, const double MaxDuration,
                       const double StarRA, const double StarDec,
                       const double MoonPhase, const double SunDist, const double MoonDist,
                       const double Brightness, const double BrightDelta, const double Uncertainty ) const;

    int SaveOccultationEvent( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar,
                              LOEventData * pLOEventData,
                              const double BeginOccTime, const double EndOccTime,
                              const int EarthFlag, const double MaxDuration, const double ET_UT ) const;

    double CalcDuration( const APSVec3d & eStar, const double Diameter, const APSVec3d & r,
                         const APSVec3d & r_prev, const double SmallStep ) const;

    int CreateOccultationEvent( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar,
                                LOEventData * pLOEventData,
                                const APSVec3d & eStar, double * StartMjdate, int * StartStep,
                                const double ET_UT, const double Step, const double MaxDist ) const;

    int ProcessStar1( const LOAsteroid * pLOAsteroid, const LOStar * pLOStar, LOEventData * pLOEventData,
                      const double BeginMjdate, const double EndMjdate,
                      const double ET_UT, const double Step, const int ScanStep );

    int ProcessStarData( const LOAsteroid * pLOAsteroid, const APSVec3d * r_equ,
                         const double ETMjdate, const double Mjdate );

    int ProcessAsteroid( const LOAsteroid * pLOAsteroid, const LOStarData * pLOStarData );

    //int NewProcessAsteroid( const LOAsteroid * pLOAsteroid, const LOStarData * pLOStarData );

    int NewNewNewProcessAsteroid( const LOAsteroid * pLOAsteroid, const LOStarData * pLOStarData,
                                  LOEventData * pLOEventData );

    int IfAsteroid( const LOAsteroid * pLOAsteroid ) const;

    int ProcessManyAsteroids( const LOAstOrbData * pLOAstOrbData, const LOStarData * pLOStarData,
                              LOEventData * pLOEventData );

    int ProcessOnePosition( LOPos * pLOPos, LOEventData * pLOEventData, LOPointEventData * pLOPointEventData ) const;

  public:

    LOCalc( LOCalcSubModule * pLOCalcSubModule );

    virtual ~LOCalc( void );

    int Run( LOData * pLOData );

    int OldReRun( void );

    int ReRun( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------
