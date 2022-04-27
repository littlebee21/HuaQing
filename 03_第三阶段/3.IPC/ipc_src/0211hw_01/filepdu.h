#ifndef FILE_PDU_H
#define FILE_PDU_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIFO_C_TO_S "/tmp/cs_fifo"
#define FIFO_S_TO_C "/tmp/sc_fifo"

struct filepdu
{
	int len;//整个PDU的字节数
        int type;//1-表示获取文件内容的请求 2-表示获取文件内容的回应 3-表示获取文件大小的请求 4->表示获取文件大小的回应
        char data[1];//本成员开始存放每种type对应的数据，具体如下：
                     /*type为1时：字符串，字符串内容为文件名
                       type为2时：前4个字节为整数，该整数表示处理是否成功，0表示成功，其它值表示失败
                                  后续字节，如果成功获得文件内容则存放文件内容，否则无本部分
                       type为3时：字符串，字符串内容为文件名
                       type为4时：前4个字节为整数，该整数表示处理是否成功，0表示成功，其它值表示失败
                                  后续字节，如果成功获得文件内容则用4个字节存放文件大小，否则无本>部分
                     */
};

struct filepdu *create_getcontent_request(char *filename);

struct filepdu *create_getlength_request(char *filename);

struct filepdu *create_getcontent_response(char *filename);

struct filepdu *create_getlength_response(char *filename);

int send_filepdu(int fd,struct filepdu *pdu);

struct filepdu *recv_filepdu(int fd);

int destroy_filepdu(struct filepdu *pdu);

enum filepdu_type
{
	TYPE_GET_CONTENT_REQ = 1,
	TYPE_GET_CONTENT_RSP,
	TYPE_GET_FILELEN_REQ,
	TYPE_GET_FILELEN_RSP
};

#endif
