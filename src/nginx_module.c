#include "nginx_module.h"

static ngx_int_t ngx_http_hello_handler(ngx_http_request_t *r)
{
    ngx_int_t rc;
    ngx_buf_t *b;
    ngx_chain_t out;

    /* Ответ только на GET и HEAD */
    if (!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD)))
    {
        return NGX_HTTP_NOT_ALLOWED;
    }

    /* Устанавливаем Content-Type */
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *)"text/plain";

    /* Устанавливаем возвращаемый статус */
    r->headers_out.status = NGX_HTTP_OK;

    /* Отправляем заголовки */
    rc = ngx_http_send_header(r);
    if (rc != NGX_OK)
    {
        return rc;
    }

    /* Если это HEAD — тело не отправляем */
    if (r->method == NGX_HTTP_HEAD)
    {
        return ngx_http_send_special(r, NGX_HTTP_FLUSH);
    }

    /* Создаём буфер */
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if (b == NULL)
    {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Данные для ответа */
    u_char *response = (u_char *)"Hello from Nginx module!\n";
    b->pos = response;
    b->last = response + ngx_strlen(response);
    b->memory = 1;
    b->last_buf = 1;
    

    /* Цепочка буферов */
    out.buf = b;
    out.next = NULL;

    /* Отправляем тело */
    return ngx_http_output_filter(r, &out);
}

static char *ngx_http_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_handler;

    return NGX_CONF_OK;
}