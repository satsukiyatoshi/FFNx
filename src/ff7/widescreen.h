/****************************************************************************/
//    Copyright (C) 2009 Aali132                                            //
//    Copyright (C) 2018 quantumpencil                                      //
//    Copyright (C) 2018 Maxime Bacoux                                      //
//    Copyright (C) 2020 myst6re                                            //
//    Copyright (C) 2020 Chris Rizzitello                                   //
//    Copyright (C) 2020 John Pritchard                                     //
//    Copyright (C) 2022 Julian Xhokaxhiu                                   //
//    Copyright (C) 2022 Tang-Tang Zhou                                     //
//    Copyright (C) 2022 Cosmos                                             //
//                                                                          //
//    This file is part of FFNx                                             //
//                                                                          //
//    FFNx is free software: you can redistribute it and/or modify          //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License         //
//                                                                          //
//    FFNx is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#pragma once

#include "common.h"
#include "globals.h"

#include <vector>

int wide_viewport_x = -107;
int wide_viewport_y = 0;
int wide_viewport_width = 854;
int wide_viewport_height = 480;

int wide_game_x = 0;
int wide_game_y = 0;
int wide_game_width = 854;
int wide_game_height = 480;

void ff7_widescreen_hook_init();

enum WIDESCREEN_MODE
{
    WM_DISABLED,
    WM_EXTEND_ONLY,
    WM_ZOOM,
    WM_EXTEND_WIDE
};

struct Keyframe
{
    int frame = 0;
    int v_offset = 0;
};

struct KeyPair
{
    Keyframe first;
    Keyframe second;
};

class Widescreen
{
public:
    void init();
    void initParamsFromConfig();
    void initMovieParamsFromConfig(char *name);

    const field_camera_range& getCameraRange();
    int getHorizontalOffset();
    int getVerticalOffset();
    bool isResetVerticalPos();
    WIDESCREEN_MODE getMode();

    KeyPair getMovieKeyPair(int frame);
    WIDESCREEN_MODE getMovieMode();

    void zoomBackground();

private:
    void loadConfig();
    void loadMovieConfig();

private:
    // Config
    toml::parse_result config;
    toml::parse_result movie_config;

    field_camera_range camera_range;
    int h_offset = 0;
    int v_offset = 0;
    bool is_reset_vertical_pos = false;
    WIDESCREEN_MODE widescreen_mode = WM_DISABLED;

    std::vector<Keyframe> movie_v_offset;
    WIDESCREEN_MODE widescreen_movie_mode = WM_DISABLED;
};

inline const field_camera_range& Widescreen::getCameraRange()
{
    return camera_range;
}

inline int Widescreen::getHorizontalOffset()
{
    return h_offset;
}

inline int Widescreen::getVerticalOffset()
{
    return v_offset;
}

inline bool Widescreen::isResetVerticalPos()
{
    return is_reset_vertical_pos;
}

inline WIDESCREEN_MODE Widescreen::getMode()
{
    struct game_mode* mode = getmode_cached();
    if (mode->driver_mode != MODE_FIELD) return WM_DISABLED;

    return widescreen_mode;
}

inline WIDESCREEN_MODE Widescreen::getMovieMode()
{
    return widescreen_movie_mode;
}

extern Widescreen widescreen;
