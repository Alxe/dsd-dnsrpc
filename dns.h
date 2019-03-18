/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DNS_H_RPCGEN
#define _DNS_H_RPCGEN

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

struct respuesta {
	int errno;
	union {
		char *cadena;
	} respuesta_u;
};
typedef struct respuesta respuesta;

struct registrar_1_argument {
	char *arg1;
	char *arg2;
};
typedef struct registrar_1_argument registrar_1_argument;

#define DNS 0x20000000
#define DNSv1 1

#if defined(__STDC__) || defined(__cplusplus)
#define consultar 1
extern  respuesta * consultar_1(char *, CLIENT *);
extern  respuesta * consultar_1_svc(char *, struct svc_req *);
#define registrar 2
extern  int * registrar_1(char *, char *, CLIENT *);
extern  int * registrar_1_svc(char *, char *, struct svc_req *);
#define liberar 3
extern  int * liberar_1(char *, CLIENT *);
extern  int * liberar_1_svc(char *, struct svc_req *);
extern int dns_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define consultar 1
extern  respuesta * consultar_1();
extern  respuesta * consultar_1_svc();
#define registrar 2
extern  int * registrar_1();
extern  int * registrar_1_svc();
#define liberar 3
extern  int * liberar_1();
extern  int * liberar_1_svc();
extern int dns_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_respuesta (XDR *, respuesta*);
extern  bool_t xdr_registrar_1_argument (XDR *, registrar_1_argument*);

#else /* K&R C */
extern bool_t xdr_respuesta ();
extern bool_t xdr_registrar_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DNS_H_RPCGEN */