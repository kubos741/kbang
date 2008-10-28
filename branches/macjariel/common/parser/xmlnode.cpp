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
#include "xmlnode.h"
#include <QXmlStreamAttributes>
#include <QStringRef>
#include <QtDebug>


XmlNode::XmlNode(XmlNode* parent, const QString& elementName)
 : QObject(parent), m_elementName(elementName)
{
//    qDebug() << "Creating node (1): " << m_elementName;
}

XmlNode::XmlNode(XmlNode* parent, const QStringRef& elementName, const QXmlStreamAttributes& attributes):
QObject(parent), m_elementName(elementName.toString())
{
//    qDebug() << "Creating node (2): " << m_elementName;
    createAttributes(attributes);
}



XmlNode::~XmlNode()
{
}

XmlNode* XmlNode::parentNode()
{
    XmlNode* p = qobject_cast<XmlNode* >(parent());
    Q_ASSERT(p != 0);
    return p;
}

XmlNode* XmlNode::createChildNode(const QString& elementName)
{
    XmlNode* newNode = new XmlNode(this, elementName);
    m_children.append(newNode);
    return newNode;
}

XmlNode* XmlNode::createChildNode(const QStringRef& elementName, const QXmlStreamAttributes& attributes)
{
    XmlNode* newNode = createChildNode(elementName.toString());
    newNode->createAttributes(attributes);
    return newNode;
}

void XmlNode::createAttribute(const QString& name, const QString& value)
{
    m_attributes[name] = value;
}


void XmlNode::createAttributes(const QXmlStreamAttributes& attributes)
{
    foreach(QXmlStreamAttribute attr, attributes)
    {
        QString name = attr.name().toString();
        QString value = attr.value().toString();
        createAttribute(name, value);
    }
}

void XmlNode::debugPrint(int indent) const
{
    if (indent == 0)
    {
        qDebug() << "debugPrint of XmlNode:";
    }
    qDebug("%s%s", qPrintable(QString(indent, ' ')), qPrintable(m_elementName));
    qDebug("%s%s", qPrintable(QString(indent, ' ')), "ARGUMENTS:");
    
    foreach(QString key, m_attributes.keys())
    {
        qDebug("%s%s=%s", qPrintable(QString(indent + 1, ' ')), qPrintable(key), qPrintable(m_attributes[key]));
    }
    
    qDebug("%s%s", qPrintable(QString(indent, ' ')), "CHILDREN:");
    foreach(XmlNode* child, m_children)
    {
        child->debugPrint(indent + 2);
    }
}

QString XmlNode::name() const
{
    return m_elementName;
}

QString XmlNode::attribute(const QString& name) const
{
    return m_attributes[name];
}

XmlNode* XmlNode::getFirstChild() const
{
    if (m_children.size() == 0) return 0;
    return m_children[0];
}

QList<XmlNode*> XmlNode::getChildren() const
{
    return m_children;
}



