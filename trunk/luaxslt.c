#include <errno.h>
#include <lualib.h>
#include <lauxlib.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

int luaopen_luaxsltlib (lua_State *L);

#define LUA_EXTRALIBS { "luaxsltlib", luaopen_luaxsltlib },

static int l_transform(lua_State *L) {
    int n = lua_gettop(L);
    const char *s = luaL_checkstring(L, 1);
    const char *ss = luaL_checkstring(L, 2);

    const char *params[16 + 1];
    char *out;
    int nbparams = 0;
    int len = 9999;
    xsltStylesheetPtr cur = NULL;
    xmlDocPtr doc, res;
    int i = 0;


    if (n > 2 && (n/2)*2 == n ) {
        for (i = 3; i <= n; i++) {
            params[nbparams++] = luaL_checkstring(L, i);
        }
    }

    params[nbparams] = NULL;
    xmlSubstituteEntitiesDefault(0);
    xmlLoadExtDtdDefaultValue = 1;
    cur = xsltParseStylesheetFile((const xmlChar *)ss);

    doc = xmlParseDoc((const xmlChar *)s);
    res = xsltApplyStylesheet(cur, doc, params);
    xsltSaveResultToString(&out,&len, res, cur);

    out[len] = NULL;

    xsltFreeStylesheet(cur);
    xmlFreeDoc(res);
    xmlFreeDoc(doc);

    lua_pushstring(L,out);
    lua_pushnumber(L,len);

    xmlFree(out);

    xsltCleanupGlobals();
    xmlCleanupParser();


    return 2;
}


static const struct luaL_reg luaxsltlib [] = {
      {"transform", l_transform},
      {NULL, NULL}
};


int luaopen_luaxsltlib (lua_State *L) {
      luaL_openlib(L, "luaxsltlib", luaxsltlib, 0);
      return 1;
}

