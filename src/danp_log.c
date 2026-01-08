/* danp_log.c - one line definition */

/* All Rights Reserved */

/* Includes */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>

#include "danp/danp.h"
#include "danp/danp_buffer.h"
#include "danp/danp_log.h"

/* Imports */


/* Definitions */

LOG_MODULE_REGISTER(danp, CONFIG_DANP_LOG_LEVEL);

/* Types */


/* Forward Declarations */


/* Variables */


/* Functions */

void danp_log_message_impl(
    danp_log_level_t level,
    const char *funcName,
    const char *message,
    va_list args)
{
    char log_buf[256];
    vsnprintf(log_buf, sizeof(log_buf), message, args);

    switch (level)
    {
    case DANP_LOG_ERROR:
        LOG_ERR("%s", log_buf);
        break;
    case DANP_LOG_WARN:
        LOG_WRN("%s", log_buf);
        break;
    case DANP_LOG_INFO:
        LOG_INF("%s", log_buf);
        break;
    case DANP_LOG_DEBUG:
    case DANP_LOG_VERBOSE:
    default:
        LOG_DBG("%s", log_buf);
        break;
    }
}