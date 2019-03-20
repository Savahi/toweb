#include "stdafx.h"

namespace Spider3d {

    static int iOperCodePos, iResCodePos, iNumberPos, iPriorPos;

    static char caOperCode[] = "OperCode";
    static char caResCode[] = "ResCode";
    static char caNumber[] = "Number";
    static char caPrior[] = "Prior";

    static int nFields = 4;
    static char *cpaFields[] = { caOperCode, caResCode, caNumber, caPrior };
    static int  *ipaFields[] = { &iOperCodePos, &iResCodePos, &iNumberPos, &iPriorPos };

    static int iOperCodeIndex, iResCodeIndex, iNumberIndex, iPriorIndex;
    static int *ipaFieldIndexes[] = { &iOperCodeIndex, &iResCodeIndex, &iNumberIndex, &iPriorIndex };

    int loadOpResAssignments( OpResAssignments& opResAssignments, const char *cpFile ) {
        FILE *fp;
        char *cpLine;
        int iStatus;
        int nScanned;

        fp = fopen( cpFile, "rb" );
        if( fp != NULL ) {
            iStatus = parseFileHeader( fp, nFields, cpaFields, ipaFields );
            if( iStatus != -1 ) {
                while(1) {
                    cpLine = parseFileLine( fp, nFields, ipaFields, ipaFieldIndexes, &iStatus );
                    if( cpLine == NULL ) {
                        break;
                    }
                    if( iStatus == 0 ) {
                        OpResAssignment opResAssignment;
                        opResAssignment.sOperCode = std::string( trimString( &cpLine[iOperCodeIndex] ) );
                        opResAssignment.sResCode = std::string( trimString( &cpLine[iResCodeIndex] ) );
                        nScanned = sscanf( &cpLine[iNumberIndex], "%f", &opResAssignment.fNumber );
                        opResAssignment.bNumber = ( nScanned == 1 ) ? true : false;
                        nScanned = sscanf( &cpLine[iPriorIndex], "%f", &opResAssignment.fPrior );
                        opResAssignment.bPrior = ( nScanned == 1 ) ? true : false;
                        
                        opResAssignments.add(opResAssignment);
                    }
                    free(cpLine);
                }
            }
            fclose(fp);
        }
        return 0;
    }
}