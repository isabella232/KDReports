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

#ifndef KDREPORTSFRAME_H
#define KDREPORTSFRAME_H

#include "KDReportsElement.h"
#include "KDReportsUnit.h"
#include "KDReportsVariableType.h"
#include <QMap>
#include <QPair>
#include <QtCore/Qt>

namespace KDReports {
class ReportBuilder;
class Element;
class FramePrivate;

/**
 * This class represents a frame, with other elements inside.
 * The frame can be visible or not.
 * \since 1.7
 */
class KDREPORTS_EXPORT Frame : public Element
{
public:
    /**
     * Creates a frame.
     */
    explicit Frame();
    /**
     * Destroys this frame.
     */
    ~Frame() override;

    /**
     * Copies a frame.
     * The contents are copied over.
     */
    Frame(const Frame &other);
    /**
     * Copies the text and settings from another frame.
     */
    Frame &operator=(const Frame &other);

    /**
     * Set the frame width in millimeters or in percent of the page width.
     */
    void setWidth(qreal width, Unit unit = Millimeters);
    /**
     * Set the frame height in millimeters or in percent of the page height.
     */
    void setHeight(qreal height, Unit unit = Millimeters);

    /**
     * Specifies the size of the padding in millimeters.
     * Padding is the distance between the contents of the frame and the frame border,
     * all around the contents (above, below, on the left and on the right).
     * The default padding has a size of 0.5 mm.
     */
    void setPadding(qreal padding);

    /**
     * Returns the width of the frame's internal padding in millimeters.
     */
    qreal padding() const;

    /**
     * Specifies the width of the border in pixels.
     * The default border has a width of 1.
     * Set it to 0 for a frame without borders.
     */
    void setBorder(qreal border);

    /**
     * Returns the width of the frame
     */
    qreal border() const;

    /**
     * Adds an element to the frame, next to the previous element, in the same paragraph.
     */
    void addInlineElement(const Element &element);

    /**
     * Adds an element to the frame, creating a new paragraph for it.
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
     * @internal
     * @reimp
     */
    Element *clone() const override;

private:
    std::unique_ptr<FramePrivate> d;
};

}

#endif /* KDREPORTSFRAME_H */
