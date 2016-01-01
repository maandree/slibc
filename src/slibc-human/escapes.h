/**
 * slibc — Yet another C library
 * Copyright © 2015, 2016  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



/**
 * List all escapes, excluding initial backslash,
 * with ASCII-character names, mapped to their
 * codepoint.
 */
#define LIST_ASCII_NAMES  \
  X("NUL",  0)  \
  X("SOH",  1)  \
  X("STX",  2)  \
  X("ETX",  3)  \
  X("EOT",  4)  \
  X("ENQ",  5)  \
  X("ACK",  6)  \
  X("BEL",  7)  \
  X("BS",   8)  \
  X("HT",   9)  \
  X("LF",  10)  \
  X("VT",  11)  \
  X("FF",  12)  \
  X("CR",  13)  \
  X("SO",  14)  \
  X("SI",  15)  \
  X("DLE", 16)  \
  X("DC1", 17)  \
  X("DC2", 18)  \
  X("DC3", 19)  \
  X("DC4", 20)  \
  X("NAK", 21)  \
  X("SYN", 22)  \
  X("ETB", 23)  \
  X("CAN", 24)  \
  X("EM",  25)  \
  X("SUB", 26)  \
  X("ESC", 27)  \
  X("FS",  28)  \
  X("GS",  29)  \
  X("RS",  30)  \
  X("US",  31)  \
  X("SP",  32)  \
  X("DEL", 0x7F)


/**
 * List all escapes, excluding initial backslash,
 * of the characters (including initial backslash)
 * that should both escaped and unescaped, mapped
 * to their codepoint.
 */
#define LIST_BIJECTIVE_ESCAPES  \
  X('a', '\a')  \
  X('b', '\b')  \
  X('e', 033)   \
  X('f', '\f')  \
  X('n', '\n')  \
  X('r', '\r')  \
  X('t', '\t')  \
  X('v', '\v')  \
  X('\\', '\\')

