#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include <vlc-qt/Enums.h>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
QT_END_NAMESPACE

class Controls : public QWidget
{
    Q_OBJECT

public:
    Controls(QWidget *parent = 0);

    Vlc::State state() const;
    int volume() const;
    bool isMuted() const;

public slots:
    void setState(Vlc::State state);
    void setVolume(int volume);
    void setMuted(bool muted);

signals:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void changeVolume(int volume);
    void changeMuting(bool muting);

private slots:
    void playClicked();
    void muteClicked();

private:
    Vlc::State playerState;
    bool playerMuted;
    QAbstractButton *playButton;
    QAbstractButton *stopButton;
    QAbstractButton *nextButton;
    QAbstractButton *previousButton;
    QAbstractButton *muteButton;
    QAbstractSlider *volumeSlider;
};


#endif // CONTROLS_H
