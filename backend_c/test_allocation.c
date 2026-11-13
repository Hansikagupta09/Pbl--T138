
#include <stdio.h>
#include "allocation.h"

int main()
{
    NGO ngos[3];

    printf("\n===== FAIR ALLOCATION TESTING =====\n");

    /* TEST 1: Normal proportional allocation */
    printf("\nTEST 1: Normal proportional allocation\n");

    ngos[0] = (NGO){1, "NGO_A", "Rice", 60, 100};
    ngos[1] = (NGO){2, "NGO_B", "Rice", 40, 100};

    fairAllocation(50, ngos, 2);

    /* TEST 2: Food quantity satisfies all requirements */
    printf("\nTEST 2: Sufficient food quantity\n");

    ngos[0] = (NGO){1, "NGO_A", "Rice", 30, 100};
    ngos[1] = (NGO){2, "NGO_B", "Rice", 20, 100};

    fairAllocation(100, ngos, 2);

    /* TEST 3: Capacity restriction */
    printf("\nTEST 3: NGO capacity restriction\n");

    ngos[0] = (NGO){1, "NGO_A", "Rice", 60, 10};
    ngos[1] = (NGO){2, "NGO_B", "Rice", 40, 50};

    fairAllocation(100, ngos, 2);

    /* TEST 4: No NGO requirements */
    printf("\nTEST 4: Zero total requirements\n");

    ngos[0] = (NGO){1, "NGO_A", "Rice", 0, 100};
    ngos[1] = (NGO){2, "NGO_B", "Rice", 0, 100};

    fairAllocation(50, ngos, 2);

    /* TEST 5: Zero available food */
    printf("\nTEST 5: Zero available food\n");

    ngos[0] = (NGO){1, "NGO_A", "Rice", 60, 100};
    ngos[1] = (NGO){2, "NGO_B", "Rice", 40, 100};

    fairAllocation(0, ngos, 2);

    /* TEST 6: One NGO */
    printf("\nTEST 6: Single NGO allocation\n");

    ngos[0] = (NGO){1, "NGO_A", "Rice", 30, 100};

    fairAllocation(20, ngos, 1);

    printf("\n===== ALLOCATION TESTING COMPLETED =====\n");

    return 0;
}
