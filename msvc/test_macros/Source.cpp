#include "geco-ds-config.h"
#include <windows.h>
struct spin_vals_t
{
    enum : size_t { __low_max = 30, __high_max = 1000 };
    // Low if we suspect uniprocessor, high for multiprocessor.
    static unsigned __max;
    static unsigned __last;
};
unsigned spin_vals_t::__max = spin_vals_t::__low_max;
unsigned spin_vals_t::__last = 0;
int main(int argc, char** argv)
{
    spin_vals_t::__max;
    return 0;
}