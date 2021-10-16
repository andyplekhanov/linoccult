//------------------------------------------------------------------------------
//
// File:    loModuleUpdatesDataReader.cc
//
// Purpose: Module for updates data reading.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 17.04.2005
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

#include "loModuleUpdatesDataReader.h"
#include "loUpdatesDataReaderSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleUpdatesDataReader =================================

LOModuleUpdatesDataReader :: LOModuleUpdatesDataReader( LOUpdatesDataReaderSubModule * pOwner ) :
                             APSModule( "LOModuleUpdatesDataReader", pOwner )
{
}

LOModuleUpdatesDataReader :: ~LOModuleUpdatesDataReader( void )
{
}

const std::string LOModuleUpdatesDataReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_UPDATES_DATA_READER_NO_ERROR:
      return("No error\n");
    case LO_UPDATES_DATA_READER_OPEN_FILE:
      return("Can't open updates file.\n");
    case LO_UPDATES_DATA_READER_READ_ERROR:
      return("Read error.\n");
    case LO_UPDATES_DATA_READER_UPDATE:
      return("Can't read update.\n");
    case LO_UPDATES_DATA_READER_START_READING:
      return("Start reading updates file.");
    case LO_UPDATES_DATA_READER_FINISH_READING:
      return("Updates file has been read.");
    case LO_UPDATES_DATA_READER_PROGRESS:
      return("*");
    case LO_UPDATES_DATA_READER_NEW_LINE:
      return("\n");
    case LO_UPDATES_ASTEROID_ID_READ:
      return("Asteroid ID.\n");
    case LO_UPDATES_EPOCH_READ:
      return("Epoch.\n");
    case LO_UPDATES_MEAN_ANOMALY_READ:
      return("Mean anomaly.\n");
    case LO_UPDATES_PERICENTER_READ:
      return("Pericenter.\n");
    case LO_UPDATES_LONG_NODE_READ:
      return("Node longitude.\n");
    case LO_UPDATES_INCLINATION_READ:
      return("Inclination.\n");
    case LO_UPDATES_ECCENTRICITY_READ:
      return("Eccentricity.\n");
    case LO_UPDATES_SEMIMAJOR_AXIS_READ:
      return("Semimajor axis.\n");
    case LO_UPDATES_MAJOR_READ:
      return("Major.\n");
    case LO_UPDATES_MINOR_READ:
      return("Minor.\n");
    case LO_UPDATES_PA_READ:
      return("PA.\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOUpdatesDataReaderSubModule * LOModuleUpdatesDataReader :: GetLOUpdatesDataReaderSubModule( void ) const
{
  return( static_cast<const LOUpdatesDataReaderSubModule *>( GetOwnerPtr() ) );
}

}}

//---------------------------- End of file ---------------------------
