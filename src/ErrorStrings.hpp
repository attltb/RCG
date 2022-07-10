#ifndef _ErrorStringsHeader_
#define _ErrorStringsHeader_
#include <string>
std::string getErrorString_UnexpectedToken(std::string token);
std::string getErrorString_UnexpectedToken_ExpectedIdentifier(std::string token);
std::string getErrorString_UnexpectedToken_ExpectedFilePath(std::string token);
std::string getErrorString_UnexpectedToken_ExpectedFormat(std::string token);
std::string getErrorString_UnexpectedToken_Expected(std::string token, std::string tokenExpected);
std::string getErrorString_UnexpectedLineBreak_ExpectedIdentifier();
std::string getErrorString_UnexpectedLineBreak_ExpectedFilePath();
std::string getErrorString_UnexpectedLineBreak_ExpectedFormat();
std::string getErrorString_UnexpectedLineBreak_Expected(std::string tokenExpected);
std::string getErrorString_CannotParseALine(std::string line);

std::string getErrorString_File_CannotOpen(std::string fileName);
std::string getErrorString_File_CannotOpenImage(std::string fileName);
std::string getErrorString_File_CannotCreate(std::string fileName);
std::string getErrorString_File_Unknown(std::string fileName);
#endif