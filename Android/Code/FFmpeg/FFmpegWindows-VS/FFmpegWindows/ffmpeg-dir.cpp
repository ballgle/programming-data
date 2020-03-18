#include "stdafx.h"
#include <stdio.h>

extern "C"{
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <libavformat/avio.h>
}

//--------------------------------------------
//ffmpeg Ŀ¼����
//--------------------------------------------

/*
������
avio_open_dir
avio_read_dir
avio_close_dir
avio_free_directory_entry

�ṹ�壺
AVIODirContext ����Ŀ¼������
AVIODirEntry Ŀ¼����ڴ���ļ������ļ���С��
*/

//gcc -g ffmpeg-dirs.c -o dirs.out `pkg-config --libs libavformat`
int dir_main() {
	av_log_set_level(AV_LOG_INFO);

	int ret;

	AVIODirContext *ctx = NULL;
	AVIODirEntry *entry = NULL;

	ret = avio_open_dir(&ctx, "./", NULL);

	if (ret <0){
		char buf[256];
		av_strerror(ret, buf, sizeof(buf));

		// ע��Windows�»᷵��-40��Ҳ����Function not implement������δʵ�֣�Ҳ����˵windows�²�֧�ִ˷���
		av_log(NULL, AV_LOG_ERROR, "failed to open dir: %s \n", buf);
		system("pause");
		return -1;
	}

	while (1){
		ret = avio_read_dir(ctx, &entry);
		if (ret <0){
			av_log(NULL, AV_LOG_ERROR, "failed to read dir");
			goto __fail;
		}
		if (!entry){
			break;
		}
		av_log(NULL, AV_LOG_INFO, "size = %ld, name = %s\n", entry->size, entry->name);
		avio_free_directory_entry(&entry);
	}

__fail:
	avio_close_dir(&ctx);

	system("pause");
	return 0;
}