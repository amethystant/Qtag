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

#include "ui/dialogs/configdialog.h"
#include "core/main.h"
#include "core/qtagapp.h"
#include "core/settings.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent) {

    setWindowTitle("Settings - Qtag");

    contentsWidget = new QListWidget(this);
    stackedWidget = new QStackedWidget(this);

    closeButton = new QPushButton("Close", this);
    okButton = new QPushButton("OK", this);

    generalSettingsWidget = new QWidget(this);
    appearanceSettingsWidget = new QWidget(this);

    behaviorGroup = new QGroupBox("Behavior", generalSettingsWidget);
    openLastFilesCheck = new QCheckBox("Open files from last session at startup", generalSettingsWidget);
    warnBeforeClosingCheck = new QCheckBox("Warn me before I close unsaved files", generalSettingsWidget);
    viewGroup = new QGroupBox("View", generalSettingsWidget);
    coverPreviewSizeLabel = new QLabel("Cover art preview size:", generalSettingsWidget);
    coverPreviewSizeEdit = new QLineEdit(generalSettingsWidget);
    coverPreviewSizeEdit->setValidator(new QIntValidator);
    coverPreviewSizeEdit->setMaxLength(3);

    styleGroup = new QGroupBox("Style", appearanceSettingsWidget);
    styleLabel = new QLabel("Style:", appearanceSettingsWidget);
    warningLabel = new QLabel("<i>Warning: this option may apply after restarting Qtag.</i>",
                              appearanceSettingsWidget);
    styleSelection = new QComboBox(appearanceSettingsWidget);
    styleSelection->addItem("Native");
    styleSelection->addItem("GTK");
    styleSelection->addItem("Fusion");

    QString currentStyle = Settings::getApplicationTheme();
    styleSelection->setCurrentText(currentStyle);

    iconsGroup = new QGroupBox("Icon theme", appearanceSettingsWidget);
    iconsSelection = new QButtonGroup(iconsGroup);
    nativeIconsButton = new QRadioButton("Use native icon theme (Linux only)", appearanceSettingsWidget);
    oxygenIconsButton = new QRadioButton("Use Oxygen icon theme", appearanceSettingsWidget);

    Settings::IconTheme currentIconTheme = Settings::getIconTheme();
    if(currentIconTheme == Settings::NATIVE) {
        nativeIconsButton->setChecked(true);
    } else {
        oxygenIconsButton->setChecked(true);
    }

    if(Settings::getOpenLastSession()) {
        openLastFilesCheck->setChecked(true);
    }

    if(Settings::getWarnBeforeClosingUnsavedFiles()) {
        warnBeforeClosingCheck->setChecked(true);
    }

    coverPreviewSizeEdit->setText(intToString(Settings::getPicturePreviewSize()));

    iconsSelection->addButton(nativeIconsButton);
    iconsSelection->addButton(oxygenIconsButton);

    stackedWidget->addWidget(generalSettingsWidget);
    stackedWidget->addWidget(appearanceSettingsWidget);

    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setIconSize(QSize(60, 60));
    contentsWidget->setSpacing(12);
    contentsWidget->setMaximumWidth(128);

    createIcons();
    createLayout();

    stackedWidget->setCurrentIndex(0);
    contentsWidget->setCurrentRow(0);

    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
                     this, SLOT(changeLayout(QListWidgetItem*)));
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(applyChanges()));

}

void ConfigDialog::createLayout() {


    QVBoxLayout* behaviorGroupLayout = new QVBoxLayout(behaviorGroup);
    behaviorGroupLayout->addWidget(openLastFilesCheck);
    behaviorGroupLayout->addWidget(warnBeforeClosingCheck);
    behaviorGroup->setLayout(behaviorGroupLayout);

    QHBoxLayout* viewGroupLayout = new QHBoxLayout(viewGroup);
    viewGroupLayout->addWidget(coverPreviewSizeLabel);
    viewGroupLayout->addWidget(coverPreviewSizeEdit);
    viewGroup->setLayout(viewGroupLayout);

    QVBoxLayout* generalSettingsLayout = new QVBoxLayout(generalSettingsWidget);
    generalSettingsLayout->addWidget(behaviorGroup);
    generalSettingsLayout->addWidget(viewGroup);
    generalSettingsWidget->setLayout(generalSettingsLayout);

    QVBoxLayout* iconsGroupLayout = new QVBoxLayout(iconsGroup);
    iconsGroupLayout->addWidget(nativeIconsButton);
    iconsGroupLayout->addWidget(oxygenIconsButton);
    iconsGroup->setLayout(iconsGroupLayout);

    QGridLayout* styleGroupLayout = new QGridLayout(styleGroup);
    styleGroupLayout->addWidget(styleLabel, 0, 0);
    styleGroupLayout->addWidget(styleSelection, 0, 1);
    styleGroupLayout->addWidget(warningLabel, 1, 0, 1, 0);
    styleGroup->setLayout(styleGroupLayout);

    QVBoxLayout *appearanceSettingsLayout = new QVBoxLayout(appearanceSettingsWidget);
    appearanceSettingsLayout->addWidget(styleGroup);
    appearanceSettingsLayout->addWidget(iconsGroup);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(stackedWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(horizontalLayout);
    layout->addLayout(buttonsLayout);
    setLayout(layout);

}

void ConfigDialog::createIcons() {

    QListWidgetItem *generalSettings = new QListWidgetItem(contentsWidget);
    generalSettings->setIcon(QIcon::fromTheme("preferences-system",
                                              QIcon(":/images/settings-general.png")));
    generalSettings->setText("General");
    generalSettings->setTextAlignment(Qt::AlignHCenter);
    generalSettings->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *appearanceSettings = new QListWidgetItem(contentsWidget);
    appearanceSettings->setIcon(QIcon::fromTheme("applications-graphics",
                                              QIcon(":/images/settings-appearance.png")));
    appearanceSettings->setText("Appearance");
    appearanceSettings->setTextAlignment(Qt::AlignHCenter);
    appearanceSettings->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}

void ConfigDialog::changeLayout(QListWidgetItem *item) {
    stackedWidget->setCurrentIndex(contentsWidget->row(item));
}

void ConfigDialog::applyChanges() {

    Settings::setOpenFilesFromLastSession(openLastFilesCheck->isChecked());
    Settings::setPicturePreviewSize(coverPreviewSizeEdit->text().toInt());

    Settings::setApplicationTheme(styleSelection->currentText());
    if(nativeIconsButton->isChecked()) {
        Settings::setIconTheme(Settings::NATIVE);
    } else {
        Settings::setIconTheme(Settings::OXYGEN);
    }

    Settings::setWarnBeforeClosingUnsavedFiles(warnBeforeClosingCheck->isChecked());

    QApplication::setStyle(QtagApp::getStyleFromSettings());

    close();

}
