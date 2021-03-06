#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <boolean.h>

#include "rsx.h"
#include "rsx_intf.h"
#include "../libretro_cbs.h"

bool rsx_soft_open(bool is_pal)
{
   content_is_pal = is_pal;
   return true;
}

void rsx_soft_get_system_av_info(struct retro_system_av_info *info)
{
   memset(info, 0, sizeof(*info));
   info->timing.fps            = content_is_pal ? FPS_PAL : FPS_NTSC;
   info->timing.sample_rate    = SOUND_FREQUENCY;
   info->geometry.base_width   = MEDNAFEN_CORE_GEOMETRY_BASE_W;
   info->geometry.base_height  = MEDNAFEN_CORE_GEOMETRY_BASE_H;
   info->geometry.max_width    = MEDNAFEN_CORE_GEOMETRY_MAX_W  << psx_gpu_upscale_shift;
   info->geometry.max_height   = MEDNAFEN_CORE_GEOMETRY_MAX_H  << psx_gpu_upscale_shift;
   info->geometry.aspect_ratio = !widescreen_hack ? MEDNAFEN_CORE_GEOMETRY_ASPECT_RATIO : 16.0 / 9.0;
}

void rsx_soft_set_environment(retro_environment_t callback)
{
}

void rsx_soft_set_video_refresh(retro_video_refresh_t callback)
{
}

void rsx_soft_finalize_frame(const void *fb, unsigned width,
                             unsigned height, unsigned pitch)
{
   video_cb(fb, width, height, pitch);
}
