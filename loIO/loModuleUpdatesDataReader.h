//------------------------------------------------------------------------------
//
// File:    loModuleUpdatesDataReader.h
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

#ifndef LO_MODULE_UPDATES_DATA_READER_H
#define LO_MODULE_UPDATES_DATA_READER_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSModule;

class LOUpdatesDataReaderSubModule;

enum {
  LO_UPDATES_DATA_READER_NO_ERROR = 0,
  LO_UPDATES_DATA_READER_OPEN_FILE,
  LO_UPDATES_DATA_READER_READ_ERROR,
  LO_UPDATES_DATA_READER_UPDATE,
  LO_UPDATES_DATA_READER_START_READING,
  LO_UPDATES_DATA_READER_FINISH_READING,
  LO_UPDATES_DATA_READER_PROGRESS,
  LO_UPDATES_DATA_READER_NEW_LINE,
  LO_UPDATES_ASTEROID_ID_READ,
  LO_UPDATES_EPOCH_READ,
  LO_UPDATES_MEAN_ANOMALY_READ,
  LO_UPDATES_PERICENTER_READ,
  LO_UPDATES_LONG_NODE_READ,
  LO_UPDATES_INCLINATION_READ,
  LO_UPDATES_ECCENTRICITY_READ,
  LO_UPDATES_SEMIMAJOR_AXIS_READ,
  LO_UPDATES_MAJOR_READ,
  LO_UPDATES_MINOR_READ,
  LO_UPDATES_PA_READ
};

//======================= LOModuleUpdatesDataReader ==========================

class LOModuleUpdatesDataReader : public APSModule
{
  private:

    const LOUpdatesDataReaderSubModule * GetLOUpdatesDataReaderSubModule( void ) const;

  public:

    LOModuleUpdatesDataReader( LOUpdatesDataReaderSubModule * pOwner );

    virtual ~LOModuleUpdatesDataReader( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
