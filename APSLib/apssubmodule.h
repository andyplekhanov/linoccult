//------------------------------------------------------------------------------
//
// File:    apssubmodule.h
//
// Purpose: Submodule support
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

#ifndef 	_APSSUBMODULE_H_
#define         _APSSUBMODULE_H_	1

#include "apsabsmodule.h"

namespace aps {

  namespace apslib {

class APSModule;

class APSSubModule : public APSAbsModule
{
  private:

    APSModule * pOwner;
    APSModule * pSubModule;

  public:

    APSSubModule( APSModule * apOwner );

    virtual ~APSSubModule( void );

    const APSModule * GetOwnerPtr( void ) const
      { return( pOwner ); }

    const APSModule * GetSubMudulePtr( void ) const
      { return( pSubModule ); }

    void SetSubModule( const APSModule * apSubModule )
      { pSubModule = pSubModule; }

    virtual const std::string & GetModuleName( void ) const;

    virtual int InfoMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const;

    virtual int WarningMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const;

    virtual int ErrorMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const;

    virtual int DebugMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const;

    virtual int StrMessage( const int MsgNumber, const std::string & Msg = "", const APSAbsModule * pSubModule = 0 ) const;

    virtual const std::string GetMessageText( const int MsgNumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------

