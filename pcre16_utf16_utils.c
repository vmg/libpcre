/*************************************************
*      Perl-Compatible Regular Expressions       *
*************************************************/

/* PCRE is a library of functions to support regular expressions whose syntax
and semantics are as close as possible to those of the Perl 5 language.

                       Written by Philip Hazel
           Copyright (c) 1997-2009 University of Cambridge

-----------------------------------------------------------------------------
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of the University of Cambridge nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------
*/


/* This module contains a function for converting any UTF-16 character
strings to host byte order. */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Generate code with 16 bit character support. */
#define COMPILE_PCRE16

#include "pcre_internal.h"

int
pcre16_utf16_to_host_byte_order(PCRE_SCHAR16 *output, PCRE_SPTR16 input, int length, int keep_boms)
{
#ifdef SUPPORT_UTF16
/* This function converts any UTF-16 string to host byte order and optionally removes
any Byte Order Marks (BOMS). Returns with the remainig length. */
BOOL same_bo = TRUE;
PCRE_SPTR16 end = input + length;
/* The c variable must be unsigned. */
register pcre_uchar c;

while (input < end)
  {
  c = *input++;
  if (c == 0xfeff || c == 0xfffe)
    {
    /* Detecting the byte order of the machine is unnecessary, it is
    enough to know that the UTF-16 string has the same byte order or not. */
    same_bo = c == 0xfeff;
    if (keep_boms != 0)
      *output++ = 0xfeff;
    else
      length--;
    }
  else
    *output++ = same_bo ? c : ((c >> 8) | (c << 8)); /* Flip bytes if needed. */
  }

#else
(void)(output);  /* Keep picky compilers happy */
(void)(input);
(void)(keep_boms);
#endif
return length;
}

/* End of pcre16_utf16_utils.c */
