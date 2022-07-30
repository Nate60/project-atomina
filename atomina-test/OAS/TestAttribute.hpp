#pragma once
#include "../AtominaTest.hpp"

class TestAttribute : public ATMA::AttrBase
{
public:

        TestAttribute();

		~TestAttribute();

		//friend function to output attributes 
		friend std::stringstream& operator >> (std::stringstream& l_stream, AttrBase& b);


		void readIn(std::stringstream& l_stream);

		bool flag = false;
        
};