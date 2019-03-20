#include "stdafx.h"

namespace Spider3d {

    int loadGantt( Gantt& gantt, const char *cpFile ) {

        std::ifstream infile( cpFile );
        if( !infile.is_open() ) {
            return -1;
        }
        int numHeaderParsed = parseAllFileHeader( infile, gantt.fieldsNames, gantt.fieldsPositions );
        if( numHeaderParsed != -1 ) {
            int numFlagsParsed = parseAllFileHeaderFlags( infile, gantt.fieldsNames, gantt.fieldsFlags );
            if( numFlagsParsed == numHeaderParsed ) {
                int numTitlesParsed = parseAllFileHeaderTitles( infile, gantt.fieldsNames, gantt.fieldsTitles );
                if( numTitlesParsed == numHeaderParsed ) {
                    while(1) {
                        std::vector<std::string> fieldsParsed;    
                        int numParsed = parseFileLine( infile, fieldsParsed );
                        if( numParsed == -1 ) {
                            break;
                        }
                        GanttOperation ga;
                        for( int i = 0 ; i < fieldsParsed.size() ; i++ ) {
                            ga.fields.push_back( fieldsParsed[ i ] );                
                        }
                        gantt.add( ga );
                    }
                }
            }
        }
        infile.close();
        return gantt.size();
    }
}