#include "player.h"
#include <QHBoxLayout>
#include <QDir>
Player::Player(const QString &path, QWidget *parent) :
    QWidget(parent),m_appPath(path)
{
    //----------------Phonon--------------------------------------------------------
    //------- -phonon---------------
    slider = new Phonon::SeekSlider();
    slider->setMediaObject(&m_MediaObject);
    volume = new Phonon::VolumeSlider(&m_AudioOutput);
    volume->setMaximumWidth(100);

    playIcon=QIcon(":/img/media-playback-start.png");
    pauseIcon=QIcon(":/img/media-playback-pause.png");
    actionPlayPause=new QToolButton;
    actionPlayPause->setIcon(playIcon);
    connect(actionPlayPause,SIGNAL(clicked()),this,SLOT(playPause()));

    actionStopMedia=new QToolButton;
    actionStopMedia->setIcon(QIcon(":/img/media-playback-stop.png"));
    connect(actionStopMedia,SIGNAL(clicked()),this,SLOT(stop()));

    connect(&m_MediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(&m_MediaObject, SIGNAL(finished()), this, SLOT(mediaFinished()));
    m_audioOutputPath = Phonon::createPath(&m_MediaObject, &m_AudioOutput);
    QHBoxLayout *horizontalLayoutMedia = new QHBoxLayout(this);
    horizontalLayoutMedia->addWidget(actionStopMedia);
    horizontalLayoutMedia->addWidget(actionPlayPause);
    horizontalLayoutMedia->addWidget(slider);
    horizontalLayoutMedia->addWidget(volume);

    //البحث عن اي ملف   m_MediaObject.clear();استعاذة باي ملحقة كانت
    QStringList filters("audhubillah.*");
    QDir dir(m_appPath);
    QStringList list=dir.entryList(filters,QDir::Files,QDir::Name);
    QString aodho ;
    if (list.count()>0)
        aodho = list.at(0);
     playOne=false;
   m_MediaObject .setCurrentSource(m_appPath+"/"+aodho);
    m_MediaObject.play();
    playOne=true;
#if defined(Q_OS_WIN)
                m_besmala=m_appPath+"/bismillah.mp3";
#else
                m_besmala=m_appPath+"/bismillah.ogg"   ;
#endif

}

void Player::playPause()
{
isPlay=true;
    if (m_MediaObject.state() == Phonon::PlayingState){
        m_MediaObject.pause();
        return;
    }
  if(m_MediaObject.currentSource().type()==Phonon::MediaSource::Empty)
      emit finished();

   m_MediaObject.play();

}

void Player::play(Phonon::MediaSource url, bool besmala)
{

    if(url==m_MediaObject.currentSource())
        return;

    m_MediaObject.clearQueue();
    m_MediaObject.clear();
    if(besmala){
       m_MediaObject.enqueue(m_besmala);
       m_MediaObject.enqueue(url);

    }else{
         m_MediaObject.setCurrentSource(url);
    }

    isPlay=true;
    m_MediaObject.play();

}

void Player::stop()
{

    m_MediaObject.stop();
    isPlay=false;
    slider->show();
}

void Player::stateChanged(Phonon::State newstate, Phonon::State oldstate)
{
    Q_UNUSED(oldstate);

    switch (newstate) {
    case Phonon::ErrorState:
        if (m_MediaObject.errorType() == Phonon::FatalError) {

            m_MediaObject.clearQueue();
            m_MediaObject.stop();
        } else {
            m_MediaObject.pause();
             isPlay=true;
        }
     qDebug()<<m_MediaObject.errorString();
        break;

    case Phonon::StoppedState:
        //qDebug()<<"Phonon::StoppedState";
        actionPlayPause->setIcon(playIcon);
    //    isPlay=false;
        break;

    case Phonon::LoadingState:
            // qDebug()<<"Phonon::LoadingState";
        break;

    case Phonon::BufferingState:

        break;

    case Phonon::PausedState:
         //  qDebug()<<"Phonon::PausedState";
           //  isPlay=true;
        actionPlayPause->setIcon(playIcon);
        if (m_MediaObject.currentSource().type() != Phonon::MediaSource::Invalid){
            actionPlayPause->setEnabled(true);
        } else {
           actionPlayPause->setEnabled(false);
        }
        break;

    case Phonon::PlayingState:

        actionPlayPause->setEnabled(true);
        actionPlayPause->setIcon(pauseIcon);
        isPlay=true;
        break;
    }

}

void Player::mediaFinished()
{

    m_MediaObject.pause();
    m_MediaObject.seek(0);
    if(playOne){
        m_MediaObject.clear();
        playOne=false;
        return;
    }
    emit finished();

}
