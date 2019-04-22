#ifndef __GW_VALUE_NAMES__
#define __GW_VALUE_NAMES__

#define SN_NAME "S/N"
#define DESC_NAME "Desc"
#define STATUS_NAME "Status"
#define POWER_GRID_NAME "Pgrid"
#define DAY_ENERGY_NAME "Eday"
#define TOTAL_ENERGY_NAME "Etotal"
#define TOTAL_HOURS_NAME "Htotal"
#define START_DATE "StartDate"
#define ERR_NAME "Error"

#define V_PV0_NAME "Vpv0"
#define V_PV1_NAME "Vpv1"
#define I_PV0_NAME "Ipv0"
#define I_PV1_NAME "Ipv1"

#define V_AC0_NAME "Vac0"
#define V_AC1_NAME "Vac1"
#define V_AC2_NAME "Vac2"
#define I_AC0_NAME "Iac0"
#define I_AC1_NAME "Iac1"
#define I_AC2_NAME "Iac2"
#define F_AC0_NAME "Fac0"
#define F_AC1_NAME "Fac1"
#define F_AC2_NAME "Fac2"

#define TEMPERATURE_NAME "Temp"
#define V_BAT_NAME "Vbat"
#define SOC_NAME "SOC"
#define V_LOAD_NAME "Vload"
#define I_LOAD_NAME "Iload"
#define C_TOTAL_NAME "Ctot"
#define EFF_NAME "Eff"


#define SOCKET_DATA_KEY_VALUE_SEPARATOR "\t"


#define SOCKET_ENERGY_START_MARK "EnergyStart"
#define SOCKET_ENERGY_END_MARK "EnergyEnd"
#define SOCKET_HOURLY_POWER_START_MARK "HourlyPowerStart"
#define SOCKET_HOURLY_POWER_END_MARK "HourlyPowerEnd"
#define SOCKET_MONTHLY_POWER_START_MARK "MonthlyPowerStart"
#define SOCKET_MONTHLY_POWER_END_MARK "MonthlyPowerEnd"

#define INVETER_MAX_POWER 10.0

#define LANGUAGE_ARGUMENT_NAME "Language"

//config.ini
#define SERVER_IP_NAME "ServerIP"
#define SERVER_PORT_NAME  "ServerPort"
#define BG_IMG_PATH  "BackgroundImagePath"
#define LOGO_PATH  "LogoPath"
#define ENG_IMG_PATH  "EnergyImagePath"
#define ENV_IMG_PATH  "EnvironmentImagePath"

enum GUI_Language
{
	LANG_EN,
	LANG_AM,
};



enum LogType
{
	ERROR_LOG_TYPE,
	WARNING_LOG_TYPE,
	INFO_LOG_TYPE,
	DEBUG_LOG_TYPE,
};



#endif
