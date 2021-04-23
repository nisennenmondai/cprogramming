#include "log.h"

int main(void)
{

        int i;

        INFO("LOG INFO\n");
        for (i = 0; i < 5; i++)
                INFO("var: %d\n", i);

        WARN("LOG WARN\n");
        for (i = 0; i < 5; i++)
                WARN("var: %d\n", i);

        TRACE("LOG TRACE\n");
        for (i = 0; i < 5; i++)
                TRACE("var: %d\n", i);

        DEBUG("LOG DEBUG\n");
        for (i = 0; i < 5; i++)
                DEBUG("var: %d\n", i);

        ERROR("LOG ERROR\n");
        for (i = 0; i < 5; i++)
                ERROR("var: %d\n", i);

        FATAL("LOG FATAL\n");
        for (i = 0; i < 5; i++)
                FATAL("var: %d\n", i);
        TESTS("LOG TESTS\n");
        for (i = 0; i < 5; i++)
                TESTS("var: %d\n", i);

        return 0;
}
