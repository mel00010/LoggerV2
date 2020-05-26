/******************************************************************************
 * LogMetaMetaFuncs.inc
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

#define LOG_curr_iter BOOST_PP_FRAME_ITERATION(1)

#define LOG_max_iter 12
// clang-format off
//                         |                                            Array                                                                              |
//                         | Size |                                       Tuple                                                                          | |
//                         |      | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | |
#define LOG_func_ret_arr   ( 12,  ( TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE ) )
#define LOG_func_name_arr  ( 12,  ( TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE ) )
#define LOG_level_arr      ( 12,  ( TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE ) )
#define LOG_id_arr         ( 12,  ( FALSE, FALSE, TRUE , TRUE , FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, TRUE , TRUE ) )
#define LOG_mod_arr        ( 12,  ( FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, TRUE , TRUE , FALSE, TRUE , TRUE , FALSE) )
#define LOG_loc_ndef_arr   ( 12,  ( FALSE, FALSE, FALSE, FALSE, TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, FALSE) )
#define LOG_loc_def_arr    ( 12,  ( TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, TRUE , TRUE , TRUE , TRUE ) )
#define LOG_format_arr     ( 12,  ( TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE ) )
#define LOG_template_arr   ( 12,  ( FALSE, FALSE, FALSE, FALSE, TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, FALSE) )
#define LOG_var_arr        ( 12,  ( TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE) )


#define LOG_temp_dec()       template <typename... Args>
#define LOG_temp_dec_n()     template <BOOST_PP_ENUM_PARAMS(iter, class T)>
#define LOG_func_ret()       inline void

#define LOG_level_dec()      const Level level BOOST_PP_COMMA()
#define LOG_id_dec()         const std::uint16_t id BOOST_PP_COMMA()
#define LOG_mod_dec()        const ModuleHandle& handle BOOST_PP_COMMA()
#define LOG_format_dec()     const std::string& format BOOST_PP_COMMA()
#define LOG_loc_dec_def()    const CustomSourceLocation loc = CustomSourceLocation::current BOOST_PP_LPAREN()BOOST_PP_RPAREN()
#define LOG_loc_dec_ndef()   const CustomSourceLocation loc BOOST_PP_COMMA()
#define LOG_temp_args_dec()  const Args... all


#define LOG_blank()//
#define LOG_level_n_base       Level::

#define LOG_forward_func       RawTrace // (
#define LOG_level_for()        std::forward<const Level>BOOST_PP_LPAREN() level BOOST_PP_RPAREN()
#define LOG_level_n()          BOOST_PP_CAT(LOG_level_n_base,LOG_level_value)
#define LOG_id_for()           BOOST_PP_COMMA() std::forward<const std::uint16_t>BOOST_PP_LPAREN()id BOOST_PP_RPAREN()
#define LOG_id_n()             BOOST_PP_COMMA() 0
#define LOG_mod_for()          BOOST_PP_COMMA() std::forward<const ModuleHandle&>BOOST_PP_LPAREN()handle BOOST_PP_RPAREN()
#define LOG_mod_n()            BOOST_PP_COMMA() ModuleHandle{}
#define LOG_format_for()       BOOST_PP_COMMA() std::forward<const std::string&>BOOST_PP_LPAREN()format BOOST_PP_RPAREN()
#define LOG_format_n()         BOOST_PP_COMMA() "" //TODO Add varargs support
#define LOG_loc_ndef_for()     BOOST_PP_COMMA() std::forward<const CustomSourceLocation>BOOST_PP_LPAREN()loc BOOST_PP_RPAREN()
#define LOG_loc_ndef_n()
#define LOG_loc_def_for()      BOOST_PP_COMMA() std::forward<const CustomSourceLocation>BOOST_PP_LPAREN()loc BOOST_PP_RPAREN()
#define LOG_loc_def_n()
#define LOG_temp_args_for()    BOOST_PP_COMMA() std::forward<const Args>BOOST_PP_LPAREN()all BOOST_PP_RPAREN()...
#define LOG_temp_args_n()
// clang-format on

#define LOG_func_name() BOOST_PP_ARRAY_ELEM(LOG_curr_iter, LOG_func_names)

#define LOG_level_enabled \
  BOOST_PP_ARRAY_ELEM(LOG_curr_iter, LOG_funcs_level_p_enabled)
#define LOG_level_value() \
  BOOST_PP_ARRAY_ELEM(LOG_curr_iter, LOG_funcs_level_value)

#define BOOST_PP_ITERATION_LIMITS (0, LOG_max_iter - 1)
#define BOOST_PP_FILENAME_2 "LoggerV2/LogMetaFuncs.inc"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_ITERATION_LIMITS
#undef BOOST_PP_FILENAME_2

#undef LOG_variadic_instantiated
#undef LOG_max_iter
#undef LOG_func_name
#undef LOG_level_enabled
#undef LOG_level_value
#undef LOG_temp_dec
#undef LOG_func_ret
#undef LOG_level_dec
#undef LOG_id_dec
#undef LOG_mod_dec
#undef LOG_format_dec
#undef LOG_loc_dec_ndef
#undef LOG_loc_dec_def
#undef LOG_temp_args_dec
#undef LOG_blank
#undef LOG_level_n_base
#undef LOG_forward_func
#undef LOG_level_for
#undef LOG_level_n
#undef LOG_id_for
#undef LOG_id_n
#undef LOG_mod_for
#undef LOG_mod_n
#undef LOG_format_for
#undef LOG_format_n
#undef LOG_loc_ndef_for
#undef LOG_loc_ndef_n
#undef LOG_loc_def_for
#undef LOG_loc_def_n
#undef LOG_temp_args_for
#undef LOG_temp_args_n
#undef LOG_template_arr
#undef LOG_func_ret_arr
#undef LOG_func_name_arr
#undef LOG_id_arr
#undef LOG_level_arr
#undef LOG_mod_arr
#undef LOG_format_arr
#undef LOG_loc_def_arr
#undef LOG_loc_ndef_arr
