//------------------------------------------------------------------------------
//
// File:    loGaiaReader.h
//
// Purpose: Gaia star catalog reader for LinOccult.
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

#ifndef LO_GAIA_READER_H
#define LO_GAIA_READER_H

#include <string>

#include "GaiaEDR3Reader.h"

namespace aps {

  namespace apsastroio {
    class GaiaEDR3Reader;
  }

  namespace apslinoccult {

using apsastroio::GaiaEDR3Reader;

class LOModuleGaiaReader;
class LOData;
class LOGaiaReadSubModule;

//======================= LOGaiaReader ==========================

class LOGaiaReader : protected GaiaEDR3Reader
{
  private:

    LOModuleGaiaReader * pModule;

  public:

    LOGaiaReader( LOGaiaReadSubModule * pLOGaiaReadSubModule, const std::string & GaiaFilePath );

    virtual ~LOGaiaReader( void );

    int Read( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------
