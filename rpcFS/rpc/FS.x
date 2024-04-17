/*init*/
program Init_PROG{
	version Init_VERS{
		void Init() = 1;
	} = 1;
} = 0x2345111f;

/*getcursetnoerr*/

struct GetcurSetnoerr_re{
	char name[50];
};

program GetcurSetnoerr_PROG{
	version GetcurSetnoerr_VERS{
		GetcurSetnoerr_re GetcurSetnoerr() = 1;
	} = 1;
} = 0x23451110;

/*1 Ls*/
struct Ls_re{
	char name[1024];
	char reMessage[100];
};

program Ls_PROG{
	version Ls_VERS{
		Ls_re Ls() = 1;
	} = 1;
} = 0x23451111;

/*2 Fopen*/
struct Fopen_s{
	char name[50];
};

struct Fopen_re{
	char reMessage[100];
	int fd;
};

program Fopen_PROG{
	version Fopen_VERS{
		Fopen_re Fopen(Fopen_s) = 1;
	} = 1;
} = 0x23451112;

/*3 Fclose*/
struct Fclose_s{
	int fd;
};

struct Fclose_re{
	char reMessage[100];
};

program Fclose_PROG{
	version Fclose_VERS{
		Fclose_re Fclose(Fclose_s) = 1;
	} = 1;
} = 0x23451113;


/*4 Fread*/
struct Fread_s{
	int fd;
	int length;
};

struct Fread_re{
	char x[1024];
	int count;
};

program Fread_PROG{
	version Fread_VERS{
		Fread_re Fread(Fread_s) = 1;
	} = 1;
} = 0x23451114;


/*5 Fwrite*/
struct Fwrite_s{
	int fd;
	char x[1024];
	int length;
};

struct Fwrite_re{
	char reMessage[100];
	int count;
};

program Fwrite_PROG{
	version Fwrite_VERS{
		Fwrite_re Fwrite(Fwrite_s) = 1;
	} = 1;
} = 0x23451115;

/*6 Flseek*/
struct Flseek_s{
	int fd;
	int pos;
};

struct Flseek_re{
	char reMessage[100];
};


program Flseek_PROG{
	version Flseek_VERS{
		Flseek_re Flseek(Flseek_s) = 1;
	} = 1;
} = 0x23451116;


/*7 Fcreate*/
struct Fcreate_s{
	char name[50];
};

struct Fcreate_re{
	char reMessage[100];
	int fd;
};

program Fcreate_PROG{
	version Fcreate_VERS{
		Fcreate_re Fcreate(Fcreate_s) = 1;
	} = 1;
} = 0x23451117;

/*8 Mkdir*/
struct Mkdir_s{
	char name[50];
};

struct Mkdir_re{
	char reMessage[100];
};

program Mkdir_PROG{
	version Mkdir_VERS{
		Mkdir_re Mkdir(Mkdir_s) = 1;
	} = 1;
} = 0x23451118;

/*9 Fdelete*/
struct Fdelete_s{
	char name[50];
};

struct Fdelete_re{
	char reMessage[100];
};

program Fdelete_PROG{
	version Fdelete_VERS{
		Fdelete_re Fdelete(Fdelete_s) = 1;
	} = 1;
} = 0x23451119;

/*10 Cd*/
struct Cd_s{
	char name[50];
};

struct Cd_re{
	char reMessage[100];
};

program Cd_PROG{
	version Cd_VERS{
		Cd_re Cd(Cd_s) = 1;
	} = 1;
} = 0x2345111a;

/*11 Fin*/

/*12 Fout*/


/*13 shutdown*/

struct Shutdown_re{
	char reMessage[100];
};

program Shutdown_PROG{
	version Shutdown_VERS{
		Shutdown_re Shutdown() = 1;
	} = 1;
} = 0x2345111d;


/*14 exit*/

/*15 help*/



