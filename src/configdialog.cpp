#include "configdialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent) {

    setWindowTitle("Settings - Qtag");

    contentsWidget = new QListWidget(this);
    stackedWidget = new QStackedWidget(this);

    closeButton = new QPushButton("Close", this);
    applyButton = new QPushButton("Apply", this);

    generalSettingsWidget = new QWidget(this);
    appearanceSettingsWidget = new QWidget(this);

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
    QObject::connect(applyButton, SIGNAL(clicked()), this, SLOT(applyChanges()));

}

void ConfigDialog::createLayout() {

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(stackedWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(applyButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(horizontalLayout);
    layout->addStretch(1);
    layout->addSpacing(12);
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

}
