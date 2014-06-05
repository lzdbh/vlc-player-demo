#include "controls.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QDebug>

Controls::Controls(QWidget *parent)
    : QWidget(parent)
    , playerMuted(false)
    , playButton(0)
    , stopButton(0)
    , nextButton(0)
    , previousButton(0)
    , muteButton(0)
    , volumeSlider(0)
{
    playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);

    nextButton = new QToolButton(this);
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    previousButton = new QToolButton(this);
    previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    muteButton = new QToolButton(this);
    muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);

    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));
    connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));
    connect(nextButton, SIGNAL(clicked()), this, SIGNAL(next()));
    connect(previousButton, SIGNAL(clicked()), this, SIGNAL(previous()));
    connect(muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));
    connect(volumeSlider, SIGNAL(sliderMoved(int)), this, SIGNAL(changeVolume(int)));


    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(stopButton);
    layout->addWidget(previousButton);
    layout->addWidget(playButton);
    layout->addWidget(nextButton);
    layout->addWidget(muteButton);
    layout->addWidget(volumeSlider);
    setLayout(layout);
}

Vlc::State Controls::state() const
{
    return playerState;
}

void Controls::setState(Vlc::State state)
{
    if (state != playerState) {
        playerState = state;

        switch (state) {
        case Vlc::Stopped:
            stopButton->setEnabled(false);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case Vlc::Playing:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case Vlc::Paused:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case Vlc::Ended:
            stopButton->setEnabled(false);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

int Controls::volume() const
{
    return volumeSlider ? volumeSlider->value() : 0;
}

void Controls::setVolume(int volume)
{
    if (volumeSlider)
        volumeSlider->setValue(volume);
}

bool Controls::isMuted() const
{
    return playerMuted;
}

void Controls::setMuted(bool muted)
{
    if (muted != playerMuted) {
        playerMuted = muted;

        muteButton->setIcon(style()->standardIcon(muted
                ? QStyle::SP_MediaVolumeMuted
                : QStyle::SP_MediaVolume));
    }
}

void Controls::playClicked()
{
    switch (playerState) {
    case Vlc::Stopped:
    case Vlc::Paused:
        emit play();
        break;
    case Vlc::Playing:
        emit pause();
        break;
    }
}

void Controls::muteClicked()
{
    emit changeMuting(!playerMuted);
}
