//------------------------------------------------------------------------------
//
// File:    loWriteEventData.cc
//
// Purpose: Class for writing occultation events data base for LinOccult.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 28.12.2004
//         version 0.2 13.02.2005 Storing events
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
#include <iomanip>

#include "apsobinfile.h"
#include "apsmodule.h"
#include "apsmainmodule.h"
#include "apstime.h"
#include "loData.h"
#include "loEventData.h"
#include "loEvent.h"
#include "loWriteEventData.h"
#include "loModuleEventDataWriter.h"
#include "loEventDataWriterSubModule.h"

namespace aps {

  namespace apslinoccult {

const int SHOW_EVENT_NUMBER   = 10000;

//======================= LOWriteEventData ==========================

LOWriteEventData :: LOWriteEventData( LOEventDataWriterSubModule * pLOEventDataWriterSubModule,
                                      const std::string & EventDataFileName ) : LOAbsEventDataIO()
{
  pModule     = new LOModuleEventDataWriter( pLOEventDataWriterSubModule );
  pOutputFile = new APSOBinFile( EventDataFileName );  
}

LOWriteEventData :: ~LOWriteEventData( void )
{
  delete pModule;
  delete pOutputFile;
}

bool LOWriteEventData :: WriteHeader( LOEventData * pLOEventData ) const
{
  const apslib::APSMainModule * pMainModule;
  int                           Version;
  int                           Length;
  int                           RecordsNumber;
  std::string                   ProgramName;
  bool                          RetCode;

  RetCode = pOutputFile->PutRecord( &LOAbsEventDataIO :: Descriptor, sizeof( LOAbsEventDataIO :: Descriptor ) );

  if( RetCode ) {
    pMainModule = pModule->FindMainModule();

    pMainModule->GetModuleInfo( ProgramName, 1 );

    Length = ProgramName.length();

    RetCode = pOutputFile->PutRecord( &Length, sizeof( Length ) );

    if( RetCode ) {
      RetCode = pOutputFile->PutRecord( ProgramName.c_str(), Length );

      if( RetCode ) {
        Version = FILE_VERSION_1; /* File version */

        RetCode = pOutputFile->PutRecord( &Version, sizeof( Version ) );

        if( RetCode ) {
          RecordsNumber = pLOEventData->GetEventsNumber();

          RetCode = pOutputFile->PutRecord( &RecordsNumber, sizeof( RecordsNumber ) );
        }
      }
    }
  }

  return( RetCode );
}

bool LOWriteEventData :: WriteEvent( LOEvent * pEvent, int & Count, const double MjdStart, const double MjdEnd ) const
{
  int            i;
  int            AsteroidID;
  std::string    AsteroidName;
  double         Diameter;
  double         EphemerisUncertainty;
  double         ObservationEpoch;
  double         M;
  double         W;
  double         O;
  double         I;
  double         E;
  double         A;
  unsigned char  Catalog;
  int            StarNumber;
  short          Mv;
  short          ChebOrder;
  const double * cX;
  const double * cY;
  const double * cZ;
  double         ET_UT;
  double         BeginOccTime;
  double         EndOccTime;
  int            EarthFlag;
  double         MaxDuration;
  double         StarRA;
  double         StarDec;
  double         MoonPhase;
  double         SunDist;
  double         MoonDist;
  double         Brightness;
  double         BrightDelta;
  double         Uncertainty;
  int            Length;

  if( IfInInterval( MjdStart, MjdEnd, pEvent->GetBeginOccTime(), pEvent->GetEndOccTime() ) ) {

    //---------------- AsteroidID -----------------

    AsteroidID = pEvent->GetAsteroidID();

    if( !pOutputFile->PutRecord( &AsteroidID, sizeof( AsteroidID ) ) ) {
      return( false );
    }

    //---------------- AsteroidName -----------------

    AsteroidName = pEvent->GetAsteroidNamePtr();

    Length = AsteroidName.length();

    if( !pOutputFile->PutRecord( &Length, sizeof( Length ) ) ) {
      return( false );
    }

    if( !pOutputFile->PutRecord( AsteroidName.c_str(), Length ) ) {
      return( false );
    }

    //---------------- Diameter -----------------

    Diameter = pEvent->GetDiameter();

    if( !pOutputFile->PutRecord( &Diameter, sizeof( Diameter ) ) ) {
      return( false );
    }

    //---------------- EphemerisUncertainty -----------------

    EphemerisUncertainty = pEvent->GetEphemerisUncertainty();

    if( !pOutputFile->PutRecord( &EphemerisUncertainty, sizeof( EphemerisUncertainty ) ) ) {
      return( false );
    }

    //---------------- ObservationEpoch -----------------

    ObservationEpoch = pEvent->GetObservationEpoch();

    if( !pOutputFile->PutRecord( &ObservationEpoch, sizeof( ObservationEpoch ) ) ) {
      return( false );
    }

    //---------------- M -----------------

    M = pEvent->GetM();

    if( !pOutputFile->PutRecord( &M, sizeof( M ) ) ) {
      return( false );
    }

    //---------------- W -----------------

    W = pEvent->GetW();

    if( !pOutputFile->PutRecord( &W, sizeof( W ) ) ) {
      return( false );
    }

    //---------------- O -----------------

    O = pEvent->GetO();

    if( !pOutputFile->PutRecord( &O, sizeof( O ) ) ) {
      return( false );
    }

    //---------------- I -----------------

    I = pEvent->GetI();

    if( !pOutputFile->PutRecord( &I, sizeof( I ) ) ) {
      return( false );
    }

    //---------------- E -----------------

    E = pEvent->GetE();

    if( !pOutputFile->PutRecord( &E, sizeof( E ) ) ) {
      return( false );
    }

    //---------------- A -----------------

    A = pEvent->GetA();

    if( !pOutputFile->PutRecord( &A, sizeof( A ) ) ) {
      return( false );
    }

    //---------------- Catalog -----------------

    Catalog = pEvent->GetCatalog();

    if( !pOutputFile->PutRecord( &Catalog, sizeof( Catalog ) ) ) {
      return( false );
    }

    //---------------- StarNumber -----------------

    StarNumber = pEvent->GetStarNumber();

    if( !pOutputFile->PutRecord( &StarNumber, sizeof( StarNumber ) ) ) {
      return( false );
    }

    //---------------- Mv -----------------

    Mv = pEvent->GetMv();

    if( !pOutputFile->PutRecord( &Mv, sizeof( Mv ) ) ) {
      return( false );
    }

    //---------------- ChebOrder -----------------

    ChebOrder = pEvent->GetChebOrder();

    if( !pOutputFile->PutRecord( &ChebOrder, sizeof( ChebOrder ) ) ) {
      return( false );
    }

    //---------------- cX -----------------

    cX = pEvent->GetcX();

    for( i = 0; i <= ChebOrder; i++ ) {
      if( !pOutputFile->PutRecord( &cX[ i ], sizeof( cX[ 0 ] ) ) ) {
        return( false );
      }
    }

    //---------------- cY -----------------

    cY = pEvent->GetcY();

    for( i = 0; i <= ChebOrder; i++ ) {
      if( !pOutputFile->PutRecord( &cY[ i ], sizeof( cY[ 0 ] ) ) ) {
        return( false );
      }
    }

    //---------------- cZ -----------------

    cZ = pEvent->GetcZ();

    for( i = 0; i <= ChebOrder; i++ ) {
      if( !pOutputFile->PutRecord( &cZ[ i ], sizeof( cZ[ 0 ] ) ) ) {
        return( false );
      }
    }

    //---------------- ET_UT -----------------

    ET_UT = pEvent->GetET_UT();

    if( !pOutputFile->PutRecord( &ET_UT, sizeof( ET_UT ) ) ) {
      return( false );
    }

    //---------------- BeginOccTime -----------------

    BeginOccTime = pEvent->GetBeginOccTime();

    if( !pOutputFile->PutRecord( &BeginOccTime, sizeof( BeginOccTime ) ) ) {
      return( false );
    }

    //---------------- EndOccTime -----------------

    EndOccTime = pEvent->GetEndOccTime();

    if( !pOutputFile->PutRecord( &EndOccTime, sizeof( EndOccTime ) ) ) {
      return( false );
    }

    //---------------- EarthFlag -----------------

    EarthFlag = pEvent->GetEarthFlag();

    if( !pOutputFile->PutRecord( &EarthFlag, sizeof( EarthFlag ) ) ) {
      return( false );
    }

    //---------------- MaxDuration -----------------

    MaxDuration = pEvent->GetMaxDuration();

    if( !pOutputFile->PutRecord( &MaxDuration, sizeof( MaxDuration ) ) ) {
      return( false );
    }

    //---------------- StarRA -----------------

    StarRA = pEvent->GetStarRA();

    if( !pOutputFile->PutRecord( &StarRA, sizeof( StarRA ) ) ) {
      return( false );
    }

    //---------------- StarDec -----------------

    StarDec = pEvent->GetStarDec();

    if( !pOutputFile->PutRecord( &StarDec, sizeof( StarDec ) ) ) {
      return( false );
    }

    //---------------- MoonPhase -----------------

    MoonPhase = pEvent->GetMoonPhase();

    if( !pOutputFile->PutRecord( &MoonPhase, sizeof( MoonPhase ) ) ) {
      return( false );
    }

    //---------------- SunDist -----------------

    SunDist = pEvent->GetSunDist();

    if( !pOutputFile->PutRecord( &SunDist, sizeof( SunDist ) ) ) {
      return( false );
    }

    //---------------- MoonDist -----------------

    MoonDist = pEvent->GetMoonDist();

    if( !pOutputFile->PutRecord( &MoonDist, sizeof( MoonDist ) ) ) {
      return( false );
    }

    //---------------- Brightness -----------------

    Brightness = pEvent->GetBrightness();

    if( !pOutputFile->PutRecord( &Brightness, sizeof( Brightness ) ) ) {
      return( false );
    }

    //---------------- BrightDelta -----------------

    BrightDelta = pEvent->GetBrightDelta();

    if( !pOutputFile->PutRecord( &BrightDelta, sizeof( BrightDelta ) ) ) {
      return( false );
    }

    //---------------- Uncertainty -----------------

    Uncertainty = pEvent->GetUncertainty();

    if( !pOutputFile->PutRecord( &Uncertainty, sizeof( Uncertainty ) ) ) {
      return( false );
    }

    Count++;
  }

  return( true );
}

int LOWriteEventData :: Write( LOData * pLOData )
{
  unsigned int   i;
  int            Count;
  LOEventData  * pLOEventData;
  LOEvent      * pEvent;
  double         MjdStart;
  double         MjdEnd;
  int            RetCode = LO_EVENT_DATA_WRITER_NO_ERROR;

  pLOEventData = pLOData->GetEventDataPtr();

  if( pOutputFile->Open() ) {
    if( WriteHeader( pLOEventData ) ) {
      {
      std::ostringstream Msg;
      Msg << pLOEventData->GetEventsNumber() << " records. Start data " << pModule->GetStartYear() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetStartMonth() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetStartDay() <<
             " End data " << pModule->GetEndYear() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetEndMonth() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetEndDay() << "." << std::endl;

      pModule->InfoMessage( LO_EVENT_DATA_WRITER_START_WRITING, Msg.str() );
      }

      MjdStart = apsastroalg::Mjd( pModule->GetStartYear(), pModule->GetStartMonth(), pModule->GetStartDay() );
      MjdEnd = apsastroalg::Mjd( pModule->GetEndYear(), pModule->GetEndMonth(), pModule->GetEndDay() ) + 1.0;

      Count = 0;

      for( i = 0; i < pLOEventData->GetEventsNumber(); i++ ) {
        pEvent = pLOEventData->GetEventPtr( i );

        RetCode = WriteEvent( pEvent, Count, MjdStart, MjdEnd );

        if( !RetCode ) {
          pModule->ErrorMessage( LO_EVENT_DATA_WRITER_EVENT );
          RetCode = LO_EVENT_DATA_WRITER_EVENT;
          break;
        }

        if( !( i % SHOW_EVENT_NUMBER ) ) {
          pModule->StrMessage( LO_EVENT_DATA_WRITER_PROGRESS );
        }
      }

      pModule->StrMessage( LO_EVENT_DATA_WRITER_NEW_LINE );

      {
      std::ostringstream Msg;
      Msg << Count << " records." << std::endl;
      pModule->InfoMessage( LO_EVENT_DATA_WRITER_FINISH_WRITING, Msg.str() );
      }
    }
    else {
      pModule->ErrorMessage( LO_EVENT_DATA_WRITER_HEADER );
      RetCode = LO_EVENT_DATA_WRITER_HEADER;
    }

    pOutputFile->Close();
  }
  else {
    pModule->ErrorMessage( LO_EVENT_DATA_WRITER_OPEN_FILE );
    RetCode = LO_EVENT_DATA_WRITER_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
