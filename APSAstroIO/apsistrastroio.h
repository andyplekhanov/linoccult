//------------------------------------------------------------------------------
//
// File:    apsistrastroio.h
//
// Purpose: Base class for text astro file input.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 05.02.2006
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

#ifndef APS_ISTR_ASTRO_IO_H
#define APS_ISTR_ASTRO_IO_H

#include <string>
#include <list>

#include "apsistrfile.h"

namespace aps {

  namespace apsastroio {

using apslib :: APSIStrFile;

//=============================== APSIStrAstroIO =========================

class APSIStrAstroIO : protected APSIStrFile
{
  private:

    std::string Str;
    bool        IfReady;

    int ParseString( const std::string & Str, std::list<std::string> & List ) const;

    int ProcessString( const std::string & Str, std::list<std::string> & List,
                       int & Number, double & sign ) const;

  protected:

    bool ReadStr( void );

    const std::string & GetBuffer( void ) const
      { return( Str ); }

    int GetDoubleWithPrecision( const std::string & Str, double & Angle, double & Prec ) const;

    int GetInteger( int & pInt, const unsigned int Offset, const unsigned int Length ) const;

    int GetShort( short & pShort, const unsigned int Offset, const unsigned int Length ) const;

    int GetString( std :: string & pStr, const unsigned int Offset, const unsigned int Length ) const;

    int GetChar( char & pChar, const unsigned int Offset ) const;

    int GetFloat( float & pFlt, const unsigned int Offset, const unsigned int Length ) const;

    int GetDouble( double & pDbl, const unsigned int Offset, const unsigned int Length ) const;

    int GetAngle( double & Angle, double & Prec, const unsigned int Offset, const unsigned int Length ) const;

  public:

    APSIStrAstroIO( const std::string & FileName );

    virtual ~APSIStrAstroIO( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
