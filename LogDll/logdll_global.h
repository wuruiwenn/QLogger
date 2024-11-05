#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOGDLL_LIB)
#  define LOGDLL_EXPORT Q_DECL_EXPORT
# else
#  define LOGDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOGDLL_EXPORT
#endif
