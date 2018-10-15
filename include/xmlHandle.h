#ifndef XMLHANDLE_H
#define XMLHANDLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <libxml/xmlreader.h>

#if defined(LIBXML_READER_ENABLED)
#else
    #error "here"
#endif

#ifdef __cplusplus
}
#endif

#endif /* XMLHANDLE_H */

