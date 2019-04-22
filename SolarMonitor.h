#ifndef SolarMonitor_H
#define SolarMonitor_H

#include <QtWidgets/QMainWindow>
#include "ui_SolarMonitor.h"
#include <QtCharts>
#include <QTimer>
#include <QPixmap>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include "names.h"
#include "InverterData.h"
#include "MultiLangText.h"

#include "SocketDataParser.h"
#include <map>


#define DATE_FORMAT_IN_SOCKET "MM.dd.yyyy"
#define DATE_FORMAT_FOR_GUI "MMMM dd, yyyy"

using namespace std;




struct InvData
{
	QByteArray m_qbaSN="";
	bool m_bIsOnline = false;
	float m_fPgrid = 0.0; //Watt
	float m_fDayEnergy = 0.0; //KWh
	float m_fTotalEnergy = 0.0; //KWh
	float m_fHourTotal = 0.0;

	inline void clear()
	{ 
		m_qbaSN.clear(); 
		m_fPgrid = m_fDayEnergy = m_fTotalEnergy = m_fHourTotal = 0.0; 
	}
};
struct EnergyElement
{
	EnergyElement(const QByteArray &qbaValue, const QByteArray &qbaUnit) : m_qbaValue(qbaValue), m_qsUnit(qbaUnit)
	{
		bool bIsNumber = false;
		m_fValue = qbaValue.toFloat(&bIsNumber);
		if(bIsNumber)
			m_qbaValue = "";
	}
	EnergyElement() {}	
	
	float m_fValue = 0.0;
	QByteArray m_qbaValue = "";
	QByteArray m_qsUnit = "";

	inline QByteArray ToOneString() const { return m_qbaValue + " " + m_qsUnit; }
};


class SolarMonitor : public QMainWindow
{
	Q_OBJECT

public:
	SolarMonitor(QWidget *parent = 0);
	~SolarMonitor();
	

public slots:
	
	void UpdateData(); //Update all values
	
	static float CalcReducedCO2(float fProducedEnergy) { return 0.8f * fProducedEnergy; }
	static int CalcPlantedTrees(float fReducedCO2) { return (int)(fReducedCO2/18.0); }


private:
	Ui::SolarMonitorClass ui;

	void ShowMessage(const QString & strMessage, LogType messageType);
	bool ReadDataFile(const QString &strFilePath, QHash<QString, QString> &qhashKey2Value, QString &strErrMsg);
	bool CheckConfigData(const QHash<QString, QString> qhashConfigData2Value, QString &strErrMsg);

	//Init charts
	void InitPowerChart();
	QBarSeries* InitEnergyChart(QChartView *chartView, const QString &qsChartTitle, const QStringList &qslX_Axis_categories, float fMaxVal, int nTickCount);

	//Update charts
	void SetMarkerColor(const QColor &color);
	void UpdatePowerChart();
	void UpdateEnergyValues();
	void UpdateEnergyChart(QBarSeries * const pbars, const map<int, float> & mapKey2Value, bool bUseCategoryPosition);
	
	//Socket
	QString m_qsServerIP;
	int m_nPort = 0;
	QTcpSocket *m_pSocket = NULL;
	
	//Charts
	QLabel m_qlabelPower;
	bool m_color_switch_flag = false;
	QVector<QLabel*> m_qvlabelsPower;
	QPieSeries *m_pieCurPowerseries = NULL;
	QBarSeries *m_pHourlyChart_series = NULL;
	QBarSeries *m_pMonthlyChart_series = NULL;


	QString m_qsDefFontName;
		

	QTimer *m_pUpdateTimer = NULL;	
	
	InverterData m_invData;

	CMultiLangText* m_pML_Text = NULL;

	QString m_qsProgDir;

	//Log	
	QFile m_qfileLog;

};

#endif // SolarMonitor_H
