#ifndef XMLHANDLE_H
#define XMLHANDLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <libxml/xmlreader.h>

#if defined(LIBXML_READER_ENABLED)
    
    void parse_config(xmlDocPtr doc, xmlNodePtr cur);
    void parse_packet_simulation(xmlDocPtr doc, xmlNodePtr cur);
    void parse_struct_description(xmlDocPtr doc, xmlNodePtr cur);
    void parse_field(xmlDocPtr doc, xmlNodePtr cur);
    void parse_variation(xmlDocPtr doc, xmlNodePtr cur);
#else
    #error "here"
#endif

#ifdef __cplusplus
}
#endif

#endif /* XMLHANDLE_H */

