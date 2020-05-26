/******************************************************************************
 * LogMetaFuncs.inc
 * Copyright (C) 2020  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of LoggerV2.
 *
 * LoggerV2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LoggerV2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LoggerV2.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#define LOG_curr_iter_2 BOOST_PP_FRAME_ITERATION(2)
// clang-format off

#define LOG_start_enumerating BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2 , LOG_var_arr )

#if BOOST_PP_EQUAL(LOG_start_enumerating, TRUE)
#define LOG_current_iteration_index BOOST_PP_ITERATION()
 #define BOOST_PP_ITERATION_LIMITS (0, LOG_func_max_args)
#define BOOST_PP_FILENAME_3 "LoggerV2/LogFuncs.inc"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_ITERATION_LIMITS
#undef BOOST_PP_FILENAME_3
#undef LOG_curr_iter_3
#else

BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_template_arr  ), LOG_temp_dec, LOG_blank)()
BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_func_ret_arr  ), LOG_func_ret, LOG_blank)()
BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_func_name_arr ), LOG_func_name, LOG_blank)() (
    BOOST_PP_IF(BOOST_PP_AND(LOG_level_enabled, BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_level_arr ) ),
            LOG_level_dec, LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_id_arr         ), LOG_id_dec,         LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_mod_arr        ), LOG_mod_dec,        LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_loc_ndef_arr   ), LOG_loc_dec_ndef,   LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_format_arr     ), LOG_format_dec,     LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_template_arr   ), LOG_temp_args_dec,  LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_loc_def_arr    ), LOG_loc_dec_def,    LOG_blank )()) const {
  LOG_forward_func (
      BOOST_PP_IF(BOOST_PP_AND(LOG_level_enabled, BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_level_arr ) ),
              LOG_level_for, LOG_level_value )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_id_arr         ), LOG_id_for,         LOG_id_n         )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_mod_arr        ), LOG_mod_for,        LOG_mod_n        )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_loc_ndef_arr   ), LOG_loc_ndef_for,   LOG_loc_ndef_n   )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_loc_def_arr    ), LOG_loc_def_for,    LOG_loc_def_n    )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_format_arr     ), LOG_format_for,     LOG_format_n     )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_template_arr   ), LOG_temp_args_for,  LOG_temp_args_n  )()
  );
}
#endif

// clang-format on
