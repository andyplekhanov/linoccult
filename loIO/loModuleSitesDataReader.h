//------------------------------------------------------------------------------
//
// File:    loModuleSitesDataReader.h
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

#ifndef LO_MODULE_SITES_DATA_READER_H
#define LO_MODULE_SITES_DATA_READER_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSModule;

class LOSitesDataReaderSubModule;

enum {
  LO_SITES_DATA_READER_NO_ERROR = 0,
  LO_SITES_DATA_READER_OPEN_FILE,
  LO_SITES_DATA_READER_READ_ERROR,
  LO_SITES_DATA_READER_SITE,
  LO_SITES_DATA_READER_START_READING,
  LO_SITES_DATA_READER_FINISH_READING,
  LO_SITES_DATA_READER_PROGRESS,
  LO_SITES_DATA_READER_NEW_LINE,
  LO_SITES_OUTPUT_FILES_READ,
  LO_SITES_SORT_READ,
  LO_SITES_LONGITUDE_READ,
  LO_SITES_LATITUDE_READ,
  LO_SITES_MAX_DISTANCE_READ,
  LO_SITES_MAX_MV_READ,
  LO_SITES_MIN_DURATION_READ,
  LO_SITES_SUN_ELEV_READ,
  LO_SITES_MIN_DROP_READ,
  LO_SITES_MIN_PROB_READ,
  LO_SITES_MIN_CENTER_PROB_READ,
  LO_SITES_MIN_STAR_ELEV_READ
};

//======================= LOModuleSitesDataReader ==========================

class LOModuleSitesDataReader : public APSModule
{
  private:

    const LOSitesDataReaderSubModule * GetLOSitesDataReaderSubModule( void ) const;

  public:

    LOModuleSitesDataReader( LOSitesDataReaderSubModule * pOwner );

    virtual ~LOModuleSitesDataReader( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------


