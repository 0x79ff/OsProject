# 定义编译器和编译选项
CC = g++
CFLAGS = -g 

# 定义目录
RPC_DIR = rpc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# 定义源文件和目标文件
RPC_SRCS = $(wildcard $(RPC_DIR)/*.x)


all: rpc_compile $(BIN_DIR)/FS_client $(BIN_DIR)/FS_server

rpc_compile:
# 编译RPC文件
	cd $(RPC_DIR) && rpcgen -C $(notdir $(RPC_SRCS))
	mv rpc/FS_clnt.c rpc/FS_clnt.cpp
	mv rpc/FS_svc.c rpc/FS_svc.cpp
	mv rpc/FS_xdr.c rpc/FS_xdr.cpp
	$(CC) $(CFLAGS) -DRPC_SVC_FG -c -o obj/FS_clnt.o   rpc/FS_clnt.cpp
	$(CC) $(CFLAGS) -DRPC_SVC_FG -c -o obj/FS_client.o rpc/FS_client.cpp
	$(CC) $(CFLAGS) -DRPC_SVC_FG -c -o obj/FS_xdr.o    rpc/FS_xdr.cpp
	$(CC) $(CFLAGS) -DRPC_SVC_FG -c -o obj/FS_svc.o    rpc/FS_svc.cpp
	$(CC) $(CFLAGS) -DRPC_SVC_FG -c -o obj/FS_server.o rpc/FS_server.cpp
#	for file in $(RPC_DIR)/*.c ;do \
#		mv $$file $(RPC_DIR)/$$(basename $$file .c).cpp; \
#	done

# 编译客户端程序
$(BIN_DIR)/FS_client: $(OBJ_DIR)/FS_clnt.o $(OBJ_DIR)/FS_client.o $(OBJ_DIR)/FS_xdr.o
	$(CC) $(CFLAGS) -DRPC_SVC_FG -o $@ $^ -lnsl -DRPC_SVC_FG

# 编译服务端程序
$(BIN_DIR)/FS_server: $(OBJ_DIR)/FS_svc.o $(OBJ_DIR)/FS_server.o $(OBJ_DIR)/FS_xdr.o $(OBJ_DIR)/BufferManager.o $(OBJ_DIR)/OpenFileManager.o $(OBJ_DIR)/Kernel.o $(OBJ_DIR)/FileSystem.o $(OBJ_DIR)/DiskDriver.o $(OBJ_DIR)/File.o $(OBJ_DIR)/Inode.o $(OBJ_DIR)/FileManager.o $(OBJ_DIR)/Utility.o $(OBJ_DIR)/mainFS.o 
	$(CC) $(CFLAGS) -DRPC_SVC_FG -o $@ $^ -lnsl -DRPC_SVC_FG


#编译源文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -w -c -o $@ $^


# 清理规则
clean:
	rm -f $(RPC_DIR)/*.h $(RPC_DIR)/FS_clnt.cpp $(RPC_DIR)/FS_svc.cpp $(RPC_DIR)/FS_xdr.cpp $(OBJ_DIR)/*.o $(BIN_DIR)/FS_client $(BIN_DIR)/FS_server
