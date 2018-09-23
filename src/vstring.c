/*
 *  This file is a part of libacars
 *
 *  Copyright (c) 2018 Tomasz Lemiech <szpajder@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdarg.h>
#include "macros.h"
#include "util.h"
#include "vstring.h"

#define LA_VSTR_INITIAL_SIZE 256
#define LA_VSTR_SIZE_MULT 2

static void la_vstring_grow(la_vstring * const vstr, int const space_needed) {
	la_assert(vstr);
	la_assert(space_needed > 0);

	int new_size = vstr->allocated_size;
	while(vstr->len + space_needed >= new_size) {
		new_size *= LA_VSTR_SIZE_MULT;
	}
	la_debug_print("allocated_size=%d len=%d space_needed=%d new_size: %d\n",
		vstr->allocated_size, vstr->len, space_needed, new_size);
	vstr->str = LA_XREALLOC(vstr->str, new_size);
	vstr->allocated_size = new_size;
}

static int la_vstring_space_left(la_vstring const * const vstr) {
	la_assert(vstr);
	return vstr->allocated_size - vstr->len;
}

la_vstring *la_vstring_new() {
	la_vstring *vstr = LA_XCALLOC(1, sizeof(la_vstring));
	vstr->str = LA_XCALLOC(LA_VSTR_INITIAL_SIZE, sizeof(char));
	vstr->allocated_size = LA_VSTR_INITIAL_SIZE;
	vstr->len = 0;
	return vstr;
}

void la_vstring_destroy(la_vstring *vstr) {
	if(vstr) {
		LA_XFREE(vstr->str);
	}
	LA_XFREE(vstr);
}

void la_vstring_append_sprintf(la_vstring * const vstr, char const *fmt, ...) {
	la_assert(vstr);
	la_assert(fmt);

	int space_left = la_vstring_space_left(vstr);
	int result_size;
	va_list ap;
	va_start(ap, fmt);
		result_size = 1 + vsnprintf(vstr->str + vstr->len, space_left, fmt, ap);
	va_end(ap);
	if(result_size < space_left) {	// we have enough space
		la_debug_print("result_size %d < space_left %d - no need to grow\n", result_size, space_left);
		goto end;
	} else {
		// Not enough space - realloc and retry once
		la_debug_print("result_size %d >= space_left %d - need to grow\n", result_size, space_left);
		la_vstring_grow(vstr, result_size);
		space_left = la_vstring_space_left(vstr);
		va_start(ap, fmt);
			result_size = 1 + vsnprintf(vstr->str + vstr->len, space_left, fmt, ap);
		va_end(ap);
		la_assert(result_size < space_left);
	}
end:
	vstr->len += result_size - 1;	// not including '\0'
	la_debug_print("sprintf completed: allocated_size=%d len=%d\n",
		vstr->allocated_size, vstr->len);
	return;
}
