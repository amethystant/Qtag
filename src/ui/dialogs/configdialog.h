/*
 *    Qtag is an advanced but simple to use audio metadata editor. Runs on Linux
 *    and Windows. Supports many formats, including MPEG, Ogg Vorbis, Wave and FLAC
 *
 *    Copyright (C) 2015 - 2016  Karel Patlejch <kaja.patlejch@gmail.com>
 *
 *    Used libraries:
 *      TagLib - http://taglib.github.io/
 *      Qt - http://qt.io
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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

    QGroupBox* behaviorGroup;
    QCheckBox* openLastFilesCheck;
    QCheckBox* warnBeforeClosingCheck;
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
