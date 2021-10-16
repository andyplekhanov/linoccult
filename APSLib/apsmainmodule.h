//------------------------------------------------------------------------------
//
// File:    apsmainmodule.h
//
// Purpose: Main module
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 08.03.2004
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

#ifndef 	_APSMAINMODULE_H_
#define         _APSMAINMODULE_H_	1

#include "apsmodule.h"

namespace aps {

  namespace apslib {

typedef enum {
  APS_NORMAL_VERSION = 0,
  APS_BETA_VERSION,
  APS_ALPHA_VERSION
} APS_PROGRAM_VERSION_TYPE;

class APSMainModule : public APSModule
{
  private:

    int           X_Version;
    int           Y_Version;
    int           Z_Version;
    int           FirstCopyRightYear;
    int           CopyRightYear;
    APS_PROGRAM_VERSION_TYPE VersionType;

  protected:

    void ShowBanner( void ) const;

  public:

    APSMainModule( const std::string & apModuleName,
                   const int aX_Version,
                   const int aY_Version,
                   const int aZ_Version,
                   const int aFirstCopyRightYear,
                   const int aCopyRightYear,
                   const APS_PROGRAM_VERSION_TYPE aVersionType = APS_NORMAL_VERSION );

    virtual ~APSMainModule( void );

    void GetModuleInfo( std::string & Str, const int Mode = 0 ) const;

    int GetFirstCopyRightYear( void ) const
      { return( FirstCopyRightYear ); }

    int GetCopyRightYear( void ) const
      { return( CopyRightYear ); }

    int GetX_Version( void ) const
      { return( X_Version ); }

    int GetY_Version( void ) const
      { return( Y_Version ); }

    int GetZ_Version( void ) const
      { return( Z_Version ); }

    int GetVersionType( void ) const
      { return( VersionType ); }

    virtual int Run( void ) = 0;
};

}}

#endif

//---------------------------- End of file ---------------------------
