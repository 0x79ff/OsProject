/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _FS_H_RPCGEN
#define _FS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct GetcurSetnoerr_re {
	char name[50];
};
typedef struct GetcurSetnoerr_re GetcurSetnoerr_re;

struct Ls_re {
	char name[1024];
	char reMessage[100];
};
typedef struct Ls_re Ls_re;

struct Fopen_s {
	char name[50];
};
typedef struct Fopen_s Fopen_s;

struct Fopen_re {
	char reMessage[100];
	int fd;
};
typedef struct Fopen_re Fopen_re;

struct Fclose_s {
	int fd;
};
typedef struct Fclose_s Fclose_s;

struct Fclose_re {
	char reMessage[100];
};
typedef struct Fclose_re Fclose_re;

struct Fread_s {
	int fd;
	int length;
};
typedef struct Fread_s Fread_s;

struct Fread_re {
	char x[1024];
	int count;
};
typedef struct Fread_re Fread_re;

struct Fwrite_s {
	int fd;
	char x[1024];
	int length;
};
typedef struct Fwrite_s Fwrite_s;

struct Fwrite_re {
	char reMessage[100];
	int count;
};
typedef struct Fwrite_re Fwrite_re;

struct Flseek_s {
	int fd;
	int pos;
};
typedef struct Flseek_s Flseek_s;

struct Flseek_re {
	char reMessage[100];
};
typedef struct Flseek_re Flseek_re;

struct Fcreate_s {
	char name[50];
};
typedef struct Fcreate_s Fcreate_s;

struct Fcreate_re {
	char reMessage[100];
	int fd;
};
typedef struct Fcreate_re Fcreate_re;

struct Mkdir_s {
	char name[50];
};
typedef struct Mkdir_s Mkdir_s;

struct Mkdir_re {
	char reMessage[100];
};
typedef struct Mkdir_re Mkdir_re;

struct Fdelete_s {
	char name[50];
};
typedef struct Fdelete_s Fdelete_s;

struct Fdelete_re {
	char reMessage[100];
};
typedef struct Fdelete_re Fdelete_re;

struct Cd_s {
	char name[50];
};
typedef struct Cd_s Cd_s;

struct Cd_re {
	char reMessage[100];
};
typedef struct Cd_re Cd_re;

struct Shutdown_re {
	char reMessage[100];
};
typedef struct Shutdown_re Shutdown_re;

#define Init_PROG 0x2345111f
#define Init_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Init 1
extern  void * init_1(void *, CLIENT *);
extern  void * init_1_svc(void *, struct svc_req *);
extern int init_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Init 1
extern  void * init_1();
extern  void * init_1_svc();
extern int init_prog_1_freeresult ();
#endif /* K&R C */

#define GetcurSetnoerr_PROG 0x23451110
#define GetcurSetnoerr_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define GetcurSetnoerr 1
extern  GetcurSetnoerr_re * getcursetnoerr_1(void *, CLIENT *);
extern  GetcurSetnoerr_re * getcursetnoerr_1_svc(void *, struct svc_req *);
extern int getcursetnoerr_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GetcurSetnoerr 1
extern  GetcurSetnoerr_re * getcursetnoerr_1();
extern  GetcurSetnoerr_re * getcursetnoerr_1_svc();
extern int getcursetnoerr_prog_1_freeresult ();
#endif /* K&R C */

#define Ls_PROG 0x23451111
#define Ls_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Ls 1
extern  Ls_re * ls_1(void *, CLIENT *);
extern  Ls_re * ls_1_svc(void *, struct svc_req *);
extern int ls_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Ls 1
extern  Ls_re * ls_1();
extern  Ls_re * ls_1_svc();
extern int ls_prog_1_freeresult ();
#endif /* K&R C */

#define Fopen_PROG 0x23451112
#define Fopen_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Fopen 1
extern  Fopen_re * fopen_1(Fopen_s *, CLIENT *);
extern  Fopen_re * fopen_1_svc(Fopen_s *, struct svc_req *);
extern int fopen_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Fopen 1
extern  Fopen_re * fopen_1();
extern  Fopen_re * fopen_1_svc();
extern int fopen_prog_1_freeresult ();
#endif /* K&R C */

#define Fclose_PROG 0x23451113
#define Fclose_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Fclose 1
extern  Fclose_re * fclose_1(Fclose_s *, CLIENT *);
extern  Fclose_re * fclose_1_svc(Fclose_s *, struct svc_req *);
extern int fclose_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Fclose 1
extern  Fclose_re * fclose_1();
extern  Fclose_re * fclose_1_svc();
extern int fclose_prog_1_freeresult ();
#endif /* K&R C */

#define Fread_PROG 0x23451114
#define Fread_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Fread 1
extern  Fread_re * fread_1(Fread_s *, CLIENT *);
extern  Fread_re * fread_1_svc(Fread_s *, struct svc_req *);
extern int fread_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Fread 1
extern  Fread_re * fread_1();
extern  Fread_re * fread_1_svc();
extern int fread_prog_1_freeresult ();
#endif /* K&R C */

#define Fwrite_PROG 0x23451115
#define Fwrite_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Fwrite 1
extern  Fwrite_re * fwrite_1(Fwrite_s *, CLIENT *);
extern  Fwrite_re * fwrite_1_svc(Fwrite_s *, struct svc_req *);
extern int fwrite_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Fwrite 1
extern  Fwrite_re * fwrite_1();
extern  Fwrite_re * fwrite_1_svc();
extern int fwrite_prog_1_freeresult ();
#endif /* K&R C */

#define Flseek_PROG 0x23451116
#define Flseek_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Flseek 1
extern  Flseek_re * flseek_1(Flseek_s *, CLIENT *);
extern  Flseek_re * flseek_1_svc(Flseek_s *, struct svc_req *);
extern int flseek_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Flseek 1
extern  Flseek_re * flseek_1();
extern  Flseek_re * flseek_1_svc();
extern int flseek_prog_1_freeresult ();
#endif /* K&R C */

#define Fcreate_PROG 0x23451117
#define Fcreate_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Fcreate 1
extern  Fcreate_re * fcreate_1(Fcreate_s *, CLIENT *);
extern  Fcreate_re * fcreate_1_svc(Fcreate_s *, struct svc_req *);
extern int fcreate_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Fcreate 1
extern  Fcreate_re * fcreate_1();
extern  Fcreate_re * fcreate_1_svc();
extern int fcreate_prog_1_freeresult ();
#endif /* K&R C */

#define Mkdir_PROG 0x23451118
#define Mkdir_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Mkdir 1
extern  Mkdir_re * mkdir_1(Mkdir_s *, CLIENT *);
extern  Mkdir_re * mkdir_1_svc(Mkdir_s *, struct svc_req *);
extern int mkdir_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Mkdir 1
extern  Mkdir_re * mkdir_1();
extern  Mkdir_re * mkdir_1_svc();
extern int mkdir_prog_1_freeresult ();
#endif /* K&R C */

#define Fdelete_PROG 0x23451119
#define Fdelete_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Fdelete 1
extern  Fdelete_re * fdelete_1(Fdelete_s *, CLIENT *);
extern  Fdelete_re * fdelete_1_svc(Fdelete_s *, struct svc_req *);
extern int fdelete_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Fdelete 1
extern  Fdelete_re * fdelete_1();
extern  Fdelete_re * fdelete_1_svc();
extern int fdelete_prog_1_freeresult ();
#endif /* K&R C */

#define Cd_PROG 0x2345111a
#define Cd_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Cd 1
extern  Cd_re * cd_1(Cd_s *, CLIENT *);
extern  Cd_re * cd_1_svc(Cd_s *, struct svc_req *);
extern int cd_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Cd 1
extern  Cd_re * cd_1();
extern  Cd_re * cd_1_svc();
extern int cd_prog_1_freeresult ();
#endif /* K&R C */

#define Shutdown_PROG 0x2345111d
#define Shutdown_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define Shutdown 1
extern  Shutdown_re * shutdown_1(void *, CLIENT *);
extern  Shutdown_re * shutdown_1_svc(void *, struct svc_req *);
extern int shutdown_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Shutdown 1
extern  Shutdown_re * shutdown_1();
extern  Shutdown_re * shutdown_1_svc();
extern int shutdown_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_GetcurSetnoerr_re (XDR *, GetcurSetnoerr_re*);
extern  bool_t xdr_Ls_re (XDR *, Ls_re*);
extern  bool_t xdr_Fopen_s (XDR *, Fopen_s*);
extern  bool_t xdr_Fopen_re (XDR *, Fopen_re*);
extern  bool_t xdr_Fclose_s (XDR *, Fclose_s*);
extern  bool_t xdr_Fclose_re (XDR *, Fclose_re*);
extern  bool_t xdr_Fread_s (XDR *, Fread_s*);
extern  bool_t xdr_Fread_re (XDR *, Fread_re*);
extern  bool_t xdr_Fwrite_s (XDR *, Fwrite_s*);
extern  bool_t xdr_Fwrite_re (XDR *, Fwrite_re*);
extern  bool_t xdr_Flseek_s (XDR *, Flseek_s*);
extern  bool_t xdr_Flseek_re (XDR *, Flseek_re*);
extern  bool_t xdr_Fcreate_s (XDR *, Fcreate_s*);
extern  bool_t xdr_Fcreate_re (XDR *, Fcreate_re*);
extern  bool_t xdr_Mkdir_s (XDR *, Mkdir_s*);
extern  bool_t xdr_Mkdir_re (XDR *, Mkdir_re*);
extern  bool_t xdr_Fdelete_s (XDR *, Fdelete_s*);
extern  bool_t xdr_Fdelete_re (XDR *, Fdelete_re*);
extern  bool_t xdr_Cd_s (XDR *, Cd_s*);
extern  bool_t xdr_Cd_re (XDR *, Cd_re*);
extern  bool_t xdr_Shutdown_re (XDR *, Shutdown_re*);

#else /* K&R C */
extern bool_t xdr_GetcurSetnoerr_re ();
extern bool_t xdr_Ls_re ();
extern bool_t xdr_Fopen_s ();
extern bool_t xdr_Fopen_re ();
extern bool_t xdr_Fclose_s ();
extern bool_t xdr_Fclose_re ();
extern bool_t xdr_Fread_s ();
extern bool_t xdr_Fread_re ();
extern bool_t xdr_Fwrite_s ();
extern bool_t xdr_Fwrite_re ();
extern bool_t xdr_Flseek_s ();
extern bool_t xdr_Flseek_re ();
extern bool_t xdr_Fcreate_s ();
extern bool_t xdr_Fcreate_re ();
extern bool_t xdr_Mkdir_s ();
extern bool_t xdr_Mkdir_re ();
extern bool_t xdr_Fdelete_s ();
extern bool_t xdr_Fdelete_re ();
extern bool_t xdr_Cd_s ();
extern bool_t xdr_Cd_re ();
extern bool_t xdr_Shutdown_re ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_FS_H_RPCGEN */