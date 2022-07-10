#ifndef _ParserHeader_
#define _ParserHeader_
#include <string>
#include <vector>
#include "ResourceKind.hpp"
enum class CharType {
	CH_BLANK = 0,
	CH_WORD,
	CH_NUMBER,
	CH_OPERATOR,
	CH_DOT,
	CH_COLON,
	CH_COMMA,
	CH_QUOTE,
	CH_D_QUOTE,
	CH_SHARP,
	CH_OTHER,
	CH_NULL,
};
enum class TokenType {
	TT_WORD = 0,
	TT_NUMBER,
	TT_OPERATOR,
	TT_DOT,
	TT_COLON,
	TT_COMMA,
	TT_QUOTE,
	TT_D_QUOTE,
	TT_OTHER,
	TT_NULL,
};

class Syntax_AddResourseElement {
public:
	ResourceKind dataKind;
	std::string name;
	std::vector<std::string> paths;

public:
	Syntax_AddResourseElement() : dataKind(ResourceKind::Invalid) {};
	Syntax_AddResourseElement(ResourceKind _dataKind, std::string _name, std::vector<std::string> _paths)
		: dataKind (_dataKind), name(_name), paths(_paths) {};
};
Syntax_AddResourseElement parse(const std::string& input);
#endif