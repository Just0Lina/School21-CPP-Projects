#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QString>
namespace s21 {
class StyleHelper {
public:
  StyleHelper() = default;
  ~StyleHelper() = default;

  static QString getStyleButton1() {
    return "QPushButton {"
           "background-color: #9DB9C3;"
           "border: 5px double  #E7EEF0;"
           "color: #E7EEF0;"
           "border-right: 4px solid #6D96A5;"
           "border-bottom: 5px solid #6D96A5 ;"
           "}"
           "QPushButton:pressed {"
           "background-color: #E7EEF0;"
           "border: 5px double  #85A8B4;"
           "padding: 5px;color: #85A8B4;"
           "}";
  }
  static QString getStyleButton2() {
    return "QPushButton {"
           "background-color: #C2D3DA;"
           "border: 5px double  #E7EEF0;"
           "color: #FFFFFF;"
           "border-right: 4px solid #91B0BC ;"
           "border-bottom: 5px solid #6D96A5 ;"
           "}"
           "QPushButton:pressed {"
           "background-color: #E7EEF0;"
           "border: 5px double  #85A8B4;"
           "padding: 5px;color: #85A8B4;"
           "}";
  }
  static QString getStyleButton3() {
    return "QPushButton {"
           "background-color: #DAE5E9;"
           "border: 5px double  #FFFFFF;"
           "color: #124559;"
           "border-right: 4px solid #85A8B4 ;"
           "border-bottom: 5px solid #85A8B4 ;"
           "}"
           "QPushButton:pressed {"
           "background-color: #85A8B4;"
           "border: 5px double  #E7EEF0;"
           "padding: 5px;color: #E7EEF0;"
           "}";
  }
  static QString getStyleLabel() {
    return "QLineEdit {"
           "background-color: #F3F6F8;"
           "color: #124559;"
           "}";
  }
};
}
#endif // STYLEHELPER_H
