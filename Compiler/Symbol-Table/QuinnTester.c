#include <stdio.h>
#include <string.h>

#include "SymTab.h"
#include "assert.h" /* WHAT IS THIS??? */

void testStartIterator(SymTab *table, int expected_value)
{
    int rv = startIterator(table);
    assert(rv == expected_value);
}

void testNextEntry(SymTab *table, int expected_value)
{
    int rv = nextEntry(table);
    assert(rv == expected_value);
}

// Checks to see if the pointer points to the same place.
void testGetCurrentAttr(SymTab *table, void *expected_outcome)
{
    void *current_attribute = getCurrentAttr(table);
    assert(current_attribute == expected_outcome);
}

void testGetCurrentName(SymTab *table, char *expected_outcome)
{
    char *current_name = getCurrentName(table);
    assert(strcmp(expected_outcome, current_name) == 0);
}

void testHasCurrent(SymTab *table, int expected_outcome)
{
    int rv = hasCurrent(table);
    assert(rv == expected_outcome);
}

void testFindName(SymTab *table, char *name, int expected_outcome)
{
    int rv = findName(table, name);
    assert(rv == expected_outcome);
}

void testEnterName(SymTab *table, char *name, int expected_outcome)
{
    int rv = enterName(table, name);
    assert(rv == expected_outcome);
}

int main(void)
{
    SymTab *table = createSymTab(10);

    testEnterName(table, "Quinn", 1);
    testEnterName(table, "Jill", 1);
    testEnterName(table, "Stephanie", 1);

    testHasCurrent(table, 0);

    testEnterName(table, "Quinn", 0);

    testHasCurrent(table, 1);

    testFindName(table, "Quinn", 1);
    testFindName(table, "Steph", 0);

    testHasCurrent(table, 1);

    testEnterName(table, "Shannon", 1);
    testEnterName(table, "Phoebe", 1);
    testEnterName(table, "Will", 1);
    testEnterName(table, "will", 1);

    testFindName(table, "Jill", 1);
    testFindName(table, "Quinn", 1);
    testFindName(table, "Will", 1);
    testFindName(table, "Phoebe", 1);

    testEnterName(table, "Micah", 1);

    destroySymTab(table);

    return 0;
}