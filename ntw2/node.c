#include "contiki.h"
#include "node-id.h"
#include "sys/log.h"
#include "net/netstack.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/ipv6/uip-sr.h"
#include "net/mac/tsch/tsch.h"
#include "net/mac/tsch/tsch-schedule.h"
#include "net/mac/tsch/tsch-log.h"
#include "net/routing/routing.h"

#define DEBUG DEBUG_PRINT
#include "net/ipv6/uip-debug.h"


struct tsch_slotframe * sf_data;
struct tsch_slotframe * sf_eb;

linkaddr_t n1 = {{0,1,0,1,0,1,0,1}};
linkaddr_t n4 = {{0,4,0,4,0,4,0,4}};
linkaddr_t n6 = {{0,6,0,6,0,6,0,6}};
linkaddr_t n8 = {{0,8,0,8,0,8,0,8}};
linkaddr_t dest;

struct msg {
  uint16_t panid;
};
struct msg msg_buf;

void p_ou(void *ptr, int status, int transmissions);
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
void slot_rx(){
  printf("SPD: slot rx\n");
}
/*---------------------------------------------------------------------------*/
static void nt_send_packet(){
  msg_buf.panid = IEEE802154_PANID;
  packetbuf_clear();
  packetbuf_copyfrom(&msg_buf,sizeof(struct msg));
  packetbuf_set_attr(PACKETBUF_ATTR_FRAME_TYPE, FRAME802154_DATAFRAME);
  packetbuf_set_addr(PACKETBUF_ADDR_SENDER, &linkaddr_node_addr);
  packetbuf_set_addr(PACKETBUF_ADDR_RECEIVER, &dest);
  //packetbuf_set_addr(PACKETBUF_ADDR_RECEIVER, &tsch_broadcast_address);
  NETSTACK_MAC.send(p_ou,&msg_buf);
  //NETSTACK_MAC.send(p_ou,NULL);
}
/*---------------------------------------------------------------------------*/
void p_ou(void *ptr, int status, int transmissions){
  struct msg * output = (struct msg *) ptr;
  if(status != MAC_TX_OK) printf("SPD: packet tx fail %d %d %u\n",status, transmissions, output->panid);
  else printf("SPD: packet tx %d %u\n", transmissions,  output->panid);
}
/*---------------------------------------------------------------------------*/
void p_in(){
  //if(packetbuf_attr(PACKETBUF_ATTR_FRAME_TYPE) == FRAME802154_DATAFRAME){
  //  struct msg * input = (struct msg *) packetbuf_dataptr();
  //  printf("SPD: packet rx %u\n",input->panid);
  //}
}
/*---------------------------------------------------------------------------*/
PROCESS(node_process, "spd-RPL Node");
AUTOSTART_PROCESSES(&node_process);
/*---------------------------------------------------------------------------*/
static void schedule_init(){
  return;
  sf_eb = tsch_schedule_add_slotframe(1,104);
  sf_data = tsch_schedule_add_slotframe(0,31);

  tsch_schedule_add_link(sf_eb, LINK_OPTION_TX | LINK_OPTION_RX | LINK_OPTION_SHARED, LINK_TYPE_ADVERTISING, &tsch_broadcast_address, 1,1);
  uint8_t opt;
  if (node_id == 1 || node_id == 4) {opt = LINK_OPTION_RX| LINK_OPTION_SHARED;}
  else {opt = LINK_OPTION_TX| LINK_OPTION_SHARED;}
  tsch_schedule_add_link(sf_data, opt , LINK_TYPE_NORMAL, &dest, 0,0);
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(node_process, ev, data)
{

  PROCESS_BEGIN();

  int is_coordinator;
  printf("SPD: dest is n4\n");
  linkaddr_copy(&dest,&n4);

  is_coordinator = (linkaddr_cmp(&linkaddr_node_addr,&n4));

  if(is_coordinator) {
    NETSTACK_ROUTING.root_start();
  }
  schedule_init();

  NETSTACK_MAC.on();

  static struct etimer et;
  etimer_set(&et, CLOCK_SECOND);
  while(1) {
    if(node_id != 4 && tsch_is_associated){
      nt_send_packet();
    }
    PROCESS_YIELD_UNTIL(etimer_expired(&et));
    etimer_reset(&et);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
