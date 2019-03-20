#pragma once
#include "stdafx.h"
	
namespace Spider3d {

	class Cost {
		public:
			std::string sCode;
			std::string sName;

			Cost() {;}
			~Cost() {;}
	};

	class Costs {
		public:
			std::vector<Cost> mCosts;

			int add( Cost& cost ) {
				this->mCosts.push_back( cost );
				return 0;
			}

			int clear( void ) {
				this->mCosts.clear();
			}

			Costs() {;}
			~Costs() {;}

			unsigned int number( void ) {
				return this->mCosts.size(); 
			}
	};
}