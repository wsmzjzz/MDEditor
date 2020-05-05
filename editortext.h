#ifndef EDITORTEXT_H
#define EDITORTEXT_H

#include <QObject>
#include <QString>

class EditorText : public QObject
{
  Q_OBJECT
//  Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged FINAL)
public:
  explicit EditorText(QObject *parent = nullptr) : QObject(parent) {}
    QString mdCodeText;
    void setText(const QString &text) {
        if (text == mdCodeText) return;
        mdCodeText = text;
        emit mdCodeTextChanged(text);
    }
signals:
    void mdCodeTextChanged(const QString &text);
};

#endif // EDITORTEXT_H
