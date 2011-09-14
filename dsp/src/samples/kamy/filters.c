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
#define NUM_FILTERS         6

/** ============================================================================
 *  @name   KM_Filters
 *
 *  @desc   Array of KM_Filter function (pointers)
 *  ============================================================================
 */
KM_Filter KM_Filters [NUM_FILTERS] = {
    {   /* Bypass filter */
        {
            NULL, NULL, 0, 0, /* Image attributes */
            0,                /* Kernel size      */
            0,                /* Offset           */
            0,                /* Spacing          */
            0                 /* Orientation      */
        },
        &bypass_func          /* Filter function  */
    },
    {   /* Daniel's 1D fast vertical blur */
        {
            NULL, NULL, 0, 0, /* Image attributes */
            5,                /* Kernel size      */
            0,                /* Offset           */
            2,                /* Spacing          */
            0                 /* Orientation      */
        },
        &convBox1D            /* Filter function  */
    },
    {   /* Daniel's 1D fast horizontal blur */
        {
            NULL, NULL, 0, 0, /* Image attributes */
            5,                /* Kernel size      */
            0,                /* Offset           */
            2,                /* Spacing          */
            1                 /* Orientation      */
        },
        &convBox1D            /* Filter function  */
    },
    {   /* Daniel's 2D fast blur */
        {
            NULL, NULL, 0, 0, /* Image attributes */
            3,                /* Kernel size      */
            0,                /* Offset           */
            2,                /* Spacing          */
            0                 /* Orientation      */
        },
        &convBox2D            /* Filter function  */
    },
    {   /* B/W filter */
        {
            NULL, NULL, 0, 0, /* Image attributes */
            0,                /* Kernel size      */
            0,                /* Offset           */
            0,                /* Spacing          */
            0                 /* Orientation      */
        },
        &BWFilter_func        /* Filter function  */
    },
    {   /* Legacy blur filter */
        {
            NULL, NULL, 0, 0, /* Image attributes */
            5,                /* Kernel size      */
            0,                /* Offset           */
            0,                /* Spacing          */
            0                 /* Orientation      */
        },
        &convimg_func         /* Filter function  */
    }
};

