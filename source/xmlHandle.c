/* System libraries */
#include <stdint.h>
#include <string.h>

/* External libraries */
#include <libxml/xmlversion.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlstring.h>
#include <libxml/tree.h>

/* Application header */
#include "../include/data_defs.h"

int convert_field_type(char * str)
{
    int en = -1;
    
    if( strcmp(str,"bit") == 0)
    {
 	printf("Bit\n"); 
	en = 0;
    }else if (strcmp(str,"u8") == 0)
    {
         printf("U8\n"); 
	 en = 1;
    }else if (strcmp(str,"u16") == 0)
    {
         printf("U16\n"); 
	 en = 2;
    }else if (strcmp(str,"u32") == 0)
    {
         printf("U32\n"); 
	 en = 3;
    }else if (strcmp(str,"float") == 0)
    {
         printf("FLOAT\n"); 
	 en = 4;
    }else if (strcmp(str,"text") == 0)
    {
         printf("TEXT\n"); 
	 en = 5;
    }else if (strcmp(str,"custom") == 0)
    {
         printf("CUSTOM\n"); 
	 en = 6;
    }

    return en;
    
}

int convert_variation_type(char * str)
{
    int en = -1;
    
    if( strcmp(str,"fixed") == 0)
    {
 	printf("Fixed\n"); 
	en = 0;
    }else if (strcmp(str,"binary") == 0)
    {
         printf("Binary\n"); 
	 en = 1;
    }else if (strcmp(str,"swap") == 0)
    {
         printf("Swap\n"); 
	 en = 2;
    }
    return en;
    
}


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
