##
## This file is part of the KD Reports library.
##
## SPDX-FileCopyrightText: 2015-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
##
## SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDReports OR LicenseRef-KDAB-KDReports-US
##
## Licensees holding valid commercial KD Reports licenses may use this file in
## accordance with the KD Reports Commercial License Agreement provided with
## the Software.
##
## Contact info@kdab.com if any conditions of this licensing are not clear to you.
##

remove_definitions(-DQT_NO_CAST_FROM_BYTEARRAY)
remove_definitions(-DQT_NO_CAST_FROM_ASCII)

add_subdirectory(tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools ${CMAKE_CURRENT_SOURCE_DIR}/../src/KDReports ${CMAKE_CURRENT_BINARY_DIR}/../src/KDReports)
add_subdirectory(Letter)
add_subdirectory(Labels)
add_subdirectory(HelloWorld)
add_subdirectory(ReferenceReport)
add_subdirectory(PriceList)
add_subdirectory(HelloWorldXML)
add_subdirectory(PriceListXML)
add_subdirectory(SpreadsheetAutoTable)
add_subdirectory(LongTextReport)
add_subdirectory(BigImage)
add_subdirectory(MailMergeXML)
add_subdirectory(ReportSection)

if(NOT EMSCRIPTEN)
  if(TARGET Qt${Qt_VERSION_MAJOR}::Sql)
    list(APPEND QT_LIBRARIES Qt${Qt_VERSION_MAJOR}::Sql)
    add_subdirectory(Database)
    add_subdirectory(DatabaseXML)
  else()
    message(STATUS "QtSql not found.  skipping the Sql examples")
  endif()
endif()

if(KDChart_FOUND)
  add_subdirectory(ChartXML)
else()
  message(STATUS "KDChart not found.  skipping the ChartXML example")
endif()
