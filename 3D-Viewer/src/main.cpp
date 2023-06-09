#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "QT_3D_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  s21::MainWindow w;
  w.show();
  return a.exec();
}
