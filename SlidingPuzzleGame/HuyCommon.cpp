#include "HuyCommon.h"

wstring MyCommon::trim(wstring str) {
	wstring result = str;
	while (result.at(0) == L' ') result = result.substr(1);
	while (result.at(result.size() - 1) == L' ') result = result.substr(0, result.size() - 1);

	return result;
}
string MyCommon::trim(string str) {
	string result = str;
	while (result.at(0) == L' ') result = result.substr(1);
	while (result.at(result.size() - 1) == L' ') result = result.substr(0, result.size() - 1);

	return result;
} 