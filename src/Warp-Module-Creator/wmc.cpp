#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define VCPRJ_EXT ".vcxproj"
#define WARP_PROJ "Warp-Framework.vcxproj"
#define WARP_PATH "..\\Warp-Framework\\"
#define PROJ_PATH "..\\Warp-Framework\\Warp-Framework.vcxproj"
#define FLTR_PATH "..\\Warp-Framework\\Warp-Framework.vcxproj.filters"
#define EMPTY_VAL ""
#define PLHDR_VAL ""
#define STR_NEWLN 10
#define ENV_NEWLN std::endl
#define STR_CPRGT "//© 2019 NIREX ALL RIGHTS RESERVED"

namespace File
{
	// Simple (std::string)
	std::string ReadAllText(std::string file)
	{
		std::ifstream f(file.c_str());

		std::string str = EMPTY_VAL;
		std::string outstr = EMPTY_VAL;
		int iter = 0;
		while (std::getline(f, str))
		{
			iter++;
			outstr += str;
			outstr += STR_NEWLN;
		}
		f.close();
		return outstr;
	}

	int WriteAllText(std::string file, std::string str)
	{
		std::ofstream f;
		f.open(file);
		f << str;
		f.close();
		return 0;
	}

	std::int32_t FindFirst(std::string file, std::string val)
	{
		std::ifstream f(file.c_str());

		std::string str = EMPTY_VAL;
		int iter = 0;
		while (std::getline(f, str))
		{
			if (val == str)
			{
				return iter;
			}
			iter++;
		}
		f.close();
		return -1;
	}

	// Complex (std::vector)
	std::vector<std::string> ReadAllLines(std::string file)
	{
		std::ifstream f(file.c_str());
		std::vector<std::string> retv;

		std::string str = EMPTY_VAL;
		while (std::getline(f, str))
		{
			retv.push_back(str);
		}

		f.close();
		return retv;
	}

	int WriteAllLines(std::string file, std::vector<std::string> vecstr)
	{
		std::ofstream f;
		f.open(file);

		for (size_t i = 0; i < vecstr.size(); i++)
		{
			f << vecstr[i];
			f << ENV_NEWLN;
		}

		f.close();
		return 0;
	}

	std::vector<int32_t> FindAll(std::string file, std::string val)
	{
		std::ifstream f(file.c_str());
		std::vector<int32_t> retv;

		std::string str = EMPTY_VAL;
		int iter = 0;

		while (std::getline(f, str))
		{
			if (val == str)
			{
				retv.push_back(iter);
			}
			iter++;
		}

		f.close();
		return retv;
	}

	// Misc
	bool SafeFread(void* buffer, int size, int number, FILE* fp)
	{
		using namespace std;
		int ItemsRead;
		if (feof(fp))
		{
			return false;
		}
		ItemsRead = (int)fread(buffer, size, number, fp);
		if (ItemsRead < number)
		{
			return false;
		}
		return true;
	}
}

namespace String
{
	// c_str
	char* ToUpper(char* temp)
	{
		char* retc = temp;
		
		int i = 0;
		while (retc[i])
		{
			retc[i] = toupper(retc[i]);
			i++;
		}
		return retc;
	}

	char* ToLower(char* temp)
	{
		char* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = tolower(retc[i]);
			i++;
		}
		return retc;
	}

	char* Proper(char* temp)
	{
		char* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = tolower(retc[i]);
			i++;
		}
		retc[0] = toupper(retc[0]);
		return retc;
	}

	// std::string
	std::string ToUpper(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = toupper(temp[i]);
			i++;
		}
		return temp;
	}

	std::string ToLower(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		return temp;
	}

	std::string Proper(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		temp[0] = toupper(temp[0]);
		return temp;
	}

	// std::vector
	std::vector<std::string> Split(std::string in_s, const std::string& delim)
	{
		std::vector <std::string> retvec;
		size_t pos = 0;
		std::string token;

		while ((pos = in_s.find(delim)) != std::string::npos)
		{
			token = in_s.substr(0, pos);
			retvec.push_back(token);
			in_s.erase(0, pos + delim.length());
		}

		retvec.push_back(in_s);
		return retvec;
	}
}

auto AddToVs(std::string name, bool headerOnly, bool WPrefix) -> int
{
	std::vector<std::string> content;
	content = File::ReadAllLines(PROJ_PATH);
	std::vector<int32_t> locs;
	locs = File::FindAll(PROJ_PATH, "  <ItemGroup>");

	// HEADER
	if (WPrefix)
	{
		content[locs[0]] += "\n    <ClInclude Include=\"W" + name + ".h\" />";
	}
	else
	{
		content[locs[0]] += "\n    <ClInclude Include=\"" + name + ".h\" />";
	}

	// CPP
	if (!headerOnly)
	{
		if (WPrefix)
		{
			content[locs[1]] += "\n    <ClCompile Include=\"W" + name + ".cpp\" />";
		}
		else
		{
			content[locs[1]] += "\n    <ClCompile Include=\"" + name + ".cpp\" />";
		}
	}

	std::vector<std::string> fcontent;
	fcontent = File::ReadAllLines(FLTR_PATH);
	std::vector<int32_t> flocs;
	flocs = File::FindAll(FLTR_PATH, "  <ItemGroup>");

	// HEADER
	if (WPrefix)
	{
		fcontent[flocs[1]] += "\n    <ClInclude Include=\"W" + name + ".h\">\n      <Filter>Header Files</Filter>\n    </ClInclude>\n";
	}
	else
	{
		fcontent[flocs[1]] += "\n    <ClInclude Include=\"" + name + ".h\">\n      <Filter>Header Files</Filter>\n    </ClInclude>\n";
	}

	// CPP
	if (!headerOnly)
	{
		if (WPrefix)
		{
			fcontent[flocs[2]] += "\n    <ClCompile Include=\"W" + name + ".cpp\">\n      <Filter>Source Files</Filter>\n    </ClCompile>\n";
		}
		else
		{
			fcontent[flocs[2]] += "\n    <ClCompile Include=\"" + name + ".cpp\">\n      <Filter>Source Files</Filter>\n    </ClCompile>\n";
		}
	}

	File::WriteAllLines(PROJ_PATH, content);
	File::WriteAllLines(FLTR_PATH, fcontent);

	return 0;
}

auto Empty(int argc, char** argv) -> int
{
	std::string name = argv[1];
	std::string upperName = String::ToUpper(argv[1]);
	std::string lowerName = String::ToLower(argv[1]);

	std::string hfileName = name + ".h";
	std::string cfileName = name + ".cpp";

	std::string hfileCont = EMPTY_VAL;
	std::string cfileCont = EMPTY_VAL;

	// .H
	// Copyright
	hfileCont += STR_CPRGT;
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// #ifndef
	hfileCont += "#ifndef _";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;

	// #define
	hfileCont += "#define _";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// #endif
	hfileCont += "#endif // !_";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;

	// .CPP
	// CopyRight
	cfileCont += STR_CPRGT;
	cfileCont += STR_NEWLN;
	cfileCont += STR_NEWLN;

	// #Include
	cfileCont += "#include \"";
	cfileCont += hfileName;
	cfileCont += "\"";
	cfileCont += STR_NEWLN;

	File::WriteAllText(WARP_PATH + hfileName, hfileCont);
	File::WriteAllText(WARP_PATH + cfileName, cfileCont);
	AddToVs(name, false, false);

	return 0;
}

auto ObjectOriented(int argc, char** argv, bool Entity) -> int
{
	std::string name = argv[1];
	std::string upperName = String::ToUpper(argv[1]);
	std::string lowerName = String::ToLower(argv[1]);

	std::string hfileName = "W" + name + ".h";
	std::string cfileName = "W" + name + ".cpp";

	std::string hfileCont = EMPTY_VAL;
	std::string cfileCont = EMPTY_VAL;

	// .H
	// Copyright
	hfileCont += STR_CPRGT;
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// #ifndef
	hfileCont += "#ifndef ";
	hfileCont += "_W_";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;

	// #define
	hfileCont += "#define ";
	hfileCont += "_W_";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	if (Entity)
	{
		// #include "WEntity.h"
		hfileCont += "#include \"WEntity.h\"";
		hfileCont += STR_NEWLN;
		hfileCont += STR_NEWLN;
	}

	// Class

	hfileCont += "class ";
	hfileCont += "W";
	hfileCont += name;
	if (Entity)
	{
		hfileCont += " : public WEntity";
	}
	hfileCont += STR_NEWLN;
	hfileCont += "{";
	hfileCont += STR_NEWLN;
	hfileCont += "public:";
	hfileCont += STR_NEWLN;

	// CTOR
	hfileCont += "\t";
	hfileCont += "W";
	hfileCont += name;
	hfileCont += "();";

	// DTOR
	hfileCont += STR_NEWLN;
	hfileCont += "\t~";
	hfileCont += "W";
	hfileCont += name;
	hfileCont += "();";
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// End Notation
	hfileCont += "};";
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// #endif
	hfileCont += "#endif // !_W_";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;

	// .CPP
	// CopyRight
	cfileCont += STR_CPRGT;
	cfileCont += STR_NEWLN;
	cfileCont += STR_NEWLN;

	// #Include
	cfileCont += "#include \"";
	cfileCont += hfileName;
	cfileCont += "\"";
	cfileCont += STR_NEWLN;
	cfileCont += STR_NEWLN;

	// CTOR
	cfileCont += "W";
	cfileCont += name;
	cfileCont += "::";
	cfileCont += "W";
	cfileCont += name;
	cfileCont += "()";
	cfileCont += STR_NEWLN;
	cfileCont += "{";
	cfileCont += STR_NEWLN;
	cfileCont += STR_NEWLN;
	cfileCont += "}";
	cfileCont += STR_NEWLN;
	cfileCont += STR_NEWLN;

	// DTOR
	cfileCont += "W";
	cfileCont += name;
	cfileCont += "::~";
	cfileCont += "W";
	cfileCont += name;
	cfileCont += "()";
	cfileCont += STR_NEWLN;
	cfileCont += "{";
	cfileCont += STR_NEWLN;
	cfileCont += STR_NEWLN;
	cfileCont += "}";
	cfileCont += STR_NEWLN;

	File::WriteAllText(WARP_PATH + hfileName, hfileCont);
	File::WriteAllText(WARP_PATH + cfileName, cfileCont);
	AddToVs(name, false, true);

	return 0;
}

auto HeaderOnly(int argc, char** argv, bool Entity) -> int
{
	std::string name = argv[1];
	std::string upperName = String::ToUpper(argv[1]);
	std::string lowerName = String::ToLower(argv[1]);

	std::string hfileName = "W" + name + ".h";
	std::string hfileCont = EMPTY_VAL;

	// .H
	// Copyright
	hfileCont += STR_CPRGT;
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// #ifndef
	hfileCont += "#ifndef ";
	hfileCont += "_W_";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;

	// #define
	hfileCont += "#define ";
	hfileCont += "_W_";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	if (Entity)
	{
		// #include "WEntity.h"
		hfileCont += "#include \"WEntity.h\"";
		hfileCont += STR_NEWLN;
		hfileCont += STR_NEWLN;
	}

	// Class

	hfileCont += "class ";
	hfileCont += "W";
	hfileCont += name;
	if (Entity)
	{
		hfileCont += " : public WEntity";
	}
	hfileCont += STR_NEWLN;
	hfileCont += "{";
	hfileCont += STR_NEWLN;
	hfileCont += "public:";
	hfileCont += STR_NEWLN;

	// CTOR
	hfileCont += "\t";
	hfileCont += "W";
	hfileCont += name;
	hfileCont += "();";

	// DTOR
	hfileCont += STR_NEWLN;
	hfileCont += "\t~";
	hfileCont += "W";
	hfileCont += name;
	hfileCont += "();";
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// End Notation
	hfileCont += "};";
	hfileCont += STR_NEWLN;
	hfileCont += STR_NEWLN;

	// #endif
	hfileCont += "#endif // !_W_";
	hfileCont += upperName;
	hfileCont += "_H_";
	hfileCont += STR_NEWLN;

	File::WriteAllText(WARP_PATH + hfileName, hfileCont);
	AddToVs(name, true, true);

	return 0;
}

auto main(int argc, char** argv) -> int
{
	if (argc < 2)
	{
		std::cout << ENV_NEWLN;
		std::cout << "wmc <name> <option>";
		std::cout << ENV_NEWLN;
		std::cout << ENV_NEWLN;
		std::cout << "Options: " << ENV_NEWLN;
		std::cout << "   header: Creates a single header file (.h)" << ENV_NEWLN;
		std::cout << "   wheader: Creates a single warp header file (.h)" << ENV_NEWLN;
		std::cout << "   class: Creates class files (.h .cpp)" << ENV_NEWLN;
		std::cout << "   wclass: Creates warp class files (.h .cpp)" << ENV_NEWLN;
		std::cout << "   'nothing': Creates empty files (.h .cpp)" << ENV_NEWLN;

		return 1;
	}
	
	std::string arg1 = argv[1];
	std::string cmd = EMPTY_VAL;

	if (arg1 == "-h" || arg1 == "--help")
	{
		std::cout << ENV_NEWLN;
		std::cout << "wmc <name> <option>";
		std::cout << ENV_NEWLN;
		std::cout << ENV_NEWLN;
		std::cout << "Options: " << ENV_NEWLN;
		std::cout << "   header: Creates a single header file (.h)" << ENV_NEWLN;
		std::cout << "   wheader: Creates a single warp header file (.h)" << ENV_NEWLN;
		std::cout << "   class: Creates class files (.h .cpp)" << ENV_NEWLN;
		std::cout << "   wclass: Creates warp class files (.h .cpp)" << ENV_NEWLN;
		std::cout << "   'nothing': Creates empty files (.h .cpp)" << ENV_NEWLN;

		return 1;
	}
	else if (argc == 2)
	{
		std::cout << "Creating Empty files." << ENV_NEWLN;
		return (Empty(argc, argv));
	}
	else if (argc == 3)
	{
		std::string arg2 = argv[2];

		if (arg2 == "header")
		{
			std::cout << "header" << ENV_NEWLN;
			std::cout << "Creating header file." << ENV_NEWLN;
			return (HeaderOnly(argc, argv, false));
		}
		else if (arg2 == "wheader")
		{
			std::cout << "header" << ENV_NEWLN;
			std::cout << "Creating Warp header file." << ENV_NEWLN;
			return (HeaderOnly(argc, argv, true));
		}
		else if (arg2 == "class")
		{
			std::cout << "Creating class files." << ENV_NEWLN;
			return (ObjectOriented(argc, argv, false));
		}
		else if (arg2 == "wclass")
		{
			std::cout << "Creating Warp class files." << ENV_NEWLN;
			return (ObjectOriented(argc, argv, true));
		}
		else
		{
			std::cout << "Creating Empty files." << ENV_NEWLN;
			return (Empty(argc, argv));
		}
	}
	
    return 0;
}
