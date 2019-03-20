#include "stdafx.h"

namespace Spider3d {

    static int iOperCodePos, iCostCodePos, iFixPos;

    static char caOperCode[] = "OperCode";
    static char caCostCode[] = "CostCode";
    static char caFix[] = "Fix";

    static int nFields = 3;
    static char *cpaFields[] = { caOperCode, caCostCode, caFix };
    static int  *ipaFields[] = { &iOperCodePos, &iCostCodePos, &iFixPos };

    static int iOperCodeIndex, iCostCodeIndex, iFixIndex;
    static int *ipaFieldIndexes[] = { &iOperCodeIndex, &iCostCodeIndex, &iFixIndex };

    int loadOpCosts( OpCosts& opCosts, const char *cpFile ) {
        FILE *fp;
        char *cpLine;
        int iStatus;

        fp = fopen( cpFile, "rb" );
        if( fp != NULL ) {
            iStatus = parseFileHeader( fp, nFields, cpaFields, ipaFields );
            if( iStatus != -1 ) {
                while(1) {
                    int iParseFileLineStatus;
                    cpLine = parseFileLine( fp, nFields, ipaFields, ipaFieldIndexes, &iParseFileLineStatus );
                    if( cpLine == NULL ) {
                        break;
                    }
                    if( iParseFileLineStatus == 0 ) {
                        OpCost opCost;
                        opCost.sOperCode = std::string( trimString( &cpLine[iOperCodeIndex] ) );
                        opCost.sCostCode = std::string( trimString( &cpLine[iCostCodeIndex] ) );
                        int nScanned = sscanf( &cpLine[iFixIndex], "%d", &opCost.iFix );
                        opCost.bFix = ( nScanned == 1 ) ? true : false;
                        
                        opCosts.add( opCost );
                    }
                    free(cpLine);
                }
            }
            fclose(fp);
        }
        return 0;
    }
}