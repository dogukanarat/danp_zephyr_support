/* danp_utilities.c - one line definition */

/* All Rights Reserved */

/* Includes */

#include <errno.h>

#include <zephyr/logging/log.h>

#include "danp/danp_utilities.h"
#include "danp/danp.h"

/* Imports */


/* Definitions */

LOG_MODULE_DECLARE(danp);

/* Types */


/* Forward Declarations */


/* Variables */


/* Functions */

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

