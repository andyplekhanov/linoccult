//------------------------------------------------------------------------------
//
// File:    apsabsmodule.h
//
// Purpose: Abstruct module
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

#ifndef 	_APSABSMODULE_H_
#define         _APSABSMODULE_H_	1

#include <string>

namespace aps {

  namespace apslib {

enum {
  MODULE_CONTINUE = 0,
  MODULE_STOP
};

class APSAbsModule
{
  public:

    APSAbsModule( void );

    virtual ~APSAbsModule( void );

    virtual const std::string & GetModuleName( void ) const = 0;

    virtual int InfoMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const = 0;

    virtual int WarningMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const = 0;

    virtual int ErrorMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const = 0;

    virtual int DebugMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const = 0;

    virtual int StrMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const = 0;

    virtual const std::string GetMessageText( const int MsgNumber ) const = 0;
};

}}

#endif

//---------------------------- End of file ---------------------------


