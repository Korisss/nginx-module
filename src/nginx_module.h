#include <ngx_core.h>
#include <ngx_http.h>

static char *ngx_http_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_hello_handler(ngx_http_request_t *r);

static ngx_command_t nginx_module_commands[] = {{
    name : ngx_string("hello_world"),
    type : NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
    set : ngx_http_hello,
    conf : 0,
    offset : 0,
    post : NULL
}};

static ngx_http_module_t nginx_module_ctx = {
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL  /* merge location configuration */
};

ngx_module_t nginx_module = {
    NGX_MODULE_V1,
    ctx : &nginx_module_ctx,          /* module context */
    commands : nginx_module_commands, /* module directives */
    type : NGX_HTTP_MODULE,           /* module type */
    init_master : NULL,               /* init master */
    init_module : NULL,               /* init module */
    init_process : NULL,              /* init process */
    init_thread : NULL,               /* init thread */
    exit_thread : NULL,               /* exit thread */
    exit_process : NULL,              /* exit process */
    exit_master : NULL,               /* exit master */
    NGX_MODULE_V1_PADDING
};
