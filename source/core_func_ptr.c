/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>

#include "data_defs.h"
#include "bsp.h"

extern PACKET_BUILDER pck_builder;

float _swap_func(FIELD *f, uint32_t idx) 
{
    
    VARIATION_TYPE_SWAP *var = 
            (VARIATION_TYPE_SWAP *)f->field_info.variation->var_description;

    if(pck_builder.actual_value >= var->start_value ||
       pck_builder.actual_value <= var->end_value)
    {
        
        if( (pck_builder.actual_value += var->delta_up)
                < var->end_value )
        {
            pck_builder.actual_value += var->delta_up;
        }else
        {
            // Overflow
            pck_builder.actual_value = var->start_value;
        }
    }else{
        plog("FATAL ERROR: out of bound in the _swap_func", 1, 1);
    }
    return pck_builder.actual_value;
}

float _binary_func(FIELD *f, uint32_t idx) {
    
        VARIATION_TYPE_BINARY *var = 
            (VARIATION_TYPE_BINARY *)f->field_info.variation->var_description;
        
    if(pck_builder.actual_value == var->val1 ||
       pck_builder.actual_value == var->val2)        
    {
        pck_builder.actual_value = pck_builder.actual_value == var->val1 ?
                                   var->val2                             :
                                   var->val1;            
    }
    else
    {
        plog("FATAL ERROR: out of bound in the _binary_func", 1, 1);
    }
    return pck_builder.actual_value;        
}

float _fixed_func(FIELD *f, uint32_t idx) {
        VARIATION_TYPE_FIXED *var = 
            (VARIATION_TYPE_FIXED *)f->field_info.variation->var_description;
        
    pck_builder.actual_value = var->value;
    return pck_builder.actual_value;        
}













