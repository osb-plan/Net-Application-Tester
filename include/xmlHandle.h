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
    /* Convert string related to variation in the relative enum */
    int convert_variation_type(char * str);
    int convert_field_type(char * str);
    
#else
    #error "here"
#endif

#ifdef __cplusplus
}
#endif

#endif /* XMLHANDLE_H */

