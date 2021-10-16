//------------------------------------------------------------------------------
//
// File:    loModuleGaiaReader.h
//
// Purpose: Module for Gaia catalog reader.
//   
// (c) 2021 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
// Gaia EDR3       0.2 10.01.2021
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

#ifndef LO_MODULE_GAIA_READER_H
#define LO_MODULE_GAIA_READER_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSModule;

class LOGaiaReadSubModule;

enum {
  LO_GAIA_READER_NO_ERROR = 0,
  LO_GAIA_OPEN_FILE,
  LO_GAIA_READER_FILE_LENGTH,
  LO_GAIA_READER_START_READING,
  LO_GAIA_READER_FINISH_READING,
  LO_GAIA_READER_PROGRESS,
  LO_GAIA_READER_TOO_MANY_STARS,
  LO_GAIA_READER_NOT_ENOUGH_DATA,
  LO_GAIA_READER_WRONG_STARS_NUMBER,
  LO_GAIA_NEW_LINE,
  LO_GAIA_READER_RA,
  LO_GAIA_READER_RA2,
  LO_GAIA_READER_DEC,
  LO_GAIA_READER_DEC2,
  LO_GAIA_READER_PARALLAX,
  LO_GAIA_READER_PM_RA,
  LO_GAIA_READER_PM_DEC,
  LO_GAIA_READER_VRAD,
  LO_GAIA_READER_EPOCH,
  LO_GAIA_READER_MV,
  LO_GAIA_READER_CATALOGUE,
  LO_GAIA_READER_STAR_NUMBER
};

//======================= LOModuleGaiaReader ==========================

class LOModuleGaiaReader : public APSModule
{
  private:

    const LOGaiaReadSubModule * GetLOGaiaReadSubModule( void ) const;

  public:

    LOModuleGaiaReader( LOGaiaReadSubModule * pOwner );

    virtual ~LOModuleGaiaReader( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    double GetMaxMv( void ) const;

    int GetIfOneStar( void ) const;

    int GetRA_Hour( void ) const;

    int GetRA_Min( void ) const;

    double GetRA_Sec( void ) const;

    int GetDec_Deg( void ) const;

    int GetDec_Min( void ) const;

    double GetDec_Sec( void ) const;

    double GetpmRA( void ) const;

    double GetpmDec( void ) const;

    int GetOneStarCatalog( void ) const;

    double GetOneStarMv( void ) const;

    double GetOneStarParallax( void ) const;
    
    double GetVrad( void ) const;
    
    double GetEpoch( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
