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

#include "configdialog.h"
#include "main.h"
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

    filesGroup = new QGroupBox("Files", generalSettingsWidget);
    openLastFilesCheck = new QCheckBox("Open files from last session at startup", generalSettingsWidget);
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

    settings = new QSettings(this);

    QString currentStyle = settings->value("style", "native").toString();
    styleSelection->setCurrentText(currentStyle);

    iconsGroup = new QGroupBox("Icon theme", appearanceSettingsWidget);
    iconsSelection = new QButtonGroup(iconsGroup);
    nativeIconsButton = new QRadioButton("Use native icon theme (Linux only)", appearanceSettingsWidget);
    oxygenIconsButton = new QRadioButton("Use Oxygen icon theme", appearanceSettingsWidget);

    QString currentIconTheme = settings->value("icons", "native").toString();
    if(currentIconTheme == "native") {
        nativeIconsButton->setChecked(true);
    } else {
        oxygenIconsButton->setChecked(true);
    }

    bool openLastFiles = settings->value("openfiles", QVariant(false)).toBool();
    if(openLastFiles) {
        openLastFilesCheck->setChecked(true);
    }

    int previewSize = settings->value("previewsize", QVariant(150)).toInt();
    coverPreviewSizeEdit->setText(intToString(previewSize));

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


    QVBoxLayout* filesGroupLayout = new QVBoxLayout(filesGroup);
    filesGroupLayout->addWidget(openLastFilesCheck);
    filesGroup->setLayout(filesGroupLayout);

    QHBoxLayout* viewGroupLayout = new QHBoxLayout(viewGroup);
    viewGroupLayout->addWidget(coverPreviewSizeLabel);
    viewGroupLayout->addWidget(coverPreviewSizeEdit);
    viewGroup->setLayout(viewGroupLayout);

    QVBoxLayout* generalSettingsLayout = new QVBoxLayout(generalSettingsWidget);
    generalSettingsLayout->addWidget(filesGroup);
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

    if(openLastFilesCheck->isChecked()) {
        settings->setValue("openfiles", true);
    } else {
        settings->setValue("openfiles", false);
    }
    settings->setValue("previewsize", QVariant(coverPreviewSizeEdit->text().toInt()));

    settings->setValue("style", QVariant(styleSelection->currentText()));
    if(nativeIconsButton->isChecked()) {
        settings->setValue("icons", "native");
    } else {
        settings->setValue("icons", "oxygen");
    }

    QApplication::setStyle(getStyleFromSettings());
    settings->sync();

    close();

}
