//------------------------------------------------------------------------------
//
// File:    EtUtReader.h
//
// Purpose: Read data from ET-UT file.
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

#ifndef ET_UT_READER_H
#define ET_UT_READER_H

#include <string>

#include "apsistrfile.h"

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apsastrodata {
    class APSEtUtData;
  }

  namespace apsastroio {

using apslib::APSSubModule;
using apslib::APSIStrFile;
using apsastrodata::APSEtUtData;

class APSModuleEtUtReader;

//======================= EtUtReader ==========================

class EtUtReader : protected APSIStrFile
{
  protected:

    APSModuleEtUtReader * pModule;

    bool CheckMjd( const APSEtUtData * pAPSEtUtData, const double Mjd ) const;

    bool ParseLine( const std::string & Str, int & Day, int & Month,
                    int & Year, double & Value ) const;

    bool SkipHeader( void );

  public:

    EtUtReader( APSSubModule * pSubModule, const std::string & pEtUtFilePath );

    virtual ~EtUtReader( void );

    int Read( APSEtUtData * pAPSEtUtData );
};

}}

#endif

//---------------------------- End of file ---------------------------
