#include <libxml/xmlversion.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlstring.h>
#include <libxml/tree.h>

void parse_variation(xmlDocPtr doc, xmlNodePtr cur)
{

            xmlChar *key;
        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"type"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf("\t\t type: %s\n", key);
                        xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"value"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf("\t\t value: %s\n", key);
                        xmlFree(key);
                }
                cur = cur->next;
        }    
    
}
void parse_field(xmlDocPtr doc, xmlNodePtr cur)
{

            xmlChar *key;
        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"field_name"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf("\t field_name: %s\n", key);
                        xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"field_type"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf("\t field_type: %s\n", key);
                        xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"field_repet_time"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf("\t field_repet_time: %s\n",key);
                        parse_field(doc, cur);
                        xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"variation"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf("\t variation\n");
                        parse_variation(doc, cur);
                        xmlFree(key);
                }                
                cur = cur->next;
        }
    
}

void parse_struct_description(xmlDocPtr doc, xmlNodePtr cur)
{

        xmlChar *key;
        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"id"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf(" id: %s\n", key);
                        xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf(" name: %s\n", key);
                        xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"field"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf(" field\n");
                        parse_field(doc, cur);
                        xmlFree(key);
                }
                cur = cur->next;
        }

    
}

void parse_packet_simulation(xmlDocPtr doc, xmlNodePtr cur)
{
        xmlChar *key;
        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"struct_description"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf(" struct_description\n");
                        parse_struct_description(doc, cur);
                        xmlFree(key);
                }
                cur = cur->next;

        }
}


void parse_config(xmlDocPtr doc, xmlNodePtr cur)
{
        xmlChar *key;
        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"packet_simulation"))) {
                        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                        printf("packet_simulation\n");
                        parse_packet_simulation(doc, cur);
                        xmlFree(key);
                }
                cur = cur->next;
        }
}
