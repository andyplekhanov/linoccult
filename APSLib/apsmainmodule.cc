//------------------------------------------------------------------------------
//
// File:    apsmainmodule.cc
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

#include <sstream>

#include "apsmainmodule.h"

namespace aps {

  namespace apslib {

APSMainModule :: APSMainModule( const std::string & apModuleName,
                                const int aX_Version,
                                const int aY_Version,
                                const int aZ_Version,
                                const int aFirstCopyRightYear,
                                const int aCopyRightYear,
                                const APS_PROGRAM_VERSION_TYPE aVersionType ) :
   APSModule( apModuleName, 0 ), X_Version( aX_Version ), Y_Version( aY_Version ),
   Z_Version( aZ_Version ), FirstCopyRightYear( aFirstCopyRightYear ),
   CopyRightYear( aCopyRightYear ), VersionType( aVersionType )
{
}

APSMainModule :: ~APSMainModule( void )
{
}

void APSMainModule :: GetModuleInfo( std::string & Str, const int Mode ) const
{
  std::ostringstream MsgText;

  switch( Mode ) {
    case 0:
      switch( VersionType ) {
        case APS_BETA_VERSION:
          MsgText << "  " << GetModuleName() << " " << GetX_Version() << "." <<
                             GetY_Version() << "." << GetZ_Version() << " BETA " <<
                             GetFirstCopyRightYear() << " - " << GetCopyRightYear() << std::endl;
        break;
        case APS_ALPHA_VERSION:
          MsgText << "  " << GetModuleName() << " " << GetX_Version() << "." <<
                             GetY_Version() << "." << GetZ_Version() << " ALPHA " <<
                             GetFirstCopyRightYear() << " - " << GetCopyRightYear() << std::endl;
          break;
        default:
          MsgText << "  " << GetModuleName() << " " << GetX_Version() << "." <<
                             GetY_Version() << "." << GetZ_Version() << " " <<
                             GetFirstCopyRightYear() << " - " << GetCopyRightYear() << std::endl;
      }
    break;
    case 1:
      switch( VersionType ) {
        case APS_BETA_VERSION:
          MsgText << GetModuleName() << " " << GetX_Version() << "." <<
                     GetY_Version() << "." << GetZ_Version() << " BETA";
        break;
        case APS_ALPHA_VERSION:
          MsgText << GetModuleName() << " " << GetX_Version() << "." <<
                     GetY_Version() << "." << GetZ_Version() << " ALPHA";
          break;
        default:
          MsgText << GetModuleName() << " " << GetX_Version() << "." <<
                     GetY_Version() << "." << GetZ_Version();
      }
    break;
    default:;
  }

  Str = MsgText.str();
}

void APSMainModule :: ShowBanner( void ) const
{
  std::string InfoStr;

  GetModuleInfo( InfoStr );

  PutMessage( InfoStr );
}

}}

//---------------------------- End of file ---------------------------
