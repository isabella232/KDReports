## This file is part of the KD Reports library.
##
## SPDX-FileCopyrightText: 2021-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
##
## SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDReports OR LicenseRef-KDAB-KDReports-US
##
## Licensees holding valid commercial KD Reports licenses may use this file in
## accordance with the KD Reports Commercial License Agreement provided with
## the Software.
##
## Contact info@kdab.com if any conditions of this licensing are not clear to you.
##

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.py.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.py @ONLY)

set(TEST_PYTHONPATH
    ${CMAKE_BINARY_DIR}/python
    ${CMAKE_CURRENT_BINARY_DIR}
)
set(TEST_LIBRARYPATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if(WIN32)
  set(TEST_LIBRARY_VAR "PATH")
  string(REPLACE "\\" "/" TEST_PYTHONPATH "${TEST_PYTHONPATH}")
  string(REPLACE "\\" "/" TEST_LIBRARYPATH "${TEST_LIBRARYPATH}")
  list(JOIN TEST_PYTHONPATH "\\;" TEST_PYTHONPATH)
  list(JOIN TEST_LIBRARYPATH "\\;" TEST_LIBRARYPATH)
else()
  set(TEST_LIBRARY_VAR "LD_LIBRARY_PATH")
  list(JOIN TEST_PYTHONPATH ":" TEST_PYTHONPATH)
  list(JOIN TEST_LIBRARYPATH ":" TEST_LIBRARYPATH)
endif()

set(PYTHON_ENV_COMMON "PYTHONPATH=${TEST_PYTHONPATH};${TEST_LIBRARY_VAR}=${TEST_LIBRARYPATH}")

file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tst_*.py)
foreach(test_file ${TEST_FILES})
  get_filename_component(test_name ${test_file} NAME_WE)
  add_test(${test_name} ${Python3_EXECUTABLE} ${test_file})
  set_tests_properties(${test_name} PROPERTIES ENVIRONMENT "${PYTHON_ENV_COMMON}")
endforeach()

