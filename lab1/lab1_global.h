#ifndef LAB1_GLOBAL_H
#define LAB1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LAB1_LIBRARY)
#  define LAB1SHARED_EXPORT Q_DECL_EXPORT
#else
#  define LAB1SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LAB1_GLOBAL_H
