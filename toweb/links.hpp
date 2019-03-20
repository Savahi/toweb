#pragma once

#include "stdafx.h"
	
namespace Spider3d {

	#define LINK_FS  0x00000000
	#define LINK_SS  0x00000010
	#define LINK_FF  0x00000020
	#define LINK_SF  0x00000030

	class Link {
		public:

		std::string sPredCode;
		std::string sSuccCode;
		long int iTypeSF2;
		bool bTypeSF2;

		Link() {;}
		~Link() {;}
	};

	class Links {
		public:
	    std::vector<std::string> fieldsNames;
	    std::map<std::string,int> fieldsPositions;
	    std::map<std::string,std::string> fieldsTitles;
	    std::map<std::string,long int> fieldsFlags;

		std::vector<Link> links;

		int add( Link& link ) {
			this->links.push_back( link );
			return 0;
		}

		int clear( void ) {
			this->links.clear();
		}

		Links() {;}
		~Links() {;}

		unsigned int size( void ) {
			return this->links.size(); 
		}
	};
}