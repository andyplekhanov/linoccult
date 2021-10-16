//------------------------------------------------------------------------------
//
// File:    loAppl.cc
//
// Purpose: Asteroids occultation program for Linux
//          Implementation of the LinOccult application
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.01.2004
//         version 0.2 24.05.2004 linoccult version 0.1.1 beta
//         version 0.3 10.06.2004 linoccult version 0.2.0 beta
//         version 0.4 18.12.2004 linoccult version 0.3.0 beta
//         version 1.0 13.01.2005 linoccult version 1.0.0 beta
//         version 1.1 24.01.2005 ReRun was added
//         version 1.2 31.01.2005 CalculationMode was added
//         version 1.3 08.02.2005 EventDataWriter was added
//         version 1.4 13.02.2005 EventDataReader was added
//         version 1.5 22.02.2005 ReadEvents, WriteEvents were added
//         version 1.6 27.02.2005 LOPointEventData, WritePositions were added
//         version 1.7 15.03.2005 Sites reading was added
//         version 1.8 21.03.2005 linoccult version 1.0.1 beta
//         version 1.9 17.04.2005 Updates reading was added. linoccult version 1.1.0 beta
//         version 1.10 14.10.2005 linoccult version 1.1.0
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

#include "loAppl.h"
#include "loData.h"
#include "loAstOrbReader.h"
#include "loGaiaReader.h"
#include "loWriteEventData.h"
#include "loWritePositionData.h"
#include "loReadEventData.h"
#include "loReadSitesData.h"
#include "loReadUpdatesData.h"
#include "loCalc.h"
#include "loModuleAppl.h"

namespace aps {

  namespace apslinoccult {

static const int X_Version                    = 2;
static const int Y_Version                    = 4;
static const int Z_Version                    = 0;
static const int FirstCopyRightYear           = 2004;
static const int CopyRightYear                = 2021;
static const apslib::APS_PROGRAM_VERSION_TYPE VersionType = apslib::APS_BETA_VERSION; //apslib::APS_BETA_VERSION;

//======================= LinOccultAppl ==========================

LinOccultAppl :: LinOccultAppl( const std::string & ProjectFilePath )
{
  pModule = new LOModuleAppl( ProjectFilePath, "LinOccult", X_Version, Y_Version, Z_Version, FirstCopyRightYear, CopyRightYear, VersionType );
}

LinOccultAppl :: ~LinOccultAppl( void )
{
  delete pModule;
}

int LinOccultAppl :: ReadUpdates( LOData * pLOData ) const
{
  LOReadUpdatesData * pLOReadUpdatesData;
  int                 RetCode = 0;

  if( pModule->IfUpdatesFilePath() ) {
    pLOReadUpdatesData = new LOReadUpdatesData( pModule->GetUpdatesDataReaderSubModulePtr(), pModule->GetUpdatesFilePath() );

    RetCode = pLOReadUpdatesData->Read( pLOData );

    delete pLOReadUpdatesData;
  }
  else {
    pLOData->CreateUpdateData();
  }

  return( RetCode );
}

int LinOccultAppl :: ReadSites( LOData * pLOData ) const
{
  LOReadSitesData * pLOReadSitesData;
  int               RetCode = 0;

  if( pModule->IfSitesFilePath() ) {
    pLOReadSitesData = new LOReadSitesData( pModule->GetSitesDataReaderSubModulePtr(), pModule->GetSitesFilePath() );

    RetCode = pLOReadSitesData->Read( pLOData );

    delete pLOReadSitesData;
  }
  else {
    pLOData->CreatePosData();
  }

  return( RetCode );
}

int LinOccultAppl :: ReadEvents( LOData * pLOData ) const
{
  LOReadEventData * pLOReadEventData;
  int               RetCode = 0;

  if( pModule->IfInputEventsFilePath() ) {
    pLOReadEventData = new LOReadEventData( pModule->GetEventDataReaderSubModulePtr(), pModule->GetInputEventsFilePath() );

    RetCode = pLOReadEventData->Read( pLOData );

    delete pLOReadEventData;
  }
  else {
    pLOData->CreateEventData();
  }

  return( RetCode );
}

int LinOccultAppl :: WriteEvents( LOData * pLOData ) const
{
  LOWriteEventData * pLOWriteEventData;
  int                RetCode = 0;

  if( pModule->IfOutputEventsFilePath() ) {
    pLOWriteEventData = new LOWriteEventData( pModule->GetEventDataWriterSubModulePtr(), pModule->GetOutputEventsFilePath() );

    RetCode = pLOWriteEventData->Write( pLOData );

    delete pLOWriteEventData;
  }

  return( RetCode );
}

int LinOccultAppl :: WritePositions( LOData * pLOData ) const
{
  LOWritePositionData * pLOWritePositionData;
  int                   RetCode = 0;

  pLOWritePositionData = new LOWritePositionData( pModule->GetEventPosWriterSubModulePtr() );

  RetCode = pLOWritePositionData->Write( pLOData );

  delete pLOWritePositionData;

  return( RetCode );
}

int LinOccultAppl :: Run( void )
{
  LOAstOrbReader   * pLOAstOrbReader;
  LOGaiaReader     * pLOGaiaReader;
  LOCalc           * pLOCalc;
  LOData           * pLOData;
  int                RetCode;

  RetCode = pModule->Run();

  if( !RetCode ) {
    pLOData = new LOData();

    pLOData->CreatePointEventData();

    RetCode = ReadEvents( pLOData );

    if( !RetCode ) {
      RetCode = ReadSites( pLOData );

      if( !RetCode ) {
        RetCode = ReadUpdates( pLOData ); // Must be before LOAstOrbReader

        if( !RetCode ) {
          if( pModule->GetCalculationMode() ) {
            pLOAstOrbReader = new LOAstOrbReader( pModule->GetAstOrbReadSubModulePtr(), pModule->GetAstOrbFilePath() );

            RetCode = pLOAstOrbReader->Read( pLOData );

            if( !RetCode ) {
              pLOGaiaReader = new LOGaiaReader( pModule->GetGaiaReadSubModulePtr(), pModule->GetStarCatalogFilePath() );

              RetCode = pLOGaiaReader->Read( pLOData );
	      
              if( !RetCode ) {
                pLOCalc = new LOCalc( pModule->GetCalcSubModulePtr() );

                RetCode = pLOCalc->Run( pLOData );

                if( !RetCode ) {

                }
                else {
                  RetCode = LO_APPL_CALC;
                }

                delete pLOCalc;
              }
              else {
                RetCode = LO_APPL_GAIA_READ;
              }

	      delete pLOGaiaReader;
            }
            else {
              RetCode = LO_APPL_AST_ORB_READ;
            }

            delete pLOAstOrbReader;
          }
          else {
            pLOCalc = new LOCalc( pModule->GetCalcSubModulePtr() );

            RetCode = pLOCalc->ReRun( pLOData );

            if( !RetCode ) {
              RetCode = WritePositions( pLOData );

              if( RetCode ) {
                RetCode = LO_APPL_WRITE_POSITIONS_DATA;
              }
            }
            else {
              RetCode = LO_APPL_CALC;
            }

            delete pLOCalc;
          }

          if( !RetCode ) {
            RetCode = WriteEvents( pLOData );

            if( RetCode ) {
              RetCode = LO_APPL_WRITE_EVENT_DATA;
            }
          }
        }
        else {
          RetCode = LO_APPL_READ_UPDATES_DATA;
        }
      }
      else {
        RetCode = LO_APPL_READ_SITES_DATA;
      }
    }
    else {
      RetCode = LO_APPL_READ_EVENT_DATA;
    }

    delete pLOData;
  }
  else {
    RetCode = LO_APPL_MODULE;    
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
