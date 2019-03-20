
#include "stdafx.h"

namespace Spider3d {

    int loadTable( Table& table, const char *cpFile ) {

        std::ifstream infile( cpFile );
        if( !infile.is_open() ) {
            return -1;
        }

        int numHeaderParsed = parseAllFileHeader( infile, table.fieldsNames, table.fieldsPositions );
        if( numHeaderParsed != -1 ) {
            int numFlagsParsed = parseAllFileHeaderFlags( infile, table.fieldsNames, table.fieldsFlags );
            if( numFlagsParsed == numHeaderParsed ) {
                int numTitlesParsed = parseAllFileHeaderTitles( infile, table.fieldsNames, table.fieldsTitles );
                if( numTitlesParsed == numHeaderParsed ) {
                    while(1) {
                        std::vector<std::string> fieldsParsed;    
                        int numParsed = parseFileLine( infile, fieldsParsed );
                        if( numParsed == -1 ) {
                            break;
                        }
                        TableLine tl;
                        for( int i = 0 ; i < fieldsParsed.size() ; i++ ) {
                            tl.fields.push_back( fieldsParsed[ i ] );                
                        }
                        table.add( tl );
                    }
                }
            }
        }
        infile.close();
        return table.size();
    }
}