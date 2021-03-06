/*
   +----------------------------------------------------------------------+
   | eAccelerator project                                                 |
   +----------------------------------------------------------------------+
   | Copyright (c) 2004 - 2012 eAccelerator                               |
   | http://eaccelerator.sourceforge.net                                  |
   +----------------------------------------------------------------------+
   | This program is free software; you can redistribute it and/or        |
   | modify it under the terms of the GNU General Public License          |
   | as published by the Free Software Foundation; either version 2       |
   | of the License, or (at your option) any later version.               |
   |                                                                      |
   | This program is distributed in the hope that it will be useful,      |
   | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        |
   | GNU General Public License for more details.                         |
   |                                                                      |
   | You should have received a copy of the GNU General Public License    |
   | along with this program; if not, write to the Free Software          |
   | Foundation, Inc., 59 Temple Place - Suite 330, Boston,               |
   | MA  02111-1307, USA.                                                 |
   |                                                                      |
   | A copy is availble at http://www.gnu.org/copyleft/gpl.txt            |
   +----------------------------------------------------------------------+
   $Id: opcodes.c 411 2010-02-25 10:54:31Z hans $
*/

#include "opcodes.h"

#ifdef HAVE_EACCELERATOR

#ifdef WITH_EACCELERATOR_DISASSEMBLER
#  define OPDEF(NAME, OPS) {NAME, OPS}
#else
#  define OPDEF(NAME, OPS) {OPS}
#endif

#define LAST_OPCODE (sizeof(opcodes)/sizeof(opcodes[0]))

static const opcode_dsc opcodes[] = {
    OPDEF("NOP",                       EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 0 */
    OPDEF("ADD",                       EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 1 */
    OPDEF("SUB",                       EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 2 */
    OPDEF("MUL",                       EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 3 */
    OPDEF("DIV",                       EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 4 */
    OPDEF("MOD",                       EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 5 */
    OPDEF("SL",                        EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 6 */
    OPDEF("SR",                        EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 7 */
    OPDEF("CONCAT",                    EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 8 */
    OPDEF("BW_OR",                     EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 9 */
    OPDEF("BW_AND",                    EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 10 */
    OPDEF("BW_XOR",                    EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 11 */
    OPDEF("BW_NOT",                    EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_TMP), /* 12 */
    OPDEF("BOOL_NOT",                  EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 13 */
    OPDEF("BOOL_XOR",                  EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 14 */
    OPDEF("IS_IDENTICAL",              EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 15 */
    OPDEF("IS_NOT_IDENTICAL",          EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 16 */
    OPDEF("IS_EQUAL",                  EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 17 */
    OPDEF("IS_NOT_EQUAL",              EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 18 */
    OPDEF("IS_SMALLER",                EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 19 */
    OPDEF("IS_SMALLER_OR_EQUAL",       EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 20 */
    OPDEF("CAST",                      EXT_CAST   | OP1_STD    | OP2_UNUSED | RES_TMP), /* 21 */
    OPDEF("QM_ASSIGN",                 EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_TMP), /* 22 */
    OPDEF("ASSIGN_ADD",                EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 23 */
    OPDEF("ASSIGN_SUB",                EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 24 */
    OPDEF("ASSIGN_MUL",                EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 25 */
    OPDEF("ASSIGN_DIV",                EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 26 */
    OPDEF("ASSIGN_MOD",                EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 27 */
    OPDEF("ASSIGN_SL",                 EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 28 */
    OPDEF("ASSIGN_SR",                 EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 29 */
    OPDEF("ASSIGN_CONCAT",             EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 30 */
    OPDEF("ASSIGN_BW_OR",              EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 31 */
    OPDEF("ASSIGN_BW_AND",             EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 32 */
    OPDEF("ASSIGN_BW_XOR",             EXT_ASSIGN | OP1_STD    | OP2_STD    | RES_VAR), /* 33 */
    OPDEF("PRE_INC",                   EXT_UNUSED | OP1_VAR    | OP2_UNUSED | RES_VAR), /* 34 */
    OPDEF("PRE_DEC",                   EXT_UNUSED | OP1_VAR    | OP2_UNUSED | RES_VAR), /* 35 */
    OPDEF("POST_INC",                  EXT_UNUSED | OP1_VAR    | OP2_UNUSED | RES_TMP), /* 36 */
    OPDEF("POST_DEC",                  EXT_UNUSED | OP1_VAR    | OP2_UNUSED | RES_TMP), /* 37 */
    OPDEF("ASSIGN",                    EXT_UNUSED | OP1_VAR    | OP2_STD    | RES_VAR), /* 38 */
    OPDEF("ASSIGN_REF",                EXT_UNUSED | OP1_VAR    | OP2_VAR    | RES_VAR), /* 39 */
    OPDEF("ECHO",                      EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_UNUSED), /* 40 */
    OPDEF("PRINT",                     EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_TMP), /* 41 */
    OPDEF("JMP",                       EXT_UNUSED | OP1_JMPADDR| OP2_UNUSED | RES_UNUSED), /* 42 */
    OPDEF("JMPZ",                      EXT_UNUSED | OP1_STD    | OP2_JMPADDR| RES_UNUSED), /* 43 */
    OPDEF("JMPNZ",                     EXT_UNUSED | OP1_STD    | OP2_JMPADDR| RES_UNUSED), /* 44 */
    OPDEF("JMPZNZ",                    EXT_OPLINE | OP1_STD    | OP2_OPLINE | RES_UNUSED), /* 45 */
    OPDEF("JMPZ_EX",                   EXT_UNUSED | OP1_STD    | OP2_JMPADDR| RES_TMP), /* 46 */
    OPDEF("JMPNZ_EX",                  EXT_UNUSED | OP1_STD    | OP2_JMPADDR| RES_TMP), /* 47 */
    OPDEF("CASE",                      EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 48 */
    OPDEF("SWITCH_FREE",               EXT_BIT    | OP1_STD    | OP2_UNUSED | RES_UNUSED), /* 49 */
    OPDEF("BRK",                       EXT_UNUSED | OP1_BRK    | OP2_STD    | RES_UNUSED), /* 50 */
    OPDEF("CONT",                      EXT_UNUSED | OP1_CONT   | OP2_STD    | RES_UNUSED), /* 51 */
    OPDEF("BOOL",                      EXT_UNUSED | OPS_STD    | OP2_UNUSED | RES_TMP), /* 52 */
    OPDEF("INIT_STRING",               EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_TMP), /* 53 */
    OPDEF("ADD_CHAR",                  EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 54 */
    OPDEF("ADD_STRING",                EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 55 */
    OPDEF("ADD_VAR",                   EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 56 */
    OPDEF("BEGIN_SILENCE",             EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_TMP), /* 57 */
    OPDEF("END_SILENCE",               EXT_UNUSED | OP1_TMP    | OP2_UNUSED | RES_UNUSED), /* 58 */
    OPDEF("INIT_FCALL_BY_NAME",        EXT_INIT_FCALL | OP1_STD | OP2_STD   | RES_UNUSED), /* 59 */
    OPDEF("DO_FCALL",                  EXT_FCALL  | OP1_STD    | OP2_UNUSED | RES_VAR), /* 60 */
    OPDEF("DO_FCALL_BY_NAME",          EXT_FCALL  | OP1_STD    | OP2_UNUSED | RES_VAR), /* 61 */
    OPDEF("RETURN",                    EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_UNUSED), /* 62 */
    OPDEF("RECV",                      EXT_UNUSED | OP1_ARG    | OP2_UNUSED | RES_VAR), /* 63 */
    OPDEF("RECV_INIT",                 EXT_UNUSED | OP1_ARG    | OP2_STD    | RES_VAR), /* 64 */
    OPDEF("SEND_VAL",                  EXT_SEND   | OP1_STD    | OP2_ARG    | RES_UNUSED), /* 65 */
    OPDEF("SEND_VAR",                  EXT_SEND   | OP1_VAR    | OP2_ARG    | RES_UNUSED), /* 66 */
    OPDEF("SEND_REF",                  EXT_SEND   | OP1_VAR    | OP2_ARG    | RES_UNUSED), /* 67 */
    OPDEF("NEW",                       EXT_UNUSED | OP1_CLASS  | OP2_UNUSED | RES_VAR), /* 68 */
#ifdef ZEND_ENGINE_2_3
    OPDEF("INIT_NS_FCALL_BY_NAME",     EXT_STD    | OP1_STD    | OP1_STD    | RES_UNUSED), /* 69 */
#else
    OPDEF("JMP_NO_CTOR",               EXT_UNUSED | OP1_STD    | OP2_OPLINE | RES_UNUSED), /* 69 */
#endif
    OPDEF("FREE",                      EXT_UNUSED | OP1_TMP    | OP2_UNUSED | RES_UNUSED), /* 70 */
    OPDEF("INIT_ARRAY",                EXT_BIT    | OP1_STD    | OP2_STD    | RES_TMP), /* 71 */
    OPDEF("ADD_ARRAY_ELEMENT",         EXT_BIT    | OP1_STD    | OP2_STD    | RES_TMP), /* 72 */
    OPDEF("INCLUDE_OR_EVAL",           EXT_UNUSED | OP1_STD    | OP2_INCLUDE| RES_VAR), /* 73 */
    OPDEF("UNSET_VAR",                 EXT_UNUSED | OP1_STD    | OP2_FETCH  | RES_UNUSED), /* 74 */
    OPDEF("UNSET_DIM",                 EXT_STD    | OP1_STD    | OP2_STD    | RES_UNUSED), /* 75 */
    OPDEF("UNSET_OBJ",                 EXT_STD    | OP1_STD    | OP2_STD    | RES_UNUSED), /* 76 */
    OPDEF("FE_RESET",                  EXT_BIT    | OP1_STD    | OP2_OPLINE | RES_VAR), /* 77 */
    OPDEF("FE_FETCH",                  EXT_FE     | OP1_STD    | OP2_OPLINE | RES_TMP), /* 78 */
    OPDEF("EXIT",                      EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_UNUSED), /* 79 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("FETCH_R",                   EXT_FETCHTYPE | OP1_STD | OP2_STD | RES_VAR),    /* 80 */
#else
    OPDEF("FETCH_R",                   EXT_UNUSED | OP1_STD    | OP2_FETCH  | RES_VAR), /* 80 */
#endif
    OPDEF("FETCH_DIM_R",               EXT_FETCH  | OP1_VAR    | OP2_STD    | RES_VAR), /* 81 */
    OPDEF("FETCH_OBJ_R",               EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 82 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("FETCH_W",                   EXT_FETCHTYPE | OP1_STD | OP2_STD    | RES_VAR), /* 83 */
#else
    OPDEF("FETCH_W",                   EXT_UNUSED | OP1_STD    | OP2_FETCH  | RES_VAR), /* 83 */
#endif
    OPDEF("FETCH_DIM_W",               EXT_UNUSED | OP1_VAR    | OP2_STD    | RES_VAR), /* 84 */
    OPDEF("FETCH_OBJ_W",               EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 85 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("FETCH_RW",                  EXT_FETCHTYPE | OP1_STD | OP2_STD    | RES_VAR), /* 86 */
#else
    OPDEF("FETCH_RW",                  EXT_UNUSED | OP1_STD    | OP2_FETCH  | RES_VAR), /* 86 */
#endif
    OPDEF("FETCH_DIM_RW",              EXT_UNUSED | OP1_VAR    | OP2_STD    | RES_VAR), /* 87 */
    OPDEF("FETCH_OBJ_RW",              EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 88 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("FETCH_IS",                  EXT_FETCHTYPE | OP1_STD | OP2_STD    | RES_VAR), /* 89 */
#else
    OPDEF("FETCH_IS",                  EXT_UNUSED | OP1_STD    | OP2_FETCH  | RES_VAR), /* 89 */
#endif
    OPDEF("FETCH_DIM_IS",              EXT_UNUSED | OP1_VAR    | OP2_STD    | RES_VAR), /* 90 */
    OPDEF("FETCH_OBJ_IS",              EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 91 */
#ifdef ZEND_ENGINE_2_4
    /* TODO: extended_value also contains EXT_FETCHTYPE info in the form of a bitmask 
             this whole thing needs a serious overhaul... */
    OPDEF("FETCH_FUNC_ARG",            EXT_ARG    | OP1_STD    | OP2_STD    | RES_VAR), /* 92 */
#else
    OPDEF("FETCH_FUNC_ARG",            EXT_ARG    | OP1_STD    | OP2_FETCH  | RES_VAR), /* 92 */
#endif
    OPDEF("FETCH_DIM_FUNC_ARG",        EXT_ARG    | OP1_VAR    | OP2_STD    | RES_VAR), /* 93 */
    OPDEF("FETCH_OBJ_FUNC_ARG",        EXT_ARG    | OP1_STD    | OP2_STD    | RES_VAR), /* 94 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("FETCH_UNSET",               EXT_FETCHTYPE | OP1_STD | OP2_STD    | RES_VAR), /* 95 */
#else
    OPDEF("FETCH_UNSET",               EXT_UNUSED | OP1_STD    | OP2_FETCH  | RES_VAR), /* 95 */
#endif
    OPDEF("FETCH_DIM_UNSET",           EXT_UNUSED | OP1_VAR    | OP2_STD    | RES_VAR), /* 96 */
    OPDEF("FETCH_OBJ_UNSET",           EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 97 */
    OPDEF("FETCH_DIM_TMP_VAR",         EXT_FETCH  | OP1_STD    | OP2_STD    | RES_VAR), /* 98 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("FETCH_CONSTANT",            EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 99 */
#else
    OPDEF("FETCH_CONSTANT",            EXT_UNUSED | OP1_UCLASS | OP2_STD    | RES_TMP), /* 99 */
#endif
#ifdef ZEND_ENGINE_2_3
    OPDEF("GOTO",                      EXT_STD    | OP1_JMPADDR | OP2_STD    | RES_UNUSED), /* 100 */
#else
    OPDEF("UNDEF-100",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 100 */
#endif
    OPDEF("EXT_STMT",                  EXT_STD    | OP1_STD    | OP2_STD    | RES_STD), /* 101 */
    OPDEF("EXT_FCALL_BEGIN",           EXT_STD    | OP1_STD    | OP2_STD    | RES_STD), /* 102 */
    OPDEF("EXT_FCALL_END",             EXT_STD    | OP1_STD    | OP2_STD    | RES_STD), /* 103 */
    OPDEF("EXT_NOP",                   EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 104 */
    OPDEF("TICKS",                     EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_UNUSED), /* 105 */
    OPDEF("SEND_VAR_NO_REF",           EXT_SEND_NOREF| OP1_VAR | OP2_ARG    | RES_UNUSED),  /* 106 */
    OPDEF("CATCH",                     EXT_OPLINE | OP1_CLASS  | OP2_STD    | RES_UNUSED), /* 107 */
    OPDEF("THROW",                     EXT_UNUSED | OP1_STD    | OP2_OPLINE | RES_UNUSED), /* 108 */
    OPDEF("FETCH_CLASS",               EXT_FCLASS | OP1_STD    | OP2_STD    | RES_CLASS), /* 109 */
    OPDEF("CLONE",                     EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_VAR), /* 110 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("RETURN_BY_REF",             EXT_STD    | OP1_STD    | OP2_UNUSED | RES_UNUSED), /* 111 */
#else
    OPDEF("UNDEF-111",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 111 */
#endif
    OPDEF("INIT_METHOD_CALL",          EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 112 */
#ifdef ZEND_ENGINE_2_4
    OPDEF("INIT_STATIC_METHOD_CALL",   EXT_UNUSED | OP1_STD    | OP2_STD    | RES_UNUSED), /* 113 */
#else
    OPDEF("INIT_STATIC_METHOD_CALL",   EXT_UNUSED | OP1_UCLASS | OP2_STD    | RES_UNUSED), /* 113 */
#endif
#ifdef ZEND_ENGINE_2_4
    OPDEF("ISSET_ISEMPTY_VAR",         EXT_ISSET  | OP1_STD    | OP2_STD    | RES_TMP), /* 114 */
#else
    OPDEF("ISSET_ISEMPTY_VAR",         EXT_ISSET  | OP1_STD    | OP2_FETCH  | RES_TMP), /* 114 */
#endif
    OPDEF("ISSET_ISEMPTY_DIM_OBJ",     EXT_ISSET  | OP1_STD    | OP2_STD    | RES_TMP), /* 115 */

    OPDEF("UNDEF-116",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 116 */
    OPDEF("UNDEF-117",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 117 */
    OPDEF("UNDEF-118",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 118 */
    OPDEF("UNDEF-119",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 119 */
    OPDEF("UNDEF-120",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 120 */
    OPDEF("UNDEF-121",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 121 */
    OPDEF("UNDEF-122",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 122 */
    OPDEF("UNDEF-123",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 123 */
    OPDEF("UNDEF-124",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 124 */
    OPDEF("UNDEF-125",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 125 */
    OPDEF("UNDEF-126",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 126 */
    OPDEF("UNDEF-127",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 127 */
    OPDEF("UNDEF-128",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 128 */
    OPDEF("UNDEF-129",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 129 */
    OPDEF("UNDEF-130",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 130 */
    OPDEF("UNDEF-131",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 131 */

    OPDEF("PRE_INC_OBJ",               EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 132 */
    OPDEF("PRE_DEC_OBJ",               EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 133 */
    OPDEF("POST_INC_OBJ",              EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 134 */
    OPDEF("POST_DEC_OBJ",              EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP), /* 135 */
    OPDEF("ASSIGN_OBJ",                EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR), /* 136 */
    OPDEF("OP_DATA",                   EXT_UNUSED | OP1_STD    | OP2_STD    | RES_STD), /* 137 */
    OPDEF("INSTANCEOF",                EXT_UNUSED | OP1_STD    | OP2_CLASS  | RES_TMP), /* 138 */
    OPDEF("DECLARE_CLASS",             EXT_UNUSED | OP1_STD    | OP2_STD    | RES_CLASS), /* 139 */
    OPDEF("DECLARE_INHERITED_CLASS",   EXT_CLASS  | OP1_STD    | OP2_STD    | RES_CLASS), /* 140 */
    OPDEF("DECLARE_FUNCTION",          EXT_UNUSED | OP1_STD    | OP2_STD    | RES_UNUSED), /* 141 */
    OPDEF("RAISE_ABSTRACT_ERROR",      EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 142 */
#ifdef ZEND_ENGINE_2_3
    OPDEF("DECLARE_CONST",             EXT_DECLARE| OP1_STD    | OP2_STD    | RES_UNUSED), /* 143 */
#else
    OPDEF("UNDEF-143",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 143 */
#endif
#ifdef ZEND_ENGINE_2_3
    OPDEF("ADD_INTERFACE",             EXT_IFACE  | OP1_CLASS  | OP2_STD  | RES_UNUSED), /* 144 */
#else
    OPDEF("ADD_INTERFACE",             EXT_IFACE  | OP1_CLASS  | OP2_CLASS  | RES_UNUSED), /* 144 */
#endif
#ifdef ZEND_ENGINE_2_3
    OPDEF("DECLARE_INHERITED_CLASS_DELAYED",         EXT_CLASS | OP1_STD  | OP2_STD    | RES_OPLINE), /* 145 */
#else
    OPDEF("UNDEF-145",                 EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 145 */
#endif
    OPDEF("VERIFY_ABSTRACT_CLASS",     EXT_UNUSED | OP1_CLASS  | OP2_UNUSED | RES_UNUSED), /* 146 */
    OPDEF("ASSIGN_DIM",                EXT_UNUSED | OP1_STD    | OP2_STD    | RES_VAR),   /* 147 */
    OPDEF("ISSET_ISEMPTY_PROP_OBJ",    EXT_ISSET  | OP1_STD    | OP2_STD    | RES_TMP),   /* 148 */
    OPDEF("HANDLE_EXCEPTION",          EXT_STD    | OP1_UNUSED | OP2_UNUSED | RES_STD),   /* 149 */
    OPDEF("USER_OPCODE",               EXT_STD    | OP1_UNUSED | OP2_UNUSED | RES_STD)    /* 150 */
# ifdef ZEND_ENGINE_2_3
    ,
    OPDEF("UNDEF-151",                EXT_UNUSED | OP1_UNUSED | OP2_UNUSED | RES_UNUSED), /* 151 */
    OPDEF("JMP_SET",                  EXT_UNUSED | OP1_STD    | OP2_JMPADDR| RES_TMP),    /* 152 */
    OPDEF("DECLARE_LAMBDA_FUNCTION",  EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_UNUSED)  /* 153 */
# endif
#ifdef ZEND_ENGINE_2_4
    ,
    OPDEF("ADD_TRAIT",                EXT_FCLASS | OP1_STD    | OP2_STD    | RES_UNUSED), /* 154 */
    OPDEF("BIND_TRAITS",              EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_UNUSED), /* 155 */
    OPDEF("SEPARATE",                 EXT_UNUSED | OP1_STD    | OP2_STD    | RES_STD),    /* 156 */
    OPDEF("QM_ASSIGN_VAR",            EXT_UNUSED | OP1_STD    | OP2_UNUSED | RES_TMP),    /* 157 */
    OPDEF("JMP_SET_VAR",              EXT_UNUSED | OP1_STD    | OP2_STD    | RES_TMP)     /* 158 */
#endif
};

const opcode_dsc* get_opcode_dsc(unsigned int n)
{
    if (n < LAST_OPCODE) {
        return &opcodes[n];
    } else {
        return NULL;
    }
}
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: et sw=4 ts=4 fdm=marker
 * vim<600: et sw=4 ts=4
 */
