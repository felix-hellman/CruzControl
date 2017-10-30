#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <functional>
#include <chrono>
#include <vector>

#define KEYLENGTH 256

std::string getname(std::string inputline)
{
	std::string name = "";

	int index = 0;
	while(inputline[index] != '=')
	{
		name += inputline[index];
		index++;
	}
	auto found = name.find("string");
	found += 7; //Hardcode skip of 7 chars should be fine
	name = name.substr(found,name.size());
	name = "extern int  " + name + "[];";
	return name;
}

std::string obfuscate(std::string inputline, std::vector<unsigned char> key)
{
	std::string name = "";

	int index = 0;
	while(inputline[index] != '=')
	{
		name += inputline[index];
		index++;
	}
	auto found = name.find("string");
	found += 7; //Hardcode skip of 7 chars should be fine
	name = name.substr(found,name.size());
	name = "locker::"+name;
	std::string field;
	index = 0;
	while(inputline[index] != '\"')
		index++;
	index++;
	while(inputline[index] != '\"')
		field += inputline[index++];

	std::string result = "int " + name + "[] = {";
	result += std::to_string(field.size()) + ", ";
	for(int i = 0; i < field.size(); i++)
	{
		result += std::to_string((int)(field[i]^key[(i%KEYLENGTH)]));
		if(i+1 != field.size())
			result += ", ";
	}
	result += "};";
	return result;
}



int main()
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	auto rand = std::bind(std::uniform_int_distribution<int>(0,255),std::mt19937(seed));
	std::vector<unsigned char> keyVector;


	for(int i = 0; i < KEYLENGTH; i++)
		keyVector.push_back(rand());

	std::ifstream input("strings.h");
	std::ifstream credentials("credentials");
	std::ofstream output("strings.obf.h");
	std::ofstream output2("strings.obf.cpp");
	std::string line;

	output << "#pragma once" << std::endl;
	output << "namespace locker{" << std::endl;
	output2 << "#include \"strings.obf.h\"" << std::endl;


	while(getline(input,line))
	{
		output << getname(line) << std::endl;
		output2 << obfuscate(line,keyVector) << std::endl;
	}
	while(getline(credentials,line))
	{
		output << getname(line) << std::endl;
		output2 << obfuscate(line,keyVector) << std::endl;
	}

	std::string keystring = "";

	for(auto i = 0; i < KEYLENGTH; i++)
	{
		keystring += std::to_string((int)keyVector[i]);
		if(i+1 != KEYLENGTH)
			keystring += ", ";
	}
	output << "extern int key[];" << std::endl;
	output2 << "int locker::key[] = {" << keystring << "};";

	output <<std::endl<< "}" << std::endl;

	output.close();



	return 0;
}
