#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

extern "C"{
	#define __STDC_CONSTANT_MACROS
	#include <libavutil/log.h>
}

int _main(){

	//���������ȼ�
	av_log_set_level(AV_LOG_DEBUG);
	//��ӡlog
	av_log(NULL, AV_LOG_INFO, "...%s\n", "Hello World");
	//��ͣ
	system("pause");
	return EXIT_SUCCESS;

}