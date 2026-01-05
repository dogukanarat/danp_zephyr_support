/* danp_zephyr_support.c - Core implementation of danp_zephyr_support library */

/* All Rights Reserved */

/* Includes */

#include "danp_zephyr_support/danp_zephyr_support.h"
#include <stdio.h>
#include <string.h>

/* Imports */


/* Definitions */

#define VERSION_STRING "1.0.0"
#define MAX_FACTORIAL_INPUT 12

/* Types */


/* Forward Declarations */


/* Variables */


/* Functions */

const char *danp_zephyr_support_get_version(void)
{
    return VERSION_STRING;
}

int32_t danp_zephyr_support_add(int32_t a, int32_t b)
{
    return a + b;
}

danp_zephyr_support_status_t danp_zephyr_support_multiply(
    int32_t a,
    int32_t b,
    int32_t *result)
{
    /* Validate input parameter */
    if (result == NULL)
    {
        return DANP_ZEPHYR_SUPPORT_ERROR_NULL;
    }

    /* Perform multiplication */
    *result = a * b;

    return DANP_ZEPHYR_SUPPORT_SUCCESS;
}

danp_zephyr_support_status_t danp_zephyr_support_foo(
    const char *input,
    char *output,
    size_t outputSize)
{
    /* Validate input parameters */
    if (input == NULL || output == NULL)
    {
        return DANP_ZEPHYR_SUPPORT_ERROR_NULL;
    }

    if (outputSize == 0)
    {
        return DANP_ZEPHYR_SUPPORT_ERROR_INVALID;
    }

    /* Get input length */
    size_t inputLen = strlen(input);

    /* Check if output buffer is large enough */
    if (inputLen + 10 >= outputSize)
    {
        return DANP_ZEPHYR_SUPPORT_ERROR_INVALID;
    }

    /* Process the string by adding a prefix */
    snprintf(output, outputSize, "Processed: %s", input);

    return DANP_ZEPHYR_SUPPORT_SUCCESS;
}

bool danp_zephyr_support_bar(int32_t value)
{
    /* Example validation: value must be in range [0, 100] */
    return (value >= 0 && value <= 100);
}

danp_zephyr_support_result_t danp_zephyr_support_factorial(int32_t n)
{
    danp_zephyr_support_result_t result;

    /* Validate input */
    if (n < 0)
    {
        result.value = 0;
        result.status = DANP_ZEPHYR_SUPPORT_ERROR_INVALID;
        return result;
    }

    /* Check for overflow protection */
    if (n > MAX_FACTORIAL_INPUT)
    {
        result.value = 0;
        result.status = DANP_ZEPHYR_SUPPORT_ERROR_INVALID;
        return result;
    }

    /* Calculate factorial */
    int32_t factorial = 1;
    for (int32_t i = 2; i <= n; i++)
    {
        factorial *= i;
    }

    result.value = factorial;
    result.status = DANP_ZEPHYR_SUPPORT_SUCCESS;

    return result;
}
