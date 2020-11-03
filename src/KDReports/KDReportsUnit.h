/****************************************************************************
**
** This file is part of the KD Reports library.
**
** SPDX-FileCopyrightText: 2007-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: ((LGPL-2.1-only OR LGPL-3.0-only) AND (GPL-2.0-only OR GPL-3.0-only)) OR LicenseRef-KDAB-KDReports OR LicenseRef-KDAB-KDReports-US
**
** Licensees holding valid commercial KD Reports licenses may use this file in
** accordance with the KD Reports Commercial License Agreement provided with
** the Software.
**
** Contact info@kdab.com if any conditions of this licensing are not clear to you.
**
****************************************************************************/

#ifndef KDREPORTSUNIT_H
#define KDREPORTSUNIT_H

namespace KDReports
{

/**
 * Units used when setting a size.
 */
enum Unit {
    Millimeters, ///< Millimeters (the default)
    Percent      ///< Percentage of the text width, i.e. the page width minus margins
};

}

#endif /* KDREPORTSUNIT_H */

