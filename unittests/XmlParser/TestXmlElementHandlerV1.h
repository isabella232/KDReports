/****************************************************************************
**
** This file is part of the KD Reports library.
**
** SPDX-FileCopyrightText: 2007-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#ifndef TESTXMLELEMENTHANDLERV1_H
#define TESTXMLELEMENTHANDLERV1_H

#include "KDReportsXmlElementHandler.h"
#include <QStringList>

class TestXmlElementHandlerV1 : public KDReports::XmlElementHandler
{
public:
    explicit TestXmlElementHandlerV1(KDReports::Report &report);
    QStringList callbacks() const { return cb; }

    bool startReport(KDReports::Report &report, QDomElement &xmlElement) override;
    bool startHeader(KDReports::Header &header, QDomElement &xmlElement) override;
    void endHeader(KDReports::Header &header, const QDomElement &xmlElement) override;
    bool startFooter(KDReports::Footer &footer, QDomElement &xmlElement) override;
    void endFooter(KDReports::Footer &footer, const QDomElement &xmlElement) override;
    bool textElement(KDReports::TextElement &textElement, QDomElement &xmlElement) override;
    bool htmlElement(KDReports::HtmlElement &htmlElement, QDomElement &xmlElement) override;
    bool startTableElement(KDReports::TableElement &tableElement, QDomElement &xmlElement) override;
    bool endTableElement(KDReports::TableElement &tableElement, QDomElement &xmlElement) override;
    bool startCell(KDReports::Cell &cell, QDomElement &xmlElement) override;
    bool endCell(KDReports::Cell &cell, QDomElement &xmlElement) override;
    bool autoTableElement(KDReports::AutoTableElement &tableElement, QDomElement &xmlElement) override;
    bool chartElement(KDReports::ChartElement &chartElement, QDomElement &xmlElement) override;
    bool imageElement(KDReports::ImageElement &imageElement, QDomElement &xmlElement) override;
    bool pageBreak(QDomElement &xmlElement) override;
#ifdef KDREPORTS_ALLOW_BINARY_INCOMPATIBILITY
    virtual bool hLineElement(KDReports::HLineElement &textElement, QDomElement &xmlElement);
#endif
    void customElement(const QDomElement &xmlElement) override;
    void endReport(KDReports::Report &report, const QDomElement &xmlElement) override;

private:
    QStringList cb;
    KDReports::Report &mReport;
};

#endif /* TESTXMLELEMENTHANDLERV1_H */
