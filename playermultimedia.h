#ifndef PLAYERMULTIMEDIA_H
#define PLAYERMULTIMEDIA_H
#include <QtWidgets/QWidget>
#include <QWidget>
#include <QMediaPlayer>
#include <QToolButton>
#include <QLabel>
#include <QSlider>
#include <QTimer>
//#include <QtWinExtras>
//QT_FORWARD_DECLARE_CLASS(QLabel)
//QT_FORWARD_DECLARE_CLASS(QSlider)
//QT_FORWARD_DECLARE_CLASS(QAbstractButton)
//QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)
//QT_FORWARD_DECLARE_CLASS(QWinTaskbarProgress)
//QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolBar)
//QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolButton)

class PlayerMultimedia : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerMultimedia(const QString &path, QWidget *parent = 0);
     ~PlayerMultimedia();
    void createTaskbar();
    void createThumbnailToolBar();


//    QWinTaskbarButton* taskbarButton;
//    QWinTaskbarProgress* taskbarProgress;
//    QWinThumbnailToolBar* thumbnailToolBar;
//    QWinThumbnailToolButton *playToolButton;
//    QWinThumbnailToolButton *forwardToolButton;
//    QWinThumbnailToolButton *backwardToolButton;

signals:
     void finished();
     void invalidMedia();
public slots:
  void updateThumbnailToolBar();
 bool isPlaying(){return isPlay;}
    void playPause();
    QString curentMedia(){return mediaPlayer->currentMedia().canonicalUrl().toString();}
void clearList();
    void play(QMediaContent url,bool besmala=false);
    void pause(){mediaPlayer->pause();}
    void stop();
    void repeate(){mediaPlayer->setPosition(0); mediaPlayer->play();}
    void setPlayPauseShortcut(QKeySequence shortcut){playButton->setShortcut(shortcut);}
private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();
void statusChanged(QMediaPlayer::MediaStatus status);
void playlistPositionChanged(int);
void inimateStatus();
private:
    QMediaPlayer *mediaPlayer;
    QToolButton *playButton;
    QToolButton *stopButton;
    QLabel *imageLabel;
    QSlider *positionSlider;
QTimer *mTimer;
int mCurImage;
    bool isPlay;
    QString m_appPath;
    bool playOne;
    QString m_besmala;
    QMediaPlaylist *playlist;




};

#endif // PLAYERMULTIMEDIA_H
