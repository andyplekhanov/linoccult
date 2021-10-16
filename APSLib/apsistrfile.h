//------------------------------------------------------------------------------
//
// File:    apsistrfile.h
//
// Purpose: General purpose procedures for input text file processing
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.04.2004
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

#ifndef 	_APSISTRFILE_H_
#define         _APSISTRFILE_H_	1

#include <fstream>
#include <string>

#include "apsifile.h"

namespace aps {

  namespace apslib {

class APSIStrFile : public APSIFile
{
  public:

    APSIStrFile( const std::string & aFileName );

    virtual ~APSIStrFile( void );

    bool GetStr( std::string & Str );
};

}}

#endif

//---------------------------- End of file ---------------------------

