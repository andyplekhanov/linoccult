//------------------------------------------------------------------------------
//
// File:    loModuleAstOrbReader.h
//
// Purpose: Module for asteroids ephemeris reader.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 10.02.2004
// version 0.2 11.04.2004 LO_AST_ORB_READER_NO_DIAMETER_AND_BRIGTHNESS has been added
// version 0.3 24.05.2004 IfOneAsteroid, ObservationEpoch,
//                                OrbitM, OrbitW, OrbitO, OrbitI, OrbitE, OrbitA parameters were added
// version 0.4 05.03.2005 StartAsteroidNumber, EndAsteroidNumber were added
// version 0.5 17.04.2005 UpdatesExpirePeriod was added
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

#ifndef LO_MODULE_ASTORB_READER_H
#define LO_MODULE_ASTORB_READER_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSModule;

class LOAstOrbReadSubModule;

enum {
  LO_AST_ORB_READER_NO_ERROR = 0,
  LO_AST_ORB_OPEN_FILE,
  LO_AST_ORB_SEEK,
  LO_AST_ORB_READ,
  LO_AST_ORB_READER_FILE_LENGTH,
  LO_AST_ORB_READER_START_READING,
  LO_AST_ORB_READER_FINISH_READING,
  LO_AST_ORB_READER_PROGRESS,
  LO_AST_ORB_READER_START_READ_ONE_ASTEROID,
  LO_AST_ORB_READER_FINISH_READ_ONE_ASTEROID,
  LO_AST_ORB_READER_TOO_MANY_ASTEROIDS,
  LO_AST_ORB_READER_NOT_ENOUGH_DATA,
  LO_AST_ORB_READER_WRONG_ASTEROIDS_NUMBER,
  LO_AST_ORB_READER_NO_DIAMETER_AND_BRIGTHNESS,
  LO_AST_ORB_NEW_LINE,
  LO_AST_ORB_READER_ASTEROID_ID,
  LO_AST_ORB_READER_ASTEROID_NAME,
  LO_AST_ORB_READER_ORBIT_COMPUTER,
  LO_AST_ORB_READER_BRIGTENES,
  LO_AST_ORB_READER_SLOPE,
  LO_AST_ORB_READER_COLOR,
  LO_AST_ORB_READER_DIAMETER,
  LO_AST_ORB_READER_TAXONOMIC,
  LO_AST_ORB_READER_CODE1,
  LO_AST_ORB_READER_CODE2,
  LO_AST_ORB_READER_CODE3,
  LO_AST_ORB_READER_CODE4,
  LO_AST_ORB_READER_CODE5,
  LO_AST_ORB_READER_CODE6,
  LO_AST_ORB_READER_ORBITAL_ARC,
  LO_AST_ORB_READER_NUMBER_OF_OBSERVATIONS,
  LO_AST_ORB_READER_OBSERVATION_YEAR,
  LO_AST_ORB_READER_OBSERVATION_MONTH,
  LO_AST_ORB_READER_OBSERVATION_DAY,
  LO_AST_ORB_READER_M,
  LO_AST_ORB_READER_W,
  LO_AST_ORB_READER_O,
  LO_AST_ORB_READER_I,
  LO_AST_ORB_READER_E,
  LO_AST_ORB_READER_A,
  LO_AST_ORB_READER_COMPUTATION_YEAR,
  LO_AST_ORB_READER_COMPUTATION_MONTH,
  LO_AST_ORB_READER_COMPUTATION_DAY,
  LO_AST_ORB_READER_EPHEMERIS_UNCERTAINTY,
  LO_AST_ORB_READER_EPHEMERIS_UNCERTAINTY_RATE,
  LO_AST_ORB_READER_CEU_YEAR,
  LO_AST_ORB_READER_CEU_MONTH,
  LO_AST_ORB_READER_CEU_DAY,
  LO_AST_ORB_READER_NEXT_PEAK_EPHEMERIS_UNCERTAINTY,
  LO_AST_ORB_READER_PEU_YEAR,
  LO_AST_ORB_READER_PEU_MONTH,
  LO_AST_ORB_READER_PEU_DAY,
  LO_AST_ORB_READER_GREATEST_PEAK_EPHEMERIS_UNCERTAINTY,
  LO_AST_ORB_READER_GEU_YEAR,
  LO_AST_ORB_READER_GEU_MONTH,
  LO_AST_ORB_READER_GEU_DAY,
  LO_AST_ORB_READER_GREATEST_PEAK2_EPHEMERIS_UNCERTAINTY,
  LO_AST_ORB_READER_GEU2_YEAR,
  LO_AST_ORB_READER_GEU2_MONTH,
  LO_AST_ORB_READER_GEU2_DAY
};

//======================= LOModuleAstOrbReader ==========================

class LOModuleAstOrbReader : public APSModule
{
  private:

    const LOAstOrbReadSubModule * GetLOAstOrbReadSubModulePtr( void ) const;

  public:

    LOModuleAstOrbReader( LOAstOrbReadSubModule * pOwner );

    virtual ~LOModuleAstOrbReader( void );

    virtual int WarningMessage( const int MsgNumber, const std::string & Msg = "", const APSModule * pSubModule = 0 ) const;

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    int GetAsteroidNumber( void ) const;

    int GetIfOneAsteroid( void ) const;

    double GetObservationEpoch( void ) const;

    double GetOrbitM( void ) const;

    double GetOrbitW( void ) const;

    double GetOrbitO( void ) const;

    double GetOrbitI( void ) const;

    double GetOrbitE( void ) const;

    double GetOrbitA( void ) const;

    int GetStartAsteroidNumber( void ) const;

    int GetEndAsteroidNumber( void ) const;

    int GetUpdatesExpirePeriod( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
