/* danp_init.h - one line definition */

/* All Rights Reserved */

#ifndef INC_DANP_INIT_H
#define INC_DANP_INIT_H

/* Includes */

#include "danp/danp.h"

#ifdef __cplusplus
extern "C"
{
#endif


/* Configurations */


/* Definitions */


/* Types */


/* External Declarations */

extern void danp_log_message_impl(
    danp_log_level_t level,
    const char *funcName,
    const char *message,
    va_list args);

#ifdef __cplusplus
}
#endif

#endif /* INC_DANP_INIT_H */