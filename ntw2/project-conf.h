
#ifndef __PROJECT_CONF_H__
#define __PROJECT_CONF_H__

/* Set to enable TSCH security */
#ifndef WITH_SECURITY
#define WITH_SECURITY 0
#endif /* WITH_SECURITY */

/* USB serial takes space, free more space elsewhere */
#define SICSLOWPAN_CONF_FRAG 0
#define UIP_CONF_BUFFER_SIZE 160

/*******************************************************/
/******************* Configure TSCH ********************/
/*******************************************************/


/* IEEE802.15.4 PANID */
#define IEEE802154_CONF_PANID 0x0002
#define TSCH_CONF_JOIN_MY_PANID_ONLY 1
#define TSCH_CONF_DEFAULT_HOPPING_SEQUENCE TSCH_HOPPING_SEQUENCE_1_1
//#define TSCH_CONF_DEFAULT_HOPPING_SEQUENCE TSCH_HOPPING_SEQUENCE_4_4
//#define TSCH_CONF_DEFAULT_HOPPING_SEQUENCE TSCH_HOPPING_SEQUENCE_16_16

/* Do not start TSCH at init, wait for NETSTACK_MAC.on() */
#define TSCH_CONF_AUTOSTART 0

/* 6TiSCH minimal schedule length.
 * Larger values result in less frequent active slots: reduces capacity and saves energy. */
 #define TSCH_SCHEDULE_CONF_WITH_6TISCH_MINIMAL 1
 #define TSCH_SCHEDULE_CONF_DEFAULT_LENGTH 11
 #define TSCH_CONF_MAC_MAX_FRAME_RETRIES 7

void slot_rx();
//#define TSCH_CALLBACK_SLOT_RX_SPD slot_rx
void p_in();
#define MAC_CALLBACK_INPUT p_in

#define TSCH_CONF_DEFAULT_TIMESLOT_LENGTH 1

#if WITH_SECURITY

/* Enable security */
#define LLSEC802154_CONF_ENABLED 1

#endif /* WITH_SECURITY */

/*******************************************************/
/************* Other system configuration **************/
/*******************************************************/

/* Logging */
#define LOG_CONF_LEVEL_RPL                         LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_TCPIP                       LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_IPV6                        LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_6LOWPAN                     LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_MAC                         LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_FRAMER                      LOG_LEVEL_WARN//LOG_LEVEL_DBG
#define TSCH_LOG_CONF_PER_SLOT                     0//1

#endif /* __PROJECT_CONF_H__ */
