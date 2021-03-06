//------------------------------------------------------------------------------
//
// File:    loTychoReader.cc
//
// Purpose: Tycho2 star catalog reader for LinOccult.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 31.01.2004
//         version 0.2 10.06.2004 Mv has been added
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

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "APC_Const.h"
#include "APC_Math.h"

#include "loTychoReader.h"
#include "loData.h"
#include "loStarData.h"
#include "loModuleTychoReader.h"
#include "loTychoReadSubModule.h"

const int MAX_STR_LENGTH   = 1024;
const int SHOW_STAR_NUMBER = 100000;
const int MAX_MSG_LENGTH   = 1024;

LOTychoReader :: LOTychoReader( LOTychoReadSubModule * pLOTychoReadSubModule, const char * pTychoFilePath ) :
                 TychoReader( pTychoFilePath )
{
  pModule = new LOModuleTychoReader( pLOTychoReadSubModule );
}

LOTychoReader :: ~LOTychoReader( void )
{
  delete pModule;
}

int LOTychoReader :: Read( LOData * pLOData )
{
  int           RA;
  int           IfRA;
  float         pmRA;
  int           IfpmRA;
  int           Dec;
  int           IfDec;
  float         pmDec;
  int           IfpmDec;
  short         Parallax;
  int           IfParallax;
  short         Mv;
  int           IfMv;
  short         Mp;
  int           IfMp;
  unsigned char Catalogue;
  int           IfCatalogue;
  int           StarNumber;
  int           IfStarNumber;
  LOStarData  * pLOStarData;
  off_t         StarsNumber;
  float         Tmp1;
  float         Tmp2;
  char          Msg[ MAX_MSG_LENGTH ];
  int           Count;
  int           RetCode;

  RetCode = LO_TYCHO_READER_NO_ERROR;



  FILE * MySQL;

  MySQL = fopen( "Events.sql", "wt" );

  if( !MySQL ) {
    printf("ERROR: open MySQL\n");
    return( 1 );
  }




  if( !OpenFile() ) {
    Count = 0;

    if( GetStarsNumber( &StarsNumber ) ) {
      pModule->WarningMessage( LO_TYCHO_READER_FILE_LENGTH );
    }

    pLOStarData = pLOData->CreateStarData( StarsNumber );

    sprintf( Msg, "%d records.\n", StarsNumber );
    pModule->InfoMessage( LO_TYCHO_READER_START_READING, Msg );    

    while( !ReadStar() ) {
      Count++;

      if( !GetRA( &RA ) ) {
        IfRA = 1;
      }
      else {
        IfRA = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_RA, Msg );
      }

      if( !GetpmRA( &pmRA ) ) {
        IfpmRA = 1;
      }
      else {
        IfpmRA = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_PM_RA, Msg );
      }

      if( !GetDec( &Dec ) ) {
        IfDec = 1;
      }
      else {
        IfDec = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_DEC, Msg );
      }

      if( !GetpmDec( &pmDec ) ) {
        IfpmDec = 1;
      }
      else {
        IfpmDec = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_PM_DEC, Msg );
      }

      if( !GetParallax( &Parallax ) ) {
        IfParallax = 1;
      }
      else {
        IfParallax = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_PARALLAX, Msg );
      }

      if( !GetMv( &Mv ) ) {
        IfMv = 1;
      }
      else {
        IfMv = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_MV, Msg );
      }

      if( !GetMp( &Mp ) ) {
        IfMp = 1;
      }
      else {
        IfMp = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_MP, Msg );
      }

      if( !GetCatalogue( &Catalogue ) ) {
        IfCatalogue = 1;
      }
      else {
        IfCatalogue = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_CATALOGUE, Msg );
      }

      if( !GetStarCatalogNumber( &StarNumber ) ) {
        IfStarNumber = 1;
      }
      else {
        IfStarNumber = 0;
        sprintf( Msg, "Line %d\n", Count + 1 );
        pModule->WarningMessage( LO_TYCHO_READER_STAR_NUMBER, Msg );
      }

      if( !( Count % SHOW_STAR_NUMBER ) ) {
        pModule->StrMessage( LO_TYCHO_READER_PROGRESS );
      }

      if( IfRA && IfDec ) {
/*pLOStarData->CreateStar( 15 * Rad * Ddd( 10, 39, 26.917 ), 0.0,
                         Rad * Ddd( 7, 25, 38.39 ), 0.0, 
                         0.0, 0, 52164, 0 );
break;*/

/*if( ( Mv / 100.0 ) > 7.0 ) {
  continue;
}*/

        Tmp1 = Ddd( 0, 0, pmRA );
        Tmp2 = Ddd( 0, 0, pmDec );


fprintf( MySQL, "INSERT INTO occult.Tycho2 VALUES(%u,%d,%f,%d,%f,%d,%d,%d,%u,%u);\n",
        Count, RA, pmRA, Dec, pmDec, Parallax, Mv, Mp, Catalogue, StarNumber );


        if( !pLOStarData->CreateStar( Rad * ( 180.0 + ( RA / 10000000.0 ) ), Rad * Tmp1,
                                      Rad * Dec / 10000000.0, Rad * Tmp2, 
                                      Parallax / 10000.0, Catalogue, StarNumber, Mv ) ) {
          pModule->WarningMessage( LO_TYCHO_READER_TOO_MANY_STARS );
        }

/*if( StarNumber == 507201230 ) {
  printf("RA = %lf Dec = %lf m1 = %lf m2 =%lf\n", 180.0 + ( RA / 10000000.0 ), Tmp1, Dec / 10000000.0, Tmp2 );
}*/
      }
      else {
        pModule->WarningMessage( LO_TYCHO_READER_NOT_ENOUGH_DATA );
      } 
    }

    if( Count != StarsNumber ) {
      pModule->WarningMessage( LO_TYCHO_READER_WRONG_STARS_NUMBER );
    }

    CloseFile();

    pModule->StrMessage( LO_TYCHO_NEW_LINE );

    sprintf( Msg, "%d records.\n", Count );
    pModule->InfoMessage( LO_TYCHO_READER_FINISH_READING, Msg );
  }
  else {
    pModule->ErrorMessage( LO_TYCHO_OPEN_FILE );
    RetCode = LO_TYCHO_OPEN_FILE;
  }



  fclose( MySQL );



  return( RetCode );
}

