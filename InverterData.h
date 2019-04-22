#ifndef __INVERTER_DATA_H__
#define __INVERTER_DATA_H__

#include <QDate>
#include <map>
using namespace std;

enum InverterStatus
{
	ONLINE_INV_STATE,
	OFFLINE_INV_STATE,
	DISCONNECTED_INV_STATE
};

struct _Date
{
	int d = 0, m = 0, y = 0;
	void SetDate(int day, int mon, int year) { d = day; m = mon; y = year; }
};

class InverterData
{
	friend class SocketDataParser;
	private:
		string m_sSN = "";
		_Date m_dtStartDate;
		InverterStatus m_Status = DISCONNECTED_INV_STATE;
		int m_nPower = 0;
		float m_fDay_energy = 0.0;
		float m_fTotal_energy = 0.0;

		map<int, float> m_mapHourlyPowerData;
		map<int, float> m_mapMonthlyPowerData;

		
	public:
		//Set methods
		void SetSerialNumber(const string & sS_N) { m_sSN = sS_N; }
		void SetStartDate(int d, int m, int y) { m_dtStartDate.SetDate (y,m,d); }
		void SetStatus(InverterStatus Status)  { m_Status = Status; }
		void SetStatus(const string & strStatus) 
		{
			if(strStatus.compare("Normal") == 0)
				m_Status = ONLINE_INV_STATE;
			else if (strStatus.compare("Offline") == 0)
				m_Status = OFFLINE_INV_STATE;
			else
				m_Status = DISCONNECTED_INV_STATE;
		}
		void SetCurrentPower(int nPower)  { m_nPower = nPower; }
		void SetDayEnergy(float fE_Day)  { m_fDay_energy = fE_Day; }
		void SetTotalEnergy(float fE_Total)  { m_fTotal_energy = fE_Total; }

		void SetHourlyPowerData(const map<int, float> & mapH2Data) { m_mapHourlyPowerData = mapH2Data; }
		void SetMonthlyPowerData(const map<int, float> & mapM2Data) { m_mapMonthlyPowerData = mapM2Data; }

		//Get methods
		auto GetSerialNumber() const { return m_sSN; }
		auto GetStartDate() const { return m_dtStartDate; }
		auto GetStatus() const { return m_Status; }
		int GetCurrentPower() const { return m_nPower; }
		float GetDayEnergy() const { return m_fDay_energy; }
		float GetTotalEnergy() const { return m_fTotal_energy; }

		const auto & GetHourlyPowerData() const { return m_mapHourlyPowerData; }
		const auto & GetMonthlyPowerData() const { return m_mapMonthlyPowerData; }

		inline void clear()
		{
			m_sSN = "";
			m_Status = DISCONNECTED_INV_STATE;
			m_nPower = 0.0;
			m_fDay_energy = 0.0;
			m_fTotal_energy = 0.0;
			m_mapHourlyPowerData.clear();
			m_mapMonthlyPowerData.clear();
		}

		~InverterData()
		{
		}

	
	
};
#endif

