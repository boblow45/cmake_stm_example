#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av)
{
    CommandLineTestRunner::RunAllTests(ac, av);
    return 0;
}
