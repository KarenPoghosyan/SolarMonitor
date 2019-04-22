#include "SolarMonitor.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SolarMonitor w;
	w.show();
	return a.exec();
}
