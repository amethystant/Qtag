#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>

class ConfigDialog : public QDialog {

    Q_OBJECT

public:
    ConfigDialog(QWidget* parent);

private:
    QListWidget* contentsWidget;
    QStackedWidget* stackedWidget;

    QPushButton* closeButton;
    QPushButton* applyButton;

    QWidget* generalSettingsWidget;
    QWidget* appearanceSettingsWidget;

    void createLayout();
    void createIcons();

private slots:
    void applyChanges();
    void changeLayout(QListWidgetItem* item);

};

#endif // CONFIGDIALOG_H
