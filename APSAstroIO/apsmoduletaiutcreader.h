//------------------------------------------------------------------------------
//
// File:    apsmoduletaiutcreader.h
//
// Purpose: Module for TAI_UTC data base reader.
//   
// (c) Plekhanov Andrey
//
// Initial version 0.1
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

#ifndef APS_MODULE_TAI_UTC_READER_H
#define APS_MODULE_TAI_UTC_READER_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apsastroio {

using apslib::APSModule;
using apslib::APSSubModule;

enum {
  APS_TAI_UTC_READER_NO_ERROR = 0,
  APS_TAI_UTC_READER_OPEN_FILE,
  APS_TAI_UTC_READER_PARSE,
  APS_TAI_UTC_READER_NEW_LINE,
  APS_TAI_UTC_READER_FINISH_READING,
  APS_TAI_UTC_READER_SORT,
  APS_TAI_UTC_READER_SKIP_HEADER
};

//======================= APSModuleTaiUtcReader ==========================

class APSModuleTaiUtcReader : public APSModule
{
  public:

    APSModuleTaiUtcReader( APSSubModule * pAPSSubModule );

    virtual ~APSModuleTaiUtcReader( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
