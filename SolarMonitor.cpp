#include "SolarMonitor.h"
#include "SocketDataParser.h"
using namespace QtCharts;


SolarMonitor::SolarMonitor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	m_qsProgDir = QCoreApplication::applicationDirPath();

	//Init log
	QDir qdirLogDir(m_qsProgDir + "/log");
	
	if (!qdirLogDir.exists())
		if (!qdirLogDir.mkdir(qdirLogDir.absolutePath()))
			printf("ERROR: Can't create a directory for log file.");
	
	m_qfileLog.setFileName(qdirLogDir.absolutePath() + "/DataFromInverter.log");
	m_qfileLog.open(QIODevice::WriteOnly);	

	m_qsDefFontName = "Arial";
	
	//Load config.ini file
	QHash<QString, QString> qhashConfigData;
	QString error;
	if (!ReadDataFile(m_qsProgDir + "/config.ini", qhashConfigData, error))
	{
		m_qfileLog.write(error.toLatin1());
		ShowMessage(error, INFO_LOG_TYPE);		
		exit(1);
	}
	
	if (!CheckConfigData(qhashConfigData, error))
	{
		m_qfileLog.write(error.toLatin1());
		ShowMessage(error, ERROR_LOG_TYPE);
		exit(1);
	}

	m_qsServerIP = qhashConfigData[SERVER_IP_NAME];
	m_nPort = qhashConfigData[SERVER_PORT_NAME].toInt();

	if (qhashConfigData[LANGUAGE_ARGUMENT_NAME].compare("am", Qt::CaseInsensitive) == 0)
		m_pML_Text = new CLang_AM;
	else if (qhashConfigData[LANGUAGE_ARGUMENT_NAME].compare("ru", Qt::CaseInsensitive) == 0)
		m_pML_Text = new CLang_RU;
	else
		m_pML_Text = new CLang_ENG;


	this->setWindowFlags(Qt::FramelessWindowHint);
	//this->showFullScreen();

	QPixmap bkgnd(qhashConfigData[BG_IMG_PATH]);
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);


	
	ui.company_logo->setStyleSheet("#company_logo{background: rgba(0,0,0,0)}");	
	QPixmap pixmapLogo(qhashConfigData[LOGO_PATH]);	
	ui.company_logo->setAlignment(Qt::AlignHCenter);
	ui.company_logo->setPixmap(pixmapLogo.scaled(ui.company_logo->width(), ui.company_logo->height(), Qt::KeepAspectRatio));
	
	
	ui.energy_logo->setStyleSheet("#energy_logo{background: rgba(0,0,0,0)}");
	QPixmap pixmapEnergyLogo(qhashConfigData[ENG_IMG_PATH]);
	ui.energy_logo->setAlignment(Qt::AlignHCenter);
	ui.energy_logo->setPixmap(pixmapEnergyLogo.scaled(ui.energy_logo->width(), ui.energy_logo->height(), Qt::KeepAspectRatio));

	ui.env_logo->setStyleSheet("#env_logo{background: rgba(0,0,0,0)}");
	QPixmap pixmapPlantLogo(qhashConfigData[ENV_IMG_PATH]);
	ui.env_logo->setAlignment(Qt::AlignHCenter);
	ui.env_logo->setPixmap(pixmapPlantLogo.scaled(ui.env_logo->width(), ui.env_logo->height(), Qt::KeepAspectRatio));
	
	InitPowerChart();

	//Init hourly energy chart
	QStringList categories;
	for (int iHour = 6; iHour < 22; iHour++)	
		categories << QString::number(iHour);
	m_pHourlyChart_series = InitEnergyChart(ui.HourChart_widget, m_pML_Text->m_qsHourlyPowerChart_title, categories, 1, 11);

	//Init monthly energy chart
	m_pMonthlyChart_series = InitEnergyChart(ui.MonthChart_widget, m_pML_Text->m_qsMonthlyPowerChart_title, m_pML_Text->m_qslMonthNames, 500, 11);
	

	//Init Energy group box
	ui.label_static_EnergyTitle->setText(m_pML_Text->m_qsEnergy_box_title);
	ui.label_static_EnergyToday->setText(m_pML_Text->m_qsToday);
	ui.label_static_EnergyTotal->setText(m_pML_Text->m_qsTotal);
	ui.label_TodayEnergy_unit->setText(m_pML_Text->m_qsKWH_upper);
	ui.label_TotalEnergy_unit->setText(m_pML_Text->m_qsKWH_upper);

	//Init Environment group box
	ui.label_static_EnvTitle->setText(m_pML_Text->m_qsEnv_box_title);
	ui.label_static_EnvToday->setText(m_pML_Text->m_qsToday);
	ui.label_static_EnvTotal->setText(m_pML_Text->m_qsTotal);
	ui.label_CO2_Today_unit->setText(m_pML_Text->m_qsKG);
	ui.label_CO_Total_unit->setText(m_pML_Text->m_qsKG);
	ui.label_PlantedTrees->setHidden(true);
	
	m_pSocket = new QTcpSocket();	
	
	m_pUpdateTimer = new QTimer();
	connect(m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(UpdateData()));
	m_pUpdateTimer->start(500);
}



SolarMonitor::~SolarMonitor()
{
	if (m_qfileLog.isOpen())
		m_qfileLog.close();
}


void SolarMonitor::ShowMessage(const QString & strMessage, LogType messageType)
{
	if (messageType == INFO_LOG_TYPE)
		QMessageBox::information(this, "INFO", "INFO: " + strMessage);
	else if (messageType == WARNING_LOG_TYPE)
		QMessageBox::warning(this, "WARNING", "WARNING: " + strMessage);
	else if(messageType== ERROR_LOG_TYPE)
		QMessageBox::critical(this, "ERROR", "ERROR: " + strMessage);
}

bool SolarMonitor::ReadDataFile(const QString &strFilePath, QHash<QString, QString> &qhashKey2Value, QString &strErrMsg)
{	
	bool bResult = false;
	QFile f(strFilePath);
	
	try
	{
		qhashKey2Value.clear();
		
		if (!f.open(QIODevice::ReadOnly))
			throw f.errorString();

		while (!f.atEnd())
		{
			QString qsLine_raw = f.readLine().constData();
			auto qsLine = qsLine_raw.trimmed();
			if (qsLine[0] == '#' || !qsLine.size())
				continue;

			auto qsList = qsLine.split(QRegExp("\\s"));
			if (qsList.size() != 2)
				throw QString("'%1' parameter in file is incorrect").arg(qsLine_raw);

			qhashKey2Value[qsList[0].trimmed()] = qsList[1].trimmed();
		}
		if (qhashKey2Value.isEmpty())
			throw QString("The file doesn't contain any valid parameter");

		//qhashKey2Value[BG_IMG_PATH] = QDir(qhashKey2Value[BG_IMG_PATH]).absolutePath();
		qhashKey2Value[LOGO_PATH] = QDir(qhashKey2Value[LOGO_PATH]).absolutePath();
		qhashKey2Value[ENG_IMG_PATH] = QDir(qhashKey2Value[ENG_IMG_PATH]).absolutePath();
		qhashKey2Value[ENV_IMG_PATH] = QDir(qhashKey2Value[ENV_IMG_PATH]).absolutePath();		

		bResult = true;
	}
	catch (const QString &err)
	{
		strErrMsg = QString("An error occurred while reading file '%1'. %2").arg(strFilePath).arg(err);
	}
	if (f.isOpen())
		f.close();

	return bResult;
}

bool SolarMonitor::CheckConfigData(const QHash<QString, QString> qhashConfigData2Value, QString &strErrMsg)
{
	//Check parameter existence
	try
	{
		if (!qhashConfigData2Value.contains(SERVER_IP_NAME))
			throw SERVER_IP_NAME;
		if (!qhashConfigData2Value.contains(SERVER_PORT_NAME))
			throw SERVER_PORT_NAME;
		if (!qhashConfigData2Value.contains(LANGUAGE_ARGUMENT_NAME))
			throw LANGUAGE_ARGUMENT_NAME;

		if (!qhashConfigData2Value.contains(BG_IMG_PATH))
			throw BG_IMG_PATH;
		if (!qhashConfigData2Value.contains(LOGO_PATH))
			throw LOGO_PATH;
		if (!qhashConfigData2Value.contains(ENG_IMG_PATH))
			throw ENG_IMG_PATH;
		if (!qhashConfigData2Value.contains(ENV_IMG_PATH))
			throw ENV_IMG_PATH;
	}
	catch (const char* szParamName)
	{
		strErrMsg = QString(szParamName) + "parameter is missing from configuration file.";
		return false;
	}

	//validate
	try
	{

		if (!QFile::exists(qhashConfigData2Value[BG_IMG_PATH]))
			throw QString(qhashConfigData2Value[BG_IMG_PATH]);
		
		if (!QFile::exists(qhashConfigData2Value[LOGO_PATH]))
			throw QString(qhashConfigData2Value[LOGO_PATH]);
		
		if (!QFile::exists(qhashConfigData2Value[ENG_IMG_PATH]))
			throw QString(qhashConfigData2Value[ENG_IMG_PATH]);
		
		if (!QFile::exists(qhashConfigData2Value[ENV_IMG_PATH]))
			throw QString(qhashConfigData2Value[ENV_IMG_PATH]);
		
	}
	catch (const QString &qsErr)
	{
		strErrMsg = "' " + qsErr + "' file doesn't not exist.";
		return false;
	}
	
	return true;
}


void SolarMonitor::InitPowerChart()
{
	QFont qfontLabels(m_pML_Text->m_qsFontName);	
	QFont qfontLegend(m_pML_Text->m_qsFontName);
	QFont qfontTitle(m_pML_Text->m_qsFontName);

	qfontTitle.setPointSize(20);
	ui.label_Power_title->setFont(qfontTitle);

	m_pieCurPowerseries = new QPieSeries();
	m_pieCurPowerseries->setHoleSize(0.4);
	m_pieCurPowerseries->setPieStartAngle(-90);
	m_pieCurPowerseries->setPieEndAngle(90);
	m_pieCurPowerseries->append("", 0);
	m_pieCurPowerseries->setPieSize(0.8);
	m_pieCurPowerseries->setVerticalPosition(0.74);

	//Active slice (green)
	QPieSlice *pActiveSlice = m_pieCurPowerseries->slices().at(0);
	pActiveSlice->setPen(QPen(Qt::white, 2));
	pActiveSlice->setBrush(QColor(153, 204, 51));	
	//pActiveSlice->setLabel("0 " + m_pML_Text->m_qsWatt);
	pActiveSlice->setLabelVisible(false);
	pActiveSlice->setValue(0);

	//Not acvtive slice (white zone)
	QPieSlice *pPassiveSlice = m_pieCurPowerseries->append("", 0);
	//slice2->setPen(QPen(Qt::darkGreen, 2));
	pPassiveSlice->setBrush(Qt::white);
	pPassiveSlice->setLabelVisible(false);
	pPassiveSlice->setValue(100);

	//Legend
	
	//qfontLegend.setPointSize(18);	
	//qfontLegend.setLetterSpacing(QFont::PercentageSpacing, 90);

	QChartView *chartView = ui.PowerChart_widget;
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->chart()->addSeries(m_pieCurPowerseries);
	chartView->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	chartView->chart()->setTitleBrush(QBrush(QColor(0, 0, 0)));
	chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
	//chartView->chart()->legend()->setFont(qfontLegend);
	chartView->chart()->legend()->markers(m_pieCurPowerseries)[0]->setBrush(QColor(Qt::darkGreen));
	chartView->chart()->legend()->markers(m_pieCurPowerseries)[0]->setPen(QColor(Qt::darkGreen));
	chartView->chart()->legend()->markers(m_pieCurPowerseries)[1]->setVisible(false);

	chartView->chart()->legend()->setVisible(false);
	chartView->chart()->setBackgroundVisible(false);
	

	
	qfontLabels.setPointSize(10);

	//Set header (title)
	ui.label_Power_title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.label_Power_title->move((ui.PowerChart_widget->width()/2 - ui.label_Power_title->width() / 2), ui.PowerChart_widget->y() + 10);
	ui.label_Power_title->setText(m_pML_Text->m_qsCurPowerChart_title);

	
	for (int i = 0; i < 3; i++)
	{
		m_qvlabelsPower.append(new QLabel("i"));
		m_qvlabelsPower.last()->resize(50, 15);
		m_qvlabelsPower.last()->setFont(qfontLabels);
		m_qvlabelsPower.last()->setWordWrap(true);
	}


	//Set Power numbers
	QPoint gboxCenter(ui.Power_groupBox->x() + (ui.Power_groupBox->width() / 2), ui.Power_groupBox->y() + (ui.Power_groupBox->height() / 2));

	
	m_qlabelPower.setText("0 " + m_pML_Text->m_qsWatt);
	m_qlabelPower.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_qlabelPower.resize(200, 200);
	qfontLegend.setPointSize(22);
	m_qlabelPower.setFont(qfontLegend);
	m_qlabelPower.setWordWrap(true);	

	m_qlabelPower.move((gboxCenter.x() - m_qlabelPower.width() / 2), gboxCenter.y() - (m_qlabelPower.height() / 2) + 85);
	
	this->layout()->addWidget(&m_qlabelPower);

	m_qvlabelsPower[0]->setText("0");
	m_qvlabelsPower[0]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_qvlabelsPower[0]->move((gboxCenter.x() - m_qvlabelsPower[0]->width() / 2) - 100, gboxCenter.y() + 35);

	m_qvlabelsPower[1]->setText(QString::number(INVETER_MAX_POWER / 2.0, 'f', 1));
	m_qvlabelsPower[1]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_qvlabelsPower[1]->move(gboxCenter.x()- m_qvlabelsPower[1]->width()/2, gboxCenter.y() - 40);

	m_qvlabelsPower[2]->setText(QString::number(INVETER_MAX_POWER, 'f', 1) + ' ' + ( m_pML_Text->m_qsKW));
	m_qvlabelsPower[2]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_qvlabelsPower[2]->move(gboxCenter.x() - m_qvlabelsPower[2]->width() / 2 + 98, gboxCenter.y() + 20);
	m_qvlabelsPower[2]->resize(30, 35);

	for (int i = 0; i<m_qvlabelsPower.size(); i++)
		this->layout()->addWidget(m_qvlabelsPower[i]);

}


QBarSeries* SolarMonitor::InitEnergyChart(QChartView *chartView, const QString &qsChartTitle, const QStringList &qslX_Axis_categories, float fMaxVal, int nTickCount)
{
	QFont qfontTitle(m_pML_Text->m_qsFontName);
	QFont qfontX_label(m_qsDefFontName);
	QFont qfontY_label(m_pML_Text->m_qsFontName);
	QColor qcolorText(Qt::black);

	int nXLabelAngle = 0;

	QBarSet *set0 = new QBarSet("bar1");	
	set0->setBrush(QColor(153, 204, 51));

	foreach (auto str, qslX_Axis_categories)
	{
		if (str.size() > 2)
			nXLabelAngle = -90;
		*set0 << 0;
	}
	

	QBarSeries* pSeries = new QBarSeries;
	pSeries->append(set0);
	//series->setBarWidth(1.5);	
	
	QBarCategoryAxis *axisX = new QBarCategoryAxis;
	axisX->append(qslX_Axis_categories);
	//axisX->setLabelsColor(QColor(255, 15, 51));
	axisX->setLineVisible(true);	
	axisX->setTitleBrush(QBrush(qcolorText));
	qfontX_label.setPointSize(8);
	//qfontSideLabel.setFixedPitch(false);
	axisX->setLabelsFont(qfontX_label);
	axisX->setLabelsAngle(nXLabelAngle);

	QValueAxis *axisY = new QValueAxis;	
	axisY->setLabelFormat("%.1f");
	axisY->setRange(0, fMaxVal);
	axisY->setTickCount(nTickCount);
	axisY->setTitleBrush(QBrush(qcolorText));
	qfontY_label.setPointSize(10);
	axisY->setLabelsFont(qfontY_label);
	axisY->setTitleText(m_pML_Text->m_qsKWH);
		
	
	QChart *chart = new QChart;	
	chart->addSeries(pSeries);
	chart->setAxisX(axisX, pSeries);
	chart->setAxisY(axisY, pSeries);
	//chart->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	chart->setTitle("<center>" + qsChartTitle + "</center>");
	//chart->createDefaultAxes();
	//w->scale(1.1,1.1);
	chart->setBackgroundRoundness(25);
	chart->legend()->hide(); // hide serie
	chart->setBackgroundVisible(false);
	chart->setTitleBrush(QBrush(qcolorText));
	qfontTitle.setPointSize(16);
	chart->setTitleFont(qfontTitle);
	chartView->setChart(chart);

	return pSeries;
}


void SolarMonitor::UpdateData()
{
	try
	{
		QByteArray qbaSockeBuff;

		//Update power marker color
		if (m_invData.GetStatus() == ONLINE_INV_STATE)
		{
			if (m_color_switch_flag)
				SetMarkerColor(QColor(153, 204, 51));
			else
				SetMarkerColor(QColor(Qt::darkGreen));
			m_color_switch_flag = !m_color_switch_flag;
		}

		

/*
		qbaSockeBuff = "EnergyStart\r\n\
S/N	1010KDTU158W0032\r\n\
Desc Inverter address	0x11\r\n\
Status	Normal\r\n\
Pgrid	8800.0\r\n\
Eday	113.3\r\n\
Etotal	114560.0\r\n\
Htotal	4560.0\r\n\
EnergyEnd\r\n\
HourlyPowerStart\r\n\
5\t10.0\r\n\
7\t11.2\r\n\
8\t12.5\r\n\
10\t13.3\r\n\
15\t15.3\r\n\
22\t14.2\r\n\
HourlyPowerEnd\r\n";
		qbaSockeBuff += "MonthlyPowerStart\r\n"
			"1\t150.0\r\n"
			"2\t160.0\r\n"
			"3\t170.0\r\n"
			"4\t180.6\r\n"
			"5\t400.6\r\n"
			"6\t200.6\r\n"
			"7\t250.6\r\n"
			"8\t260.6\r\n"
			"9\t210.6\r\n"
			"10\t180.6\r\n"
			"11\t180.6\r\n"
			"12\t180.6\r\n"
			"MonthlyPowerEnd\r\n";
*/
		m_invData.clear();
		if (m_pSocket->state() != QAbstractSocket::ConnectedState)
			m_pSocket->connectToHost(m_qsServerIP, m_nPort, QIODevice::ReadOnly);
		if (m_pSocket->waitForConnected(1000))
		{
			m_invData.SetStatus(OFFLINE_INV_STATE);

			m_pSocket->waitForReadyRead(1000);
			m_pSocket->readyRead();
			qbaSockeBuff = m_pSocket->readAll().trimmed();
			m_pSocket->flush();			
			
			m_qfileLog.write(QDateTime::currentDateTime().toString("HH:mm:ss").toLatin1() + "\r\n");
			m_qfileLog.write(qbaSockeBuff);

			if (!qbaSockeBuff.isEmpty())
			{
				m_invData.SetStatus(ONLINE_INV_STATE);

				//Parse data from socket
				SocketDataParser sockData(qbaSockeBuff.data(), m_invData);
				UpdatePowerChart();

				UpdateEnergyValues();

				UpdateEnergyChart(m_pHourlyChart_series, m_invData.GetHourlyPowerData(), false);
				UpdateEnergyChart(m_pMonthlyChart_series, m_invData.GetMonthlyPowerData(), true);
			}
		}
		else
		{
			m_invData.SetStatus(DISCONNECTED_INV_STATE);

			UpdatePowerChart();

			m_qfileLog.write("ERROR: Disconnected from server.");
		}



	}
	catch (...)
	{
		m_color_switch_flag = false;
		SetMarkerColor(QColor(Qt::red));
		m_invData.clear();
		m_qfileLog.write("ERROR: Data update failed.");
	}

	this->update();
	
}


void SolarMonitor::SetMarkerColor(const QColor &color)
{	
	QChart* pPowerChart = m_pieCurPowerseries->chart();
	pPowerChart->legend()->markers(m_pieCurPowerseries)[0]->setBrush(color);
	pPowerChart->legend()->markers(m_pieCurPowerseries)[0]->setPen(color);
}

void SolarMonitor::UpdatePowerChart()
{
	int nPower = m_invData.GetCurrentPower();

	float nMaxPowerValue = 10000;
	
	switch (m_invData.GetStatus())
	{
	case ONLINE_INV_STATE:
		if (nPower <= 1000)
			nMaxPowerValue = 1000;
		else if (nPower <= 5000)
			nMaxPowerValue = 5000;
		else if (nPower <= 10000)
			nMaxPowerValue = 10000;
		else
			nMaxPowerValue = 100000;

		m_pieCurPowerseries->slices()[0]->setValue(100 * nPower / nMaxPowerValue);
		m_qlabelPower.setText(QString::number(nPower) + ' ' + m_pML_Text->m_qsWatt);
		m_pieCurPowerseries->slices()[1]->setValue(100 - m_pieCurPowerseries->slices()[0]->value());

		break;

	case OFFLINE_INV_STATE:
		//SetMarkerColor(QColor(Qt::darkGray));
		m_qlabelPower.setText("<font color='gray'>" + m_pML_Text->m_qsOffline + "</font>");
		m_pieCurPowerseries->slices()[0]->setValue(0);
		m_pieCurPowerseries->slices()[1]->setValue(100);
		break;

	case DISCONNECTED_INV_STATE:
		//SetMarkerColor(QColor(Qt::red));
		m_qlabelPower.setText("<font color = 'red'>" + m_pML_Text->m_qsDisconnected + "</font>");
		m_pieCurPowerseries->slices()[0]->setValue(0);
		m_pieCurPowerseries->slices()[1]->setValue(100);
		break;
	};
	
	//set labels
	if (nMaxPowerValue >= 1000)
	{
		m_qvlabelsPower[1]->setText(QString::number(nMaxPowerValue / 2000.0, 'f', 1));
		m_qvlabelsPower[2]->setText(QString::number(nMaxPowerValue / 1000.0, 'f', 1) + ' ' + m_pML_Text->m_qsKW);
	}
	else
	{
		m_qvlabelsPower[1]->setText(QString::number(nMaxPowerValue / 2.0, 'f', 1));
		m_qvlabelsPower[2]->setText(QString::number(nMaxPowerValue) + ' ' + m_pML_Text->m_qsWatt);
	}
}

void SolarMonitor::UpdateEnergyValues()
{
	
	//ui.label_static_EnergyTotal->setText(QString(m_qsTotalMsg_pattern).arg(m_invData.GetStartDate().toString(DATE_FORMAT_FOR_GUI)));
	ui.label_static_EnergyTotal->setText(QString(m_pML_Text->m_qsTotalMsg_pattern).arg("2018.01.01"));
	ui.label_static_EnergyTotal->setHidden(false);

	//Set Today and Total energy
	ui.label_TodayEnergy->setText(QByteArray::number(m_invData.GetDayEnergy(),'f',1));
	ui.label_TodayEnergy_unit->setText(m_pML_Text->m_qsKWH_upper);

	ui.label_TotalEnergy->setText(QByteArray::number(m_invData.GetTotalEnergy(), 'f', 1));
	ui.label_TotalEnergy_unit->setText(m_pML_Text->m_qsKWH_upper);

	
	ui.label_static_EnvTotal->setText(QString(m_pML_Text->m_qsTotalMsg_pattern).arg("2018.01.01"));
	ui.label_static_EnvTotal->setHidden(false);
	
	//Reduced CO2 in tones
	float fReducedCO2 = 0.0;
	ui.label_CO2_Today->setText(QString::number(CalcReducedCO2(m_invData.GetDayEnergy()),'f',1));
	ui.label_CO2_Today_unit->setText(m_pML_Text->m_qsTon);

	ui.label_CO_Total->setText(QString::number(fReducedCO2 = CalcReducedCO2(m_invData.GetTotalEnergy()),'f',1));
	ui.label_CO_Total_unit->setText(m_pML_Text->m_qsTon);

	//Around six trees will fix 1 tonne of CO2
	//Convert total reduced CO2 to planted trees
	ui.label_PlantedTrees->setHidden(false);
	ui.label_PlantedTrees->setText(QString(m_pML_Text->m_qsTreesMsg_pattern).arg(CalcPlantedTrees(fReducedCO2)));	

}

void SolarMonitor::UpdateEnergyChart(QBarSeries * const pbars, const map<int, float> & mapKey2Value, bool bUseCategoryPosition)
{
	float fMaxValue = 0.0;

	auto axisY = static_cast<QValueAxis*>(pbars->chart()->axisY());
	auto axisX = static_cast<QBarCategoryAxis*>(pbars->chart()->axisX());

	
	for (auto it : mapKey2Value)
	{
		if (it.second > fMaxValue)
			fMaxValue = it.second;
	}

	if (fMaxValue < 1.0)
		axisY->setRange(0, 1.0);
	else if (fMaxValue < 10)
		axisY->setRange(0, 10);
	else if (fMaxValue < 30)
		axisY->setRange(0, 50);
	else if (fMaxValue < 100)
		axisY->setRange(0, 100);
	else if (fMaxValue < 500)
		axisY->setRange(0, 500);
	else if (fMaxValue < 1000)
		axisY->setRange(0, 1000);
	else
		axisY->setRange(0, 10000);
	
	
	const QStringList & cat = axisX->categories();
	std::map<int, float>::const_iterator it;	
	if (bUseCategoryPosition)
	{
		for (int i = 0; i < cat.size(); i++)
		{
			
			if ((it = mapKey2Value.find(i + 1)) != mapKey2Value.end())
				pbars->barSets()[0]->replace(i, it->second);			
			else
				pbars->barSets()[0]->replace(i, 0.0);
		}
	}
	else
	{
		for (int i = 0; i < cat.size(); i++)
		{
			if ((it = mapKey2Value.find(cat[i].toInt())) != mapKey2Value.end())
				pbars->barSets()[0]->replace(i, it->second);
			else
				pbars->barSets()[0]->replace(i, 0.0);
		}
	}
}
