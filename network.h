#ifndef NETWORK_H
#define NETWORK_H
#include <QObject>
#include <QProgressDialog>
#include <QHttp>
#include <QFile>
 #include <QtNetwork>
class netWork: public QObject
{
    Q_OBJECT
public:
      explicit netWork(QObject *parent = 0);
signals:
    void progresseIsVisible(bool );
private:

 // QString mypath;

   // QProgressDialog *progressDialog;
    QProgressBar *progressDialog;
    QHttp *http;
    QFile *fileHttp;
    int httpGetId;
    bool httpRequestAborted;
    //  QString m_bkUrlPath;
    QString m_urlPath;
    bool isloaded;
public slots:
      bool downloadFile(QString urlPath,QString distPath);
      void setProgress(QProgressBar *prog);
       void cancelDownload();
private slots:







    void httpRequestFinished(int requestId, bool error);
    void updateDataReadProgress(int bytesRead, int totalBytes);
    void readResponseHeader(const QHttpResponseHeader &responseHeader);


#ifndef QT_NO_OPENSSL
    void sslErrors(const QList<QSslError> &errors);
#endif
};

#endif // NETWORK_H
