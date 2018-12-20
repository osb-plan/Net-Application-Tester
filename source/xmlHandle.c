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
#include "../include/bsp.h"

extern FIELD parse_field_ll;

extern char * pseudo_packet;        // packet to send
extern PACKET_BUILDER *pck_builder; // contains info about the lenght of the
                                    // singel field of the struct
extern uint32_t pseudo_packet_byte_len;

extern STRUCT_DESCRIPTION dict_description[MAX_STRUCT_DESCRIPTION];
extern unsigned int idx_dict_description;
extern uint32_t n_fields_parsed;

int convert_field_type(char * str) {
    int en = -1;

    if (strcmp(str, "bit") == 0) {
        printf("Bit\n");
        en = 0;
    } else if (strcmp(str, "u8") == 0) {
        printf("U8\n");
        en = 1;
    } else if (strcmp(str, "u16") == 0) {
        printf("U16\n");
        en = 2;
    } else if (strcmp(str, "u32") == 0) {
        printf("U32\n");
        en = 3;
    } else if (strcmp(str, "float") == 0) {
        printf("FLOAT\n");
        en = 4;
    } else if (strcmp(str, "text") == 0) {
        printf("TEXT\n");
        en = 5;
    } else if (strcmp(str, "custom") == 0) {
        printf("CUSTOM\n");
        en = 6;
    }
    return en;

}

unsigned int convert_field_type_byte(FIELD_TYPE field_type) {
    int en = -1;
    switch(field_type)
    {
        case(U8):
            //printf("U8\n");
            en = 1;            
            break;
        case(U16):
            //printf("U16\n");
            en = 2;            
            break;            
        case(U32):
            //printf("U32\n");
            en = 4;            
            break;            
    }
    return en;
}

int convert_variation_type(char * str) {
    int en = -1;

    if (strcmp(str, "fixed") == 0) {
        printf("Fixed\n");
        en = 0;
    } else if (strcmp(str, "binary") == 0) {
        printf("Binary\n");
        en = 1;
    } else if (strcmp(str, "swap") == 0) {
        printf("Swap\n");
        en = 2;
    }
    return en;

}

void parse_variation(xmlDocPtr doc, xmlNodePtr cur, VARIATION *var) {

    xmlChar *key;
    cur = cur->xmlChildrenNode;
    uint8_t idx = 0;
    VARIATION_TYPE_BINARY *var_type_tmp_binary = malloc(sizeof (VARIATION_TYPE_BINARY));
    VARIATION_TYPE_SWAP *var_type_tmp_swap = malloc(sizeof (VARIATION_TYPE_SWAP));
    VARIATION_TYPE_FIXED *var_type_tmp_fixed = malloc(sizeof (VARIATION_TYPE_FIXED));

    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "type"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            var->var_type = convert_variation_type(key);
            printf("\t\t type: %s\n", key);
            xmlFree(key);
        }
        switch (var->var_type) {
            case(BINARY):
            {
                if ((!xmlStrcmp(cur->name, (const xmlChar *) "value1"))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    var_type_tmp_binary->val1 = (float) atof(key);
                    printf("\t value1: %s\n", key);
                    xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *) "value2"))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    var_type_tmp_binary->val2 = (float) atof(key);
                    printf("\t value2: %s\n", key);
                    xmlFree(key);
                }
            }
                break;
            case(SWAP):
                if ((!xmlStrcmp(cur->name, (const xmlChar *) "start_value"))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    var_type_tmp_swap->start_value = (float) atof(key);
                    printf("\t start_value: %s\n", key);
                    xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *) "end_value"))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    var_type_tmp_swap->end_value = (float) atof(key);
                    printf("\t end_value: %s\n", key);
                    xmlFree(key);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *) "delta_up"))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    var_type_tmp_swap->delta_up = (float) atof(key);
                    printf("\t delta_up: %s\n", key);
                    xmlFree(key);
                }
                break;
            case(FIXED):
                if ((!xmlStrcmp(cur->name, (const xmlChar *) "value"))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    var_type_tmp_fixed->value = (float) atof(key);
                    printf("\t\t value: %s\n", key);
                    xmlFree(key);
                }
                break;
        }


        cur = cur->next;
    }
    switch (var->var_type) {
        case(BINARY):
            var->var_description = var_type_tmp_binary;
            free(var_type_tmp_fixed);
            free(var_type_tmp_swap);
            break;
        case(FIXED):
            var->var_description = var_type_tmp_fixed;
            free(var_type_tmp_binary);
            free(var_type_tmp_swap);
            break;
        case(SWAP):
            var->var_description = var_type_tmp_swap;
            free(var_type_tmp_fixed);
            free(var_type_tmp_binary);
            break;
    }
}

FIELD * parse_field(xmlDocPtr doc, xmlNodePtr cur) {

    xmlChar *key;
    cur = cur->xmlChildrenNode;
    FIELD *tmp_field = malloc(sizeof (FIELD));

    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "field_name"))) {

            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            memset(tmp_field->field_info.field_name, 0, NAME_CHAR_DEPTH);
            memcpy(tmp_field->field_info.field_name, key, sizeof (key));
            printf("\t field_name: %s\n", key);
            xmlFree(key);
        }
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "field_type"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            tmp_field->field_info.field_type = convert_field_type(key);
            printf("\t field_type: %s\n", key);
            xmlFree(key);
        }
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "field_repet_time"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            tmp_field->field_info.field_repeat_time = atoi(key);
            printf("\t field_repet_time: %s\n", key);
            xmlFree(key);
        }
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "variation"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("\t variation\n");
            VARIATION *var = malloc(sizeof (VARIATION));
            parse_variation(doc, cur, var);

            tmp_field->field_info.variation = var;
            xmlFree(key);
        }

        cur = cur->next;
    }
    return tmp_field;
}

void parse_struct_description(xmlDocPtr doc, xmlNodePtr cur) {


    xmlChar *key;
    cur = cur->xmlChildrenNode;
    FIELD *actual_field;
    unsigned int flag_first_field = 0;
    n_fields_parsed = 0;

    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            dict_description[idx_dict_description].id = (unsigned int) (atoi(key));

            printf(" id: %s\n", key);
            xmlFree(key);
        }
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "name"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            dict_description[idx_dict_description].name = (char*) (key);
            printf(" name: %s\n", key);
            xmlFree(key);
        }
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "field"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("field\n");
            if (!flag_first_field) {
                dict_description[idx_dict_description].first_field = parse_field(doc, cur);
                actual_field = dict_description[idx_dict_description].first_field;
                flag_first_field = 1;
                n_fields_parsed++;
                xmlFree(key);
            } else {
                actual_field->next = parse_field(doc, cur);
                actual_field = actual_field->next;
                actual_field->next = NULL;
                n_fields_parsed++;
            }
        }
        cur = cur->next;

    }

    int bufSize = 34;
    char *msg = "Number of fields parsed are = ";
    char *buf = malloc(bufSize);
    
    if (snprintf(buf, bufSize, "%s %d", msg, n_fields_parsed) >= bufSize) {
        printf("Not enough space. Aborting\n");
        exit(1);
    }

    plog(buf, INFO, 0);

    free(buf);
    
    printf("--------------------------------------------\n");
    printf("-----------------DUMP TEST------------------\n");
    printf("--------------------------------------------\n");
    
    pck_builder = malloc(sizeof(PACKET_BUILDER));
    
    pck_builder->byte_len = 0;
    pck_builder->actual_value = 0;
    pck_builder->next = malloc(sizeof(PACKET_BUILDER));
    pck_builder = pck_builder->next;
    for (actual_field = dict_description[0].first_field; actual_field; actual_field = actual_field->next) {

        printf("DUMP FIELD\n");

        printf("Field name: %s\n", actual_field->field_info.field_name);
        printf("----Repeat time %u\n", actual_field->field_info.field_repeat_time);
        printf("----Field Type: %d\n", actual_field->field_info.field_type);
        
        pseudo_packet_byte_len += convert_field_type_byte(actual_field->field_info.field_type);
        
        pck_builder->byte_len = convert_field_type_byte(actual_field->field_info.field_type);
        pck_builder->next = malloc(sizeof(PACKET_BUILDER));
        pck_builder = pck_builder->next;        

        VARIATION_TYPE_BINARY *var_tmp_b;
        VARIATION_TYPE_FIXED *var_tmp_f;
        VARIATION_TYPE_SWAP *var_tmp_s;
        
        switch (actual_field->field_info.variation->var_type) {
            case(BINARY):
            {
                var_tmp_b = (VARIATION_TYPE_BINARY *) actual_field->field_info.variation->var_description;
                printf("----BINARY: Val1: %f, Val2: %f.\n", var_tmp_b->val1, var_tmp_b->val1);
            }
                break;
            case(FIXED):
            {
                var_tmp_f = (VARIATION_TYPE_FIXED *) actual_field->field_info.variation->var_description;
                printf("----FIXED: Val: %f\n", var_tmp_f->value);
            }
                break;
            case(SWAP):
            {
                var_tmp_s = (VARIATION_TYPE_SWAP *) actual_field->field_info.variation->var_description;
                printf("----SWAP: Inc: %f, Start: %f, End: %f.\n",
                        var_tmp_s->delta_up,
                        var_tmp_s->start_value,
                        var_tmp_s->end_value);
            }
                break;
        }
    }
    pseudo_packet = malloc(pseudo_packet_byte_len);

}

void parse_packet_simulation(xmlDocPtr doc, xmlNodePtr cur) {
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "struct_description"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("Struct_description\n");
            parse_struct_description(doc, cur);
            xmlFree(key);
        }
        cur = cur->next;

    }
}

void parse_config(xmlDocPtr doc, xmlNodePtr cur) {
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) "packet_simulation"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("packet_simulation\n");
            parse_packet_simulation(doc, cur);
            xmlFree(key);
        }
        cur = cur->next;
    }
}
