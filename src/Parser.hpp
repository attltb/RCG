#ifndef _ParserHeader_
#define _ParserHeader_
#include <string>
#include <vector>
#include <memory>
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

class Syntax_ {
public:
	enum class Kind { Annotation, AddResourseElement };

public:
	Kind kind;

public:
	Syntax_(Kind _kind) : kind(_kind) {};
	virtual ~Syntax_() {};
};
class Syntax_Annotation : public Syntax_ {
public:
	Syntax_Annotation() : Syntax_(Kind::Annotation) {};
};
class Syntax_AddResourseElement : public Syntax_ {
public:
	ResourceKind dataKind;
	std::string name;
	std::vector<std::string> paths;

public:
	Syntax_AddResourseElement(ResourceKind _dataKind, std::string _name, std::vector<std::string> _paths)
		: Syntax_(Kind::AddResourseElement), dataKind (_dataKind), name(_name), paths(_paths) {};
};
class Syntax {
	std::shared_ptr<Syntax_> ptr;
	Syntax(std::shared_ptr<Syntax_> _ptr) : ptr(_ptr) {}

public:
	Syntax() : ptr() {}
	Syntax(const Syntax& other) : ptr(other.ptr) {}

public:
	Syntax_::Kind kind() {
		return ptr->kind;
	}
	Syntax_Annotation* as_Annotation() {
		return (Syntax_Annotation*)ptr.get();
	}
	Syntax_AddResourseElement* as_AddResourseElement() {
		return (Syntax_AddResourseElement*)ptr.get();
	}

public:
	static Syntax annotation() {
		return std::shared_ptr<Syntax_>(new Syntax_Annotation());
	}
	static Syntax addResourseElement(ResourceKind dataKind, std::string name, std::vector<std::string> paths) {
		return std::shared_ptr<Syntax_>(new Syntax_AddResourseElement(dataKind, name, paths));
	}
};
Syntax parse(const std::string& input);
#endif