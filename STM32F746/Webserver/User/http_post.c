#include "lwip/init.h"
#include "lwip/apps/httpd.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/apps/fs.h"
#include "httpd_structs.h"
#include "lwip/def.h"

#include "lwip/altcp.h"
#include "lwip/altcp_tcp.h"
#if HTTPD_ENABLE_HTTPS
#include "lwip/altcp_tls.h"
#endif
#ifdef LWIP_HOOK_FILENAME
#include LWIP_HOOK_FILENAME
#endif
#if LWIP_HTTPD_TIMING
#include "lwip/sys.h"
#endif /* LWIP_HTTPD_TIMING */

#include <string.h> /* memset */
#include <stdlib.h> /* atoi */
#include <stdio.h>
#include "printEx.h"
/**
 * Mặc định LWIP chỉ hỗ trợ GET cho http
 * lWIP cho phép chúng ta xử lý POST riêng qua 3 hàm
 * httpd_post_begin
 * httpd_post_receive_data
 * httpd_post_finished
 */
extern tCGI *httpd_cgis;
extern struct http_state;

char http_post_response_filename[32];
err_t httpd_post_begin(void *connection, const char *uri, const char *http_request,u16_t http_request_len, int content_len, char *response_uri,u16_t response_uri_len, u8_t *post_auto_wnd)
{
 memset(http_post_response_filename,0,sizeof(http_post_response_filename));

      strcpy(response_uri,uri);

      return ERR_OK;
}

 

#define LWIP_HTTPD_POST_MAX_PAYLOAD_LEN     1600 //Phải 1600 hoặc lớn hơn , nhỏ hơn có thể lỗi vì max len gói tin là 15xx không nhiws

static char http_post_payload[LWIP_HTTPD_POST_MAX_PAYLOAD_LEN];
static u16_t http_post_payload_len = 0;

err_t httpd_post_receive_data(void *connection, struct pbuf *p)

{
    my_printf("DATA nhan %s",p->payload);
    struct http_state *hs=(struct http_state*) connection;

      *(strrchr(p->payload,'&')) = 0;

    sprintf(http_post_response_filename +strlen(http_post_response_filename),"?%s",p->payload);

    return ERR_MEM;//Do not reply ERR_OK, in order to allow outside functions to call http_handle_post_finished()
}

 

void httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len)

{
   
}
static err_t http_handle_post_finished(struct http_state *hs)

{

  /* application error or POST finished */

  /* NULL-terminate the buffer */

// http_post_response_filename[0] = 0;//Data processing has been processed in httpd_post_begin() and httpd_post_receive_data() functions

//  httpd_post_finished(hs,http_post_response_filename, LWIP_HTTPD_POST_MAX_RESPONSE_URI_LEN);

  return http_find_file(hs, http_post_response_filename,0);

}