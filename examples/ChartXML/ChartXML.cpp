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

#include <QApplication>
#include <QDebug>

#include <KDReports>
#include <KDReportsChartElement.h>
#include <KDReportsXmlElementHandler.h>
#include <QDomElement>
#include <QFile>
#include <QMessageBox>
#include <QPrintDialog>
#include <TableModel.h>

#include <KDChartChart>
#include <KDChartPieDiagram>
#include <KDChartPolarCoordinatePlane>

class MyXmlElementHandler : public KDReports::XmlElementHandler
{
public:
    MyXmlElementHandler(KDChart::Chart *chart)
        : m_chart(chart)
    {
    }
    bool chartElement(KDReports::ChartElement &chartElement, QDomElement &xmlElement) override
    {
        qDebug() << "chartElement called";
        Q_UNUSED(xmlElement);
        chartElement.setChart(m_chart);
        return true;
    }

private:
    KDChart::Chart *m_chart;
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Create a report
    KDReports::Report report;

    QFile reportFile(":/Chart.xml");
    if (!reportFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0, QObject::tr("Warning"), QObject::tr("Could not open report description file 'Chart.xml', which should have been compiled into the application."));
        return -1;
    }

    // Prepare chart model
    TableModel chartModel;
    chartModel.setDataHasVerticalHeaders(false);
    chartModel.loadFromCSV(":/chart_model");

    // Prepare chart
    KDChart::Chart chart;
    chart.replaceCoordinatePlane(new KDChart::PolarCoordinatePlane(&chart));
    KDChart::PieDiagram *diagram = new KDChart::PieDiagram();
    diagram->setModel(&chartModel);
    chart.coordinatePlane()->replaceDiagram(diagram);

    MyXmlElementHandler myHandler(&chart);
    report.setXmlElementHandler(&myHandler);

    KDReports::ErrorDetails details;
    if (!report.loadFromXML(&reportFile, &details)) {
        QMessageBox::warning(0, QObject::tr("Warning"), QObject::tr("Could not parse report description file:\n%1").arg(details.message()));
        reportFile.close();
        return -2;
    }

    // show a print preview:
    KDReports::PreviewDialog preview(&report);
    return preview.exec();
}
