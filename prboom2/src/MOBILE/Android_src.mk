
LOCAL_PATH := $(call my-dir)/../


include $(CLEAR_VARS)

LOCAL_MODULE    := dsda

LOCAL_CFLAGS :=  -DGL_DOOM  -DENGINE_NAME=\"dsda\" -fsigned-char  -DHAVE_CONFIG_H -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp -DDSDA_DOOM -DPROJECT_STRING=\"DSDA\" -DPROJECT_TARNAME=\"dsda-doom\" -DPROJECT_NAME=\"DSDA\" -DPROJECT_VERSION=\"dev\"

# Fixes SIGILL ion 32bit, can not debug properly to find the cause so use this hack
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
 LOCAL_CFLAGS += -O1
endif

LOCAL_C_INCLUDES :=     $(SDL_INCLUDE_PATHS)  \
                        $(TOP_DIR) \
                        $(TOP_DIR)/MobileTouchControls \
                        $(TOP_DIR)/Clibs_OpenTouch\libzip \
                        $(TOP_DIR)/Clibs_OpenTouch \
                        $(TOP_DIR)/Clibs_OpenTouch/idtech1 \
                        $(LOCAL_PATH)/MOBILE  \
                        $(TOP_DIR)/gl4es/include \
                        $(TOP_DIR)/AudioLibs_OpenTouch/fluidsynth/include \
                        $(TOP_DIR)/AudioLibs_OpenTouch/liboggvorbis/include \
                        $(TOP_DIR)/AudioLibs_OpenTouch/libsndfile-android/jni/ \
                        $(TOP_DIR)/Doom/dsda-doom/prboom2/src/MOBILE/libtess/



LOCAL_SRC_FILES =   ../../../../Clibs_OpenTouch/idtech1/android_jni.cpp \
                    ../../../../Clibs_OpenTouch/idtech1/touch_interface.cpp \
                    ./MOBILE/game_interface.c \

COMMON_SRC = \
    am_map.c \
    doomdef.c \
    doomstat.c \
    dsda.c \
    dsda/aim.c \
    dsda/ambient.cpp \
    dsda/analysis.c \
    dsda/args.c \
    dsda/brute_force.c \
    dsda/build.c \
    dsda/compatibility.c \
    dsda/configuration.c \
    dsda/console.c \
    dsda/cr_table.c \
    dsda/data_organizer.c \
    dsda/death.c \
    dsda/deh_hash.c \
    dsda/demo.c \
    dsda/destructible.c \
    dsda/endoom.c \
    dsda/episode.c \
    dsda/excmd.c \
    dsda/exdemo.c \
    dsda/exhud.c \
    dsda/features.c \
    dsda/font.c \
    dsda/game_controller.c \
    dsda/ghost.c \
    dsda/gl/render_scale.c \
    dsda/global.c \
    dsda/hud_components/ammo_text.c \
    dsda/hud_components/armor_text.c \
    dsda/hud_components/attempts.c \
    dsda/hud_components/base.c \
    dsda/hud_components/big_ammo.c \
    dsda/hud_components/big_armor.c \
    dsda/hud_components/big_armor_text.c \
    dsda/hud_components/big_artifact.c \
    dsda/hud_components/big_health.c \
    dsda/hud_components/big_health_text.c \
    dsda/hud_components/color_test.c \
    dsda/hud_components/command_display.c \
    dsda/hud_components/composite_time.c \
    dsda/hud_components/coordinate_display.c \
    dsda/hud_components/event_split.c \
    dsda/hud_components/fps.c \
    dsda/hud_components/free_text.c \
    dsda/hud_components/health_text.c \
    dsda/hud_components/keys.c \
    dsda/hud_components/level_splits.c \
    dsda/hud_components/line_display.c \
    dsda/hud_components/line_distance_tracker.c \
    dsda/hud_components/line_tracker.c \
    dsda/hud_components/local_time.c \
    dsda/hud_components/map_coordinates.c \
    dsda/hud_components/map_time.c \
    dsda/hud_components/map_title.c \
    dsda/hud_components/map_totals.c \
    dsda/hud_components/message.c \
    dsda/hud_components/minimap.c \
    dsda/hud_components/mobj_tracker.c \
    dsda/hud_components/null.c \
    dsda/hud_components/player_tracker.c \
    dsda/hud_components/ready_ammo_text.c \
    dsda/hud_components/render_stats.c \
    dsda/hud_components/secret_message.c \
    dsda/hud_components/sector_tracker.c \
    dsda/hud_components/speed_text.c \
    dsda/hud_components/stat_totals.c \
    dsda/hud_components/tracker.c \
    dsda/hud_components/weapon_text.c \
    dsda/id_list.c \
    dsda/input.c \
    dsda/key_frame.c \
    dsda/map_format.c \
    dsda/mapinfo.c \
    dsda/mapinfo/doom.c \
    dsda/mapinfo/doom/parser.cpp \
    dsda/mapinfo/hexen.c \
    dsda/mapinfo/legacy.c \
    dsda/mapinfo/u.c \
    dsda/memory.c \
    dsda/messenger.c \
    dsda/mobjinfo.c \
    dsda/mouse.c \
    dsda/msecnode.c \
    dsda/music.c \
    dsda/name.c \
    dsda/options.c \
    dsda/palette.c \
    dsda/pause.c \
    dsda/pclass.c \
    dsda/playback.c \
    dsda/preferences.c \
    dsda/quake.c \
    dsda/render_stats.c \
    dsda/save.c \
    dsda/scroll.c \
    dsda/settings.c \
    dsda/sfx.c \
    dsda/skill_info.c \
    dsda/skip.c \
    dsda/sndinfo.c \
    dsda/spawn_number.c \
    dsda/split_tracker.c \
    dsda/sprite.c \
    dsda/state.c \
    dsda/stretch.c \
    dsda/text_color.c \
    dsda/text_file.c \
    dsda/thing_id.c \
    dsda/time.c \
    dsda/tracker.c \
    dsda/tranmap.c \
    dsda/udmf.cpp \
    dsda/utility.c \
    dsda/utility/string_view.c \
    dsda/wad_stats.c \
    dsda/zipfile.c \
    dsda/gameinfo.cpp \
    dstrings.c \
    d_deh.c \
    d_items.c \
    d_main.c \
    e6y.c \
    f_finale.c \
    f_wipe.c \
    g_game.c \
    g_overflow.c \
    heretic/d_main.c \
    heretic/f_finale.c \
    heretic/info.c \
    heretic/in_lude.c \
    heretic/level_names.c \
    heretic/mn_menu.c \
    heretic/sb_bar.c \
    heretic/sounds.c \
    hexen/a_action.c \
    hexen/info.c \
    hexen/f_finale.c \
    hexen/h2_main.c \
    hexen/in_lude.c \
    hexen/p_acs.c \
    hexen/p_anim.c \
    hexen/p_things.c \
    hexen/po_man.c \
    hexen/sn_sonix.c \
    hexen/sounds.c \
    hexen/sv_save.c \
    hu_lib.c \
    hu_stuff.c \
    info.c \
    i_capture.c \
    i_glob.c \
    lprintf.c \
    md5.c \
    m_argv.c \
    m_bbox.c \
    m_cheat.c \
    m_file.c \
    m_menu.c \
    m_misc.c \
    m_random.c \
    p_ceilng.c \
    p_doors.c \
    p_enemy.c \
    p_floor.c \
    p_genlin.c \
    p_inter.c \
    p_lights.c \
    p_map.c \
    p_maputl.c \
    p_mobj.c \
    p_plats.c \
    p_pspr.c \
    p_saveg.c \
    p_setup.c \
    p_sight.c \
    p_spec.c \
    p_switch.c \
    p_telept.c \
    p_tick.c \
    p_user.c \
    r_bsp.c \
    r_data.c \
    r_draw.c \
    r_fps.c \
    r_main.c \
    r_patch.c \
    r_plane.c \
    r_segs.c \
    r_sky.c \
    r_things.c \
    scanner.cpp \
    sc_man.c \
    smooth.c \
    sounds.c \
    st_lib.c \
    st_stuff.c \
    s_advsound.c \
    s_sound.c \
    tables.c \
    umapinfo.cpp \
    v_video.c \
    wadtbl.c \
    wi_stuff.c \
    w_wad.c \
    z_bmalloc.c \
    z_zone.c \


NET_CLIENT_SRC = d_client.c

MUS2MID_SRC = \
    memio.c \
    mus2mid.c \

SDLDOOM_SOURCES = \
    SDL/i_main.c \
    SDL/i_sound.c \
    SDL/i_sndfile.c \
    SDL/i_sshot.c \
    SDL/i_system.c \
    SDL/i_video.c \

DOOMMUSIC_SOURCES = \
    MUSIC/flplayer.c \
    MUSIC/madplayer.c \
    MUSIC/midifile.c \
    MUSIC/opl.c \
    MUSIC/opl3.c \
    MUSIC/oplplayer.c \
    MUSIC/opl_queue.c \
    MUSIC/portmidiplayer.c \
    MUSIC/vorbisplayer.c \
    MUSIC/xmpplayer.c \

GL_SRC = \
   gl_clipper.c \
        gl_drawinfo.c \
        gl_fbo.c \
        gl_light.c \
        gl_main.c \
        gl_map.c \
        gl_missingtexture.c \
        gl_opengl.c \
        gl_preprocess.c \
        gl_progress.c \
        gl_shader.c \
        gl_sky.c \
        gl_texture.c \
        gl_vertex.c \
        gl_wipe.c \

TESS_SRC = \
    MOBILE/glutess/dict.c \
    MOBILE/glutess/memalloc.c \
    MOBILE/glutess/mesh.c \
     MOBILE/glutess/geom.c \
    MOBILE/glutess/normal.c \
    MOBILE/glutess/priorityq.c \
    MOBILE/glutess/render.c \
    MOBILE/glutess/sweep.c \
    MOBILE/glutess/tess.c \
    MOBILE/glutess/tessellate.c \
    MOBILE/glutess/tessmono.c \



LOCAL_SRC_FILES += \
    ${COMMON_SRC} \
    ${NET_CLIENT_SRC} \
    ${WAD_SRC} \
    ${MUS2MID_SRC} \
    ${SDLDOOM_SOURCES} \
    ${DOOMMUSIC_SOURCES} \
    ${EXTRA_FILES} \
    ${GL_SRC} \
    ${TESS_SRC} \
    w_memcache.c

LOCAL_LDLIBS += -llog -lz -lGLESv1_CM

LOCAL_STATIC_LIBRARIES += fluidsynth-static SDL2_net logwritter zipotg sndfile

LOCAL_SHARED_LIBRARIES := touchcontrols SDL2 SDL2_mixer SDL2_image core_shared saffal GL4ES ogg vorbis

#Strip unused functions/data
LOCAL_CFLAGS += -fvisibility=hidden -fdata-sections -ffunction-sections -fPIC
LOCAL_LDFLAGS += -Wl,--gc-sections -flto

include $(BUILD_SHARED_LIBRARY)






