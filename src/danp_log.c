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

int32_t danp_transaction(
    uint16_t dest_id,
    uint16_t dest_port,
    uint8_t *data,
    size_t data_len,
    uint8_t *resp_buffer,
    size_t resp_buffer_size,
    uint32_t timeout)
{
    int32_t ret = 0;
    danp_socket_t *sock = NULL;
    bool is_sock_created = false;
    int32_t recv_len = 0;
    int32_t sent_len = 0;

    for (;;)
    {
        sock = danp_socket(DANP_TYPE_STREAM);
        if (!sock)
        {
            ret = -1; // Socket creation failed
            LOG_ERR("Failed to create socket");
            break;
        }
        is_sock_created = true;

        ret = danp_connect(sock, dest_id, dest_port);
        if (ret != 0)
        {
            ret = -2; // Connection failed
            LOG_ERR("Failed to connect to %u:%u", dest_id, dest_port);
            break;
        }

        sent_len = danp_send(sock, data, data_len);
        if (sent_len < 0)
        {
            ret = -3; // Send failed
            LOG_ERR("Failed to send data");
            break;
        }

        if (resp_buffer == NULL || resp_buffer_size == 0)
        {
            // No response expected
            ret = 0;
            LOG_DBG("No response expected, transaction complete");
            break;
        }

        recv_len = danp_recv(sock, resp_buffer, resp_buffer_size, timeout);
        if (recv_len < 0)
        {
            ret = -4; // Receive failed
            LOG_ERR("Failed to receive data");
            break;
        }

        ret = (size_t)recv_len; // Actual bytes received

        LOG_DBG("Transaction completed successfully, received %d bytes", recv_len);

        break;
    }

    if (is_sock_created && sock)
    {
        danp_close(sock);
    }

    return ret;
}