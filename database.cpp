/****************************************************************************
//   elforkane Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
//
//      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//      This is free software, and you are welcome to redistribute it
//      under certain conditions; type `show c' for details.
//
//  The hypothetical commands `show w' and `show c' should show the appropriate
//  parts of the General Public License.  Of course, your program's commands
//  might be different; for a GUI interface, you would use an "about box".
//
//    You should also get your employer (if you work as a programmer) or school,
//  if any, to sign a "copyright disclaimer" for the program, if necessary.
//  For more information on this, and how to apply and follow the GNU GPL, see
//  <http://www.gnu.org/licenses/>.
//
//    The GNU General Public License does not permit incorporating your program
//  into proprietary programs.  If your program is a subroutine library, you
//  may consider it more useful to permit linking proprietary applications with
//  the library.  If this is what you want to do, use the GNU Lesser General
//  Public License instead of this License.  But first, please read
//  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
// ----------------------------------------------------------
** If you have questions regarding the use of this file, please contact
** yahia nouah (yahiaui@gmail.com)
** $elforkane_END_LICENSE$
**
****************************************************************************/

#include "database.h"
//#include <QtGui>
//#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
//#include <QDomDocument>
#include <QFile>
#include <QXmlStreamReader>

#include <QTextStream>
#include <QFileInfo>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QAction>
 #include <QSqlError>
Database::Database()

{
    QDir appDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)

    appDir.cdUp();
    appPath=  appDir.absolutePath()+"/share/elforkane";
#elif defined(Q_OS_MAC)
    if (appDir.dirName() == "MacOS") {
        appDir.cdUp();
        appDir.cdUp();
        appDir.cdUp();
        appPath=  appDir.absolutePath()+"/elforkane";
    }
#else
    appDir.cdUp();
    appPath=  appDir.absolutePath()+"/share/elforkane";
    // qDebug()<<appPath;
#endif

    myList=new QList<QString>;
    myListSura=new QList<int>;
    myListSafhat=new QList<QString>;
    // myListJozaa=new QList<QString>;
    myListJozaa=new QList<int>;
    myListHizb=new QList<int>;
    myListArbaa=new QList<QString>;
    //  myListAction=new  QList<QAction *>;
    db = QSqlDatabase::addDatabase("QSQLITE");
}

void Database::treeChargeSoura(QTreeWidget *view,  bool suraCharged,QComboBox *combo,QString lng,int id)
{
//   QLocale lc(QLocale::system().name());
     QLocale lc;
    int n=0;
    int nsura=0;
    int naya=1;
    QTreeWidgetItem *itemsora=new QTreeWidgetItem(view);
    QTreeWidgetItem *itemaya ;
    QFile file(appPath +"/quran.xml");
    file.open(QIODevice::ReadOnly);
    //combo->clear();
    view->clear();
    QXmlStreamReader xml;
    xml.setDevice(&file);
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.name() == "Department"){

      //      QString idSora= xml.attributes().value("id").toString();
            QString textSora;
            if(lng=="ltr"){
                textSora=xml.attributes().value("Ename").toString();
            }else{
                textSora=xml.attributes().value("Name").toString();
            }
         // QString   textSoraEn=xml.attributes().value("Ename").toString();//---------------------------
            if(!textSora.isNull()){
                nsura++;
                   naya=1;
                itemsora= new QTreeWidgetItem(view);
                QString txt=lc.toString(nsura)+textSora;
                itemsora->setText(0,txt );
         //       itemsora->setData(1,1,idSora);
               //   itemsora->setData(0,1,textSoraEn );//---------------------------------
                itemsora->setText(1,QString::number(n+1) );
                if( suraCharged==false){
                    myListSura->append(n+1);
                    // combo->addItem(textSora,idSora);
                }
            }
        }
        if (xml.name() == "Item"){
          //  QString idAya= xml.attributes().value("ID").toString();
            QString textAya=xml.readElementText();
            if(!textAya.isNull()){
                n++;


                itemaya= new QTreeWidgetItem(itemsora);
             QString txt=lc.toString(naya)+" - "+textAya;

             itemaya->setText(0,txt );
                itemaya->setText(1,QString::number(n) );

               // itemaya->setData(1,1,idAya);
                naya++;
            }
        }
    }

    xml.clear();
    file.close();
    int count=view->topLevelItemCount();
    if (suraCharged==true)return;
     for(int i=0;i<count;i++){
        QString txt=view->topLevelItem(i)->text(0);
        QString txtid=view->topLevelItem(i)->text(1);
        int itemcount=view->topLevelItem(i)->childCount();
        combo->addItem(txt,txtid+","+QString::number(itemcount));
    }
combo->setCurrentIndex(id);
}


void Database::treeChargeJozaa(QTreeWidget *view)
{
    //-------------------------------
   // int firstRobaa=0;
//    int khizb=0;
//    QFile fileReciter(QApplication::applicationDirPath()+"/data/ssv");
//    if (!fileReciter.open(QFile::WriteOnly)){
//          return ;
//      }
//    QTextStream out(&fileReciter);
//    out << "jozaa,hizb,robaa \n";

    //-------------------------------------------
    QTreeWidgetItem *item=new QTreeWidgetItem(view) ;
    QTreeWidgetItem *osloItem=new QTreeWidgetItem(item) ;
    QTreeWidgetItem *osloItem2 ;

    QFile file(appPath+"/ajzaa.xml");
    file.open(QIODevice::ReadOnly);
    view->clear();
    myListJozaa->clear();
    myListHizb->clear();
    QXmlStreamReader xml;
    xml.setDevice(&file);
    int nJoz=0;
    int nHizb=0;
    int nRob=0;
     QString idjoza;
     QString idhizb;
     QString idhrobaa;

    while (!xml.atEnd()) {

        xml.readNext();
        if (xml.name() == "root"){

             idjoza= xml.attributes().value("id").toString();
            QString textjoza=xml.attributes().value("Name").toString();
           //QString id=   creatIndex(idjoza);
            if(!textjoza.isNull()){
                  nJoz++;
                item= new QTreeWidgetItem(view);
                item->setText(0,QString::number(nJoz)+"-"+textjoza );
        //    item->setData(1,1,idjoza);
               item->setText(1,idjoza );
               myListJozaa->append(idjoza.toInt());
            }
        }else if (xml.name() == "Item"){

             idhizb= xml.attributes().value("id").toString();
            QString texthizb= xml.attributes().value("Name").toString();
            //QString id=   creatIndex(idhizb);
            if(!texthizb.isNull()){
                  nHizb++;
                osloItem= new QTreeWidgetItem(item);
                osloItem->setText(0,QString::number(nHizb)+"-"+texthizb );
             //   osloItem->setData(1,1,idhizb);
                 osloItem->setText(1,idhizb);
                 myListHizb->append(idhizb.toInt());
            }
        }else if (xml.name() == "bk"){

             idhrobaa= xml.attributes().value("id").toString();
        QString     textrobaa= xml.attributes().value("name").toString();
         // QString id=   creatIndex(idhrobaa);

            if(!textrobaa.isNull()){
                nRob++;
                if(nRob==5){
                      nRob=1;

                }

                osloItem2= new QTreeWidgetItem(osloItem);
                osloItem2->setText(0,QString::number(nRob)+"-"+textrobaa );
              //  osloItem2->setData(1,1,idhrobaa);
                osloItem2->setText(1,idhrobaa );
 //-----------
//                int robaa=nRob-1;
//                if (robaa==0){
//                     robaa=4;

//                }

//                if (robaa==1){
//                          khizb++;
//                }

//                int count=idhrobaa.toInt()-firstRobaa;

//              for (int i=0;i<count;i++){
//                  out << QString::number(nJoz)+","+QString::number(khizb)+","+QString::number(robaa)+"\n";
//              }
//              firstRobaa=idhrobaa.toInt();
  //----------------
            }
        }

    }
    xml.clear();
    file.close();
  //  fileReciter.close();
}
QString Database::creatIndex(QString mytxt)
    {

        int icount=myList->count();
        for(int i=0;i<icount;i++)
        {
          QString txt= myList->at(i);
          QString id=txt.section(",",0,0).trimmed();
          QString sura=txt.section(",",1,1).trimmed();
           QString aya=txt.section(",",2,2).trimmed();
           QString suraaya=sura+"_"+aya;

           if (suraaya==mytxt)
               return id;
        }
        return "null";
  }

//void Database::treeSaveGroupe(QTreeWidget *view)
//{
//    QDomDocument m_doc;
//    QString myxmlgroup="<?xml version='1.0' encoding='UTF-8'?>"
//                       "<setting>"
//                       "</setting>";
//    m_doc.setContent(myxmlgroup);
//    QTreeWidgetItem *item;
//    QTreeWidgetItem *itemols;
//    QTreeWidgetItem *itemols2;
//    QString grouptext;
//    QDomElement racine = m_doc.documentElement();
//    for(int i=0;i<view->topLevelItemCount();++i)
//    {
//        item= view->topLevelItem(i);
//        grouptext=item->text(0);
//        QDomElement groupe=m_doc.createElement("root");     //انشاء عنصر جديد
//        racine.appendChild(groupe);                    //اظافته في اخر القائمة
//        groupe.setAttribute("Name",grouptext);      //اسم الكتاب
//        groupe.setAttribute("id",i);
//        for(int r=0;r<item->childCount();++r)
//        {
//            itemols=item->child(r);
//            QString id= itemols->text(1);
//            QString title=itemols->text(0);
//            QDomElement items=m_doc.createElement("Item");
//            groupe.appendChild(items);
//            items.setAttribute("id",id);
//            items.setAttribute("Name",title);
//            for(int r=0;r<itemols->childCount();++r)
//            {
//                itemols2=itemols->child(r);
//                QString id= itemols2->text(1);
//                QString name =itemols2->text(0);
//                QDomElement itemsbk=m_doc.createElement("bk");
//                items.appendChild(itemsbk);
//                itemsbk.setAttribute("id",id);
//                 itemsbk.setAttribute("name",name);

//            }
//        }
//    }
//    QFile file(QCoreApplication::applicationDirPath() +"/data/ajzaa1.xml");
//    file.open(QIODevice::WriteOnly);              //فتح الملف للكتابة
//    QTextStream out(&file);                       //الكتابة
//    m_doc.save(out,1);                      //حفظ الملف
//    file.close();
//    m_doc.clear();

//}

void  Database::chargeCsvs(QString riwaya)
{
    QString dataAyat=appPath+"/images/"+riwaya+"/datarc";
    //qDebug()<<"this data ="+dataAyat;
    QString dataSafahat=appPath+"/images/"+riwaya+"/safahatrc";
    QString dataArbaa=appPath+"/images/"+riwaya+"/arbaarc";


    if(!QFile::exists(dataAyat)||!QFile::exists(dataSafahat)||!QFile::exists(dataArbaa)){

        dataAyat=":/data/datarc";
        dataSafahat=":/data/safahatrc";
        dataArbaa=":/data/arbaarc";
    }

    //-----------------------dataAyat-----------------------------
    QFile fileAyat(dataAyat);

   /* //-----------
 QString setsafha="1";
    QString textout="";
    QFile fileCsv2(appPath+"/images/warsh/safahatrc2");
    if (!fileCsv2.open(QFile::WriteOnly)){
    //    return ;
        qDebug()<<appPath+"/images/warsh/safahatrc2";
    }
    QTextStream out(&fileCsv2);
    QString line;
    //---------------------*/

    if (!fileAyat.open(QFile::ReadOnly)){
        return ;
    }
    myList->clear();
    QTextStream textStream(&fileAyat);
    QString lineAyat;

    lineAyat = textStream.readLine();//premier line

    while (!lineAyat.isNull()) {

        myList->append(lineAyat);
      /*//--------------
        QString   id=lineAyat.section(",",0,0).trimmed();
        QString safha=lineAyat.section(",",3,3).trimmed();
        QString mx=lineAyat.section(",",4,4).trimmed();
        QString my=lineAyat.section(",",5,5).trimmed();
        if (setsafha==safha){
            textout=textout+"|"+id+","+mx+","+my;
  qDebug()<<"|"+id+","+mx+","+my;
        }else{
            out << textout+"\n";
            textout=id+","+mx+","+my;
       qDebug()<<id+","+mx+","+my;
        }
        setsafha=safha;

        //--------------------*/

        lineAyat = textStream.readLine();
    }
 //  fileCsv2.close();
    fileAyat.close();

//    //-----------------------dataSafahat-----------------------------
//    QFile fileSafahat(dataSafahat);
//    if(!fileSafahat.open( QFile::ReadOnly)){
//        qDebug() <<"no open safahat " +appPath+"/safahatrc";
//    }
//    myListSafhat->clear();
//    QTextStream textStream2(&fileSafahat);
//    QString lineSafahat;
//    lineSafahat = textStream2.readLine();//premier line

//    while (!lineSafahat.isNull()) {

//        myListSafhat->append(lineSafahat);

//        lineSafahat = textStream2.readLine();
//    }
//    fileSafahat.close();

//    //-----------------------dataArbaa-----------------------------

//    QFile fileArbaa(dataArbaa);

//    if(!fileArbaa.open( QFile::ReadOnly)){
//        qDebug() <<"no open arbaa "+appPath+"/arbaarc" ;
//    }
//    myListArbaa->clear();
//    QTextStream textStreamarba(&fileArbaa);

//    QString lineArbaa;
//    lineArbaa = textStreamarba.readLine();

//    while (!lineArbaa.isNull()) {

//        myListArbaa->append(lineArbaa);

//        lineArbaa = textStreamarba.readLine();
//    }


//    fileArbaa.close();
}

 void Database::openDb(QString dataName)
 {
     databaseName=dataName;
     QFileInfo fi(dataName);
     tableName = fi.completeBaseName();
     db.setDatabaseName(dataName);
     QString txt="no database";
     if(!db.open()){

         txt=db.lastError().text();
         QMessageBox::information(0,"",txt);

     }



 }
QString Database::getTranslation(int pos)
{


    QString querytxt=QString("SELECT* FROM %1 WHERE id=%2 ORDER BY id").arg(tableName).arg(QString::number(pos));

    QSqlQuery query(querytxt,db);
    if(query.lastError().isValid()){
        qDebug()<<query.lastError();
          // QMessageBox::information(0,"",query.lastError().text());
        return query.lastError().text();
    }
    query.next();
    int fieldNo = query.record().indexOf("text");
    if (fieldNo==-1){
        fieldNo = query.record().indexOf("tafsir");
    }
    QString mytext = query.value(fieldNo).toString();
    query.next();
    return mytext;
}

//--------------------------------search- treeview------------------------------
void Database::searchInTreeview(QTreeWidget *view,QString searchString,int colum,bool hamza)
{
    for( int i = 0; i <view->topLevelItemCount(); i++ ) {
        view->topLevelItem(i)->setHidden(false );
        showAllItems(view->topLevelItem(i),view);
    }
    if (!searchString.isEmpty()){
        for( int i = 0; i <view->topLevelItemCount(); i++ ) {
            searchTreeForString(searchString,view->topLevelItem(i),true,i,view,colum,hamza) ;
        }
    }
}

bool Database::searchTreeForString(const QString &searchString, QTreeWidgetItem* parent
                                   , bool itemtop, int  topindex, QTreeWidget *view, int colum, bool hamza)
{
    int hiddenCount = 0;
    int hiddenparent=0;
    if (parent->childCount()==0 && !parent->text(colum).contains( searchString, Qt::CaseInsensitive )) {
        parent->setHidden(true);
    }
    for( int i = 0; i < parent->childCount(); ++i) {
        QTreeWidgetItem *child = parent->child(i);
    QString txtChild=child->text(colum);
    if(hamza==true){
        txtChild.replace(trUtf8("أ"),trUtf8("ا"));
        txtChild.replace(trUtf8("إ"),trUtf8("ا"));
        txtChild.replace(trUtf8("ؤ"),trUtf8("و"));
        // txtChild.replace(trUtf8("ئ"),trUtf8(""));
    }
        if( parent->isHidden() )
            hiddenCount++;
        else if(child->childCount()>0
                && !txtChild.contains( searchString, Qt::CaseInsensitive ) ) {//لا يحمل النص وله ابناء
            if( !searchTreeForString( searchString, child ,false,topindex,view,colum,hamza)) {
                child->setHidden(true);
                hiddenCount++;
            }
        } else if(child->childCount()>0// يحمل النص  له ابناء
                  && ( txtChild.contains( searchString, Qt::CaseInsensitive ) ) ){
            searchTreeForString( searchString, child ,false,topindex,view,colum,hamza);
        } else if(child->childCount()==0//لا يحمل النص وليس له ابناء
                  && ( !txtChild.contains( searchString, Qt::CaseInsensitive ) ) ) {
            child->setHidden(true);
            hiddenCount++;
        }
        if (itemtop==true){
            if(child->isHidden()){hiddenparent++;}
        }
    }
    QTreeWidgetItem *toplevel=view->topLevelItem(topindex);
    int topc=toplevel->childCount();
    QString txtTop=toplevel->text(colum);
    if(hamza==true){
        txtTop.replace(trUtf8("أ"),trUtf8("ا"));
        txtTop.replace(trUtf8("إ"),trUtf8("ا"));
        txtTop.replace(trUtf8("ؤ"),trUtf8("و"));
    }
    if( hiddenparent == topc  && !txtTop.contains( searchString, Qt::CaseInsensitive )){
        toplevel->setHidden(true);
    }
    if( hiddenCount == parent->childCount() )
        return false;
    return true;
}

bool Database::showAllItems( QTreeWidgetItem* parent,QTreeWidget *view )
{
    for( int i = 0; i < parent->childCount(); i++ ) {
        view->setItemHidden(parent->child(i),false);
        showAllItems( parent->child( i) ,view);
    }
    return true;
}
//--------------------------------search- treeview------------------------------
void Database::searchInCuran(QString searchString )
{
QString textSora;
int n=0;
int naya=1;
    QFile file(appPath +"/quran.xml");
    file.open(QIODevice::ReadOnly);

    QXmlStreamReader xml;
    xml.setDevice(&file);
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.name() == "Department"){
           QString textS=xml.attributes().value("Name").toString();;
            if(!textS.isNull()){
                naya=1;
                textSora=textS;
            }
        }
        if (xml.name() == "Item"){

            QString textAya=xml.readElementText();
            if(!textAya.isNull()){
                naya++;
                if (textAya.contains(searchString)){
                 n++;
                    qDebug()<<textSora+" : "+QString::number(naya) +" : "+textAya;
                }
            }
        }
    }
    qDebug()<<"Result  = "+QString::number(n);
    xml.clear();
    file.close();

}
//---------------------------------search --------------------
    void Database::dataSearchString(QTreeWidget *view,QString arg1,QString arg2,QString orAnd ,int option)
    {
        db.setDatabaseName(appPath+"/quran.db");

        // tableName = "quran";
        QString txt="no database";
        if(!db.open()){
            txt=db.lastError().text();
            QMessageBox::information(0,"",txt);

        }
        //-----------------------
        QString querytxt;
        if(option==3){
            querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%%1%' %2 nass_safy like'%%3%' ORDER BY id").arg(arg1).arg(orAnd).arg(arg2);
               }else{
            if(option==0){
                querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%%1%' ORDER BY id").arg(arg1);
            }else if(option==1){
                querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%1%' ORDER BY id").arg(arg1);
            }else if(option==2){
                querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%%1' ORDER BY id").arg(arg1);
            }
        }

        QSqlQuery query(querytxt,db);
        if(query.lastError().isValid()){
            qDebug()<<query.lastError();
            QMessageBox::information(0,"",query.lastError().text());
            return ;
        }
        //query.next();
        view->clear();
        while (query.next()) {
            int fieldId= query.record().indexOf("id");
            QString myid= query.value(fieldId).toString();
            int fieldTxt= query.record().indexOf("text");
            QString mytext = query.value(fieldTxt).toString();
            int fieldSura= query.record().indexOf("sura");
            QString mysura= query.value(fieldSura).toString();
            int fieldAya= query.record().indexOf("aya");
            QString myaya= query.value(fieldAya).toString();
            QTreeWidgetItem *item=new  QTreeWidgetItem(view);
            item->setText(0,mysura);
            item->setText(1,myaya);
            item->setText(2,mytext);
            item->setText(3,myid);
            //  QMessageBox::information(0,"",mytext);
            qDebug()<< myid+"-"+mysura+"-"+myaya+"-"+mytext;
           // query.next();
        }
        openDb(databaseName);

    }
//    void  Database::chargeTree(QTreeWidget *view)
//    {
//        db.setDatabaseName(appPath+"/quran.db");

//        // tableName = "quran";
//        QString txt="no database";
//        if(!db.open()){
//            txt=db.lastError().text();
//            QMessageBox::information(0,"",txt);

//        }
//        //-----------------------

//         QString querytxt;
//           querytxt=QString("SELECT* FROM quran  ORDER BY id");
//           QSqlQuery query(querytxt,db);
//           if(query.lastError().isValid()){
//               qDebug()<<query.lastError();
//               QMessageBox::information(0,"",query.lastError().text());
//               return ;
//           }
//           while (query.next()) {
////               int fieldId= query.record().indexOf("id");
////               QString myid= query.value(fieldId).toString();
//               int fieldTxt= query.record().indexOf("nass_safy");
//               QString mytext = query.value(fieldTxt).toString();
//               int fieldSura= query.record().indexOf("sura");
//               int mysura= query.value(fieldSura).toInt();
//               int fieldAya= query.record().indexOf("aya");
//               int myaya= query.value(fieldAya).toInt();

//           //    QMessageBox::information(0,"",mytext);
//              view->topLevelItem(mysura-1)->child(myaya-1)->setText(0,mytext);
//            qApp->processEvents();
//                    //    query.next();
//          }
//    }
    QString Database::getStringPage(int begen,int end)
    {
             db.setDatabaseName(appPath+"/quran.db");
             QString txt="no database";
             if(!db.open()){
                 txt=db.lastError().text();
                 QMessageBox::information(0,"",txt);

             }
           QString textpage;
             for(int i=begen;i<end+1;i++){
                 QString querytxt=QString("SELECT* FROM quran WHERE id=%1 ORDER BY id").arg(QString::number(i));

                 QSqlQuery query(querytxt,db);
                 if(query.lastError().isValid()){
                     qDebug()<<query.lastError();
                       // QMessageBox::information(0,"",query.lastError().text());
                     return query.lastError().text();
                 }
                 query.next();
                 int fieldNo = query.record().indexOf("text");
                 QString mytext = query.value(fieldNo).toString();
                 int fieldAya= query.record().indexOf("aya");
                 QString myaya= query.value(fieldAya).toString();
                 if(myaya=="1")
                     textpage=textpage+trUtf8("\n بســـــــــــــــــــــــم الله الرحمن الرحيم\n");

                 textpage=textpage+ mytext+" ("+myaya+") ";
                    query.next();
             }

                openDb(databaseName);
                return textpage;
    }
