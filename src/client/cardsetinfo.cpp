/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#include <QDir>
#include <QFile>
#include <QXmlStreamReader>
#include <QDomDocument>

#include "cardsetinfo.h"
#include "cardsetmanager.h"

#include <QtDebug>

using namespace client;

CardSetInfo::CardSetInfo(QDir dir):
        m_isLocal(1),
        m_dir(dir)
{
    if (!m_dir.exists()) {
        qWarning("Cannot create CardSetInfo. Directory '%s' does not exist.",
                 qPrintable(dir.absolutePath()));
        return;
    }

    m_cardSetFilePath = m_dir.filePath("cardset.xml");
    QFile cardsetFile(m_cardSetFilePath);
    if (!cardsetFile.exists()) {
        qWarning("Cannot create CardSetInfo. File '%s' does not exist.",
                 qPrintable(m_cardSetFilePath));
        return;
    }

    if (!cardsetFile.open(QIODevice::ReadOnly)) {
        qWarning("Cannot create CardSetInfo. Cannot open '%s'.",
                 qPrintable(m_cardSetFilePath));
        return;
    }

    QDomDocument doc("cardset");
    if (!doc.setContent(&cardsetFile)) {
        qWarning("Cannot create CardSetInfo. Invalid file '%s'.",
                 qPrintable(m_cardSetFilePath));
        return;
    }
    cardsetFile.close();

    QDomElement docElem = doc.documentElement();
    m_name = docElem.attribute("name");
    m_slot = docElem.attribute("slot");
    m_locale = QLocale(docElem.attribute("locale"));
    m_renderSigns = (docElem.attribute("render-signs") == "true");

    CardSetManager::instance().addKnownSlot(m_slot);
}
