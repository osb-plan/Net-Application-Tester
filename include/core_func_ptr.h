/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   core_func_ptr.h
 * Author: utente
 *
 * Created on December 9, 2018, 6:19 PM
 */

#ifndef CORE_FUNC_PTR_H
#define CORE_FUNC_PTR_H

#ifdef __cplusplus
extern "C" {
#endif

    float _swap_func(FIELD *f, uint32_t idx);
    float _binary_func(FIELD *f, uint32_t idx);
    float _fixed_func(FIELD *f, uint32_t idx);

#ifdef __cplusplus
}
#endif

#endif /* CORE_FUNC_PTR_H */

