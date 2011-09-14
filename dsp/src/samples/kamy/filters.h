/** ============================================================================
 *  @file   filters.h
 *
 *  @path   $(DSPLINK)/dsp/src/samples/kamy/
 *
 *  @desc   Header file for filter definitions.
 *  ============================================================================
 */

#ifndef FILTERS_H
#define FILTERS_H

/*  ----------------------------------- DSP/BIOS Headers            */
#include <std.h>

/*  ----------------------------------- Application Headers         */
#include <conv.h>

#ifdef __cplusplus
extern "C" {
#endif

/** ============================================================================
 *  @name   filterId
 *
 *  @desc   What filter to use
 *  ============================================================================
 */
extern Uint8 filterId ;

/** ============================================================================
 *  @name   FilterAttrs
 *
 *  @desc   Structure used to pass filter attributes to filter functions
 *
 *  @field  imgIn
 *              Pointer to incoming image
 *  @field  imgOut
 *              Pointer to outgoing image
 *  @field  width
 *              Width of image
 *  @field  height
 *              Height of image
 *  @field  kernelSize
 *              Size of filter kernel
 *  @field  offset
 *              Offset to first byte to work with in image
 *  @field  spacing
 *              Length between bytes to work with
 *  @field  orientation
 *              0 == horizontal, 1 == vertical
 *  ============================================================================
 */
typedef struct FilterAttrs_tag {
    Uint8 *  imgIn       ;
    Uint8 *  imgOut      ;
    Uint16   width       ;
    Uint16   height      ;
    Uint16   kernelSize  ;
    Uint16   offset      ;
    Uint16   spacing     ;
    Uint16   orientation ;
} FilterAttrs;

/** ============================================================================
 *  @name   KM_Filter_func
 *
 *  @desc   Function prototype for filter functions
 */
typedef int (*KM_Filter_func)(FilterAttrs * attrs) ;

/** ============================================================================
 *  @name   KM_Filter
 *
 *  @desc   Structure for filter
 *  ============================================================================
 */
typedef struct KM_Filter_tag {
    FilterAttrs     attrs       ;
    KM_Filter_func func        ;
} KM_Filter;

/** ============================================================================
 *  @name   KM_Filters
 *
 *  @desc   Array of KM_Filter function (pointers)
 *  ============================================================================
 */
extern KM_Filter KM_Filters [] ;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* FILTERS_H */
