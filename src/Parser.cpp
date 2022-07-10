#include "ErrorStrings.hpp"
#include "Parser.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
CharType getCharType(char ch) {
	switch (ch) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return CharType::CH_NUMBER;
	case '!':
	case '%':
	case '&':
	case '*':
	case '+':
	case '-':
	case '/':
	case '<':
	case '=':
	case '>':
	case '^':
	case '~':
	case '@':
	case '?':
	case '(':
	case ')':
	case '{':
	case '}':
	case '[':
	case ']':
		return CharType::CH_OPERATOR;
	case '.':
		return CharType::CH_DOT;
	case ':':
		return CharType::CH_COLON;
	case ',':
		return CharType::CH_COMMA;
	case '\'':
		return CharType::CH_QUOTE;
	case '\"':
		return CharType::CH_D_QUOTE;
	case '#':
		return CharType::CH_SHARP;
	case 0:
		return CharType::CH_NULL;
	case 9:
	case ' ':
		return CharType::CH_BLANK;
	case ';':
	case '\r':
	case '\n':
	case '\\':
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 127:
		return CharType::CH_OTHER;
	default:
		return CharType::CH_WORD;
	}
}
pair<string, TokenType> get_token(const char*& strptr) {
	for (; *strptr == ' ' || *strptr == '\t'; strptr++);
	if (!*strptr) return make_pair(string(), TokenType::TT_NULL);
	if (*strptr == '#') {
		for (; *strptr; strptr++);
		return make_pair(string(), TokenType::TT_NULL);
	}

	char char_st = *strptr;
	CharType ctype_st = getCharType(char_st);

	if (ctype_st == CharType::CH_WORD || ctype_st == CharType::CH_NUMBER) {
		const char* p_start = strptr;
		const char* p_cur = strptr + 1;
		for (;; p_cur++) {
			CharType ctype_nt = getCharType(*p_cur);
			if (ctype_nt != CharType::CH_NUMBER && ctype_nt != CharType::CH_WORD) break;
		}
		strptr = p_cur;
		return make_pair(string(p_start, p_cur - p_start), TokenType::TT_WORD);
	}

	if (ctype_st == CharType::CH_QUOTE) {
		const char* p_start = strptr;
		const char* p_cur = strptr + 1;
		for (;; p_cur++) {
			if (!*p_cur) break;
			if (*p_cur == '\'') {
				p_cur++;
				break;
			}
		}
		strptr = p_cur;
		return make_pair(string(p_start + 1, p_cur - p_start - 2), TokenType::TT_QUOTE);
	}

	if (ctype_st == CharType::CH_D_QUOTE) {
		const char* p_start = strptr;
		const char* p_cur = strptr + 1;
		for (;; p_cur++) {
			if (!*p_cur) break;
			if (*p_cur == '\"') {
				p_cur++;
				break;
			}
		}
		strptr = p_cur;
		return make_pair(string(p_start + 1, p_cur - p_start - 2), TokenType::TT_D_QUOTE);
	}

	string ret_str = string(1, char_st);
	strptr++;
	if (ctype_st == CharType::CH_COLON) return make_pair(ret_str, TokenType::TT_COLON);
	if (ctype_st == CharType::CH_COMMA) return make_pair(ret_str, TokenType::TT_COMMA);
	return make_pair(ret_str, TokenType::TT_OTHER);
}
vector<pair<string, TokenType>> get_tokens(const string& input) {
	const char* strptr = input.c_str();
	vector<pair<string, TokenType>> ret;
	for (;;) {
		pair<string, TokenType> token = get_token(strptr);
		if (token.second == TokenType::TT_NULL) break;
		if (token.second == TokenType::TT_OTHER) {
			cout << getErrorString_UnexpectedToken(token.first) << endl;
			return ret;
		}
		ret.push_back(token);
	}
	return ret;
}

bool check_token(vector<pair<string, TokenType>>& tokens, unsigned int i, string token_expected) {
	if (tokens.size() <= i) {
		cout << getErrorString_UnexpectedLineBreak_Expected(token_expected) << endl;
		return false;
	}

	pair<string, TokenType>& token = tokens[i];
	if (tokens[i].first != token_expected) {
		cout << getErrorString_UnexpectedToken_Expected(token.first, token_expected) << endl;
		return false;
	}
	return true;
}
string get_identifier(vector<pair<string, TokenType>>& tokens, unsigned int i) {
	if (tokens.size() <= i) {
		cout << getErrorString_UnexpectedLineBreak_ExpectedIdentifier() << endl;
		return string();
	}

	pair<string, TokenType>& token = tokens[i];
	if (token.second != TokenType::TT_WORD) {
		cout << getErrorString_UnexpectedLineBreak_ExpectedIdentifier() << endl;
		return string();
	}
	return token.first;
}
string get_path(vector<pair<string, TokenType>>& tokens, unsigned int i) {
	if (tokens.size() <= i) {
		cout << getErrorString_UnexpectedLineBreak_ExpectedFilePath() << endl;
		return string();
	}

	pair<string, TokenType>& token = tokens[i];
	if (token.second != TokenType::TT_D_QUOTE) {
		cout << getErrorString_UnexpectedToken_ExpectedFilePath(token.first) << endl;
		return string();
	}
	return token.first;
}
ResourceKind get_datakind(vector<pair<string, TokenType>>& tokens, unsigned int i) {
	if (tokens.size() <= i) {
		cout << getErrorString_UnexpectedLineBreak_ExpectedFormat() << endl;
		return ResourceKind::Invalid;
	}

	pair<string, TokenType>& token = tokens[i];
	if (token.first == "Binary") return ResourceKind::Binary;
	if (token.first == "Bitmap32") return ResourceKind::Bitmap32;

	cout << getErrorString_UnexpectedToken_ExpectedFormat(token.first) << endl;
	return ResourceKind::Invalid;
}

Syntax_AddResourseElement parse(const string& input) {
	vector<pair<string, TokenType>> tokens = get_tokens(input);
	if (tokens.empty()) return Syntax_AddResourseElement();

	try {
		string name = get_identifier(tokens, 0);
		if (name.empty()) throw 1;
		if (!check_token(tokens, 1, ":")) throw 2;

		vector<string> paths;
		unsigned int i = 2;
		for (; i < tokens.size(); i += 2) {
			string path = get_path(tokens, i);
			if (path.empty()) throw 3;
			paths.push_back(path);

			if (i + 1 == tokens.size() || tokens[i + 1].second != TokenType::TT_COMMA) {
				i++;
				break;
			}
		}
		if (i == tokens.size()) return Syntax_AddResourseElement(ResourceKind::Binary, name, paths);

		if (!check_token(tokens, i, "as")) throw 4;
		ResourceKind dataKind = get_datakind(tokens, i + 1);
		if (dataKind == ResourceKind::Invalid) throw 5;
		return Syntax_AddResourseElement(dataKind, name, paths);
	}
	catch (...) {
		cout << getErrorString_CannotParseALine(input) << endl;
		return Syntax_AddResourseElement();
	}
}