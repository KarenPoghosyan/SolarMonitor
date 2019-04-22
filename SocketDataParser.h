#ifndef __SOCKET_DATA_PARSER__
#define __SOCKET_DATA_PARSER__

#include <string>
#include <cstring>
#include <map> 
#include <vector>
using namespace std;


#include "names.h"
#include "InverterData.h"

class SocketDataParser
{
public:
	SocketDataParser(const string & strDataBuff, InverterData &invData_dest);
	SocketDataParser(){}
	~SocketDataParser() {}	
//	inline const auto & GetLastError() const { return m_szError; }
	
private:
	bool ParseBlock(const char* szStartPoint, const char* szEndPoint, map<string, string> & mapKey2Value);

	string m_strBuff;
	
};

#endif

