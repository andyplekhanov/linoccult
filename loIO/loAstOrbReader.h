//------------------------------------------------------------------------------
//
// File:    loAstOrbReader.h
//
// Purpose: Asteroids ephemeris reader for LinOccult.
//          Read data from astorb.dat.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 31.01.2004
// version 0.2 17.04.2005 Updates database was added
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

#ifndef LO_ASTORB_READER_H
#define LO_ASTORB_READER_H

#include <string>

#include "AstOrbReader.h"

namespace aps {

  namespace apslinoccult {

using apsastroio::AstOrbReader;

class LOModuleAstOrbReader;
class LOData;
class LOAstOrbData;
class LOUpdateData;
class LOAstOrbReadSubModule;

//======================= LOAstOrbReader ==========================

class LOAstOrbReader : protected AstOrbReader
{
  private:

    LOModuleAstOrbReader * pModule;
    int                    UpdatesNumber;

    int ReadOneAsteroid( LOAstOrbData * pLOAstOrbData, LOUpdateData * pLOUpdateData, const int Count );

  public:

    LOAstOrbReader( LOAstOrbReadSubModule * pLOAstOrbReadSubModule, const std::string & AstOrbFilePath );

    virtual ~LOAstOrbReader( void );

    int Read( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------


