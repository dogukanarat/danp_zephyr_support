/* danp_log.c - one line definition */

/* All Rights Reserved */

/* Includes */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_instance.h>
#include <zephyr/sys/printk.h>

#include "danp/danp.h"
#include "danp/danp_buffer.h"
#include "danp/danp_log.h"

/* Imports */


/* Definitions */

LOG_MODULE_REGISTER(danp, CONFIG_DANP_LOG_LEVEL);

LOG_INSTANCE_REGISTER(danp, io, CONFIG_DANP_LOG_LEVEL);

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
    case DANP_LOG_LEVEL_ERR:
        LOG_ERR("%s", log_buf);
        break;
    case DANP_LOG_LEVEL_WRN:
        LOG_WRN("%s", log_buf);
        break;
    case DANP_LOG_LEVEL_INF:
        LOG_INF("%s", log_buf);
        break;
    case DANP_LOG_LEVEL_DBG:
    case DANP_LOG_LEVEL_VER:
    default:
        LOG_DBG("%s", log_buf);
        break;
    }
}

void danp_log_message_io_impl(
    danp_log_level_t level,
    const char *funcName,
    const char *message,
    va_list args)
{
    char log_buf[256];
    vsnprintf(log_buf, sizeof(log_buf), message, args);

    switch (level)
    {
    case DANP_LOG_LEVEL_ERR:
        LOG_INST_ERR(LOG_INSTANCE_PTR(danp, io), "%s", log_buf);
        break;
    case DANP_LOG_LEVEL_WRN:
        LOG_INST_WRN(LOG_INSTANCE_PTR(danp, io), "%s", log_buf);
        break;
    case DANP_LOG_LEVEL_INF:
        LOG_INST_INF(LOG_INSTANCE_PTR(danp, io), "%s", log_buf);
        break;
    case DANP_LOG_LEVEL_DBG:
    case DANP_LOG_LEVEL_VER:
    default:
        LOG_INST_DBG(LOG_INSTANCE_PTR(danp, io), "%s", log_buf);
        break;
    }
}