/********************************************************************************
** Form generated from reading UI file 'SolarMonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLARMONITOR_H
#define UI_SOLARMONITOR_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SolarMonitorClass
{
public:
    QWidget *centralWidget;
    QLabel *company_logo;
    QGroupBox *Power_groupBox;
    QtCharts::QChartView *PowerChart_widget;
    QLabel *label_Power_title;
    QGroupBox *Env_groupBox;
    QLabel *label_static_EnvTitle;
    QLabel *label_CO_Total;
    QLabel *label_static_EnvTotal;
    QLabel *label_static_EnvToday;
    QLabel *label_CO2_Today;
    QLabel *label_PlantedTrees;
    QLabel *env_logo;
    QLabel *label_CO_Total_unit;
    QLabel *label_CO2_Today_unit;
    QGroupBox *Charts_groupBox;
    QtCharts::QChartView *MonthChart_widget;
    QtCharts::QChartView *HourChart_widget;
    QGroupBox *Eng_groupBox;
    QLabel *label_static_EnergyTotal;
    QLabel *label_TotalEnergy;
    QLabel *label_static_EnergyTitle;
    QLabel *label_TodayEnergy;
    QLabel *label_static_EnergyToday;
    QLabel *energy_logo;
    QLabel *label_TodayEnergy_unit;
    QLabel *label_TotalEnergy_unit;

    void setupUi(QMainWindow *SolarMonitorClass)
    {
        if (SolarMonitorClass->objectName().isEmpty())
            SolarMonitorClass->setObjectName(QStringLiteral("SolarMonitorClass"));
        SolarMonitorClass->setEnabled(true);
        SolarMonitorClass->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SolarMonitorClass->sizePolicy().hasHeightForWidth());
        SolarMonitorClass->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("MS Sans Serif"));
        SolarMonitorClass->setFont(font);
        SolarMonitorClass->setContextMenuPolicy(Qt::NoContextMenu);
        SolarMonitorClass->setAutoFillBackground(false);
        SolarMonitorClass->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(SolarMonitorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QStringLiteral(""));
        company_logo = new QLabel(centralWidget);
        company_logo->setObjectName(QStringLiteral("company_logo"));
        company_logo->setGeometry(QRect(35, 70, 200, 220));
        company_logo->setStyleSheet(QStringLiteral("background-image: url(\"./img/logo_eng.png\") no-repeat center center stretch; border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        Power_groupBox = new QGroupBox(centralWidget);
        Power_groupBox->setObjectName(QStringLiteral("Power_groupBox"));
        Power_groupBox->setGeometry(QRect(40, 386, 230, 260));
        Power_groupBox->setStyleSheet(QStringLiteral("background:white;background-color: rgba( 255, 255, 255, 225);border-radius: 25px"));
        PowerChart_widget = new QtCharts::QChartView(Power_groupBox);
        PowerChart_widget->setObjectName(QStringLiteral("PowerChart_widget"));
        PowerChart_widget->setGeometry(QRect(0, 0, 230, 260));
        PowerChart_widget->setAutoFillBackground(false);
        PowerChart_widget->setStyleSheet(QStringLiteral("background-image: url(\"\"); background-color: rgba( 255, 255, 255, 0 )"));
        label_Power_title = new QLabel(PowerChart_widget);
        label_Power_title->setObjectName(QStringLiteral("label_Power_title"));
        label_Power_title->setGeometry(QRect(19, 10, 191, 70));
        QFont font1;
        font1.setPointSize(25);
        label_Power_title->setFont(font1);
        label_Power_title->setScaledContents(false);
        label_Power_title->setAlignment(Qt::AlignCenter);
        label_Power_title->setWordWrap(true);
        Env_groupBox = new QGroupBox(centralWidget);
        Env_groupBox->setObjectName(QStringLiteral("Env_groupBox"));
        Env_groupBox->setGeometry(QRect(319, 335, 480, 310));
        Env_groupBox->setStyleSheet(QStringLiteral("background:white;background-color: rgba( 255, 255, 255, 225);border-radius: 25px"));
        label_static_EnvTitle = new QLabel(Env_groupBox);
        label_static_EnvTitle->setObjectName(QStringLiteral("label_static_EnvTitle"));
        label_static_EnvTitle->setGeometry(QRect(0, 15, 480, 51));
        QFont font2;
        font2.setFamily(QStringLiteral("MS Sans Serif"));
        font2.setPointSize(22);
        label_static_EnvTitle->setFont(font2);
        label_static_EnvTitle->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_static_EnvTitle->setAlignment(Qt::AlignCenter);
        label_static_EnvTitle->setWordWrap(true);
        label_CO_Total = new QLabel(Env_groupBox);
        label_CO_Total->setObjectName(QStringLiteral("label_CO_Total"));
        label_CO_Total->setGeometry(QRect(250, 230, 151, 50));
        QFont font3;
        font3.setFamily(QStringLiteral("MS Sans Serif"));
        font3.setPointSize(28);
        font3.setBold(false);
        font3.setWeight(50);
        label_CO_Total->setFont(font3);
        label_CO_Total->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_CO_Total->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_static_EnvTotal = new QLabel(Env_groupBox);
        label_static_EnvTotal->setObjectName(QStringLiteral("label_static_EnvTotal"));
        label_static_EnvTotal->setGeometry(QRect(20, 230, 230, 50));
        QFont font4;
        font4.setFamily(QStringLiteral("MS Sans Serif"));
        font4.setPointSize(16);
        label_static_EnvTotal->setFont(font4);
        label_static_EnvTotal->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_static_EnvTotal->setInputMethodHints(Qt::ImhNone);
        label_static_EnvTotal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_static_EnvTotal->setWordWrap(true);
        label_static_EnvToday = new QLabel(Env_groupBox);
        label_static_EnvToday->setObjectName(QStringLiteral("label_static_EnvToday"));
        label_static_EnvToday->setGeometry(QRect(160, 170, 101, 31));
        label_static_EnvToday->setFont(font4);
        label_static_EnvToday->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_static_EnvToday->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_CO2_Today = new QLabel(Env_groupBox);
        label_CO2_Today->setObjectName(QStringLiteral("label_CO2_Today"));
        label_CO2_Today->setGeometry(QRect(250, 160, 151, 50));
        QFont font5;
        font5.setFamily(QStringLiteral("MS Sans Serif"));
        font5.setPointSize(28);
        label_CO2_Today->setFont(font5);
        label_CO2_Today->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_CO2_Today->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_PlantedTrees = new QLabel(Env_groupBox);
        label_PlantedTrees->setObjectName(QStringLiteral("label_PlantedTrees"));
        label_PlantedTrees->setGeometry(QRect(160, 70, 291, 91));
        label_PlantedTrees->setFont(font4);
        label_PlantedTrees->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_PlantedTrees->setTextFormat(Qt::AutoText);
        label_PlantedTrees->setScaledContents(false);
        label_PlantedTrees->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_PlantedTrees->setWordWrap(true);
        env_logo = new QLabel(Env_groupBox);
        env_logo->setObjectName(QStringLiteral("env_logo"));
        env_logo->setGeometry(QRect(50, 100, 100, 90));
        env_logo->setStyleSheet(QStringLiteral("background-image: url(\"./img/env_logo.png\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_CO_Total_unit = new QLabel(Env_groupBox);
        label_CO_Total_unit->setObjectName(QStringLiteral("label_CO_Total_unit"));
        label_CO_Total_unit->setGeometry(QRect(410, 241, 61, 31));
        label_CO_Total_unit->setFont(font4);
        label_CO_Total_unit->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_CO_Total_unit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_CO2_Today_unit = new QLabel(Env_groupBox);
        label_CO2_Today_unit->setObjectName(QStringLiteral("label_CO2_Today_unit"));
        label_CO2_Today_unit->setGeometry(QRect(410, 170, 61, 31));
        label_CO2_Today_unit->setFont(font4);
        label_CO2_Today_unit->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_CO2_Today_unit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Charts_groupBox = new QGroupBox(centralWidget);
        Charts_groupBox->setObjectName(QStringLiteral("Charts_groupBox"));
        Charts_groupBox->setGeometry(QRect(850, 55, 400, 590));
        Charts_groupBox->setStyleSheet(QStringLiteral("background:white;background-color: rgba( 255, 255, 255, 225);border-radius: 25px"));
        MonthChart_widget = new QtCharts::QChartView(Charts_groupBox);
        MonthChart_widget->setObjectName(QStringLiteral("MonthChart_widget"));
        MonthChart_widget->setGeometry(QRect(-20, 260, 441, 341));
        MonthChart_widget->setAutoFillBackground(false);
        MonthChart_widget->setStyleSheet(QStringLiteral("background-image: url(\"\"); background-color: rgba( 255, 255, 255, 0 )"));
        HourChart_widget = new QtCharts::QChartView(Charts_groupBox);
        HourChart_widget->setObjectName(QStringLiteral("HourChart_widget"));
        HourChart_widget->setGeometry(QRect(-20, -20, 441, 321));
        HourChart_widget->setAutoFillBackground(false);
        HourChart_widget->setStyleSheet(QStringLiteral("background-image: url(\"\"); background-color: rgba( 255, 255, 255, 0 )"));
        Eng_groupBox = new QGroupBox(centralWidget);
        Eng_groupBox->setObjectName(QStringLiteral("Eng_groupBox"));
        Eng_groupBox->setGeometry(QRect(319, 55, 480, 222));
        Eng_groupBox->setStyleSheet(QStringLiteral("background:white;background-color: rgba( 255, 255, 255, 225);border-radius: 25px"));
        label_static_EnergyTotal = new QLabel(Eng_groupBox);
        label_static_EnergyTotal->setObjectName(QStringLiteral("label_static_EnergyTotal"));
        label_static_EnergyTotal->setGeometry(QRect(10, 160, 230, 50));
        label_static_EnergyTotal->setFont(font4);
        label_static_EnergyTotal->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_static_EnergyTotal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_static_EnergyTotal->setWordWrap(true);
        label_TotalEnergy = new QLabel(Eng_groupBox);
        label_TotalEnergy->setObjectName(QStringLiteral("label_TotalEnergy"));
        label_TotalEnergy->setGeometry(QRect(250, 160, 141, 50));
        label_TotalEnergy->setMaximumSize(QSize(16777208, 16777215));
        label_TotalEnergy->setFont(font5);
        label_TotalEnergy->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_TotalEnergy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_static_EnergyTitle = new QLabel(Eng_groupBox);
        label_static_EnergyTitle->setObjectName(QStringLiteral("label_static_EnergyTitle"));
        label_static_EnergyTitle->setGeometry(QRect(0, 10, 480, 41));
        label_static_EnergyTitle->setFont(font2);
        label_static_EnergyTitle->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_static_EnergyTitle->setAlignment(Qt::AlignCenter);
        label_static_EnergyTitle->setWordWrap(true);
        label_TodayEnergy = new QLabel(Eng_groupBox);
        label_TodayEnergy->setObjectName(QStringLiteral("label_TodayEnergy"));
        label_TodayEnergy->setGeometry(QRect(250, 80, 141, 50));
        label_TodayEnergy->setFont(font5);
        label_TodayEnergy->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_TodayEnergy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_static_EnergyToday = new QLabel(Eng_groupBox);
        label_static_EnergyToday->setObjectName(QStringLiteral("label_static_EnergyToday"));
        label_static_EnergyToday->setGeometry(QRect(150, 90, 101, 31));
        label_static_EnergyToday->setFont(font4);
        label_static_EnergyToday->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_static_EnergyToday->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        energy_logo = new QLabel(Eng_groupBox);
        energy_logo->setObjectName(QStringLiteral("energy_logo"));
        energy_logo->setGeometry(QRect(50, 60, 100, 90));
        energy_logo->setStyleSheet(QStringLiteral("background-image: url(\"./img/energy_logo.png\");border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_TodayEnergy_unit = new QLabel(Eng_groupBox);
        label_TodayEnergy_unit->setObjectName(QStringLiteral("label_TodayEnergy_unit"));
        label_TodayEnergy_unit->setGeometry(QRect(400, 90, 71, 31));
        label_TodayEnergy_unit->setFont(font4);
        label_TodayEnergy_unit->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_TodayEnergy_unit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_TotalEnergy_unit = new QLabel(Eng_groupBox);
        label_TotalEnergy_unit->setObjectName(QStringLiteral("label_TotalEnergy_unit"));
        label_TotalEnergy_unit->setGeometry(QRect(400, 175, 71, 21));
        label_TotalEnergy_unit->setFont(font4);
        label_TotalEnergy_unit->setStyleSheet(QStringLiteral("background-image: url(\"\"); border-radius: 0px; background-color: rgba(0, 0, 0, 0)"));
        label_TotalEnergy_unit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        SolarMonitorClass->setCentralWidget(centralWidget);

        retranslateUi(SolarMonitorClass);

        QMetaObject::connectSlotsByName(SolarMonitorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SolarMonitorClass)
    {
        SolarMonitorClass->setWindowTitle(QApplication::translate("SolarMonitorClass", "SolarMonitorClient", Q_NULLPTR));
        company_logo->setText(QString());
        Power_groupBox->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        PowerChart_widget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_Power_title->setText(QApplication::translate("SolarMonitorClass", "Current Power", Q_NULLPTR));
        Env_groupBox->setTitle(QString());
        label_static_EnvTitle->setText(QApplication::translate("SolarMonitorClass", "Environmental savings", Q_NULLPTR));
        label_CO_Total->setText(QApplication::translate("SolarMonitorClass", "0.0", Q_NULLPTR));
        label_static_EnvTotal->setText(QApplication::translate("SolarMonitorClass", "Total:", Q_NULLPTR));
        label_static_EnvToday->setText(QApplication::translate("SolarMonitorClass", "TODAY:", Q_NULLPTR));
        label_CO2_Today->setText(QApplication::translate("SolarMonitorClass", "0.0", Q_NULLPTR));
        label_PlantedTrees->setText(QApplication::translate("SolarMonitorClass", "CO2 REDUCTION IS EQUAL TO %s PLANTED TREES", Q_NULLPTR));
        env_logo->setText(QString());
        label_CO_Total_unit->setText(QApplication::translate("SolarMonitorClass", "KG", Q_NULLPTR));
        label_CO2_Today_unit->setText(QApplication::translate("SolarMonitorClass", "KG", Q_NULLPTR));
        Charts_groupBox->setTitle(QString());
        Eng_groupBox->setTitle(QString());
        label_static_EnergyTotal->setText(QApplication::translate("SolarMonitorClass", "Total:", Q_NULLPTR));
        label_TotalEnergy->setText(QApplication::translate("SolarMonitorClass", "0.0", Q_NULLPTR));
        label_static_EnergyTitle->setText(QApplication::translate("SolarMonitorClass", "Produced energy", Q_NULLPTR));
        label_TodayEnergy->setText(QApplication::translate("SolarMonitorClass", "0.0", Q_NULLPTR));
        label_static_EnergyToday->setText(QApplication::translate("SolarMonitorClass", "TODAY:", Q_NULLPTR));
        energy_logo->setText(QString());
        label_TodayEnergy_unit->setText(QApplication::translate("SolarMonitorClass", "KWH", Q_NULLPTR));
        label_TotalEnergy_unit->setText(QApplication::translate("SolarMonitorClass", "KWH", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SolarMonitorClass: public Ui_SolarMonitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLARMONITOR_H
