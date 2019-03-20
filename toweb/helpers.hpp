#pragma once

#include "stdafx.h"

namespace Spider3d {

	#define MAX_TAG_NAME 40

	#define READ_BUFFER_SIZE 1024

	char *readLineFromFile( FILE *fp );

	int findTagContent( char *cpText, const char *cpTagName, int iStartAt, int iStopAt, int *ipStart, int *ipEnd );

	int findSubstring( char *cpText, const char *cpSubstring, 
        int iStartAt, int iStopAt, int *ipStart, int *ipEnd, bool bWholeWordSearch=true );

    int getPosByColumnName( char *cpBuffer, const char *cpColumn );	

    std::string& ltrim(std::string& str, const std::string& chars = "\t\r\n ");
    std::string& rtrim(std::string& str, const std::string& chars = "\t\r\n ");
    std::string& trim(std::string& str, const std::string& chars = "\t\r\n ");

    char *trimString( char *cp );

    int timetToStr( time_t timetDT, char *cpBuffer, int iBufferSize=0, bool bAscTime=false, bool bHHMM=true, char cDMYDelim='.' );
    int parseDatetime( std::string sDatetime, struct tm& tmDatetime );

    int parseFileHeader( FILE *fp, int nFields, char **cpaFields, int **ipaFields, bool allFieldsRequired=true );
    char *parseFileLine( FILE *fp, int nFields, int **ipaFields, int **ipaFieldIndexes, int *ipStatus, bool allFieldsRequired=true );

    int parseFileHeader( std::ifstream& infile, std::vector<std::string>& fieldsNames, std::map<std::string,int>& fieldsPositions );
    int parseFileLine( std::ifstream& infile, std::vector<std::string>& fields );
    int parseFileLine( std::ifstream& infile, std::map<std::string,int>& fieldsPositions, std::map<std::string,std::string>& fieldsParsed );

    int parseAllFileHeader( std::ifstream& infile, std::vector<std::string>& fieldsNames, std::map<std::string,int>& fieldsPositions );
    int parseAllFileHeaderTitles( std::ifstream& infile, std::vector<std::string>& fieldsNames, 
        std::map<std::string,std::string>& fieldsTitles );  
    int parseAllFileHeaderFlags( std::ifstream& infile, std::vector<std::string>& fieldsNames, 
        std::map<std::string,long int>& fieldsFlags );

    std::string toLower(std::string s);
    bool isDigitsOnly(std::string s);
    bool isEmpty( std::string s );
}