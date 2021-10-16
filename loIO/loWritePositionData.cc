//------------------------------------------------------------------------------
//
// File:    loWritePositionData.cc
//
// Purpose: Class for writing position events data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 27.02.2005
//         version 0.2 26.03.2005 Elev -> Alt, hms, Uncert -> sigma
//         version 0.3 20.04.2005 HTML output
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

#include <limits>
#include <sstream>
#include <iomanip>

#include "apsostrfile.h"
#include "apsmodule.h"
#include "apsmainmodule.h"
#include "apsmathconst.h"
#include "apsangle.h"
#include "apstime.h"
#include "loData.h"
#include "loPosData.h"
#include "loStarData.h"
#include "loEvent.h"
#include "loPos.h"
#include "loPointEvent.h"
#include "loWritePositionData.h"
#include "loModuleEventPosWriter.h"
#include "loEventPosWriterSubModule.h"

namespace aps {

  namespace apslinoccult {

const int PDF_PAGE_SIZE      = 20;

//========================= PointEventSort =============================

PointEventSort :: PointEventSort( void ) : APSSort()
{
}

PointEventSort :: ~PointEventSort( void )
{
}

int PointEventSort :: Compare( const void * pPtr1, const void * pPtr2, const int Type ) const
{
  const LOPointEvent * pPointEvent1;
  const LOPointEvent * pPointEvent2;
  const LOEvent      * pLOEvent1;
  const LOEvent      * pLOEvent2;
  int                  RetCode;

  pPointEvent1 = static_cast<const LOPointEvent *>( pPtr1 );
  pPointEvent2 = static_cast<const LOPointEvent *>( pPtr2 );

  pLOEvent1 = pPointEvent1->GetLOEventPtr();
  pLOEvent2 = pPointEvent2->GetLOEventPtr();

  RetCode = 0;

  switch( Type ) {
    case PE_SORT_BY_DATE:
      if( pPointEvent1->GetMjdate() > pPointEvent2->GetMjdate() ) {
        RetCode = 1;
      }
      else {
        if( pPointEvent1->GetMjdate() < pPointEvent2->GetMjdate() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_NUMBER:
      if( pLOEvent1->GetAsteroidID() > pLOEvent2->GetAsteroidID() ) {
        RetCode = 1;
      }
      else {
        if( pLOEvent1->GetAsteroidID() < pLOEvent2->GetAsteroidID() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_DROP:
      if( pLOEvent1->GetBrightDelta() > pLOEvent2->GetBrightDelta() ) {
        RetCode = 1;
      }
      else {
        if( pLOEvent1->GetBrightDelta() < pLOEvent2->GetBrightDelta() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_DISTANCE:
      if( pPointEvent1->GetDistance() > pPointEvent2->GetDistance() ) {
        RetCode = 1;
      }
      else {
        if( pPointEvent1->GetDistance() < pPointEvent2->GetDistance() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_DURATION:
      if( pLOEvent1->GetMaxDuration() > pLOEvent2->GetMaxDuration() ) {
        RetCode = 1;
      }
      else {
        if( pLOEvent1->GetMaxDuration() < pLOEvent2->GetMaxDuration() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_PROB:
      if( pPointEvent1->GetProbability() > pPointEvent2->GetProbability() ) {
        RetCode = 1;
      }
      else {
        if( pPointEvent1->GetProbability() < pPointEvent2->GetProbability() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_CPROB:
      if( pPointEvent1->GetMaxProbability() > pPointEvent2->GetMaxProbability() ) {
        RetCode = 1;
      }
      else {
        if( pPointEvent1->GetMaxProbability() < pPointEvent2->GetMaxProbability() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_MAG:
      if( pLOEvent1->GetMv() > pLOEvent2->GetMv() ) {
        RetCode = 1;
      }
      else {
        if( pLOEvent1->GetMv() < pLOEvent2->GetMv() ) {
          RetCode = -1;
        }
      }
    break;
    case PE_SORT_BY_UNCERT:
      if( pLOEvent1->GetUncertainty() > pLOEvent2->GetUncertainty() ) {
        RetCode = 1;
      }
      else {
        if( pLOEvent1->GetUncertainty() < pLOEvent2->GetUncertainty() ) {
          RetCode = -1;
        }
      }
    break;
    default:
      if( pPointEvent1->GetMjdate() > pPointEvent2->GetMjdate() ) {
        RetCode = 1;
      }
      else {
        if( pPointEvent1->GetMjdate() < pPointEvent2->GetMjdate() ) {
          RetCode = -1;
        }
      }
    break;
  }

  return( RetCode );
}

//======================= LOWritePositionData ==========================

LOWritePositionData :: LOWritePositionData( LOEventPosWriterSubModule * pLOEventPosWriterSubModule )
{
  pModule = new LOModuleEventPosWriter( pLOEventPosWriterSubModule );
}

LOWritePositionData :: ~LOWritePositionData( void )
{
  delete pModule;
}

const std::string LOWritePositionData :: GetSortName( const int Type ) const
{
  switch( Type ) {
    case PE_SORT_BY_DATE:
      return("Sorted by date/time.");
    case PE_SORT_BY_NUMBER:
      return("Sorted by asteroid number.");
    case PE_SORT_BY_DROP:
      return("Sorted by mag. drop.");
    case PE_SORT_BY_DISTANCE:
      return("Sorted by distance.");
    case PE_SORT_BY_DURATION:
      return("Sorted by duration.");
    case PE_SORT_BY_PROB:
      return("Sorted by probability.");
    case PE_SORT_BY_CPROB:
      return("Sorted by probability in nearest point.");
    case PE_SORT_BY_MAG:
      return("Sorted by star magnitude.");
    case PE_SORT_BY_UNCERT:
      return("Sorted by uncertenty.");
    default:;
  }

  return("Unknown sort type.");
}

int LOWritePositionData :: WriteMainTextHeader( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                                const unsigned int Number ) const
{
  int    D1;
  int    M1;
  double S1;
  int    D2;
  int    M2;
  double S2;
  int    RetCode = LO_EVENT_POS_WRITER_NO_ERROR;

  std::ostringstream Msg;
  Msg << "Observation point: " << pLOPos->GetObsNamePtr() << " EMail: " << pLOPos->GetEMail() << std::endl;

  if( pOutputFile->PutStr( Msg.str() ) ) {
    apsmathlib::DMS( pLOPos->GetObserverLongitude(), D1, M1, S1 );
    apsmathlib::DMS( pLOPos->GetObserverLatitude(), D2, M2, S2 );

    Msg.str("");
    Msg << "Longitude = " << std::fixed << std::setw( 7 ) << std::setprecision( 3 ) << pLOPos->GetObserverLongitude() <<
           " (" << D1 << "o" << std::setw( 2 ) << std::setfill( '0' ) << M1 <<
           "'" << std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << std::setfill( '0' ) << S1 <<
           "\") Latitude = " << std::setfill( ' ' ) << std::fixed << std::setw( 7 ) << std::setprecision( 3 ) << pLOPos->GetObserverLatitude() <<
           " (" << D2 << "o" << std::setw( 2 ) << std::setfill( '0' ) << M2 <<
           "'" << std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << std::setfill( '0' ) << S2 << "\")" << std::endl;

    if( pOutputFile->PutStr( Msg.str() ) ) {
      Msg.str("");
      Msg << "Maximal Distance = " << std::setfill( ' ' ) << std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOPos->GetMaxDistance() << std::endl;

      if( pOutputFile->PutStr( Msg.str() ) ) {
        if( pLOPos->GetMaxMv() != std::numeric_limits<float>::max() ) {
          Msg.str("");
          Msg << "Maximal Mv = " << std::setfill( ' ' ) << std::fixed << std::setw( 5 ) << std::setprecision( 2 ) << pLOPos->GetMaxMv() << std::endl;
          pOutputFile->PutStr( Msg.str() );
        }

        Msg.str("");
        Msg << "Minimal Duration = " << std::setfill( ' ' ) << std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOPos->GetMinDuration() << "s" << std::endl;

        if( pOutputFile->PutStr( Msg.str() ) ) {
          Msg.str("");
          Msg << "Maximal Sun Elevation = " << std::setfill( ' ' ) << std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetSunElev() << std::endl;

          if( pOutputFile->PutStr( Msg.str() ) ) {
            Msg.str("");
            Msg << "Minimal drop: " << std::setfill( ' ' ) << std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinDrop() << std::endl;

            if( pOutputFile->PutStr( Msg.str() ) ) {
              Msg.str("");
              Msg << "Minimal probability: " << std::setfill( ' ' ) << std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinProb() << std::endl;

              if( pOutputFile->PutStr( Msg.str() ) ) {
                Msg.str("");
                Msg << "Minimal probability in nearest point: " << std::setfill( ' ' ) << std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinCenterProb() << std::endl;

                if( pOutputFile->PutStr( Msg.str() ) ) {
                  Msg.str("");
                  Msg << "Minimal star elevation: " << std::setfill( ' ' ) << std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinStarElev() << std::endl;

                  if( pOutputFile->PutStr( Msg.str() ) ) {
                    Msg.str("");
                    Msg << "Program: " << ProgramName << std::endl << "Author: Plekhanov Andrey andyplekhanov@gmail.com" << std::endl;

                    if( pOutputFile->PutStr( Msg.str() ) ) {
                      Msg.str("");
                      Msg << "Events number: " << Number << std::endl << std::endl << std::endl;

                      if( pOutputFile->PutStr( Msg.str() ) ) {
                      }
                      else {
                        RetCode = 1;
                      }
                    }
                    else {
                      RetCode = 1;
                    }
                  }
                  else {
                    RetCode = 1;
                  }
                }
                else {
                  RetCode = 1;
                }
              }
              else {
                RetCode = 1;
              }
            }
            else {
              RetCode = 1;
            }
          }
          else {
            RetCode = 1;
          }
        }
        else {
          RetCode = 1;
        }
      }
      else {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteTextHeader( APSOStrFile * pOutputFile ) const
{
  int RetCode = 0;

  if( pOutputFile->PutStr("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n") ) {
    if( pOutputFile->PutStr("                    ============== Asteroid ===============       Min     Max        Nearest point                      Center  ===========================  Star ================================= ==== Sun === ====== Moon =======        \n") ) {   
      if( pOutputFile->PutStr("   Date      Time   Number       Name       Diam(km)  AMag.  Drop Dist(km)Durat(s)Longitude     Latitude Azimuth  Prob.  Prob.  Cat.  Number    SMag.        RA              Dec       Alt. Azimuth Dist.   Alt. Dist.   Alt.  Phase Uncert.\n") ) {
        if( pOutputFile->PutStr("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n") ) {
        }
        else {
          RetCode = 1;
        }
      }
      else {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteTextStr( const LOPointEvent * pLOPointEvent, APSOStrFile * pOutputFile ) const
{
  const LOEvent * pLOEvent;
  int             Year1;
  int             Month1;
  int             Day1;
  int             Hour1;
  int             Min1;
  double          Sec1;
  int             D1;
  int             M1;
  double          S1;
  int             D2;
  int             M2;
  double          S2;
  int             D3;
  int             M3;
  double          S3;
  int             D4;
  int             M4;
  double          S4;
  int             RetCode = 0;

  pLOEvent = pLOPointEvent->GetLOEventPtr();

  apsastroalg::CalDat( pLOPointEvent->GetMjdate(), Year1, Month1, Day1, Hour1, Min1, Sec1 );
  apsmathlib::DMS( apsmathlib::Deg * pLOEvent->GetStarRA() / 15.0, D1, M1, S1 );
  apsmathlib::DMS( apsmathlib::Deg * pLOEvent->GetStarDec(), D2, M2, S2 );
  apsmathlib::DMS( apsmathlib::Deg * pLOPointEvent->GetMaxLongitude(), D3, M3, S3 );
  apsmathlib::DMS( apsmathlib::Deg * pLOPointEvent->GetMaxLatitude(), D4, M4, S4 );

  std::ostringstream Msg;
  Msg << Year1 << "/" <<
         std::setw( 2 ) << std::setfill( '0' ) << Month1 << "/" << 
         std::setw( 2 ) << std::setfill( '0' ) << Day1 << " " <<
         std::setw( 2 ) << std::setfill( '0' ) << Hour1 << ":" <<
         std::setw( 2 ) << std::setfill( '0' ) << Min1 << ":" <<
         std::fixed << std::setw( 2 ) << std::setfill( '0' ) << std::setprecision( 0 ) << Sec1 << " " <<
         std::setw( 6 ) << std::setfill( ' ' ) << pLOEvent->GetAsteroidID() << " " <<
         std::setw( 18 ) << std::left << pLOEvent->GetAsteroidNamePtr() << " " <<
         std::fixed << std::setw( 6 ) << std::right << std::setprecision( 1 ) << pLOEvent->GetDiameter() << " " <<
         std::fixed << std::setw( 6 ) << std::setprecision( 2 ) << pLOEvent->GetBrightness() << " " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 2 ) << pLOEvent->GetBrightDelta() << " " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 0 ) << pLOPointEvent->GetDistance() << " " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOEvent->GetMaxDuration() << " " <<
         std::setw( 4 ) << D3 << "o" <<
         std::setw( 2 ) << std::setfill( '0' ) << M3 << "'" <<
         std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << std::setfill( '0' ) << S3 << "\" " <<
         std::setw( 4 ) << std::setfill( ' ' ) << D4 << "o" <<
         std::setw( 2 ) << std::setfill( '0' ) << M4 << "'" <<
         std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << std::setfill( '0' ) << S4 << "\" " <<
         std::fixed << std::setw( 6 ) << std::setfill( ' ' ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetAz() << " " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOPointEvent->GetProbability() << "% " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOPointEvent->GetMaxProbability() << "% " <<
         std::setw( 5 ) << LOStarData :: GetCatName( pLOEvent->GetCatalog() ) << " " <<
    //std::setw( 10 ) << std::left << pLOEvent->GetStarNumber() << " " <<
         LOStarData::GetStarName( pLOEvent->GetCatalog(), pLOEvent->GetStarNumber() ) << " " <<
         std::fixed << std::setw( 5 ) << std::right << std::setprecision( 2 ) << pLOEvent->GetMv() / 100.0 << " " <<
         std::setw( 4 ) << D1 << "h" <<
         std::setw( 2 ) << std::setfill( '0' ) << M1 << "m" <<
         std::fixed << std::setw( 6 ) << std::setfill( '0' ) << std::setprecision( 3 ) << S1 << "s " <<
         std::setw( 4 ) << std::setfill( ' ' ) << D2 << "o" <<
         std::setw( 2 ) << std::setfill( '0' ) << M2 << "'" <<
         std::fixed << std::setw( 6 ) << std::setfill( '0' ) << std::setprecision( 3 ) << S2 << "\" " <<
         std::fixed << std::setw( 5 ) << std::setfill( ' ' ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetStarElev() << " " <<
         std::fixed << std::setw( 7 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetStarAz() << " " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOEvent->GetSunDist() << " " <<
         std::fixed << std::setw( 6 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetSunElev() << " " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOEvent->GetMoonDist() << " " <<
         std::fixed << std::setw( 6 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetMoonElev() << " " <<
         std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOEvent->GetMoonPhase() << "% " <<
         std::fixed << std::setw( 7 ) << std::setprecision( 0 ) << pLOEvent->GetUncertainty() << std::endl;

  if( pOutputFile->PutStr( Msg.str() ) ) {
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteTextFooter( APSOStrFile * pOutputFile ) const
{
  int RetCode = 0;

  if( pOutputFile->PutStr("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n") ) {
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteTextTableBody( APSOStrFile * pOutputFile, const LOPointEvent ** ppLOPointEventArray,
                                               const unsigned int Number, const int Type ) const
{
  unsigned int   i;
  PointEventSort PointEventSorting;
  int            RetCode = 0;

  if( pOutputFile->PutStr( GetSortName( Type ) ) ) {
    if( pOutputFile->PutStr( "\n" ) ) {
      if( !WriteTextHeader( pOutputFile ) ) {
        PointEventSorting.Sort( reinterpret_cast<const void **>( ppLOPointEventArray ), Number, Type );

        for( i = 0; i < Number; i++ ) {
          if( WriteTextStr( ppLOPointEventArray[ i ], pOutputFile ) ) {
            RetCode = 1;
            break;
          }
        }

        if( !RetCode ) {
          RetCode = WriteTextFooter( pOutputFile );
        }
      }
      else {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteTextBody( const LOPos * pLOPos, APSOStrFile * pOutputFile,
                                          const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const
{
  int RetCode = 0;

  if( pLOPos->GetSort() & PE_SORT_BY_DATE ) {
    RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_DATE );
  }

  if( !RetCode ) {
    if( pLOPos->GetSort() & PE_SORT_BY_NUMBER ) {
      RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_NUMBER );
    }

    if( !RetCode ) {
      if( pLOPos->GetSort() & PE_SORT_BY_DROP ) {
        RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_DROP );
      }

      if( !RetCode ) {
        if( pLOPos->GetSort() & PE_SORT_BY_DISTANCE ) {
          RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_DISTANCE );
        }

        if( !RetCode ) {
          if( pLOPos->GetSort() & PE_SORT_BY_DURATION ) {
            RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_DURATION );
          }

          if( !RetCode ) {
            if( pLOPos->GetSort() & PE_SORT_BY_PROB ) {
              RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_PROB );
            }

            if( !RetCode ) {
              if( pLOPos->GetSort() & PE_SORT_BY_CPROB ) {
                RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_CPROB );
              }

              if( !RetCode ) {
                if( pLOPos->GetSort() & PE_SORT_BY_MAG ) {
                  RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_MAG );
                }

                if( !RetCode ) {
                  if( pLOPos->GetSort() & PE_SORT_BY_UNCERT ) {
                    RetCode = WriteTextTableBody( pOutputFile, ppLOPointEventArray, Number, PE_SORT_BY_UNCERT );
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return( RetCode );
}

int LOWritePositionData :: WriteMainTextFooter( const LOPos * pLOPos, APSOStrFile * pOutputFile ) const
{
  int RetCode;

  RetCode = 0;

  return( RetCode );
}

int LOWritePositionData :: WriteMainPDFHeader( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                               const unsigned int Number ) const
{
  int    D1;
  int    M1;
  double S1;
  int    D2;
  int    M2;
  double S2;
  int    RetCode = 0;

  std::ostringstream Msg;

  if( pOutputFile->PutStr("\\documentclass[10pt,a4paper]{article}\n") ) {
    if( pOutputFile->PutStr("\\usepackage{rotating}\n") ) {
      if( pOutputFile->PutStr("\\usepackage{SIunits}\n\n") ) {
        if( pOutputFile->PutStr("\\pagestyle{empty}\n\n") ) {
          if( pOutputFile->PutStr("\\begin{document}\n\n") ) {
            if( pOutputFile->PutStr("\\title{Occultations table}\n\n") ) {
              if( pOutputFile->PutStr("\\author{}\n\n") ) {
                if( pOutputFile->PutStr("\\date{}\n\n") ) {
                  if( pOutputFile->PutStr("\\maketitle\n\n") ) {
                    Msg.str("");
                    Msg << "\\noindent Observation point: " << pLOPos->GetObsNamePtr() << "\\newline" << std::endl;

                    if( pOutputFile->PutStr( Msg.str() ) ) {
                      Msg.str("");
                      Msg << "EMail: " << pLOPos->GetEMail() << "\\newline" << std::endl;

                      if( pOutputFile->PutStr( Msg.str() ) ) {
                        Msg.str("");
                        apsmathlib::DMS( pLOPos->GetObserverLongitude(), D1, M1, S1 );
                        apsmathlib::DMS( pLOPos->GetObserverLatitude(), D2, M2, S2 );
                        Msg << "Longitude = $" << std::fixed << std::setw( 6 ) << std::setprecision( 3 ) << pLOPos->GetObserverLongitude() << " (" <<
                                D1 << "\\ensuremath{^{\\circ}}" << std::setw( 2 ) << std::setfill( '0' ) << M1 << "'" <<
                                std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << S1 << "'')$ Latitude = $" <<
                                std::fixed << std::setfill( ' ' ) << std::setw( 6 ) << std::setprecision( 3 ) << pLOPos->GetObserverLatitude() << " (" <<
                                D2 << "\\ensuremath{^{\\circ}}" <<
                                std::setw( 2 ) << std::setfill( '0' ) << M2 << "'" <<
                                std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << S2 << "'')$\\newline" << std::endl;

                        if( pOutputFile->PutStr( Msg.str() ) ) {
                          Msg.str("");
                          Msg << "Maximal Distance = " << std::fixed  << std::setfill( ' ' ) << std::setw( 5 ) << std::setprecision( 1 ) << pLOPos->GetMaxDistance() << "\\newline" << std::endl;

                          if( pOutputFile->PutStr( Msg.str() ) ) {
                            if( pLOPos->GetMaxMv() != std::numeric_limits<float>::max() ) {
                              Msg.str("");
                              Msg << "Maximal Mv = " << std::fixed << std::setfill( ' ' ) << std::setw( 5 ) << std::setprecision( 2 ) << pLOPos->GetMaxMv() << "\\newline" << std::endl;
                              pOutputFile->PutStr( Msg.str() );
                            }

                            Msg.str("");
                            Msg << "Minimal Duration = " << std::fixed << std::setfill( ' ' ) << std::setw( 5 ) << std::setprecision( 1 ) << pLOPos->GetMinDuration() << "s\\newline" << std::endl;

                            if( pOutputFile->PutStr( Msg.str() ) ) {
                              Msg.str("");
                              Msg << "Maximal Sun Elevation = " << std::fixed << std::setfill( ' ' ) << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetSunElev() << "\\newline" << std::endl;

                              if( pOutputFile->PutStr( Msg.str() ) ) {
                                Msg.str("");
                                Msg << "Minimal drop: " << std::fixed << std::setfill( ' ' ) << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinDrop() << "\\newline" << std::endl;

                                if( pOutputFile->PutStr( Msg.str() ) ) {
                                  Msg.str("");
                                  Msg << "Minimal probability: " << std::fixed << std::setfill( ' ' ) << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinProb() << "\\newline" << std::endl;

                                  if( pOutputFile->PutStr( Msg.str() ) ) {
                                    Msg.str("");
                                    Msg << "Minimal probability in nearest point: " << std::fixed << std::setfill( ' ' ) << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinCenterProb() << "\\newline" << std::endl;

                                    if( pOutputFile->PutStr( Msg.str() ) ) {
                                      Msg.str("");
                                      Msg << "Minimal star elevation: " << std::fixed << std::setfill( ' ' ) << std::setw( 4 ) << std::setprecision( 1 ) << pLOPos->GetMinStarElev() << "\\newline" << std::endl;

                                      if( pOutputFile->PutStr( Msg.str() ) ) {
                                        Msg.str("");
                                        Msg << "Program: " << ProgramName << "\\newline\nAuthor: Plekhanov Andrey andyplekhanov@gmail.com\\newline" << std::endl;
                                        pOutputFile->PutStr( Msg.str() );

                                        Msg.str("");
                                        Msg << "Events number: " << Number << "\\newline" << std::endl << std::endl;

                                        if( pOutputFile->PutStr( Msg.str() ) ) {
                                          if( pOutputFile->PutStr( "\\pagebreak\n\n" ) ) {
                                            if( pOutputFile->PutStr( "\\oddsidemargin=-2cm\n" ) ) {
                                              if( pOutputFile->PutStr( "\\topmargin=-3cm\n" ) ) {
                                                if( pOutputFile->PutStr( "\\textwidth=19cm\n" ) ) {
                                                  if( pOutputFile->PutStr( "\\textheight=23.5cm\n\n" ) ) {
                                                  }
                                                  else {
                                                    RetCode = 1;
                                                  }
                                                }
                                                else {
                                                  RetCode = 1;
                                                }
                                              }
                                              else {
                                                RetCode = 1;
                                              }
                                            }
                                            else {
                                              RetCode = 1;
                                            }
                                          }
                                          else {
                                            RetCode = 1;
                                          }
                                        }
                                        else {
                                          RetCode = 1;
                                        }
                                      }
                                      else {
                                        RetCode = 1;
                                      }
                                    }
                                    else {
                                      RetCode = 1;
                                    }
                                  }
                                  else {
                                    RetCode = 1;
                                  }
                                }
                                else {
                                  RetCode = 1;
                                }
                              }
                              else {
                                RetCode = 1;
                              }
                            }
                            else {
                              RetCode = 1;
                            }
                          }
                          else {
                            RetCode = 1;
                          }
                        }
                        else {
                          RetCode = 1;
                        }
                      }
                      else {
                         RetCode = 1;
                      }
                    }
                    else {
                       RetCode = 1;
                    }
                  }
                  else {
                    RetCode = 1;
                  }
                }
                else {
                  RetCode = 1;
                }
              }
              else {
                RetCode = 1;
              }
            }
            else {
              RetCode = 1;
            }
          }
          else {
            RetCode = 1;
          }
        }
        else {
          RetCode = 1;
        }
      }
      else {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WritePDFHeader( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                           const int Table, const int Page, const int Type ) const
{
  int    D1;
  int    M1;
  double S1;
  int    D2;
  int    M2;
  double S2;
  int    RetCode = 0;

  std::ostringstream Msg;

  if( pOutputFile->PutStr("{\\small\n\n\\begin{sideways}\n\n") ) {
    if( pOutputFile->PutStr("\\begin{tabular}{|p{1.6cm}|p{2.0cm}|p{0.8cm}|p{0.7cm}|p{0.6cm}|p{0.6cm}|p{0.6cm}|p{1.7cm}|p{0.4cm}|p{0.7cm}|p{1.6cm}|p{0.7cm}|p{2.2cm}|p{0.6cm}|p{0.4cm}|p{0.6cm}|p{0.7cm}|p{0.6cm}|p{0.7cm}|p{0.7cm}|p{0.7cm}|}\n") ) {
      if( pOutputFile->PutStr("\\hline\n\\multicolumn{8}{|l|}{\n" ) ) {
        Msg.str("");
        apsmathlib::DMS( pLOPos->GetObserverLongitude(), D1, M1, S1 );
        apsmathlib::DMS( pLOPos->GetObserverLatitude(), D2, M2, S2 );
        Msg << "Longitude = $" << std::fixed << std::setw( 6 ) << std::setprecision( 3 ) << pLOPos->GetObserverLongitude() << " (" <<
                D1 << "\\ensuremath{^{\\circ}}" << std::setw( 2 ) << std::setfill( '0' ) << M1 << "'" <<
                std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << S1 << "'')$ Latitude = $" <<
                std::fixed << std::setw( 6 ) << std::setprecision( 3 ) << pLOPos->GetObserverLatitude() << " (" <<
                D2 << "\\ensuremath{^{\\circ}}" <<
                std::setw( 2 ) << std::setfill( '0' ) << M2 << "'" <<
                std::fixed << std::setw( 4 ) << std::setprecision( 1 ) << S2 << "'')$\\newline" << std::endl;

        if( pOutputFile->PutStr( Msg.str() ) ) {
          Msg.str("");
          Msg << "} &\n\\multicolumn{5}{l|}{\n" << GetSortName( Type ) << "\n} &\n\\multicolumn{2}{l|}{\nTable " <<
                 Table << "\n} &\n\\multicolumn{2}{l|}{\nPage " << Page << "\n} &\n\\multicolumn{4}{l|}{" << ProgramName << std::endl;

          if( pOutputFile->PutStr( Msg.str() ) ) {
            if( pOutputFile->PutStr("} \\\\\n\\hline\n\\hline\n\n") ) {
              if( pOutputFile->PutStr("&\n\\multicolumn{3}{|c|}{Asteroid} &\n\\multicolumn{3}{c|}{} &\n\\multicolumn{2}{c|}{Nearest point} &\n") ) {
                if( pOutputFile->PutStr("&\n\\multicolumn{5}{|c|}{Star} &\n\\multicolumn{2}{c|}{Sun} &\n\\multicolumn{3}{c|}{Moon} &\n\\\\\n") ) {
                  if( pOutputFile->PutStr("\\hline\nDate Time (UTC) &\nNumber Name &\nDiam (km) &\nMag &\nDrop &\nDist (km) &\nDurat (sec) &\n") ) {
                    if( pOutputFile->PutStr("Longitude Latitude &\nAz &\nProb (\\%) &\nCatalog Number &\nMag &\nRA Dec &\nAlt &\nAz &\n") ) {
                      if( pOutputFile->PutStr("Dist &\nAlt &\nDist &\nAlt &\nPhase (\\%)&\n$\\sigma_{km}$\n\\\\\n\\hline\n\n") ) {
                      }
                      else {
                        RetCode = 1;
                      }
                    }
                    else {
                      RetCode = 1;
                    }
                  }
                  else {
                    RetCode = 1;
                  }
                }
                else {
                  RetCode = 1;
                }
              }
              else {
                RetCode = 1;
              }
            }
            else {
              RetCode = 1;
            }
          }
          else {
            RetCode = 1;
          }
        }
        else {
          RetCode = 1;
        }
      }
      else {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WritePDFStr( const LOPointEvent * pLOPointEvent, APSOStrFile * pOutputFile ) const
{
  const LOEvent * pLOEvent;
  int             Year1;
  int             Month1;
  int             Day1;
  int             Hour1;
  int             Min1;
  double          Sec1;
  int             D1;
  int             M1;
  double          S1;
  int             D2;
  int             M2;
  double          S2;
  int             D3;
  int             M3;
  double          S3;
  int             D4;
  int             M4;
  double          S4;
  int             RetCode = 0;

  std::ostringstream Msg;

  pLOEvent = pLOPointEvent->GetLOEventPtr();

  apsastroalg::CalDat( pLOPointEvent->GetMjdate(), Year1, Month1, Day1, Hour1, Min1, Sec1 );
  apsmathlib::DMS( apsmathlib::Deg * pLOEvent->GetStarRA() / 15.0, D1, M1, S1 );
  apsmathlib::DMS( apsmathlib::Deg * pLOEvent->GetStarDec(), D2, M2, S2 );
  apsmathlib::DMS( apsmathlib::Deg * pLOPointEvent->GetMaxLongitude(), D3, M3, S3 );
  apsmathlib::DMS( apsmathlib::Deg * pLOPointEvent->GetMaxLatitude(), D4, M4, S4 );

  Msg << Year1 << "/" <<
         std::setw( 2 ) << std::setfill( '0' ) << Month1 << "/" << 
         std::setw( 2 ) << std::setfill( '0' ) << Day1 << " " <<
         std::setw( 2 ) << std::setfill( '0' ) << Hour1 << ":" <<
         std::setw( 2 ) << std::setfill( '0' ) << Min1 << ":" <<
         std::fixed << std::setw( 2 ) << std::setfill( '0' ) << std::setprecision( 0 ) << Sec1 << " &\n" <<
         std::setfill( ' ' ) << pLOEvent->GetAsteroidID() << " " <<
         std::left << pLOEvent->GetAsteroidNamePtr() << " &\n" <<
         std::fixed << std::setw( 6 ) << std::right << std::setprecision( 1 ) << pLOEvent->GetDiameter() << " &\n " <<
         std::fixed << std::setw( 6 ) << std::setprecision( 2 ) << pLOEvent->GetBrightness() << " &\n" <<
         std::fixed << std::setw( 5 ) << std::setprecision( 2 ) << pLOEvent->GetBrightDelta() << " &\n" <<
         std::fixed << std::setw( 5 ) << std::setprecision( 0 ) << pLOPointEvent->GetDistance() << " &\n" <<
         std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOEvent->GetMaxDuration() << " &\n";

  if( pOutputFile->PutStr( Msg.str() ) ) {
    Msg.str("");
    Msg << "$" << std::setfill( ' ' ) << D3 << "\\ensuremath{^{\\circ}}" <<
            std::setw( 2 ) << std::setfill( '0' ) << M3 << "'" <<
            std::fixed << std::setw( 2 ) << std::setfill( '0' ) << std::setprecision( 0 ) << S3 << "''$ \\linebreak $" <<
            std::setfill( ' ' ) << D4 << "\\ensuremath{^{\\circ}}" <<
            std::setw( 2 ) << std::setfill( '0' ) << M4 << "'" <<
            std::fixed << std::setw( 2 ) << std::setfill( '0' ) << std::setprecision( 0 ) << S4 << "''$ &\n " <<
            std::fixed << std::setw( 3 ) << std::setfill( ' ' ) << std::setprecision( 0 ) << apsmathlib::Deg * pLOPointEvent->GetAz() << " &\n" <<
            std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOPointEvent->GetProbability() << " " <<
            std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOPointEvent->GetMaxProbability() << " &" << std::endl;

    if( pOutputFile->PutStr( Msg.str() ) ) {
      Msg.str("");

      Msg << LOStarData :: GetCatName( pLOEvent->GetCatalog() ) << " " <<
	//pLOEvent->GetStarNumber() << " &\n" <<
             LOStarData::GetStarName( pLOEvent->GetCatalog(), pLOEvent->GetStarNumber() ) << " &\n" <<	
             std::fixed << std::setw( 5 ) << std::setprecision( 2 ) << pLOEvent->GetMv() / 100.0 << " &\n$" <<
             D1 << std::setfill( ' ' ) << "^h" <<
             std::setw( 2 ) << std::setfill( '0' ) << M1 << "^m" <<
             std::fixed << std::setw( 6 ) << std::setfill( '0' ) << std::setprecision( 3 ) << S1 << "^s$ \\linebreak $" <<
             D2 << std::setfill( ' ' ) << "\\ensuremath{^{\\circ}}" <<
             std::setw( 2 ) << std::setfill( '0' ) << M2 << "'" <<
             std::fixed << std::setw( 6 ) << std::setfill( '0' ) << std::setprecision( 3 ) << S2 << "''$ &\n " <<
             std::fixed << std::setw( 5 ) << std::setfill( ' ' ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetStarElev() << " &\n";

      if( pOutputFile->PutStr( Msg.str() ) ) {
        Msg.str("");

        Msg << std::fixed << std::setw( 3 ) << std::setprecision( 0 ) << apsmathlib::Deg * pLOPointEvent->GetStarAz() << " &\n" <<
               std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOEvent->GetSunDist() << " &\n" <<
               std::fixed << std::setw( 6 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetSunElev() << " &\n" <<
               std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOEvent->GetMoonDist() << " &\n" <<
               std::fixed << std::setw( 6 ) << std::setprecision( 1 ) << apsmathlib::Deg * pLOPointEvent->GetMoonElev() << " &\n" <<
               std::fixed << std::setw( 5 ) << std::setprecision( 1 ) << pLOEvent->GetMoonPhase() << " &\n " <<
               std::fixed << std::setw( 7 ) << std::setprecision( 0 ) << pLOEvent->GetUncertainty() << "\n\\\\\n\n\\hline\n\n";

        if( pOutputFile->PutStr( Msg.str() ) ) {
        }
        else {
          RetCode = 1;
        }
      }
      else {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WritePDFFooter( APSOStrFile * pOutputFile ) const
{
  int RetCode = 0;

  if( pOutputFile->PutStr("\\end{tabular}\n\\end{sideways}\n}\n\\nopagebreak\n\n") ) {
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteOnePDFTable( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                             const LOPointEvent ** ppLOPointEventArray, const unsigned int Number,
                                             const int Type, const int Table, const unsigned int Page ) const
{
  unsigned int   i;
  PointEventSort PointEventSorting;
  int            RetCode = 0;

  if( !WritePDFHeader( pLOPos, pOutputFile, ProgramName, Table, Page + 1, Type ) ) {
    PointEventSorting.Sort( reinterpret_cast<const void **>( ppLOPointEventArray ), Number, Type );

    for( i = PDF_PAGE_SIZE * Page; i < Number; i++ ) {
      if( WritePDFStr( ppLOPointEventArray[ i ], pOutputFile ) ) {
        RetCode = 1;
        break;
      }

      if( i >= PDF_PAGE_SIZE * ( Page + 1 ) - 1 ) {
        break;
      }
    }

    if( !RetCode ) {
      RetCode = WritePDFFooter( pOutputFile );
    }
  }

  return( RetCode );
}

int LOWritePositionData :: WritePDFTableBody( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                              const LOPointEvent ** ppLOPointEventArray, const unsigned int Number,
                                              const int Type, const int Table ) const
{
  int i;
  int Pages;
  int RetCode = 0;

  Pages = Number / PDF_PAGE_SIZE;

  if( Number % PDF_PAGE_SIZE ) {
    Pages++;
  }

  for( i = 0; i < Pages; i++ ) {
    if( WriteOnePDFTable( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, Type, Table, i ) ) {
      RetCode = 1;
      break;
    }
  }

  return( RetCode );
}

int LOWritePositionData :: WritePDFBody( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                         const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const
{
  int Table   = 1;
  int RetCode = 0;

  if( pLOPos->GetSort() & PE_SORT_BY_DATE ) {
    RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_DATE, Table );
    Table++;
  }

  if( !RetCode ) {
    if( pLOPos->GetSort() & PE_SORT_BY_NUMBER ) {
      RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_NUMBER, Table );
      Table++;
    }

    if( !RetCode ) {
      if( pLOPos->GetSort() & PE_SORT_BY_DROP ) {
        RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_DROP, Table );
        Table++;
      }

      if( !RetCode ) {
        if( pLOPos->GetSort() & PE_SORT_BY_DISTANCE ) {
          RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_DISTANCE, Table );
          Table++;
        }

        if( !RetCode ) {
          if( pLOPos->GetSort() & PE_SORT_BY_DURATION ) {
            RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_DURATION, Table );
            Table++;
          }

          if( !RetCode ) {
            if( pLOPos->GetSort() & PE_SORT_BY_PROB ) {
              RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_PROB, Table );
              Table++;
            }

            if( !RetCode ) {
              if( pLOPos->GetSort() & PE_SORT_BY_CPROB ) {
                RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_CPROB, Table );
                Table++;
              }

              if( !RetCode ) {
                if( pLOPos->GetSort() & PE_SORT_BY_MAG ) {
                  RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_MAG, Table );
                  Table++;
                }

                if( !RetCode ) {
                  if( pLOPos->GetSort() & PE_SORT_BY_UNCERT ) {
                    RetCode = WritePDFTableBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number, PE_SORT_BY_UNCERT, Table );
                    Table++;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return( RetCode );
}

int LOWritePositionData :: WriteMainPDFFooter( const LOPos * pLOPos, APSOStrFile * pOutputFile ) const
{
  int RetCode = 0;

  if( pOutputFile->PutStr("\\end{document}\n") ) {
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteMainHTMLHeader( APSOStrFile * pOutputFile ) const
{
  int RetCode = 0;

  if( pOutputFile->PutStr("<HTML>\n<HEAD>\n<TITLE>Occultation events</TITLE>\n</HEAD>\n<BODY>\n<PRE>\n") ) {
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteHTMLBody( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                          const LOPointEvent ** ppLOPointEventArray, unsigned int Number ) const
{
  int RetCode;

  RetCode = WriteTextFile( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number );

  return( RetCode );
}

int LOWritePositionData :: WriteMainHTMLFooter( APSOStrFile * pOutputFile ) const
{
  int RetCode = 0;

  if( pOutputFile->PutStr("</PRE>\n</BODY>\n</HTML>\n") ) {
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteTextFile( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                          const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const
{
  int RetCode = 0;

  if( !WriteMainTextHeader( pLOPos, pOutputFile, ProgramName, Number ) ) {
    if( !WriteTextBody( pLOPos, pOutputFile, ppLOPointEventArray, Number ) ) {
      if( WriteMainTextFooter( pLOPos, pOutputFile ) ) {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WritePDFFile( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                         const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const
{
  int RetCode = 0;

  if( !WriteMainPDFHeader( pLOPos, pOutputFile, ProgramName, Number ) ) {
    if( !WritePDFBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number ) ) {
      if( WriteMainPDFFooter( pLOPos, pOutputFile ) ) {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: WriteHTMLFile( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                                          const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const
{
  int RetCode = 0;

  if( !WriteMainHTMLHeader( pOutputFile ) ) {
    if( !WriteHTMLBody( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number ) ) {
      if( WriteMainHTMLFooter( pOutputFile ) ) {
        RetCode = 1;
      }
    }
    else {
      RetCode = 1;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int LOWritePositionData :: ProcessOnePosition( const LOPos * pLOPos, const std::string & ProgramName ) const
{
  int                       i;
  APSOStrFile             * pOutputFile;
  const LOPointEventItem  * pLOPointEventItem;
  unsigned int              Number;
  const LOPointEvent     ** ppLOPointEventArray;
  int                       RetCode = LO_EVENT_POS_WRITER_NO_ERROR;

  Number = 0;

  pLOPointEventItem = pLOPos->GetFirstPointEventItem();

  while( pLOPointEventItem ) {
    Number++;

    pLOPointEventItem = pLOPointEventItem->GetNextPointEventItemPtr();
  }

  if( Number > 0 ) {
    ppLOPointEventArray = new const LOPointEvent * [ Number ];

    i = 0;

    pLOPointEventItem = pLOPos->GetFirstPointEventItem();

    while( pLOPointEventItem ) {
      ppLOPointEventArray[ i ] = pLOPointEventItem->GetPointEventPtr();

      i++;

      pLOPointEventItem = pLOPointEventItem->GetNextPointEventItemPtr();
    }

    if( pLOPos->GetOutputFiles() & PE_TEXT_FILE ) {
      std::ostringstream FileName;

      FileName << pLOPos->GetObsNamePtr() << ".txt";

      pOutputFile = new APSOStrFile( FileName.str() );

      if( pOutputFile->Open() ) {
        RetCode = WriteTextFile( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number );

        if( RetCode ) {
          pModule->ErrorMessage( LO_EVENT_POS_WRITER_EVENT );
          RetCode = LO_EVENT_POS_WRITER_EVENT;
        }

        pOutputFile->Close();
      }
      else {
        pModule->ErrorMessage( LO_EVENT_POS_WRITER_OPEN_FILE );
        RetCode = LO_EVENT_POS_WRITER_OPEN_FILE;
      }

      delete pOutputFile;
    }

    if( pLOPos->GetOutputFiles() & PE_PDF_FILE ) {
      std::ostringstream FileName;

      FileName << pLOPos->GetObsNamePtr() << ".ltx";

      pOutputFile = new APSOStrFile( FileName.str() );

      if( pOutputFile->Open() ) {
        RetCode = WritePDFFile( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number );

        if( RetCode ) {
          pModule->ErrorMessage( LO_EVENT_POS_WRITER_EVENT );
          RetCode = LO_EVENT_POS_WRITER_EVENT;
        }

        pOutputFile->Close();
      }
      else {
        pModule->ErrorMessage( LO_EVENT_POS_WRITER_OPEN_FILE );
        RetCode = LO_EVENT_POS_WRITER_OPEN_FILE;
      }

      delete pOutputFile;
    }

    if( pLOPos->GetOutputFiles() & PE_HTML_FILE ) {
      std::ostringstream FileName;

      FileName << pLOPos->GetObsNamePtr() << ".htm";

      pOutputFile = new APSOStrFile( FileName.str() );

      if( pOutputFile->Open() ) {
        RetCode = WriteHTMLFile( pLOPos, pOutputFile, ProgramName, ppLOPointEventArray, Number );

        if( RetCode ) {
          pModule->ErrorMessage( LO_EVENT_POS_WRITER_EVENT );
          RetCode = LO_EVENT_POS_WRITER_EVENT;
        }

        pOutputFile->Close();
      }
      else {
        pModule->ErrorMessage( LO_EVENT_POS_WRITER_OPEN_FILE );
        RetCode = LO_EVENT_POS_WRITER_OPEN_FILE;
      }

      delete pOutputFile;
    }

    delete ppLOPointEventArray;
  }
  else {
    std::cout << "WARNING: position " << pLOPos->GetObsNamePtr() << " has no events." << std::endl;
  }

  return( RetCode );
}

int LOWritePositionData :: Write( LOData * pLOData )
{
  unsigned int          i;
  LOPosData           * pLOPosData;
  LOPos               * pLOPos;
  std::string           ProgramName;
  const apslib::APSMainModule * pMainModule;
  int                   RetCode = LO_EVENT_POS_WRITER_NO_ERROR;

  pMainModule = pModule->FindMainModule();

  pMainModule->GetModuleInfo( ProgramName, 1 ); 

  pLOPosData = pLOData->GetPosDataPtr();

  std::ostringstream Msg;
  Msg << pLOPosData->GetPositionsNumber() << " records." << std::endl;

  pModule->InfoMessage( LO_EVENT_POS_WRITER_START_WRITING, Msg.str() );

  for( i = 0; i < pLOPosData->GetPositionsNumber(); i++ ) {
    pLOPos = pLOPosData->GetPositionPtr( i );

    RetCode = ProcessOnePosition( pLOPos, ProgramName );

    if( RetCode ) {
      pModule->ErrorMessage( LO_EVENT_POS_WRITER_EVENT );
      RetCode = LO_EVENT_POS_WRITER_EVENT;
    }

    pModule->StrMessage( LO_EVENT_POS_WRITER_PROGRESS );
  }

  pModule->StrMessage( LO_EVENT_POS_WRITER_NEW_LINE );

  pModule->InfoMessage( LO_EVENT_POS_WRITER_FINISH_WRITING );

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
