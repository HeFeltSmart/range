/* tests/test_range.c */
#include "common/range.h"
#include <stdio.h>

/* 1. Instantiate the multi-dimensional tracking boundary layers */
/* Combines signed Int16 ranges for orientation and an unsigned UInt32 range for distance */
DEFINE_CUBE_3D(Int16Range, Int16Range, UInt32Range, RadarWindow)

/* 2. Define a clean coordinate value structure to pass as a single unit */
typedef struct
{
    int16_t  azimuth;
    int16_t  elevation;
    uint32_t distance;
} RadarPoint3D;

/* 3. High-efficiency function contract: Reduced from 9 arguments down to 2 pointers! */
bool is_target_in_window(const RadarWindowCube3D *window, const RadarPoint3D *target)
{
    return IN_CUBE_3D(target->azimuth, target->elevation, target->distance, *window);
}

int main(void)
{
    /* Set up our dynamic radar boundary tracking matrix (RAM Configuration) */
    RadarWindowCube3D operational_window =
    {
        .x = { .minimum = -180, .maximum = 180 }, /* Azimuth limits */
        .y = { .minimum = -90,  .maximum = 90  }, /* Elevation limits */
        .z = { .minimum = 1,    .maximum = 256 }  /* Dynamic Distance/Relay Zone limit */
    };

    /* Define a target track coordinate to evaluate */
    RadarPoint3D active_target =
    {
        .azimuth   = 45,
        .elevation = -10,
        .distance  = 150
    };

    /* Execute the streamlined spatial evaluation macro check */
    if (is_target_in_window(&operational_window, &active_target))
    {
        printf("Success: Target coordinates are within active tracking boundaries.\n");
    }
    else
    {
        printf("Warning: Target coordinates breached operational boundaries!\n");
    }

    return 0;
}
