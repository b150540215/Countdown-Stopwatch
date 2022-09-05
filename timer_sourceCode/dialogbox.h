#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <QDeclarativeItem>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QdiALOG
class DialogboxData;

class Dialogbox : public QDialog
{
public:
    Dialogbox();
    Dialogbox(const Dialogbox &);
    Dialogbox &operator=(const Dialogbox &);
    ~Dialogbox();

private:
    QSharedDataPointer<DialogboxData> data;
};

#endif // DIALOGBOX_H
