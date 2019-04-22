#include "SocketDataParser.h"


SocketDataParser::SocketDataParser(const string & strDataBuff, InverterData &invData_dest)
{
	m_strBuff = strDataBuff;
	map<string, string> mapKey2Value_tmp;

	//Energy
	if (ParseBlock(SOCKET_ENERGY_START_MARK, SOCKET_ENERGY_END_MARK, mapKey2Value_tmp))
	{
		invData_dest.SetCurrentPower(stoi(mapKey2Value_tmp[POWER_GRID_NAME])); //Set Power
		invData_dest.SetDayEnergy(stof(mapKey2Value_tmp[DAY_ENERGY_NAME])); // Set day energy
		invData_dest.SetTotalEnergy(stof(mapKey2Value_tmp[TOTAL_ENERGY_NAME])); //Set total energy
		invData_dest.SetStatus(mapKey2Value_tmp[STATUS_NAME]); //Set inverter status
	}

	//Hourly power
	mapKey2Value_tmp.clear();
	if (ParseBlock(SOCKET_HOURLY_POWER_START_MARK, SOCKET_HOURLY_POWER_END_MARK, mapKey2Value_tmp))
	{		
		for (const auto it : mapKey2Value_tmp)
			invData_dest.m_mapHourlyPowerData[stoi(it.first)] = stof(it.second); //Convert kWh to Wh
	}

	//Monthly power
	mapKey2Value_tmp.clear();
	if (ParseBlock(SOCKET_MONTHLY_POWER_START_MARK, SOCKET_MONTHLY_POWER_END_MARK, mapKey2Value_tmp))
	{
		for (const auto it : mapKey2Value_tmp)
			invData_dest.m_mapMonthlyPowerData[stoi(it.first)] = stof(it.second);
	}
}

string SubStr(const string &str, const char* szStartPoint, const char* szEndPoint)
{
	int nStartPointIndex = str.rfind(szStartPoint);
	if (nStartPointIndex == -1)
		return "";

	int nEndPointIndex = str.find(szEndPoint, nStartPointIndex);
	if (nEndPointIndex == -1) 
		return "";

	return str.substr(nStartPointIndex + strlen(szStartPoint), nEndPointIndex - nStartPointIndex-strlen(szStartPoint));
}

vector<string> SplitStr(const string &str, const char* delimiter)
{
	int nStartPoint = 0, nDelimiterInd = 0;
	vector<string> res;
	while (true)
	{
		if ((nDelimiterInd = str.find(delimiter, nStartPoint)) >= 0)
		{
			res.push_back(str.substr(nStartPoint, nDelimiterInd - nStartPoint));
			nStartPoint = nDelimiterInd + strlen(delimiter);
		}
		else
		{
			res.push_back(str.substr(nStartPoint));
			break;
		}
	}
	return res;
}

bool SocketDataParser::ParseBlock(const char* szStartPoint, const char* szEndPoint, map<string, string> & mapKey2Value)
{	
	auto strEnergy = SubStr(m_strBuff, szStartPoint, szEndPoint);
	if (!strEnergy.size()) return false;

	vector<string> lines = SplitStr(strEnergy, "\r\n");
	for (const auto &str : lines)
	{
		auto lst = SplitStr(str, SOCKET_DATA_KEY_VALUE_SEPARATOR);
		if(lst.size()>1)
			mapKey2Value[lst[0]] = lst[1];
	}	
	return true;
}


