//------------------------------------------------------------------------------
//
// File:    loModuleSitesDataReader.cc
//
// Purpose: Module for sites data reading.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 05.03.2005
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

#include "loModuleSitesDataReader.h"
#include "loSitesDataReaderSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleSitesDataReader =================================

LOModuleSitesDataReader :: LOModuleSitesDataReader( LOSitesDataReaderSubModule * pOwner ) :
                           APSModule( "LOModuleSitesDataReader", pOwner )
{
}

LOModuleSitesDataReader :: ~LOModuleSitesDataReader( void )
{
}

const std::string LOModuleSitesDataReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_SITES_DATA_READER_NO_ERROR:
      return("No error\n");
    case LO_SITES_DATA_READER_OPEN_FILE:
      return("Can't open sites file.\n");
    case LO_SITES_DATA_READER_READ_ERROR:
      return("Read error.\n");
    case LO_SITES_DATA_READER_SITE:
      return("Can't read site.\n");
    case LO_SITES_DATA_READER_START_READING:
      return("Start reading sites file.");
    case LO_SITES_DATA_READER_FINISH_READING:
      return("Sites file has been read.");
    case LO_SITES_DATA_READER_PROGRESS:
      return("*");
    case LO_SITES_DATA_READER_NEW_LINE:
      return("\n");
    case LO_SITES_OUTPUT_FILES_READ:
      return("Output file types.\n");
    case LO_SITES_SORT_READ:
      return("Sort type.\n");
    case LO_SITES_LONGITUDE_READ:
      return("Longitude.\n");
    case LO_SITES_LATITUDE_READ:
      return("Latitude.\n");
    case LO_SITES_MAX_DISTANCE_READ:
      return("Max distance.\n");
    case LO_SITES_MAX_MV_READ:
      return("Max star magnitude.\n");
    case LO_SITES_MIN_DURATION_READ:
      return("Min duration.\n");
    case LO_SITES_SUN_ELEV_READ:
      return("Sun elevation.\n");
    case LO_SITES_MIN_DROP_READ:
      return("Min drop.\n");
    case LO_SITES_MIN_PROB_READ:
      return("Min probability.\n");
    case LO_SITES_MIN_CENTER_PROB_READ:
      return("Min center probability.\n");
    case LO_SITES_MIN_STAR_ELEV_READ:
      return("Min star elevation.\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOSitesDataReaderSubModule * LOModuleSitesDataReader :: GetLOSitesDataReaderSubModule( void ) const
{
  return( static_cast<const LOSitesDataReaderSubModule *>( GetOwnerPtr() ) );
}

}}

//---------------------------- End of file ---------------------------
