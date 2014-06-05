#ifndef PLAYER_H
#define PLAYER_H

#include <QFrame>

namespace Ui {
    class VideoWidget;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class QTimer;
class VlcAudio;

class Player : public QFrame
{
    Q_OBJECT
public:
    explicit Player(QFrame *parent = 0);
    ~Player();
    void Play(const QString &file);
    QTimer *poller;

signals:
    void requestFullScreen(bool isKeyPress);

public slots:
    void toggleFullScreen(bool isKeyPress);
    void updateInterface();
    void changeVolume(int newVolume);
    void changePosition(int newPosition);
    void play();
    void pause();
    void stop();
    void setMuted(bool muted);
    void onLengthChanged(int ms);
    void onTimeChanged(int ms);

protected:
    bool eventFilter(QObject *target, QEvent *event);

private:
    Ui::VideoWidget *_ui;
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    VlcAudio *_pAudio;
};

#endif // PLAYER_H
