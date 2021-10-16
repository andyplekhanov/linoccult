//------------------------------------------------------------------------------
//
// File:    loGaiaReader.cc
//
// Purpose: Gaia star catalog reader for LinOccult.
//   
// (c) 2004-2021 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
// Gaia EDR3       0.2 10.01.2021
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
#include <iostream>
#include <iomanip>

#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsangle.h"
#include "apsvec3d.h"
#include "apsprecnut.h"

#include "loGaiaReader.h"
#include "loData.h"
#include "loStarData.h"
#include "loModuleGaiaReader.h"
#include "loGaiaReadSubModule.h"

namespace aps {

  namespace apslinoccult {

const int SHOW_STAR_NUMBER = 100000;

LOGaiaReader :: LOGaiaReader( LOGaiaReadSubModule * pLOGaiaReadSubModule, const std::string & GaiaFilePath ) :
                              GaiaEDR3Reader( GaiaFilePath )
{
  pModule = new LOModuleGaiaReader( pLOGaiaReadSubModule );
}

LOGaiaReader :: ~LOGaiaReader( void )
{
  delete pModule;
}

int LOGaiaReader :: Read( LOData * pLOData )
{
  const double  UasPerDeg = 3600000000.0;
  int32_t       RA;
  bool          IfRA;
  unsigned char RA2;
  int32_t       Dec;
  bool          IfDec;
  unsigned char Dec2;
  uint16_t      Parallax;
  int32_t       pmRA;
  int32_t       pmDec;
  int16_t       Vrad;
  uint16_t      Epoch;
  double        epoch;
  int16_t       Mv;
  unsigned char Catalogue;
  uint32_t      StarNumber;
  LOStarData  * pLOStarData;
  off_t         StarsNumber;
  float         Tmp1;
  float         Tmp2;
  float         Tmp3;
  int           Count;
  int           RetCode = LO_GAIA_READER_NO_ERROR;

  if( pModule->GetIfOneStar() ) {
    pLOStarData = pLOData->CreateStarData( 1 );

    if( pLOStarData->CreateStar( 15 * apsmathlib::Rad * apsmathlib::Ddd( pModule->GetRA_Hour(), pModule->GetRA_Min(), pModule->GetRA_Sec() ),
                                 apsmathlib::Rad * apsmathlib::Ddd( 0, 0, pModule->GetpmRA() ),
                                 apsmathlib::Rad * apsmathlib::Ddd( pModule->GetDec_Deg(), pModule->GetDec_Min(), pModule->GetDec_Sec() ),
                                 apsmathlib::Rad * apsmathlib::Ddd( 0, 0, pModule->GetpmDec() ), 
                                 apsmathlib::Rad * apsmathlib::Ddd( 0, 0, pModule->GetOneStarParallax() ),
				 pModule->GetVrad(), pModule->GetEpoch(),
				 pModule->GetOneStarCatalog(),
                                 pModule->GetIfOneStar(), static_cast<short>( pModule->GetOneStarMv() * 100.0 ) ) ) {
      std::cout << "RA = " << std::fixed << pModule->GetRA_Hour() << " " << std::fixed << pModule->GetRA_Min() << " " <<
                   std::fixed << std::setw( 5 ) << std::setprecision( 3 ) << pModule->GetRA_Sec() <<
                   " pmRA = " << std::fixed << std::setw( 12 ) << std::setprecision( 10 ) << pModule->GetpmRA() <<
                   " Dec = " << pModule->GetDec_Deg() << " " << pModule->GetDec_Min() << " " <<
                   std::fixed << std::setw( 5 ) << std::setprecision( 3 ) << pModule->GetDec_Sec() <<
                   " pmDec = " << std::fixed << std::setw( 12 ) << std::setprecision( 10 ) << pModule->GetpmDec() << std::endl;
    }
    else {
      pModule->WarningMessage( LO_GAIA_READER_TOO_MANY_STARS );
      RetCode = LO_GAIA_READER_TOO_MANY_STARS;
    }

    return( RetCode );
  }

  if( Open() ) {
    Count = 0;

    StarsNumber = 0;

    if( GetStarsNumber( StarsNumber ) ) {
      pModule->WarningMessage( LO_GAIA_READER_FILE_LENGTH );
    }

    pLOStarData = pLOData->CreateStarData( StarsNumber );

    {
    std::ostringstream Msg;
    Msg << StarsNumber << " records." << std::endl;
    pModule->InfoMessage( LO_GAIA_READER_START_READING, Msg.str() );
    }

    while( ReadStar() ) {
      Count++;

      if( !GetRA( RA ) ) {
        IfRA = true;
      }
      else {
	RA = 0;
        IfRA = false;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_RA, Msg.str() );
      }

      if( !GetRA2( RA2 ) ) {
      }
      else {
	RA2 = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_RA2, Msg.str() );
      }

      double ra = ( static_cast<double>(RA) * 1000.0 + static_cast<double>(RA2) * 4 ) / UasPerDeg;         // ra in deg

      if( !GetDec( Dec ) ) {
        IfDec = true;
      }
      else {
	Dec = 0;
        IfDec = false;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_DEC, Msg.str() );
      }

      if( !GetDec2( Dec2 ) ) {
      }
      else {
	Dec2 = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_DEC2, Msg.str() );
      }

      double dec = ( static_cast<double>(Dec) * 1000.0 + static_cast<double>(Dec2) * 4 ) / UasPerDeg;         // dec in deg

      if( !GetParallax( Parallax ) ) {
      }
      else {
	Parallax = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_PARALLAX, Msg.str() );
      }

      double parallax = static_cast<double>(Parallax) * 0.0000125;           // parallax in as
      
      if( !GetpmRA( pmRA ) ) {
      }
      else {
	pmRA = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_PM_RA, Msg.str() );
      }

      double pmra = static_cast<double>(pmRA) / 1000000.0;            // pmra in as/yr

      if( !GetpmDec( pmDec ) ) {
      }
      else {
	pmDec = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_PM_DEC, Msg.str() );
      }

      double pmdec = static_cast<double>(pmDec) / 1000000.0;            // pmdec in as/yr

      if( !GetVrad( Vrad ) ) {
      }
      else {
	Vrad = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_VRAD, Msg.str() );
      }
      
      if( !GetEpoch( Epoch ) ) {
      }
      else {
	Epoch = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_EPOCH, Msg.str() );
      }

      epoch = static_cast<double>( Epoch ) * apsastroalg::JYEAR / 1000.0; 
      
      if( !GetMagGreen( Mv ) ) {
      }
      else {
	Mv = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_MV, Msg.str() );
      }

      short mag_green = Mv / 10;

      if( !GetCatID( Catalogue ) ) {
      }
      else {
	Catalogue = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_CATALOGUE, Msg.str() );
      }

      if( !GetCatNum( StarNumber ) ) {
      }
      else {
	StarNumber = 0;
        std::ostringstream Msg;
        Msg << "Line " << Count + 1 << std::endl;
        pModule->WarningMessage( LO_GAIA_READER_STAR_NUMBER, Msg.str() );
      }

      if( !( Count % SHOW_STAR_NUMBER ) ) {
        pModule->StrMessage( LO_GAIA_READER_PROGRESS );
      }
      
      if( IfRA && IfDec ) {
        if( ( mag_green / 100.0 ) > pModule->GetMaxMv() ) {
          continue;
        }
	
        Tmp1 = apsmathlib::Ddd( 0, 0, pmra );
        Tmp2 = apsmathlib::Ddd( 0, 0, pmdec );
        Tmp3 = apsmathlib::Ddd( 0, 0, parallax );

        if( !pLOStarData->CreateStar( apsmathlib::Rad * ra, apsmathlib::Rad * Tmp1,
                                      apsmathlib::Rad * dec, apsmathlib::Rad * Tmp2, 
                                      apsmathlib::Rad * Tmp3, static_cast<float>( Vrad ),
				      epoch + apsastroalg::MJD_J2000, Catalogue, StarNumber, mag_green ) ) {
          pModule->WarningMessage( LO_GAIA_READER_TOO_MANY_STARS );
	}
      }
      else {
        pModule->WarningMessage( LO_GAIA_READER_NOT_ENOUGH_DATA );
      }
    }

    if( Count != StarsNumber ) {
      pModule->WarningMessage( LO_GAIA_READER_WRONG_STARS_NUMBER );
    }

    Close();

    pModule->StrMessage( LO_GAIA_NEW_LINE );

    std::ostringstream Msg;
    Msg << Count << " records." << std::endl;
    pModule->InfoMessage( LO_GAIA_READER_FINISH_READING, Msg.str() );
  }
  else {
    pModule->ErrorMessage( LO_GAIA_OPEN_FILE );
    RetCode = LO_GAIA_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
