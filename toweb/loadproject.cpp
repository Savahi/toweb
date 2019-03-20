#include "stdafx.h"

namespace Spider3d {

    static int fieldsToReadNum = 4;
    static const char *fieldsToRead[] = { "Code", "Name", "ProjVer", "CurTime" };

    int loadProject( Project& project, const char *cpFile ) {
        int iReturn = -1;

        std::vector<std::string> fieldsNames;
        for( int i= 0 ; i < fieldsToReadNum ; i++ ) {
            fieldsNames.push_back( fieldsToRead[i] );
        }

        std::ifstream infile( cpFile );
        if( infile.is_open() ) {
            int numHeaderParsed = parseAllFileHeader( infile, project.fieldsNames, project.fieldsPositions );
            if( numHeaderParsed != -1 ) {
                int numFlagsParsed = parseAllFileHeaderFlags( infile, project.fieldsNames, project.fieldsFlags );
                if( numFlagsParsed == numHeaderParsed ) {
                    int numTitlesParsed = parseAllFileHeaderTitles( infile, project.fieldsNames, project.fieldsTitles );
                    if( numTitlesParsed == numHeaderParsed ) {
                        std::map<std::string,std::string> fieldsParsed;    
                        int numParsed = parseFileLine( infile, project.fieldsPositions, fieldsParsed );
                        if( numParsed != -1 ) {
                            project.sCode = fieldsParsed["Code"];
                            project.sName = fieldsParsed["Name"];
                            project.sProjVer = fieldsParsed["ProjVer"];
                            int nScanned = sscanf( project.sProjVer.c_str(), "%d", &project.iProjVer );
                            if( nScanned == 1 ) {
                                project.bProjVer = true;
                            } else {
                                project.iProjVer = 0;                    
                                project.bProjVer = false;
                            }
                            project.sCurTime = fieldsParsed["CurTime"];
                            project.sNotes = fieldsParsed["Notes"];
                            iReturn = 0;
                        }
                    }
                }
            }
            infile.close();
        }
        return iReturn;
    }
}