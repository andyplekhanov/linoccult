//------------------------------------------------------------------------------
//
// File:    loModuleGaiaReader.cc
//
// Purpose: Module for Gaia catalog reader.
//   
// (c) 2004-2021 Plekhanov Andrey
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

#include "loModuleGaiaReader.h"
#include "loGaiaReadSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleGaiaEDR3Reader =================================

LOModuleGaiaReader :: LOModuleGaiaReader( LOGaiaReadSubModule * pOwner ) :
                      APSModule( "LOGaiaReader", pOwner )
{
}

LOModuleGaiaReader :: ~LOModuleGaiaReader( void )
{
}

const std::string LOModuleGaiaReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_GAIA_READER_NO_ERROR:
      return("No error\n");
    case LO_GAIA_OPEN_FILE:
      return("Can't open star catalog file.\n");
    case LO_GAIA_READER_FILE_LENGTH:
      return("Wrong file length\n");
    case LO_GAIA_READER_START_READING:
      return("Start reading star catalog file.");
    case LO_GAIA_READER_FINISH_READING:
      return("Star catalog file has been read.");
    case LO_GAIA_READER_TOO_MANY_STARS:
      return("Too many stars\n");
    case LO_GAIA_READER_NOT_ENOUGH_DATA:
      return("Not enough data\n");
    case LO_GAIA_READER_WRONG_STARS_NUMBER:
      return("Wrong stars number\n");
    case LO_GAIA_READER_RA:
      return("RA");
    case LO_GAIA_READER_RA2:
      return("RA2");
    case LO_GAIA_READER_DEC:
      return("Dec");
    case LO_GAIA_READER_DEC2:
      return("Dec2");
    case LO_GAIA_READER_PARALLAX:
      return("Parallax");
    case LO_GAIA_READER_PM_RA:
      return("pmRA");
    case LO_GAIA_READER_PM_DEC:
      return("pmDec");
    case LO_GAIA_READER_VRAD:
      return("Vrad");
    case LO_GAIA_READER_EPOCH:
      return("Epoch");
    case LO_GAIA_READER_MV:
      return("Mv");
    case LO_GAIA_READER_CATALOGUE:
      return("Catalogue");
    case LO_GAIA_READER_STAR_NUMBER:
      return("Star number");
    case LO_GAIA_READER_PROGRESS:
      return("*");
    case LO_GAIA_NEW_LINE:
      return("\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOGaiaReadSubModule * LOModuleGaiaReader :: GetLOGaiaReadSubModule( void ) const
{
  return( static_cast<const LOGaiaReadSubModule *>( GetOwnerPtr() ) );
}

double LOModuleGaiaReader :: GetMaxMv( void ) const
{
  return( GetLOGaiaReadSubModule()->GetMaxMv() );
}

int LOModuleGaiaReader :: GetIfOneStar( void ) const
{
  return( GetLOGaiaReadSubModule()->GetIfOneStar() );
}

int LOModuleGaiaReader :: GetRA_Hour( void ) const
{
  return( GetLOGaiaReadSubModule()->GetRA_Hour() );
}

int LOModuleGaiaReader :: GetRA_Min( void ) const
{
  return( GetLOGaiaReadSubModule()->GetRA_Min() );
}

double LOModuleGaiaReader :: GetRA_Sec( void ) const
{
  return( GetLOGaiaReadSubModule()->GetRA_Sec() );
}

int LOModuleGaiaReader :: GetDec_Deg( void ) const
{
  return( GetLOGaiaReadSubModule()->GetDec_Deg() );
}

int LOModuleGaiaReader :: GetDec_Min( void ) const
{
  return( GetLOGaiaReadSubModule()->GetDec_Min() );
}

double LOModuleGaiaReader :: GetDec_Sec( void ) const
{
  return( GetLOGaiaReadSubModule()->GetDec_Sec() );
}

double LOModuleGaiaReader :: GetpmRA( void ) const
{
  return( GetLOGaiaReadSubModule()->GetpmRA() );
}

double LOModuleGaiaReader :: GetpmDec( void ) const
{
  return( GetLOGaiaReadSubModule()->GetpmDec() );
}

int LOModuleGaiaReader :: GetOneStarCatalog( void ) const
{
  return( GetLOGaiaReadSubModule()->GetOneStarCatalog() );
}

double LOModuleGaiaReader :: GetOneStarMv( void ) const
{
  return( GetLOGaiaReadSubModule()->GetOneStarMv() );
}

double LOModuleGaiaReader :: GetOneStarParallax( void ) const
{
  return( GetLOGaiaReadSubModule()->GetOneStarParallax() );
}

double LOModuleGaiaReader :: GetVrad( void ) const
{
  return( GetLOGaiaReadSubModule()->GetVrad() );
}

double LOModuleGaiaReader :: GetEpoch( void ) const
{
  return( GetLOGaiaReadSubModule()->GetEpoch() );
}

}}

//---------------------------- End of file ---------------------------
