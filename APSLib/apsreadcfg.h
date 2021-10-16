//------------------------------------------------------------------------------
//
// File:    apsreadcfg.h
//
// Purpose: Class for reading config
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 06.03.2004
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

#ifndef 	_APSREADCFG_H_
#define         _APSREADCFG_H_	1

namespace aps {

  namespace apslib {

#include <string>

class APSModuleConfigReader;
class APSSubModule;
class APSIStrFile;
class APSConfig;

//------------------------------- APSReadConfig ---------------------------------

class APSReadConfig
{
  private:

    APSIStrFile           * pFile;

    APSModuleConfigReader * pModule;

    bool ParseLine( const std::string & Str, std::string & ParamType,
                    std::string & ParamName, std::string & ParamValue ) const;

  public:

    APSReadConfig( APSSubModule * pSubModule, const std::string & ConfigFilePath );

    virtual ~APSReadConfig( void );

    int Read( APSConfig * pConfig );
};

}}

#endif

//---------------------------- End of file ---------------------------
