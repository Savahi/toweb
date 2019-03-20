#pragma once
#include "stdafx.h"
	
namespace Spider3d {

	class OpCost {
		public:
			std::string sOperCode;
			std::string sCostCode;
			int iFix;
			bool bFix;

			OpCost() {;}
			~OpCost() {;}
	};

	class OpCosts {
		public:
			std::vector<OpCost> mOpCosts;

			int add( OpCost& opCost ) {
				this->mOpCosts.push_back( opCost );
				return 0;
			}

			int clear( void ) {
				this->mOpCosts.clear();
			}

			OpCosts() {;}
			~OpCosts() {;}

			unsigned int number( void ) {
				return this->mOpCosts.size(); 
			}
	};
}