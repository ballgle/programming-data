// FFmpegWindows.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

//C/C++��ָ࣬ʾ����������C���Խ��б���
extern "C"
{
#include "libavcodec\avcodec.h"
};

void _main(){
	printf("%s \n", avcodec_configuration());
	system("pause");
}
