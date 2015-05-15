/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *
 * (C) 2015 by Karel Patlejch
 *
 * Used libraries:
 *    TagLib - https://github.com/taglib
 *    Qt - http://qt.io
 *
*/

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QSettings>
#include <QLineEdit>

class ConfigDialog : public QDialog {

    Q_OBJECT

public:
    ConfigDialog(QWidget *parent);

private:
    QSettings* settings;

    QListWidget* contentsWidget;
    QStackedWidget* stackedWidget;

    QPushButton* closeButton;
    QPushButton* okButton;

    QWidget* generalSettingsWidget;
    QWidget* appearanceSettingsWidget;

    QGroupBox* filesGroup;
    QCheckBox* openLastFilesCheck;
    QGroupBox* viewGroup;
    QLabel* coverPreviewSizeLabel;
    QLineEdit* coverPreviewSizeEdit;

    QGroupBox* styleGroup;
    QLabel* styleLabel;
    QLabel* warningLabel;
    QComboBox* styleSelection;
    QGroupBox* iconsGroup;
    QButtonGroup* iconsSelection;
    QRadioButton* nativeIconsButton;
    QRadioButton* oxygenIconsButton;

    void createLayout();
    void createIcons();

private slots:
    void applyChanges();
    void changeLayout(QListWidgetItem* item);

};

#endif // CONFIGDIALOG_H
