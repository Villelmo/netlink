#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/*#include <nlinline.h>*/

int main(int argc, char *argv[]){
	uint8_t ipv4addr[] = {192,168,2,2};
	uint8_t ipv4gw[] = {192,168,2,1};
	uint8_t ipv6addr[16] = {0x20,0x01,0x07,0x60,[15] = 0x02};
	uint8_t ipv6gw[16] = {0x20,0x01,0x07,0x60,[15] = 0x01};

	int ifindex = nlinline_if_nametoindex(argv[1]);
	if(ifindex > 0)
		printf("%d\n",ifindex);
	else{
		perror("nametoindex");
		return 1;
	}

	if (nlinline_linksetupdown(ifindex,1) < 0) // turn the interface ifinde up or down 
		perror("link up");
	if(nlinline_ipaddr_add(AF_INET,ipv4addr,24,ifindex) < 0) // add an IP address to the interface ifindex 
		perror("addr ipv4");
	if (nlinline_iproute_add(AF_INET, NULL, 0, ipv4gw,0) < 0) // add a static route to dst_addr / dst_prefixlen network through the gateway gw_addr
		perror("addr ipv6");
	if(nlinline_ipaddr_add(AF_INET6,ipv6addr,64,ifindex) < 0)
		perror("route ipv4");
	if(nlinline_iproute_add(AF_INET6,NULL,0,ipv6gw,0) < 0)
		perror("route ipv6");
	return 0;

}
