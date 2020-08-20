/**
  ******************************************************************************
  * @file    LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/httpser-netconn.c
  * @author  MCD Application Team
  * @brief   Basic http server implementation using LwIP netconn API
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "string.h"
#include <stdint.h>
#include <stdbool.h>
#include "lwip/api.h"
#include "lwip/ip4_addr.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "lwip/apps/mqtt_opts.h"
#include "lwip/dns.h"

#include "mqtt_thread.h"
#include "network_para.h"
#include "printEx.h"
#include "ValidataIpAddress.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MQTT_CLIENT_THREAD_PRIO    ( osPriorityNormal )


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static u32_t nPubCounter = 0;
mqtt_client_t test_mqtt_client;
static char pub_payload[40];
ip_addr_t ipHost;
static ip_addr_t primaryDnsServer = IPADDR4_INIT_BYTES(8,8,8,8);;
osThreadId_t task_mqtt;
/* Private function prototypes -----------------------------------------------*/
//static void example_connect(mqtt_client_t *client);
void dns_get_ip_from_host_callback(const char *name, const ip_addr_t *ipaddr, void *callback_arg);
static void mqtt_connect(mqtt_client_t *client);
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
static void mqtt_sub_request_cb(void *arg, err_t result);
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);
static void data_mqtt_publish(mqtt_client_t *client, void *arg);
static void mqtt_pub_request_cb(void *arg, err_t result);
static void data_mqtt_disconnect(mqtt_client_t *client);
static void mqtt_client_thread(void *arg);


/* Private functions ---------------------------------------------------------*/

/**
 * Establish connection to MQTT sever
 * struct mqtt_connect_client_info_t {
  const char *client_id;
  const char* client_user;
  const char* client_pass;
  u16_t keep_alive;
  const char* will_topic;
  const char* will_msg;
  u8_t will_qos;
  u8_t will_retain;
 */
static void mqtt_connect(mqtt_client_t *client)
{
  struct mqtt_connect_client_info_t ci;
  err_t err;
  /* Setup an empty client info structure */
  memset(&ci, 0, sizeof(ci));
  ci.client_id = "NhanTest";
  ci.client_user = net_para.mqttUser;
  ci.client_pass = net_para.mqttPass;
  //strcpy(ci.client_user,net_para.mqttUser);
  //strcpy(ci.client_pass ,net_para.mqttPass);
  err = mqtt_client_connect(client, &ipHost, net_para.mqttPort, mqtt_connection_cb, NULL, &ci);
  if(err != ERR_OK) {
    
    my_printf("mqtt_connect return %d\n", err);
  }
}

/**
 * Connection callback -- simply report status
 */
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
  err_t err;
  if(status == MQTT_CONNECT_ACCEPTED) {
    my_printf("mqtt_connection_cb: Successfully connected\n");
    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);
    err = mqtt_subscribe(client, "test/sub_topic", 1, mqtt_sub_request_cb, arg);
      mqtt_subscribe(client, "TestHome", 1, mqtt_sub_request_cb, arg);
    if(err != ERR_OK) {
      my_printf("mqtt_subscribe return: %d\n", err);
    }
  } else {
    my_printf("mqtt_connection_cb: Disconnected, reason: %d\n", status);
  }
}

/**
 * Subscription Callback
 */
static void mqtt_sub_request_cb(void *arg, err_t result)
{
  /* Just print the result code here for simplicity,
     normal behavior would be to take some action if subscribe fails like
     notifying user, retry subscribe or disconnect from server */
  my_printf("Subscribe result: %d\n", result);
}


static int inpub_id;
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
  my_printf("Incoming publish at topic %s with total length %u\n", topic, (unsigned int)tot_len);
  if(strcmp(topic, "TestHome") == 0) {
    inpub_id = 0;
  } else if(topic[0] == 'A') {
    inpub_id = 1;
  } else {
    inpub_id = 2;
  }
}
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
  my_printf("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags);

  if(flags & MQTT_DATA_FLAG_LAST) {
    if(inpub_id == 0) {
        my_printf("mqtt_incoming_data_cb: %s\n", (const char *)data);
      
    } else if(inpub_id == 1) {
      /* Call an 'A' function... */
    } else {
      my_printf("mqtt_incoming_data_cb: Ignoring payload...\n");
    }
  } 
}


/**
 * Publish complete Callback
 */
static void mqtt_pub_request_cb(void *arg, err_t result)
{
  if(result != ERR_OK) {
    my_printf("Publish result: %d\n", result);
  }
}

/**
 * Publish Data
 */
static void data_mqtt_publish(mqtt_client_t *client, void *arg)
{
  nPubCounter++;
  sprintf(pub_payload, "PubData: 0x%X", (unsigned int) nPubCounter);
  err_t err;
  u8_t qos = 2; /* 0 1 or 2, see MQTT specification */
  u8_t retain = 0; /* No don't retain the payload... */
  err = mqtt_publish(client, "test/pub_topic", pub_payload, strlen(pub_payload), qos, retain, mqtt_pub_request_cb, arg);
  if(err != ERR_OK) {
    my_printf("Publish err: %d\n", err);
  }
 
}


/**
 * Disconnect from server
 */
static void data_mqtt_disconnect(mqtt_client_t *client)
{
	mqtt_disconnect(client);
}
/**
 * Get Ip Address frome Hostname
 */
void getIpFromeHost(char* host){
  if (is_valid_ip(host) == 0){
    dns_gethostbyname(net_para.serverMQTT, &ipHost, dns_get_ip_from_host_callback, NULL);
    return;
  } 
  ipaddr_aton(host,&ipHost);
}

/**
  * @brief  mqtt client thread
  * @param arg: pointer on argument(not used here)
  * @retval None
  */
static void mqtt_client_thread(void *arg)
{
  /* Connect to server */
  dns_init(); 
  dns_setserver(0,&primaryDnsServer);
  
  while(1)
  {
	  vTaskDelay(1000);

	  /* while connected, publish every second */
	  if(mqtt_client_is_connected(&test_mqtt_client))
	  {
		  data_mqtt_publish(&test_mqtt_client, NULL); 
	  }
	  else
	  {
      //getIpFromeHost();
      dns_gethostbyname(net_para.serverMQTT, &ipHost, dns_get_ip_from_host_callback, NULL);
      if (state_get_ip_from_host) mqtt_connect(&test_mqtt_client);
      vTaskDelay(3000);
	  }
  }
  data_mqtt_disconnect(&test_mqtt_client);
}

/* Public functions ---------------------------------------------------------*/

/**
  * @brief  Initialize the MQTT client (start its thread)
  * @param  none
  * @retval None
  */
void mqtt_client_init()
{
  task_mqtt = sys_thread_new("MQTT", mqtt_client_thread, NULL, DEFAULT_THREAD_STACKSIZE, MQTT_CLIENT_THREAD_PRIO);
}

/**
((((x) & (u32_t)0x000000ffUL) << 24) | (((x) & (u32_t)0x0000ff00UL) << 8) | (((x) & (u32_t)0x00ff0000UL) >> 8) | (((x) & (u32_t)0xff000000UL) >> 24))
*/

void dns_get_ip_from_host_callback(const char *name, const ip_addr_t *ipaddr, void *callback_arg){
  ipHost = *ipaddr;
  state_get_ip_from_host = 1;                               
}