/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu May 10 23:11:46 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGraphicsView *uv_band;
    QGraphicsView *normal_band;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *cutting_area;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *load_img_btn;
    QPushButton *load_uv_img_btn;
    QPushButton *draw_bands_btn;
    QSpacerItem *horizontalSpacer;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1061, 670);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        uv_band = new QGraphicsView(centralWidget);
        uv_band->setObjectName(QString::fromUtf8("uv_band"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uv_band->sizePolicy().hasHeightForWidth());
        uv_band->setSizePolicy(sizePolicy);
        uv_band->setMinimumSize(QSize(0, 100));
        uv_band->setMaximumSize(QSize(16777215, 130));

        verticalLayout->addWidget(uv_band);

        normal_band = new QGraphicsView(centralWidget);
        normal_band->setObjectName(QString::fromUtf8("normal_band"));
        sizePolicy.setHeightForWidth(normal_band->sizePolicy().hasHeightForWidth());
        normal_band->setSizePolicy(sizePolicy);
        normal_band->setMinimumSize(QSize(0, 100));
        normal_band->setMaximumSize(QSize(16777215, 130));

        verticalLayout->addWidget(normal_band);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        cutting_area = new QGraphicsView(centralWidget);
        cutting_area->setObjectName(QString::fromUtf8("cutting_area"));
        sizePolicy.setHeightForWidth(cutting_area->sizePolicy().hasHeightForWidth());
        cutting_area->setSizePolicy(sizePolicy);
        cutting_area->setMinimumSize(QSize(480, 360));
        cutting_area->setMaximumSize(QSize(1024, 768));
        cutting_area->setMouseTracking(false);
        cutting_area->setResizeAnchor(QGraphicsView::NoAnchor);
        cutting_area->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        verticalLayout_2->addWidget(cutting_area);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        load_img_btn = new QPushButton(centralWidget);
        load_img_btn->setObjectName(QString::fromUtf8("load_img_btn"));

        horizontalLayout->addWidget(load_img_btn);

        load_uv_img_btn = new QPushButton(centralWidget);
        load_uv_img_btn->setObjectName(QString::fromUtf8("load_uv_img_btn"));

        horizontalLayout->addWidget(load_uv_img_btn);

        draw_bands_btn = new QPushButton(centralWidget);
        draw_bands_btn->setObjectName(QString::fromUtf8("draw_bands_btn"));

        horizontalLayout->addWidget(draw_bands_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1061, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Core samples analyzer", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Selected: ", 0, QApplication::UnicodeUTF8));
        load_img_btn->setText(QApplication::translate("MainWindow", "Load img", 0, QApplication::UnicodeUTF8));
        load_uv_img_btn->setText(QApplication::translate("MainWindow", "Load UV img", 0, QApplication::UnicodeUTF8));
        draw_bands_btn->setText(QApplication::translate("MainWindow", "Draw Bands", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
