/******************************************************************************
 * LogFuncs.inc
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

#define LOG_SLOT_NUMBER_LAYER_3 4

#ifndef LOG_curr_iter_3
#undef BOOST_PP_VALUE
#define BOOST_PP_VALUE 0
#include BOOST_PP_ASSIGN_SLOT(LOG_SLOT_NUMBER_LAYER_3)
#endif

#undef BOOST_PP_VALUE
#define BOOST_PP_VALUE BOOST_PP_SLOT(LOG_SLOT_NUMBER_LAYER_3) + 1
#include BOOST_PP_ASSIGN_SLOT(LOG_SLOT_NUMBER_LAYER_3)
#define LOG_curr_iter_3 BOOST_PP_SLOT(LOG_SLOT_NUMBER_LAYER_3)

// clang-format off
#ifndef LOG_print_var_args
#define LOG_print_var_args(z, n, data) \
  const BOOST_PP_CAT(T, n) BOOST_PP_CAT(t, n) BOOST_PP_COMMA()
#endif  // LOG_print_var_args

#ifndef LOG_print_forwards
#define LOG_print_forwards(z, n, data) \
  BOOST_PP_COMMA() std::forward<const BOOST_PP_CAT(T, n)>(BOOST_PP_CAT(t, n))
#endif  // LOG_print_forwards

template <BOOST_PP_ENUM_PARAMS(LOG_curr_iter_3, class T)>
BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_func_ret_arr  ), LOG_func_ret, LOG_blank)()
BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_func_name_arr ), LOG_func_name, LOG_blank)() BOOST_PP_LPAREN()
    BOOST_PP_IF(BOOST_PP_AND(LOG_level_enabled, BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_level_arr ) ),
        LOG_level_dec, LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_id_arr         ), LOG_id_dec,         LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_mod_arr        ), LOG_mod_dec,        LOG_blank )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_format_arr     ), LOG_format_dec,     LOG_blank )()
    BOOST_PP_REPEAT(LOG_curr_iter_3, LOG_print_var_args, ~) LOG_loc_dec_def() BOOST_PP_RPAREN() const {
  LOG_forward_func BOOST_PP_LPAREN()
  BOOST_PP_IF(BOOST_PP_AND(LOG_level_enabled, BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_level_arr ) ),
      LOG_level_for, LOG_level_value)()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_id_arr         ), LOG_id_for,         LOG_id_n         )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_mod_arr        ), LOG_mod_for,        LOG_mod_n        )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_loc_def_arr    ), LOG_loc_def_for,    LOG_loc_def_n    )()
    BOOST_PP_IF( BOOST_PP_ARRAY_ELEM( LOG_curr_iter_2, LOG_format_arr     ), LOG_format_for,     LOG_format_n     )()
    BOOST_PP_REPEAT(LOG_curr_iter_3, LOG_print_forwards, ~)
    BOOST_PP_RPAREN();
}
#undef LOG_print_var_args
#undef LOG_print_forwards

