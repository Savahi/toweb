#pragma once
#include "stdafx.h"

namespace Spider3d {

	class TableLine {
		public:
	    std::vector<std::string> fields;    
		
		TableLine() { ; }
		~TableLine() { ; }
	};

	class Table {
		public:
	    std::vector<std::string> fieldsNames;
	    std::map<std::string,int> fieldsPositions;
	    std::map<std::string,std::string> fieldsTitles;
	    std::map<std::string,long int> fieldsFlags;

	    std::vector<TableLine> lines;

		Table() { ; }
		~Table() { ; }

		int add( TableLine& tl ) {
			this->lines.push_back( tl );
			return 0;
		}

		int size( void ) {
			return this->lines.size();
		}

		int clear( void ) {
			this->lines.clear();
		}

	};
}
