void myfs_InitSystem();
void myfs_HelpMenu();
void myfs_Ls();
void myfs_Fopen(char *name,int mode);
void myfs_Fclose(int fd);
void myfs_Fread(int fd, char *buffer, int length);
void myfs_Fwrite(int fd, char *buffer, int length);
void myfs_Flseek(int fd,int position,int mode);
void myfs_Fcreate(char* name,int mode);
void myfs_Mkdir(char* name);
void myfs_Fdelete(char *name);
void myfs_Cd(char *name);
void myfs_Fin(char *extername, char* intername);
void myfs_Fout(char* intername,char *extername);

