#include "configdialog.h"
#include "main.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QSettings>

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent) {

    setWindowTitle("Settings - Qtag");

    contentsWidget = new QListWidget(this);
    stackedWidget = new QStackedWidget(this);

    closeButton = new QPushButton("Close", this);
    okButton = new QPushButton("OK", this);

    generalSettingsWidget = new QWidget(this);
    appearanceSettingsWidget = new QWidget(this);

    styleLabel = new QLabel("Style:", appearanceSettingsWidget);
    styleSelection = new QComboBox(appearanceSettingsWidget);
    styleSelection->addItem("Native");
    styleSelection->addItem("GTK");
    styleSelection->addItem("Fusion");

    QSettings settings;
    QString currentStyle = settings.value("appearance/style", "native").toString();
    styleSelection->setCurrentText(currentStyle);

    iconsGroup = new QGroupBox("Icon theme", appearanceSettingsWidget);
    iconsSelection = new QButtonGroup(iconsGroup);
    nativeIconsButton = new QRadioButton("Use native icon theme (Linux only)", appearanceSettingsWidget);
    oxygenIconsButton = new QRadioButton("Use Oxygen icon theme", appearanceSettingsWidget);

    QString currentIconTheme = settings.value("appearance/icons", "native").toString();
    if(currentIconTheme == "native") {
        nativeIconsButton->setChecked(true);
    } else {
        oxygenIconsButton->setChecked(true);
    }

    iconsSelection->addButton(nativeIconsButton);
    iconsSelection->addButton(oxygenIconsButton);

    stackedWidget->addWidget(generalSettingsWidget);
    stackedWidget->addWidget(appearanceSettingsWidget);

    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setIconSize(QSize(64, 64));
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

    QVBoxLayout* iconsGroupLayout = new QVBoxLayout(iconsGroup);
    iconsGroupLayout->addWidget(nativeIconsButton);
    iconsGroupLayout->addWidget(oxygenIconsButton);
    iconsGroup->setLayout(iconsGroupLayout);

    QGridLayout *appearanceSettingsLayout = new QGridLayout(appearanceSettingsWidget);
    appearanceSettingsLayout->addWidget(styleLabel, 0, 0);
    appearanceSettingsLayout->addWidget(styleSelection, 0, 1);
    appearanceSettingsLayout->addWidget(iconsGroup, 1, 0, 1, 0);

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

    QSettings settings;
    settings.setValue("appearance/style", QVariant(styleSelection->currentText()));
    if(nativeIconsButton->isChecked()) {
        settings.setValue("appearance/icons", "native");
    } else {
        settings.setValue("appearance/icons", "oxygen");
    }
    QApplication::setStyle(getStyleFromSettings());

    settings.sync();
    close();

}
