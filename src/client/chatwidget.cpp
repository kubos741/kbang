/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "common.h"
#include "chatwidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QClipboard>
#include <QtNetwork>
#include <QHttp>

using namespace client;

ChatWidget::ChatWidget(QWidget *parent)
 : QWidget(parent)
{
    setupUi(this);
    setContentsMargins(5, 5, 5, 5);

    #ifdef Q_WS_MAC
        mp_tabWidget->setStyleSheet("margin-top: 5px;");
    #endif
    #ifndef Q_WS_MAC
        mp_tabWidget->setStyleSheet("margin-top: 0px;");
    #endif

    /*
    QPalette palette = QApplication::palette();
    palette.setColor(QPalette::Base, QColor(0, 0, 0, 16));
    setPalette(palette);
    */
    mp_chatView->setOpenExternalLinks(true);

    // Set the background color because Qt on the Mac doesn't do the transparency correctly
    mp_chatView->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 130, 98);"));
    mp_messageBox->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 130, 98);"));
    mp_chatTranslatedView->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 130, 98);"));

    mp_chatView->setFocusPolicy(Qt::TabFocus);
    mp_messageBox->setFocusPolicy(Qt::ClickFocus);

    // Creating HTTP
    httpRequest = new QHttp(this);
    // Connecting HTTP event done to slot done
    connect(httpRequest,
            SIGNAL(done(bool)),
            this, SLOT(httpDone()));

    connect(mp_messageBox,
            SIGNAL(returnPressed()),
            this, SLOT(sendMessage()));

    // Set up flag/language information for use later
    languageMap["sq"]="Albanian";
    languageMap["ar"]="Arabic";
    languageMap["bg"]="Bulgarian";
    languageMap["ca"]="Catalan";
    languageMap["zh-CN"]="Chinese (Simplified)";
    languageMap["zh-TW"]="Chinese (Traditional)";
    languageMap["hr"]="Croatian";
    languageMap["cs"]="Czech";
    languageMap["da"]="Danish";
    languageMap["nl"]="Dutch";
    languageMap["en"]="English";
    languageMap["et"]="Estonian";
    languageMap["tl"]="Filipino";
    languageMap["fi"]="Finnish";
    languageMap["fr"]="French";
    languageMap["gl"]="Galician";
    languageMap["de"]="German";
    languageMap["el"]="Greek";
    languageMap["iw"]="Hebrew";
    languageMap["hi"]="Hindi";
    languageMap["hu"]="Hungarian";
    languageMap["id"]="Indonesian";
    languageMap["it"]="Italian";
    languageMap["ja"]="Japanese";
    languageMap["ko"]="Korean";
    languageMap["lv"]="Latvian";
    languageMap["lt"]="Lithuanian";
    languageMap["mt"]="Maltese";
    languageMap["no"]="Norwegian";
    languageMap["pl"]="Polish";
    languageMap["pt"]="Portuguese";
    languageMap["ro"]="Romanian";
    languageMap["ru"]="Russian";
    languageMap["sr"]="Serbian";
    languageMap["sk"]="Slovak";
    languageMap["sl"]="Slovenian";
    languageMap["es"]="Spanish";
    languageMap["sv"]="Swedish";
    languageMap["th"]="Thai";
    languageMap["tr"]="Turkish";
    languageMap["uk"]="Ukrainian";
    languageMap["vi"]="Vietnamese";

    // This will be used to track translations
    translateTrack.clear();
    translateCounter = 0;
}

ChatWidget::~ChatWidget()
{
}

void ChatWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(event->rect().intersect(contentsRect()), QColor(0, 0, 0, 32));
}

void ChatWidget::clear()
{
    mp_chatView->clear();
    mp_chatTranslatedView->clear();
}

void ChatWidget::sendMessage()
{
    const QString& message = mp_messageBox->text();
    mp_messageBox->clear();
    emit outgoingMessage(Qt::escape(message));
}

// Take incoming messages, create a link to Google Translate, and also send the translation request
void ChatWidget::incomingMessage(int, const QString& senderName, const QString& message)
{
    //qDebug(qPrintable(QString("Sender=%1, lang=%2, msg=%3").arg(senderName).arg(mp_destinationLanguage).arg(message)));
    QString chatHTML = "<a style='color: #000000; text-decoration: none; background: #9E8262' href='%1'>%2</a>";
    QString urlTranslateFriendly = "http://translate.google.com/translate_t?sl=auto&tl=%1&text=%2#";
    QString urlTranslateRaw = "http://translate.google.com/translate_a/t?client=t&sl=auto&tl=%1";

    // Make all the text a clickable link to translate.google.com, from = auto
    mp_chatView->append(QString("<b>%1:</b> %2")
                        .arg(Qt::escape(removeHTMLtags(senderName)))
                        .arg(QString(chatHTML)
                             .arg(QString(urlTranslateFriendly)
                                  .arg(mp_destinationLanguage)
                                  .arg(QString(Qt::escape(message)).replace(" ", "%20")))
                             .arg(message)));

    // Prepare the request
    QHttpRequestHeader requestHeader =
            QHttpRequestHeader("POST", QString(urlTranslateRaw)
                                        .arg(mp_destinationLanguage)
//                                        .arg(QString(Qt::escape(message)).replace(" ", "%20"))
                               , 1, 1);
    requestHeader.setValue("Host", "www.google.com");
    requestHeader.setValue("User-Agent", "Mozilla/5.0");
    requestHeader.setValue("Accept-Encoding", "deflate");
    requestHeader.setContentLength(message.length());
    requestHeader.setValue("Connection", "Close");

    // Code up the sender name and message
    QByteArray sendByteArray("&text=");
    sendByteArray.append( message.toUtf8() + QString("||%1").arg(translateCounter));

    // Send off for the translation
    httpRequest->setHost("www.google.com");
    httpRequest->request(requestHeader, sendByteArray);
qDebug(qPrintable(QString("Sender=%1, Message=%2, %3").arg(senderName).arg(requestHeader.path()).arg(QString(sendByteArray))));
    translateTrack[translateCounter] = senderName;
    translateCounter += 1;

}

// This function is a callback when the http request is complete
void ChatWidget::httpDone()
{
    bool ok;
    qDebug("HTTP Request done.");

    QString returnedText = returnedText.fromUtf8( httpRequest->readAll() );

    qDebug(qPrintable(QString("httpRequest=%1").arg(returnedText)));

    // For use in the regex test app:  \"(.*).*\|.*\|.*([0-9]*)\",\"(.*)\"
    QRegExp regex("\\\"(.*)\\s*\\|\\s*\\|\\s*([0-9]*)\\\",\\\"(.*)\\\"");
    regex.setPatternSyntax(QRegExp::RegExp2);
    regex.setMinimal(true);
    QString senderName = "";

    if (regex.indexIn(returnedText) > -1) {
        static QString imgHTML = "<img src=\":/flags/flags/%1.png\" width=15 align=abmiddle title=\"Translated from %2\"> <b>%3</b>: <i>%4</i>";
        // Get the translated message, the language it came from
        QString newMessage = regex.cap(1);
        QString langFrom = regex.cap(3);
        // Get the number we had passed so we can look up the sender
        int findEntry = regex.cap(2).toInt(&ok, 10);
        QString senderName = translateTrack.take(findEntry);
        // Look up sender we saved when we sent it
qDebug(qPrintable(QString("TransMsg=%1, findEntry=%2, senderName=%3, langFrom=%4").arg(newMessage).arg(findEntry).arg(senderName).arg(langFrom)));
        mp_chatTranslatedView->append(QString(imgHTML).arg(langFrom).arg(languageMap[langFrom]).arg(senderName).arg(newMessage));
    } else
        mp_chatTranslatedView->append("Translation unavailable");
}

void ChatWidget::setLanguage(QString passedLanguage)
{
    mp_destinationLanguage = "en";
    if (languageMap.contains(passedLanguage))
            mp_destinationLanguage = passedLanguage;

    if (languageMap.contains(mp_destinationLanguage))  {
        mp_destinationLanguageFull = languageMap[mp_destinationLanguage];
        QString path = QString(":/flags/flags/%1.png").arg(mp_destinationLanguage);
        mp_tabWidget->setTabIcon(1, QIcon(path));
        mp_tabWidget->setTabToolTip(1, "Chat translated into " + mp_destinationLanguageFull + " via Google Translate");
    }
}
