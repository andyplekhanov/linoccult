//------------------------------------------------------------------------------
//
// File:    loUpdatesDataReaderSubModule.h
//
// Purpose: Submodule for reading updates data base for LinOccult.
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

#ifndef LO_UPDATES_DATA_READER_SUB_MODULE_H
#define LO_UPDATES_DATA_READER_SUB_MODULE_H

#include "apssubmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSSubModule;

class LOModuleAppl;

//======================= LOUpdatesDataReaderSubModule ==========================

class LOUpdatesDataReaderSubModule : public APSSubModule
{
  private:

    LOModuleAppl * GetLOModuleApplPtr( void ) const;

  public:

    LOUpdatesDataReaderSubModule( LOModuleAppl * pOwner );

    virtual ~LOUpdatesDataReaderSubModule( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
