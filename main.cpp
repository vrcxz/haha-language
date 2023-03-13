////////////////////////////////////////////////////
// Developer: Von Ryan C. Nogadas                 //
// License: MIT                                   //
////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <ctime>
#include <random>
using namespace std;
#include "lexer.hpp"

int main()
{
	string file_name;
	cout<<"haha ";
	cin>>file_name;
	interpreter::read_tokens(file_name);
}
