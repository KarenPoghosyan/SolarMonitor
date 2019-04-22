#ifndef __MULTI_LANG_TEXT__
#define __MULTI_LANG_TEXT__

#include "names.h"
#include "QtCore"

class CMultiLangText
{
public:
	CMultiLangText() {}
	~CMultiLangText() {}
	
	QString m_qsSuffix;
	QString m_qsFontName;

	QString m_qsCurPowerChart_title;
	QString m_qsHourlyPowerChart_title;
	QString m_qsMonthlyPowerChart_title;

	QString m_qsEnergy_box_title;
	QString m_qsEnv_box_title;

	QString m_qsToday;
	QString m_qsTotal;

	QString m_qsTotalMsg_pattern;
	QString m_qsTreesMsg_pattern;
	QString m_qsDisconnected;
	QString m_qsOffline;

	QString m_qsWatt;
	QString m_qsKW;
	QString m_qsKW_upper;	
	QString m_qsKWH;
	QString m_qsKWH_upper;
	QString m_qsKG;
	QString m_qsTon;

	QStringList m_qslMonthNames;
	
};


class CLang_ENG : public CMultiLangText
{
public:
	CLang_ENG()
	{
		m_qsFontName = "Arial";
		m_qsSuffix = "eng";
		m_qsCurPowerChart_title = "Current Power";
		m_qsHourlyPowerChart_title = "The amount of electricity <br> produced per hour a day";
		m_qsMonthlyPowerChart_title = "The amount of electricity <br> produced per month";

		m_qsEnergy_box_title = "Produced energy";
		m_qsEnv_box_title = "Environmental savings";

		m_qsToday = "TODAY:";
		m_qsTotal = "TOTAL:";

		m_qsTotalMsg_pattern = "TOTAL (starting from %1):";
		m_qsTreesMsg_pattern = "CO2 REDUCTION IS EQUAL TO %1 PLANTED TREES";
		

		m_qsDisconnected = "Disconnected from server";
		m_qsOffline = "Offline";



		m_qsWatt = "W";
		m_qsKW = "kW";
		m_qsKW_upper = "KW";
		m_qsKWH = "kWh";
		m_qsKWH_upper = "KWH";
		m_qsKG = "KG";
		m_qsTon = "TON";

		m_qslMonthNames << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
	}
};

class CLang_AM : public CMultiLangText
{
public:
	CLang_AM()
	{
		m_qsFontName = "Arial";
		m_qsSuffix = "am";
		m_qsCurPowerChart_title = u8"Ներկա հզորություն";
		m_qsHourlyPowerChart_title = u8"Արտադրվող էլ.էներգիայի ծավալը՝ <br> ըստ օրվա ժամերի";
		m_qsMonthlyPowerChart_title = u8"Արտադրվող էլ.էներգիայի ծավալը՝ <br> ըստ տարվա ամիսների";

		m_qsEnergy_box_title = u8"Արտադրված էներգիա";
		m_qsEnv_box_title = u8"Բնապահպանական օգուտը";

		m_qsToday = u8"ԱՅՍՕՐ՝";
		m_qsTotal = u8"ԸՆԴՀԱՆՈՒՐ՝";

		m_qsTotalMsg_pattern = u8"ԸՆԴՀԱՆՈՒՐ (ՍԿՍԱԾ %1 - ԻՑ)՝";
		m_qsTreesMsg_pattern = u8"CO2 ԱՐՏԱՆԵՏՄԱՆ ԿՐՃԱՏՈՒՄԸ ՀԱՄԱՐԺԵՔ Է %1 ՏՆԿԱԾ ԾԱՌԻ";

		m_qsDisconnected = "Disconnected from server";
		m_qsOffline = "Offline";

		m_qsWatt = u8"Վտ";
		m_qsKW = u8"կՎտ";
		m_qsKW_upper = u8"կՎտ";
		m_qsKWH = u8"կՎտ-ժ";
		m_qsKWH_upper = u8"ԿՎՏ-Ժ";
		m_qsKG = u8"ԿԳ";
		m_qsTon = u8"ՏՈՆ";

		m_qslMonthNames << u8"Հունվ" << u8"Փետր" << u8"Մարտ" << u8"Ապր" << u8"Մայ" << u8"Հուն" << u8"Հուլ" << u8"Օգ" << u8"Սեպտ" << u8"Հոկտ" << u8"Նոյ" << u8"Դեկտ";
	}
};


class CLang_RU: public CMultiLangText
{
public:
	CLang_RU()
	{
		m_qsFontName = "Arial";
		m_qsSuffix = "ru";
		m_qsCurPowerChart_title = u8"Производимая энергия";
		m_qsHourlyPowerChart_title = u8"Произведенная энергия <br> по часам";
		m_qsMonthlyPowerChart_title = u8"Произведенная энергия <br> по месяцам";

		m_qsEnergy_box_title = u8"Произведенная энергия";
		m_qsEnv_box_title = u8"Польза для окружающей среды";

		m_qsToday = u8"СЕГОДНЯ";
		m_qsTotal = u8"ОБЩАЯ";

		m_qsTotalMsg_pattern = u8"ОБЩАЯ (С %1 - а)";
		m_qsTreesMsg_pattern = u8"СООКРАЩЕННЫЙ ВЫБРОС CO2 РАВЕН %1 ПОСАЖЕННЫМ ДЕРЕВЬЯМ";

		m_qsDisconnected = "Disconnected from server";
		m_qsOffline = "Offline";

		m_qsWatt = u8"Вт";
		m_qsKW = u8"кВт";
		m_qsKW_upper = u8"кВт";
		m_qsKWH = u8"кВт-ч";
		m_qsKWH_upper = u8"КВТ-Ч";
		m_qsKG = u8"КГ";
		m_qsTon = u8"ТОН";

		m_qslMonthNames << u8"Янб" << u8"Февр" << u8"Март" << u8"Апр" << u8"Май" << u8"Июнь" << u8"Июль" << u8"Авг" << u8"Сен" << u8"Окт" << u8"Ной" << u8"Дек";
	}
};




#endif

