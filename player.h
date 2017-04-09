#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QToolButton>
#include <QProgressBar>
#include <QComboBox>

#include <phonon/audiooutput.h>
//#include <phonon/backendcapabilities.h>
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <phonon/effect.h>
#include <phonon/effectparameter.h>
#include <phonon/effectwidget.h>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(const QString &path,QWidget *parent = 0);
    bool isPlaying(){return isPlay;}

signals:
   void finished();

public slots:
   void playPause();
   void play(Phonon::MediaSource url,bool besmala=false);
   void pause(){m_MediaObject.pause();}
   void stop();
   void repeate(){ m_MediaObject.seek(0); m_MediaObject.play();}

private slots:
    //! [phonon]
    void stateChanged(Phonon::State newstate, Phonon::State oldstate); //تغير اوضاع القراءة
    void mediaFinished();//انتهاء القراءة

    //! [phononEffect]
//    void chargeAvailableAudioEffects();
//    void configureEffect();
//    void effectChanged();


private:
    QString m_appPath;
    QString m_besmala;
    QToolButton  *actionPlayPause;
    QToolButton  *actionStopMedia;
    //Phonon
    QIcon playIcon;
    QIcon pauseIcon;
    Phonon::MediaObject m_MediaObject;
    Phonon::AudioOutput m_AudioOutput;
    Phonon::SeekSlider *slider;
    Phonon::VolumeSlider *volume;
    QProgressBar *progress;
    //----------------------phonon effect----------------------------
     Phonon::Effect *nextEffect;
     Phonon::Path m_audioOutputPath;
     QComboBox *audioEffectsCombo;
     QAction *effectAction;
bool playOne;
     bool isPlay;
};

#endif // PLAYER_H
