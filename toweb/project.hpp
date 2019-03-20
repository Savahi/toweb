#pragma once

#include "stdafx.h"
	
namespace Spider3d {

	class Project {
		public:
	    std::vector<std::string> fieldsNames;
	    std::map<std::string,int> fieldsPositions;
	    std::map<std::string,std::string> fieldsTitles;
	    std::map<std::string,long int> fieldsFlags;

		std::string sCode;
		std::string sName;

		std::string sProjVer;
		int iProjVer;
		bool bProjVer;

		std::string sCurTime;
		std::string sNotes;

		Project() {;}
		~Project() {;}
	};
}