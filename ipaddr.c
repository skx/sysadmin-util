/**
 * ipaddr - Show the IP addresses associated with given devices.
 *
 * Usage:
 *   ipaddr [options]
 *
 * Options:
 *
 *   --all      Show all families.
 *   --ipv4     Show IPv4 addresses.
 *   --ipv6     Show IPv6 addresses.
 *   --device   Show only the given device.
 *
 * Examples:
 *
 *  $ ipaddr -d eth0 -4
 *  eth0 192.168.0.3
 *
 *  $ ipaddr -a
 *  lo 127.0.0.1
 *  eth0 192.168.0.3
 *  lo ::1
 *  eth0 fe80::62a4:4cff:fe2d:fab9
 *  teredo 2001:0:53ba:64c:301f:13f3:4fe4:3a0b
 *  teredo fe80::ffff:ffff:ffff
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <getopt.h>


int main (int argc, char * argv[])
{
    int c;

    /**
     * Flags.
     */
    char *dev = NULL;
    int show_ipv4 = 0;
    int show_ipv6 = 0;

    while (1)
    {
        static struct option long_options[] =
            {
                {"all",    no_argument, 0, 'a'},
                {"device", required_argument, 0, 'd'},
                {"ipv4",   no_argument, 0, '4'},
                {"ipv6",   no_argument, 0, '6'},
                {0, 0, 0, 0}
            };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "ad:46", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
        case '4':
            show_ipv4 = 1;
            break;
        case '6':
            show_ipv6 = 1;
            break;
        case 'a':
            show_ipv4 = 1;
            show_ipv6 = 1;
            break;
        case 'd':
            dev = strdup( optarg );
            break;
        case '?':
            /* getopt_long already printed an error message. */
            exit(1);
            break;

        default:
            fprintf( stderr, "Unknown argument" );
            exit (1);
        }
    }

    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        /**
         * If we have a non-null entry.
         */
        if ( ifa && ifa->ifa_addr )
        {

            /**
             * And it is IPv4 and we're showing IPv4 ..
             */
            if (ifa ->ifa_addr->sa_family==AF_INET && show_ipv4 )
            {

                tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
                char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

                if ( ( dev == NULL ) ||
                     ( strcmp( dev, ifa->ifa_name ) == 0 ) )
                    printf("%s %s\n", ifa->ifa_name, addressBuffer);
            }
            else if (ifa->ifa_addr->sa_family==AF_INET6 && show_ipv6 )
            {
                /**
                 * IPv6 address, and we're showing them.
                 */
                tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
                char addressBuffer[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                if ( ( dev == NULL ) ||
                     ( strcmp( dev, ifa->ifa_name ) == 0 ) )
                    printf("%s %s\n", ifa->ifa_name, addressBuffer);
            }
        }
    }

    if (ifAddrStruct!=NULL)
        freeifaddrs(ifAddrStruct);

    return 0;
}
