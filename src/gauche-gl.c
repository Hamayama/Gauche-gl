/*
 * gauche-gl.c - Gauche GL binding
 *
 *  Copyright(C) 2001 by Shiro Kawai (shiro@acm.org)
 *
 *  Permission to use, copy, modify, distribute this software and
 *  accompanying documentation for any purpose is hereby granted,
 *  provided that existing copyright notices are retained in all
 *  copies and that this notice is included verbatim in all
 *  distributions.
 *  This software is provided as is, without express or implied
 *  warranty.  In no circumstances the author(s) shall be liable
 *  for any damages arising out of the use of this software.
 *
 *  $Id: gauche-gl.c,v 1.5 2001-10-02 09:07:54 shirok Exp $
 */

#include <gauche.h>
#include "gauche-gl.h"

/* Utility functions */

/* List of numbers -> array of doubles.  Returns # of elements. */
int Scm_GLGetDoubles(ScmObj val1, ScmObj list, double *result,
                     int maxresult, int minresult)
{
    int i = 0;
    ScmObj lp;

    if (!SCM_UNBOUNDP(val1)) {
        if (!SCM_NUMBERP(val1)) {
            Scm_Error("number required, but got %S", val1);
        }
        result[0] = Scm_GetDouble(val1);
        i++;
    }
    
    SCM_FOR_EACH(lp, list) {
        if (i >= maxresult) {
            Scm_Error("too many arguments: %S, at most %d allowed",
                      list, maxresult);
        }
        if (!SCM_NUMBERP(SCM_CAR(lp))) {
            Scm_Error("number required, but got %S", SCM_CAR(lp));
        }
        result[i] = Scm_GetDouble(SCM_CAR(lp));
        i++;
    }
    if (i < minresult) {
        Scm_Error("too few argument: %S, at least %d required",
                  list, minresult);
    }
    return i;
}

/* returns # of values returned by glGetTYPEv call for given state.
   -1 if the state can't be queried by glGetTYPEv. */
#if 0 /* not finished */
int Scm_GLStateInfoSize(GLenum state)
{
   switch(state) {
     case GL_CURRENT_COLOR:;
     case GL_CURRENT_TEXTURE_COORDS:;
     case GL_CURRENT_RASTER_POSITION:;
     case GL_CURRENT_RASTER_COLOR:;
     case GL_CURRENT_RASTER_TEXTURE_COORDS:;
     case GL_FOG_COLOR:;
     case GL_LIGHT_MODEL_AMBIENT:;
     case GL_COLOR_CLEAR_VALUE:;
     case GL_MAP2_GRID_DOMAIN: return 4;

     case GL_CURRENT_NORMAL: return 3;

     case GL_DEPTH_RANGE:;
     case GL_MAP1_GRID_DOMAIN:;
   case GL_MAP2_GRID_SEGMENTS: return 2;
   }
}
#endif

/* Initialization */
extern void Scm_Init_gl_lib(ScmModule *mod);
extern void Scm_Init_glu_lib(ScmModule *mod);

void Scm_Init_gauche_gl(void)
{
    ScmModule *mod = SCM_MODULE(SCM_FIND_MODULE("gl", TRUE));
    Scm_Init_gl_lib(mod);
    Scm_Init_glu_lib(mod);

    /* Constants that may not defined in some platforms */
#define DEF(name)  SCM_DEFINE(mod, #name, Scm_MakeInteger(name))

#ifdef GL_TEXTURE_BINDING_3D
    DEF(GL_TEXTIRE_BINDING_3D);
#endif
#ifdef GL_TEXTURE_3D_BINDING_EXT
    DEF(GL_TEXTIRE_3D_BINDING_EXT);
#endif
#ifdef GL_COLOR_TABLE_FORMAT
    DEF(GL_COLOR_TABLE_FORMAT);
#endif
#ifdef GL_COLOR_TABLE_FORMAT_EXT
    DEF(GL_COLOR_TABLE_FORMAT_EXT);
#endif
#ifdef GL_COLOR_TABLE_FORMAT_SGI
    DEF(GL_COLOR_TABLE_FORMAT_SGI);
#endif
#ifdef GL_COLOR_TABLE_WIDTH
    DEF(GL_COLOR_TABLE_WIDTH);
#endif
#ifdef GL_COLOR_TABLE_WIDTH_EXT
    DEF(GL_COLOR_TABLE_WIDTH_EXT);
#endif
#ifdef GL_COLOR_TABLE_WIDTH_SGI
    DEF(GL_COLOR_TABLE_WIDTH_SGI);
#endif
#ifdef GL_COLOR_TABLE_RED_SIZE
    DEF(GL_COLOR_TABLE_RED_SIZE);
#endif
#ifdef GL_COLOR_TABLE_RED_SIZE_EXT
    DEF(GL_COLOR_TABLE_RED_SIZE_EXT);
#endif
#ifdef GL_COLOR_TABLE_RED_SIZE_SGI
    DEF(GL_COLOR_TABLE_RED_SIZE_SGI);
#endif
#ifdef GL_COLOR_TABLE_GREEN_SIZE
    DEF(GL_COLOR_TABLE_GREEN_SIZE);
#endif
#ifdef GL_COLOR_TABLE_GREEN_SIZE_EXT
    DEF(GL_COLOR_TABLE_GREEN_SIZE_EXT);
#endif
#ifdef GL_COLOR_TABLE_GREEN_SIZE_SGI
    DEF(GL_COLOR_TABLE_GREEN_SIZE_SGI);
#endif
#ifdef GL_COLOR_TABLE_BLUE_SIZE
    DEF(GL_COLOR_TABLE_BLUE_SIZE);
#endif
#ifdef GL_COLOR_TABLE_BLUE_SIZE_EXT
    DEF(GL_COLOR_TABLE_BLUE_SIZE_EXT);
#endif
#ifdef GL_COLOR_TABLE_BLUE_SIZE_SGI
    DEF(GL_COLOR_TABLE_BLUE_SIZE_SGI);
#endif
#ifdef GL_COLOR_TABLE_ALPHA_SIZE
    DEF(GL_COLOR_TABLE_ALPHA_SIZE);
#endif
#ifdef GL_COLOR_TABLE_ALPHA_SIZE_EXT
    DEF(GL_COLOR_TABLE_ALPHA_SIZE_EXT);
#endif
#ifdef GL_COLOR_TABLE_ALPHA_SIZE_SGI
    DEF(GL_COLOR_TABLE_ALPHA_SIZE_SGI);
#endif
#ifdef GL_COLOR_TABLE_LUMINANCE_SIZE
    DEF(GL_COLOR_TABLE_LUMINANCE_SIZE);
#endif
#ifdef GL_COLOR_TABLE_LUMINANCE_SIZE_EXT
    DEF(GL_COLOR_TABLE_LUMINANCE_SIZE_EXT);
#endif
#ifdef GL_COLOR_TABLE_LUMINANCE_SIZE_SGI
    DEF(GL_COLOR_TABLE_LUMINANCE_SIZE_SGI);
#endif
#ifdef GL_COLOR_TABLE_INTENSITY_SIZE
    DEF(GL_COLOR_TABLE_INTENSITY_SIZE);
#endif
#ifdef GL_COLOR_TABLE_INTENSITY_SIZE_EXT
    DEF(GL_COLOR_TABLE_INTENSITY_SIZE_EXT);
#endif
#ifdef GL_COLOR_TABLE_INTENSITY_SIZE_SGI
    DEF(GL_COLOR_TABLE_INTENSITY_SIZE_SGI);
#endif

#ifdef GL_TEXTURE_INDEX_SIZE_EXT
    DEF(GL_TEXTURE_INDEX_SIZE_EXT);
#endif

#ifdef GL_COLOR_INDEX1_EXT
    DEF(GL_COLOR_INDEX1_EXT);
#endif
#ifdef GL_COLOR_INDEX2_EXT
    DEF(GL_COLOR_INDEX2_EXT);
#endif
#ifdef GL_COLOR_INDEX4_EXT
    DEF(GL_COLOR_INDEX4_EXT);
#endif
#ifdef GL_COLOR_INDEX8_EXT
    DEF(GL_COLOR_INDEX8_EXT);
#endif
#ifdef GL_COLOR_INDEX12_EXT
    DEF(GL_COLOR_INDEX12_EXT);
#endif
#ifdef GL_COLOR_INDEX16_EXT
    DEF(GL_COLOR_INDEX16_EXT);
#endif

#ifdef GL_SHARED_TEXTURE_PALETTE_EXT
    DEF(GL_SHARED_TEXTURE_PALETTE_EXT);
#endif

#ifdef GL_POINT_SIZE_MIN_EXT
    DEF(GL_POINT_SIZE_MIN_EXT);
#endif
#ifdef GL_POINT_SIZE_MIN_SGI
    DEF(GL_POINT_SIZE_MIN_SGI);
#endif
#ifdef GL_POINT_SIZE_MAX_EXT
    DEF(GL_POINT_SIZE_MAX_EXT);
#endif
#ifdef GL_POINT_SIZE_MAX_SGI
    DEF(GL_POINT_SIZE_MAX_SGI);
#endif
#ifdef GL_POINT_FADE_THRESHOLD_SIZE_EXT
    DEF(GL_POINT_FADE_THRESHOLD_SIZE_EXT);
#endif
#ifdef GL_POINT_FADE_THRESHOLD_SIZE_SGI
    DEF(GL_POINT_FADE_THRESHOLD_SIZE_SGI);
#endif
#ifdef GL_DISTANCE_ATTENUATION_EXT
    DEF(GL_DISTANCE_ATTENUATION_EXT);
#endif
#ifdef GL_DISTANCE_ATTENUATION_SGI
    DEF(GL_DISTANCE_ATTENUATION_SGI);
#endif

#ifdef GL_SELECTED_TEXTURE_SGIS
    DEF(GL_SELECTED_TEXTURE_SGIS);
#endif
#ifdef GL_SELECTED_TEXTURE_COORD_SET_SGIS
    DEF(GL_SELECTED_TEXTURE_COORD_SET_SGIS);
#endif
#ifdef GL_SELECTED_TEXTURE_EXT
    DEF(GL_SELECTED_TEXTURE_EXT);
#endif
#ifdef GL_SELECTED_TEXTURE_COORD_SET_EXT
    DEF(GL_SELECTED_TEXTURE_COORD_SET_EXT);
#endif
#ifdef GL_SELECTED_TEXTURE_TRANSFORM_EXT
    DEF(GL_SELECTED_TEXTURE_TRANSFORM_EXT);
#endif

#ifdef GL_TEXTURE0_SGIS
    DEF(GL_TEXTURE0_SGIS);
#endif
#ifdef GL_TEXTURE0_EXT
    DEF(GL_TEXTURE0_EXT);
#endif
#ifdef GL_TEXTURE1_SGIS
    DEF(GL_TEXTURE1_SGIS);
#endif
#ifdef GL_TEXTURE1_EXT
    DEF(GL_TEXTURE1_EXT);
#endif
#ifdef GL_TEXTUER2_SGIS
    DEF(GL_TEXTUER2_SGIS);
#endif
#ifdef GL_TEXTURE2_EXT
    DEF(GL_TEXTURE2_EXT);
#endif
#ifdef GL_TEXTURE3_SGIS
    DEF(GL_TEXTURE3_SGIS);
#endif
#ifdef GL_TEXTURE3_EXT
    DEF(GL_TEXTURE3_EXT);
#endif
#ifdef GL_TEXTURE_COORD_SET_SOURCE_SGIS
    DEF(GL_TEXTURE_COORD_SET_SOURCE_SGIS);
#endif
#ifdef GL_TEXTURE_COORD_SET_SOURCE_EXT
    DEF(GL_TEXTURE_COORD_SET_SOURCE_EXT);
#endif

#ifdef GL_MAX_TEXTURES_SGIS
    DEF(GL_MAX_TEXTURES_SGIS);
#endif
#ifdef GL_MAX_TEXTURES_EXT
    DEF(GL_MAX_TEXTURES_EXT);
#endif
#ifdef GL_MAX_TEXTURE_COORD_SETS_EXT
    DEF(GL_MAX_TEXTURE_COORD_SETS_EXT);
#endif
#ifdef GL_TEXTURE_ENV_COORD_SET_EXT
    DEF(GL_TEXTURE_ENV_COORD_SET_EXT);
#endif
}
