/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "dns.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static respuesta *
_consultar_1 (char * *argp, struct svc_req *rqstp)
{
	return (consultar_1_svc(*argp, rqstp));
}

static int *
_registrar_1 (registrar_1_argument *argp, struct svc_req *rqstp)
{
	return (registrar_1_svc(argp->arg1, argp->arg2, rqstp));
}

static int *
_liberar_1 (char * *argp, struct svc_req *rqstp)
{
	return (liberar_1_svc(*argp, rqstp));
}

static void
dns_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		char *consultar_1_arg;
		registrar_1_argument registrar_1_arg;
		char *liberar_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case consultar:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_respuesta;
		local = (char *(*)(char *, struct svc_req *)) _consultar_1;
		break;

	case registrar:
		_xdr_argument = (xdrproc_t) xdr_registrar_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _registrar_1;
		break;

	case liberar:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _liberar_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	u_long server_id   = 0;
	u_long listen_port = DNS;
	
	if(argc < 2) {
		printf("Uso: %s <dns id>\n", *argv);
		exit(1);
	}

	server_id = atol(argv[1]);
	listen_port += (server_id > 255) ? 255 : (server_id & 0x200000FF);

	printf("Server %ld starting on port %#010lx!\n", server_id, listen_port);

	register SVCXPRT *transp;

	pmap_unset (listen_port, DNSv1);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, listen_port, DNSv1, dns_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DNS, DNSv1, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, listen_port, DNSv1, dns_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DNS, DNSv1, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
