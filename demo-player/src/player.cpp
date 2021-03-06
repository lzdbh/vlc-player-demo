#include "player.h"
#include <ui_VideoWidget.h>
#include <QUrl>
#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/Audio.h>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Player::Player(QFrame *parent)
    :QFrame(parent)
    ,_ui(new Ui::VideoWidget)
    ,_media(0)
    ,playIndex(0)
{
    _ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(_ui->videoWidget);
    _pAudio=_player->audio();

    _ui->videoWidget->setMediaPlayer(_player);
    _ui->videoWidget->installEventFilter(this);

    _player->stop();

    connect(this,SIGNAL(requestFullScreen(bool)),SLOT(toggleFullScreen(bool)));

    connect(_player,SIGNAL(lengthChanged(int)),SLOT(onLengthChanged(int)));
    connect(_player,SIGNAL(timeChanged(int)),SLOT(onTimeChanged(int)));

    connect(_ui->seekSlider,SIGNAL(sliderMoved(int)),SLOT(changePosition(int)));

    connect(_ui->controlsWidget, SIGNAL(play()),SLOT(play()));
    connect(_ui->controlsWidget, SIGNAL(pause()), SLOT(pause()));
    connect(_ui->controlsWidget, SIGNAL(stop()), SLOT(stop()));
    connect(_ui->controlsWidget, SIGNAL(changeVolume(int)), SLOT(changeVolume(int)));
    connect(_ui->controlsWidget, SIGNAL(changeMuting(bool)), SLOT(setMuted(bool)));

    connect(_ui->playList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),SLOT(onPlayListDbclick(QListWidgetItem*)));

    poller=new QTimer(this);
    poller->start(100);
    connect(poller, SIGNAL(timeout()), SLOT(updateInterface()));

    QNetworkAccessManager *m_pManager=new QNetworkAccessManager(this);

    QNetworkReply *reply = m_pManager->get(QNetworkRequest(QUrl("http://desktop.61read.com/magazine/getmagazinedetailslist?id=4A98E4DB-BB22-491E-8B1D-0FB126C5E983")));

    connect(reply,SIGNAL(finished()),SLOT(onJsonTest()));

}

void Player::Play(const QString &file)
{
    QUrl url(file);
    if(url.isEmpty())
        return;
    if(url.isLocalFile())
    {
        _media = new VlcMedia(url.toString(),true,_instance);
    }
    else
    {
        _media = new VlcMedia(url.toString(), _instance);
    }
    _player->open(_media);
}

bool Player::eventFilter(QObject *target, QEvent *event)
{
    if(target==_ui->videoWidget)
    {
        if(event->type()==QEvent::MouseButtonDblClick)
        {
            emit requestFullScreen(false);
        }
        if(event->type()==QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent=static_cast<QKeyEvent *>(event);
            if(keyEvent->key()==Qt::Key_Escape)
            {
                emit requestFullScreen(true);
            }
        }
    }
    return QWidget::eventFilter(target,event);
}

void Player::toggleFullScreen(bool isKeyPress)
{
    if(_ui->videoWidget->isFullScreen())
    {
        _ui->videoWidget->setWindowFlags(_ui->videoWidget->windowFlags()^Qt::Window);
        _ui->videoWidget->setWindowState(_ui->videoWidget->windowState()^Qt::WindowFullScreen);
        _ui->videoWidget->showNormal();
    }
    else
    {
        if(isKeyPress)
            return;
        _ui->videoWidget->setWindowFlags( _ui->videoWidget->windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::Window);
        _ui->videoWidget->setWindowState(_ui->videoWidget->windowState() | Qt::WindowFullScreen);
        _ui->videoWidget->show();
    }
}

Player::~Player()
{
    delete _player;
    delete _media;
    delete _instance;
    delete _ui;
}

void Player::updateInterface()
{
    _ui->controlsWidget->setState(_player->state());
    _ui->controlsWidget->setVolume(_pAudio->volume());
    if(_player->state()==Vlc::Ended){
        _ui->seekSlider->setValue(0);
        _ui->seekSlider->setDisabled(true);
    }else{
        _ui->seekSlider->setEnabled(true);
    }
}

void Player::play()
{
    VlcMedia *pMedia= _player->currentMedia();
    if(pMedia){
        _player->play();
        _ui->controlsWidget->setState(Vlc::Playing);
    }
}
void Player::pause()
{
    _player->pause();
    _ui->controlsWidget->setState(Vlc::Paused);
}

void Player::stop()
{
    _player->stop();
    _ui->controlsWidget->setState(Vlc::Stopped);
}

void Player::setMuted(bool muted)
{
    _ui->controlsWidget->setMuted(muted);
    //_pAudio->setMuted(muted);
    _pAudio->toggleMute();
}

void Player::changeVolume(int newVolume)
{
    _pAudio->setVolume(newVolume);
}

void Player::changePosition(int newPosition)
{
    _player->setTime(newPosition);
}

void Player::onLengthChanged(int ms)
{
    _ui->seekSlider->setMaximum(ms);
    QTime time=QTime(0,0,0,0).addMSecs(ms);
    QString display = "mm:ss";
    if (time.hour() > 0)
        display = "hh:mm:ss";
    _ui->totalLabel->setText(time.toString(display));
}

void Player::onTimeChanged(int ms)
{
    _ui->seekSlider->setValue(ms);
    QTime time = QTime(0,0,0,0).addMSecs(ms);

    QString display = "mm:ss";
    if (time.hour() > 0)
        display = "hh:mm:ss";
    _ui->elapsedLabel->setText(time.toString(display));
}

void Player::onJsonTest(){
    QNetworkReply *reply=static_cast<QNetworkReply *>(sender());

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());

    QJsonObject jsonObject = jsonResponse.object();

    QJsonArray jsonArray = jsonObject["data"].toArray();

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();

        QListWidgetItem *item=new QListWidgetItem(_ui->playList);
        //item->setIcon(iconForSymbol(i.value()));
        item->setData(Qt::UserRole,QVariant(obj));
        item->setText(obj["resname"].toString());
        item->setToolTip(obj["resname"].toString());
    }
    _ui->playList->setCurrentRow(playIndex);
    QString playUrl;
    QJsonObject obj=jsonArray.at(playIndex).toObject();
    if(!obj["videourl"].toString().isEmpty()){
        playUrl=obj["videourl"].toString();
    }else{
        playUrl=obj["audiourl"].toString();
    }
    this->Play(playUrl);
}

void Player::onPlayListDbclick(QListWidgetItem *item){
    QJsonObject obj=item->data(Qt::UserRole).toJsonObject();
    QString playUrl;
    if(!obj["videourl"].toString().isEmpty()){
        playUrl=obj["videourl"].toString();
    }else{
        playUrl=obj["audiourl"].toString();
    }
    this->playIndex=_ui->playList->currentIndex().row();
    this->Play(playUrl);
}
