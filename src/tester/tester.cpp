#include <iostream>
#include <dlfcn.h>
#include <assert.h>

#define LIBNAME "/home/igor/Study/IVS/proj2/src/mathlib.so"

using namespace std;

typedef double (*MathFunc_1)(double);
typedef double (*MathFunc_2)(double, double);

class MathLib
{
private:
    void *handle = NULL;

public:
    MathFunc_2 addition;
    MathFunc_2 subtraction;
    MathFunc_2 multiplication;
    MathFunc_2 division;
    MathFunc_1 factorial;
    MathFunc_2 eponentiation;
    MathFunc_2 nthroot;

    MathLib(const char *libname)
    {
        this->handle = dlopen(libname, RTLD_LAZY);
        cout << libname << endl;
        if (this->handle == NULL)
            throw std::invalid_argument("Library doesn't exist.");
        addition = (MathFunc_2)dlsym(handle, "addition");
        subtraction = (MathFunc_2)dlsym(handle, "subtraction");
        multiplication = (MathFunc_2)dlsym(handle, "multiplication");
        division = (MathFunc_2)dlsym(handle, "division");
        factorial = (MathFunc_1)dlsym(handle, "factorial");
        eponentiation = (MathFunc_2)dlsym(handle, "eponentiation");
        nthroot = (MathFunc_2)dlsym(handle, "nthroot");
    }

    ~MathLib()
    {
        if (this->handle != NULL)
            dlclose(this->handle);
    }
};

int main()
{
    MathLib *lib = NULL;
    try
    {
        lib = new MathLib(LIBNAME);
        assert(lib->addition(0, 0) == 0);
        assert(lib->addition(2, 3) == 5);
        assert(lib->addition(20.33, 0.66) == 20.99);
        assert(lib->addition(-68, -14) == -82);

        assert(lib->subtraction(5, 2) == 3);
        assert(lib->subtraction(-68, -14) == -54);
        assert(lib->subtraction(12.67, 335.26) == -322.59);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << endl;
    }
    if (lib != NULL)
        delete lib;
    return 0;
}