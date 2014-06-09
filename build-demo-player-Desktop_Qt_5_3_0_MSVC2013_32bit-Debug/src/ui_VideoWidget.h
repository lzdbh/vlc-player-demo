/********************************************************************************
** Form generated from reading UI file 'VideoWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOWIDGET_H
#define UI_VIDEOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "controls.h"
#include "vlc-qt/WidgetVideo.h"

QT_BEGIN_NAMESPACE

class Ui_VideoWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *controlesLayout;
    QHBoxLayout *videoLayout;
    VlcWidgetVideo *videoWidget;
    QHBoxLayout *seekLayout;
    QLabel *elapsedLabel;
    QSlider *seekSlider;
    QLabel *totalLabel;
    QHBoxLayout *manageLayout;
    Controls *controlsWidget;
    QHBoxLayout *playListLayout;
    QListWidget *playList;

    void setupUi(QWidget *VideoWidget)
    {
        if (VideoWidget->objectName().isEmpty())
            VideoWidget->setObjectName(QStringLiteral("VideoWidget"));
        VideoWidget->resize(750, 500);
        VideoWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout_3 = new QHBoxLayout(VideoWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        controlesLayout = new QVBoxLayout();
        controlesLayout->setSpacing(0);
        controlesLayout->setObjectName(QStringLiteral("controlesLayout"));
        controlesLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        controlesLayout->setContentsMargins(0, 0, 0, 0);
        videoLayout = new QHBoxLayout();
        videoLayout->setObjectName(QStringLiteral("videoLayout"));
        videoWidget = new VlcWidgetVideo(VideoWidget);
        videoWidget->setObjectName(QStringLiteral("videoWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoWidget->sizePolicy().hasHeightForWidth());
        videoWidget->setSizePolicy(sizePolicy);
        videoWidget->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        videoLayout->addWidget(videoWidget);


        controlesLayout->addLayout(videoLayout);

        seekLayout = new QHBoxLayout();
        seekLayout->setObjectName(QStringLiteral("seekLayout"));
        seekLayout->setContentsMargins(0, 0, 0, 0);
        elapsedLabel = new QLabel(VideoWidget);
        elapsedLabel->setObjectName(QStringLiteral("elapsedLabel"));
        elapsedLabel->setStyleSheet(QStringLiteral(""));

        seekLayout->addWidget(elapsedLabel);

        seekSlider = new QSlider(VideoWidget);
        seekSlider->setObjectName(QStringLiteral("seekSlider"));
        seekSlider->setOrientation(Qt::Horizontal);

        seekLayout->addWidget(seekSlider);

        totalLabel = new QLabel(VideoWidget);
        totalLabel->setObjectName(QStringLiteral("totalLabel"));
        totalLabel->setStyleSheet(QStringLiteral(""));

        seekLayout->addWidget(totalLabel);


        controlesLayout->addLayout(seekLayout);

        manageLayout = new QHBoxLayout();
        manageLayout->setSpacing(6);
        manageLayout->setObjectName(QStringLiteral("manageLayout"));
        manageLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        controlsWidget = new Controls(VideoWidget);
        controlsWidget->setObjectName(QStringLiteral("controlsWidget"));

        manageLayout->addWidget(controlsWidget);


        controlesLayout->addLayout(manageLayout);


        horizontalLayout_3->addLayout(controlesLayout);

        playListLayout = new QHBoxLayout();
        playListLayout->setSpacing(0);
        playListLayout->setObjectName(QStringLiteral("playListLayout"));
        playListLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        playListLayout->setContentsMargins(0, 0, 0, 0);
        playList = new QListWidget(VideoWidget);
        playList->setObjectName(QStringLiteral("playList"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(playList->sizePolicy().hasHeightForWidth());
        playList->setSizePolicy(sizePolicy1);
        playList->setStyleSheet(QStringLiteral(""));

        playListLayout->addWidget(playList);


        horizontalLayout_3->addLayout(playListLayout);


        retranslateUi(VideoWidget);

        QMetaObject::connectSlotsByName(VideoWidget);
    } // setupUi

    void retranslateUi(QWidget *VideoWidget)
    {
        VideoWidget->setWindowTitle(QApplication::translate("VideoWidget", "Form", 0));
        elapsedLabel->setText(QApplication::translate("VideoWidget", "00:00", 0));
        totalLabel->setText(QApplication::translate("VideoWidget", "00:00", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoWidget: public Ui_VideoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOWIDGET_H
