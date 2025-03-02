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

#ifndef KDREPORTSCELL_H
#define KDREPORTSCELL_H

#include "KDReportsElement.h"
#include "KDReportsVariableType.h"
#include <QMap>
#include <QPair>
#include <QtCore/Qt>
#include <memory>

namespace KDReports {
class ReportBuilder;
class Element;
class CellContentMap;
class TableElement;
class CellPrivate;

/**
 * This class presents a cell in a table.
 * To add an element to a cell, first get hold of the
 * right cell using Table::cell(), then add elements to it.
 */
class KDREPORTS_EXPORT Cell final : public Element
{
public:
    /**
     * Set the number of columns that this cell will span.
     * The default is 1.
     */
    void setColumnSpan(int columnSpan);
    /**
     * Returns the number of columns that this cell will span.
     */
    int columnSpan() const;

    /**
     * Set the number of rows that this cell will span.
     * The default is 1.
     */
    void setRowSpan(int rowSpan);
    /**
     * Returns the number of rows that this cell will span.
     */
    int rowSpan() const;

    /**
     * Adds an element to the cell, next to the previous element, in the same paragraph.
     */
    void addInlineElement(const Element &element);

    /**
     * Adds an element to the cell, creating a new paragraph for it.
     * You can specify the alignment of that paragraph.
     */
    void addElement(const Element &element, Qt::AlignmentFlag horizontalAlignment = Qt::AlignLeft);

    /**
     * Adds an variable in the text of the current paragraph.
     * @see KDReportsHeader::addVariable
     */
    void addVariable(VariableType variable);

    /**
     * @internal
     * @reimp
     */
    void build(ReportBuilder &builder) const override;

    /**
     * @internal - not supported
     */
    Element *clone() const override { return nullptr; } // krazy:exclude=inline

    /**
     * @internal - do not call
     */
    ~Cell() override; // public for QMap

    /**
     * @internal - do not call
     */
    Cell(const Cell &other); // public for QMap
    /**
     * @internal - do not call
     */
    Cell &operator=(const Cell &other); // public for QMap

private:
    friend class TableElement;
    friend class QMap<QPair<int, int>, Cell>;
    Cell();

    std::unique_ptr<CellPrivate> d;
};

}

#endif /* KDREPORTSCELL_H */
