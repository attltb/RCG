#include "ErrorStrings.hpp"
std::string getErrorString_UnexpectedToken(std::string token) {
	return "���� : ����ġ ���� ��ū \"" + token + "\" �Դϴ�.\n";
}
std::string getErrorString_UnexpectedToken_ExpectedIdentifier(std::string token) {
	return "���� : ����ġ ���� ��ū \"" + token + "\" �Դϴ�. �ĺ��ڰ� �ʿ��մϴ�.\n";
}
std::string getErrorString_UnexpectedToken_ExpectedFilePath(std::string token) {
	return "���� : ����ġ ���� ��ū \"" + token + "\" �Դϴ�. ���� ��ΰ� �ʿ��մϴ�.\n";
}
std::string getErrorString_UnexpectedToken_ExpectedFormat(std::string token) {
	return "���� : ����ġ ���� ��ū \"" + token + "\" �Դϴ�. ���ҽ� ������ �ʿ��մϴ�.\n";
}
std::string getErrorString_UnexpectedToken_Expected(std::string token, std::string tokenExpected) {
	return "���� : ����ġ ���� ��ū \"" + token + "\" �Դϴ�. \"" + tokenExpected + "\"�� �ʿ��մϴ�.\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedIdentifier() {
	return "���� : ����ġ ���� �� �ٲ��Դϴ�. �ĺ��ڰ� �ʿ��մϴ�.\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedFilePath() {
	return "���� : ����ġ ���� �� �ٲ��Դϴ�. ���� ��ΰ� �ʿ��մϴ�.\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedFormat() {
	return "���� : ����ġ ���� �� �ٲ��Դϴ�. ���ҽ� ������ �ʿ��մϴ�.\n";
}
std::string getErrorString_UnexpectedLineBreak_Expected(std::string tokenExpected) {
	return "���� : ����ġ ���� �� �ٲ��Դϴ�. �ʿ��� ��ū�� \"" + tokenExpected + "\"�Դϴ�.\n";
}
std::string getErrorString_CannotParseALine(std::string line) {
	return "���� : �� \"" + line + "\"�� �Ľ��� �� �����ϴ�.\n";
}

std::string getErrorString_File_CannotOpen(std::string fileName) {
	return "���� \"" + fileName + "\"�� �� �� �����ϴ�.\n";
}
std::string getErrorString_File_CannotOpenImage(std::string fileName) {
	return "���� \"" + fileName + "\"�� ���ų� �̹��� ������ �ƴմϴ�.\n";
}
std::string getErrorString_File_CannotCreate(std::string fileName) {
	return "���� \"" + fileName + "\"�� �д� ���� �� �� ���� ������ �߻��߽��ϴ�.\n";
}
std::string getErrorString_File_Unknown(std::string fileName) {
	return "���� \"" + fileName + "\"�� ������ �� �����ϴ�.\n";
}