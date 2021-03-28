#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "utils/errors.h"
#include "utils/utils.h"
#include <arpa/inet.h>
int main (int argc, char *argv[]) {
        bool is_dnsname = false; // Boolean for check if dns name promted or ip address
        bool valid_args = true;  // Boolean for check if args are valid
        struct sockaddr_in sa;   // Stuct which holds ip address. More in netinet/in.h. https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
        struct hostent *he;	 // Stuct which holds ip info from gethostbyname. More in netdb.h. https://www.gta.ufrj.br/ensino/eel878/sockets/gethostbynameman.html
        int sockfd;		 // File descriptor for socket
        int logfd;		 // File decriptor for log file
        in_addr_t dst_addr;	 // Variable which holds IPv4 destination address
        char *dst_hostname;
	char *dst_ip;
	bool verbose_output;
        printf("%s\n", "Ping starts");
        if (argc < 2) {
                printf("%s\n", "You have not specified address to send ICMP packet");
                exit(NO_ADDR);
        }
        printf("%s\n", "Validate other args");
        if(!validate_args(&is_dnsname, &dst_hostname, &dst_ip, argc, argv, &verbose_output)) {
		//logfd = create_log();
        	//if (logfd == -1) {
               		//diag(); NO IDEA WHAT SHOULD BE IN THIS FUNCTION
                	//exit(LOG_CREATION_ERROR);
        	//} else {
		//log(logfd);
                printf("%s\n", "Args are not valid. More complex output will be in validate_args function. Program will exit now!");
                exit(ARGS_NOT_VALID);
		//}
        }
        //logfd = create_log();
	//if (logfd == -1) {
		//diag(); NO IDEA WHAT SHOULD BE IN THIS FUNCTION
		//exit(LOG_CREATION_ERROR);
	//}
	// log REPLACE PRINTF WITH LOG EVERYWHERE
        printf("%s\n", "Check if next arg is dns name or ip address");
        if (is_dnsname) {
                dst_ip = getIP(&(*dst_hostname));
		// log LOGSOMETHING 
        }
        dst_addr = inet_addr(dst_ip);
        int result = send_request_icmp(dst_addr, &sockfd);
	int res = get_reply(sockfd);
        return 0;
}
