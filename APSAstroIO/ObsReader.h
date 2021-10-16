//------------------------------------------------------------------------------
//
// File:    ObsReader.h
//
// Purpose: Read data from observatories position file.
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

#ifndef OBS_READER_H
#define OBS_READER_H

#include <string>

#include "apsistrastroio.h"

namespace aps {

  namespace apsastroio {

//======================= ObsReader ==========================

class ObsReader : protected APSIStrAstroIO
{
  protected:

    int GetObsCodeName( std::string & pObsCodeName ) const;

    int GetLongitude( double & pLongitude ) const;

    int GetRhoCos( double & pRhoCos ) const;

    int GetRhoSin( double & pRhoSin ) const;

    int GetName( std::string & Name ) const;

  public:

    ObsReader( const std::string & pMPCFilePath );

    virtual ~ObsReader( void );

    static int ConvertObsCode( const std::string & ObsCodeName, int & ObsCode );
};

}}

#endif

//---------------------------- End of file ---------------------------
