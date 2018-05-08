#ifndef _FPU_TYPES_H_
#define _FPU_TYPES_H_

//#############################################################################
//! \file   include/fpu_types.h
//!
//! \brief  Prototypes and Definitions for the C28x FPU Library
//! \author Vishal Coelho
//! \date   n/a
//
//  Group: 			C2000
//  Target Family:	F2837x
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.50.00.00 $
// $Release Date: May 22, 2017 $
// $Copyright: Copyright (C) 2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>
#include "float.h"

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// typedefs
//*****************************************************************************

#ifndef FPU_TYPES
#define FPU_TYPES
// Complex Float Data Type
typedef struct {
    float dat[2];
} complex_float;
#endif //FPU_TYPES

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_TYPES_H_

// End of File
