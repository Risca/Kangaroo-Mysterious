/** ============================================================================
 *  @file   filters.c
 *
 *  @path   $(DSPLINK)/dsp/src/samples/kamy/
 *
 *  @desc   Implementation file for filter definitions.
 *  ============================================================================
 */

#include <conv.h>
#include <filters.h>

/** ============================================================================
 *  @name   filterId
 *
 *  @desc   What filter to use
 *  ============================================================================
 */
Uint8 filterId ;

/** ============================================================================
 *  @const  NUM_FILTERS
 *
 *  @desc   Number of filters configured in the system.
 *  ============================================================================
 */
#define NUM_FILTERS         3

/** ============================================================================
 *  @name   KM_Filters
 *
 *  @desc   Array of KM_Filter function (pointers)
 *  ============================================================================
 */
KM_Filter KM_Filters [NUM_FILTERS] = {
    {   /* Bypass filter */
        {
            NULL, 0, 0, NULL, /* Image attributes */
            0,                /* Kernel size      */
            0,                /* Offset           */
            0,                /* Spacing          */
            0                 /* Orientation      */
        },
        &bypass_func          /* Filter function  */
    },
    {   /* Daniels 1D fast convolution blur */
        {
            NULL, 0, 0, NULL, /* Image attributes */
            5,                /* Kernel size      */
            0,                /* Offset           */
            2,                /* Spacing          */
            0                 /* Orientation      */
        },
        &convBox1D            /* Filter function  */
    },
    {   /* B/W filter */
        {
            NULL, 0, 0, NULL, /* Image attributes */
            0,                /* Kernel size      */
            0,                /* Offset           */
            0,                /* Spacing          */
            0                 /* Orientation      */
        },
        &BWFilter_func        /* Filter function  */
    }


};

