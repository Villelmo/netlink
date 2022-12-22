# netlink
A quick and clean API for NetLink networking configuring.  NLINLINE (netlink inline) is a library of inline functions providing C programmers with very handy functions to configure network stacks. NLINLINE is entirely implemented in a header file, nlinline.h.  

NLinline provides the following functions:

* `nlinline_if_nametoindex(const char *ifname);` return the index of the network interface whose name is `ifname`

* `int nlinline_iplink_add(const char *ifname, unsigned int ifindex, const char *type, const char *data);` add a (virtual) link

* `int nlinline_iplink_del(const char *ifname, unsigned int ifindex);` remove a link

* `int nlinline_linksetupdown(unsigned int ifindex, int updown);` turn the interface `ifindex` up (`updown == 1`) or down (`updown == 0`).

* `int nlinline_ipaddr_add(int family, void *addr, int prefixlen, int ifindex)` add an IP address to the interface `ifindex`. It supports IPv4 (`family == AF_INET`) and IPv6 `(family == AF_INET6)`.

* `int nlinline_ipaddr_del(int family, void *addr, int prefixlen, int ifindex)` remove the IP address from the interface `ifindex`. It supports IPv4 (`family == AF_INET`) and IPv6 `(family == AF_INET6)`.

* `int nlinline_iproute_add(int family, void *dst_addr, int dst_prefixlen, void *gw_addr, int ifindex);` add a static route to `dst_addr`/`dst_prefixlen` network through the gateway `gw_addr`. If `dst_addr == NULL` it adds a default route. `ifindex` must be specified when `gw_addr` is an IPv6 link local address.

* `int nlinline_iproute_del(int family, void *dst_addr, int dst_prefixlen, void *gw_addr, int ifindex);` remove the static route to `dst_addr`/`dst_prefixlen` network through the gateway `gw_addr`.

* `int nlinline_linksetaddr(unsigned int ifindex, void *macaddr);` set the MAC address of the interface `ifindex`.

* `int nlinline_linkgetaddr(unsigned int ifindex, void *macaddr);` get the MAC address of the interface `ifindex`.

* `int nlinline_linksetmtu(unsigned int ifindex, unsigned int mtu);` set the MTU of the interface `ifindex`.

IP addresses are `void *` arguments, any sequence of 4 or 16 bytes (in network byte order) is a legal IPv4 or IPv6 address respectively.

### Netlink + inline

* NLINLINE is a simple way to configure networking for network namespaces and *Internet of Threads* programs.
* NLINLINE does not add dependencies at run-time. It is useful for security critical applications (like PAM modules)
* NLINLINE uses netlink only, it does not depends on the obsolete netdevice (ioctl) API.
* Only the code of referenced inline functions enters in the object and executable code.
