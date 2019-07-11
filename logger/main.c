#include "log.h"

int main(void)
{
    int i;

    INFO("LOG INFO");
    for (i = 0; i < 5; i++)
        INFO("var: %d", i);

    WARN("LOG WARN");
    for (i = 0; i < 5; i++)
        WARN("var: %d", i);

    TRACE("LOG TRACE");
    for (i = 0; i < 5; i++)
        TRACE("var: %d", i);

    DEBUG("LOG DEBUG");
    for (i = 0; i < 5; i++)
        DEBUG("var: %d", i);

    ERROR("LOG ERROR");
    for (i = 0; i < 5; i++)
        ERROR("var: %d", i);

    FATAL("LOG FATAL");
    for (i = 0; i < 5; i++)
        FATAL("var: %d", i);

    return 0;
}
