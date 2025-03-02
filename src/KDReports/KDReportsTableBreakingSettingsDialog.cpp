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

#include "KDReportsTableBreakingSettingsDialog.h"
#include "KDReportsMainTable.h"
#include "KDReportsReport.h"
#include "KDReportsTextDocument_p.h"
#include "ui_tablebreakingdialogbase.h"
#include <QDebug>

class KDReports::TableBreakingSettingsDialogPrivate : public Ui::TableBreakingSettingsDialog
{
public:
    TableBreakingSettingsDialogPrivate(KDReports::Report *report)
        : m_report(report)
    {
    }
    void slotBreakTablesToggled(bool breakTables)
    {
        if (!breakTables) {
            // If we can't break tables, then we can only scale to 1 pages horizontally
            numHorizontalPages->setValue(1);
        }
        numHorizontalPages->setEnabled(breakTables);
    }

    KDReports::Report *m_report;
};

KDReports::TableBreakingSettingsDialog::TableBreakingSettingsDialog(KDReports::Report *report, QWidget *parent)
    : QDialog(parent)
    , d(new TableBreakingSettingsDialogPrivate(report))
{
    d->setupUi(this);

    connect(d->breakTables, &QAbstractButton::toggled, this, [this](bool b) { d->slotBreakTablesToggled(b); } );

    // LOAD SETTINGS
    d->breakTables->setChecked(true); // trigger the toggled signal if the next line sets it back to false
    d->breakTables->setChecked(d->m_report->isTableBreakingEnabled());
    if (d->m_report->isTableBreakingEnabled() && d->m_report->fontScalingFactor() == 1.0) {
        const int maxH = d->m_report->maximumNumberOfPagesForHorizontalScaling();
        const int maxV = d->m_report->maximumNumberOfPagesForVerticalScaling();
        d->fit->setChecked(true);
        d->numHorizontalPages->setValue(maxH);
        d->numVerticalPages->setValue(maxV);
    } else {
        d->scaleFonts->setChecked(true); // default value, 100% scaling i.e. noop
        d->scalingFactor->setValue(qRound(d->m_report->fontScalingFactor() * 100));
    }

    if (d->m_report->tableBreakingPageOrder() == KDReports::Report::DownThenRight)
        d->downThenRight->setChecked(true);
    else
        d->rightThenDown->setChecked(true);

    KDReports::AutoTableElement *autoTable = d->m_report->mainTable()->autoTableElement();
    // Auto table settings
    if (autoTable) {
        d->showHorizontalHeader->setChecked(autoTable->isHorizontalHeaderVisible());
        d->showVerticalHeader->setChecked(autoTable->isVerticalHeaderVisible());
        d->showGrid->setChecked(autoTable->border() > 0);
    } else {
        d->tableSettingsGroupBox->hide();
    }
}

KDReports::TableBreakingSettingsDialog::~TableBreakingSettingsDialog()
{
}

void KDReports::TableBreakingSettingsDialog::accept()
{
    // SAVE SETTINGS
    const bool breakTables = d->breakTables->isChecked();
    if (d->fit->isChecked()) {
        d->m_report->setFontScalingFactor(1.0);
        d->m_report->scaleTo(breakTables ? d->numHorizontalPages->value() : 1, d->numVerticalPages->value());
    } else {
        d->m_report->setFontScalingFactor(static_cast<qreal>(d->scalingFactor->value()) / 100.0);
    }

    if (d->downThenRight->isChecked()) {
        d->m_report->setTableBreakingPageOrder(KDReports::Report::DownThenRight);
    } else {
        d->m_report->setTableBreakingPageOrder(KDReports::Report::RightThenDown);
    }

    KDReports::AutoTableElement *autoTable = d->m_report->mainTable()->autoTableElement();
    // Auto table settings
    if (autoTable) {
        autoTable->setHorizontalHeaderVisible(d->showHorizontalHeader->isChecked());
        autoTable->setVerticalHeaderVisible(d->showVerticalHeader->isChecked());
        const bool currentGrid = autoTable->border() > 0;
        if (currentGrid != d->showGrid->isChecked()) // don't change a border of 2 if the user didn't toggle the checkbox
            autoTable->setBorder(d->showGrid->isChecked() ? 1 : 0);
        d->m_report->regenerateAutoTables();
    } else {
        d->tableSettingsGroupBox->hide();
    }

    QDialog::accept();
}

void KDReports::TableBreakingSettingsDialog::reject()
{
    QDialog::reject();
}
