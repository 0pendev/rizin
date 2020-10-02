/* radare - LGPL - Copyright 2019 - deroad */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rz_lib.h>
#include <rz_util.h>
#include <rz_flag.h>
#include <rz_anal.h>
#include <rz_parse.h>

static char* get_fcn_name(RzAnal *anal, ut32 fcn_id) {
	rz_cons_push ();
	char *s = anal->coreb.cmdstrf (anal->coreb.core, "is~FUNC[6:%u]", fcn_id);
	rz_cons_pop ();
	if (s) {
		size_t namelen = strlen (s);
		s[namelen - 1] = 0;
	}
	return s;
}

static bool subvar(RzParse *p, RzAnalFunction *f, ut64 addr, int oplen, char *data, char *str, int len) {
	char *fcn_name = NULL;
	str[0] = 0;
	if (!strncmp (data, "call ", 5)) {
		ut32 fcn_id = (ut32) rz_num_get (NULL, data + 5);
		if (!(fcn_name = get_fcn_name (p->analb.anal, fcn_id))) {
			return false;
		}
		snprintf (str, len, "call sym.%s", fcn_name);
		free (fcn_name);
		return true;
	}
	return false;
}

RzParsePlugin rz_parse_plugin_wasm_pseudo = {
	.name = "wasm.pseudo",
	.desc = "WASM pseudo syntax",
	.subvar = &subvar,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct radare_plugin = {
	.type = R_LIB_TYPE_PARSE,
	.data = &rz_parse_plugin_wasm_pseudo,
	.version = RZ_VERSION
};
#endif
