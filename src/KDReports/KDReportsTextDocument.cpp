/****************************************************************************
**
** This file is part of the KD Reports library.
**
** SPDX-FileCopyrightText: 2007-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDReports OR LicenseRef-KDAB-KDReports-US
**
** Licensees holding valid commercial KD Reports licenses may use this file in
** accordance with the KD Reports Commercial License Agreement provided with
** the Software.
**
** Contact info@kdab.com if any conditions of this licensing are not clear to you.
**
****************************************************************************/

#include "KDReportsTextDocument_p.h"
#include "KDReportsLayoutHelper_p.h"

#include <QDebug>

//#define DEBUG_TABLEBREAKING

KDReports::TextDocument::TextDocument() { }

KDReports::TextDocument::~TextDocument() { }

void KDReports::TextDocument::layoutWithTextWidth(qreal w)
{
    m_contentDocument.layoutWithTextWidth(w);
}

void KDReports::TextDocument::setPageSize(QSizeF size)
{
    m_contentDocument.setPageSize(size);
}

KDReports::TextDocumentData &KDReports::TextDocument::contentDocumentData()
{
    return m_contentDocument;
}

QTextDocument &KDReports::TextDocument::contentDocument()
{
    return contentDocumentData().document();
}

QFont KDReports::TextDocument::defaultFont() const
{
    return m_contentDocument.document().defaultFont();
}

void KDReports::TextDocument::scaleFontsBy(qreal factor)
{
    m_contentDocument.scaleFontsBy(factor);
}

void KDReports::TextDocument::updateTextValue(const QString &id, const QString &newValue)
{
    m_contentDocument.updateTextValue(id, newValue);
}

//@cond PRIVATE
QString KDReports::TextDocument::asHtml() const
{
    return m_contentDocument.asHtml();
}
//@endcond

void KDReports::TextDocument::preciseDump()
{
#if 0
    qDebug() << "Dumping document:";
    QTextCursor cursor( &m_contentDocument );
    int i = 0;
    int currentBlock = -1;
    Q_FOREVER {
        const int blockNumber = cursor.block().blockNumber(); // needs Qt-4.4
        if ( blockNumber != currentBlock ) {
            currentBlock = blockNumber;
            qDebug() << " block" << currentBlock << "starts at char" << i;
            QTextFormat::PageBreakFlags flags = cursor.block().blockFormat().pageBreakPolicy();
            if ( flags & QTextFormat::PageBreak_AlwaysBefore )
                qDebug() << "  block" << currentBlock << "says: BREAK BEFORE";
            if ( flags & QTextFormat::PageBreak_AlwaysAfter )
                qDebug() << "  block" << currentBlock << "says: BREAK AFTER";
        }
        const QChar ch = m_contentDocument.characterAt( i );
        qDebug() << " char" << i << ch << ch.unicode(); // 8233 == paragraph separator

        if ( cursor.atEnd() ) {
            qDebug() << " document ends at" << cursor.position();
            break;
        }
        cursor.movePosition( QTextCursor::NextCharacter );
        ++i;
    }
#endif
}

//@cond PRIVATE
QList<KDReports::AutoTableElement *> KDReports::TextDocument::autoTableElements()
{
    return m_contentDocument.autoTableElements(); // doesn't matter in which one we call it
}

//@cond PRIVATE
void KDReports::TextDocument::regenerateAutoTables()
{
    m_contentDocument.regenerateAutoTables();
}

void KDReports::TextDocument::regenerateAutoTableForModel(QAbstractItemModel *model)
{
    m_contentDocument.regenerateAutoTableForModel(model);
}
//@endcond
