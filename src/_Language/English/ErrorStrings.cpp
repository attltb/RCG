#include "ErrorStrings.hpp"
std::string getErrorString_UnexpectedToken(std::string token) {
	return "Error : Unexpected token \"" + token + "\"";
}
std::string getErrorString_UnexpectedToken_ExpectedIdentifier(std::string token) {
	return "Error : Unexpected token \"" + token + "\" (expected an identifier).\n";
}
std::string getErrorString_UnexpectedToken_ExpectedFilePath(std::string token) {
	return "Error : Unexpected token \"" + token + "\" (expected a file path).\n";
}
std::string getErrorString_UnexpectedToken_ExpectedFormat(std::string token) {
	return "Error : Unexpected token \"" + token + "\" (expected a resource format).\n";
}
std::string getErrorString_UnexpectedToken_Expected(std::string token, std::string tokenExpected) {
	return "Error : Unexpected token \"" + token + "\" (expected \"" + tokenExpected + "\").\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedIdentifier() {
	return "Error : Unexpected end of line (expected an identifier).\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedFilePath() {
	return "Error : Unexpected end of line (expected a file path).\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedFormat() {
	return "Error : Unexpected end of line (expected a resource format).\n";
}
std::string getErrorString_UnexpectedLineBreak_Expected(std::string tokenExpected) {
	return "Error : Unexpected end of line (expected \"" + tokenExpected + "\").\n";
}
std::string getErrorString_CannotParseALine(std::string line) {
	return "Error : Cannot parse a line \"" + line + "\".\n";
}

std::string getErrorString_File_CannotOpen(std::string fileName) {
	return "Cannot open file \"" + fileName + "\"를 열 수 없습니다.\n";
}
std::string getErrorString_File_CannotOpenImage(std::string fileName) {
	return "File \"" + fileName + "\" does not exist or not an image.\n";
}
std::string getErrorString_File_CannotCreate(std::string fileName) {
	return "An unknown error occured while reading file \"" + fileName + "\".\n";
}
std::string getErrorString_File_Unknown(std::string fileName) {
	return "Cannot create file \"" + fileName + "\".\n";
}