#include <stdbool.h>

extern void printSymTab();
extern void storeVar(char *name, bool v);
extern bool doOR(bool v1, bool v2);
extern bool doAND(bool v1, bool v2);
extern bool doNOT(bool v1);
extern bool getVal(char *name);
