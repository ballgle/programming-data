#include "stdafx.h"
#include <stdio.h>


extern "C"{
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <libavformat/avio.h>
}

//--------------------------------------------
// ffmpeg ��ȡ��Ƶ��
//--------------------------------------------

#define ADTS_HEADER_LEN 7;

void adts_header(char* szAdtsHeader, int dataLen) {
	int audio_object_type = 2;
	int sampling_frequency_index = 7;
	int channel_config = 2;

	int adtsLen = dataLen + 7;

	szAdtsHeader[0] = 0xff;       //syncword:0xfff                          ��8bits
	szAdtsHeader[1] = 0xf0;       //syncword:0xfff                          ��4bits
	szAdtsHeader[1] |= (0 << 3);  //MPEG Version:0 for MPEG-4,1 for MPEG-2  1bit
	szAdtsHeader[1] |= (0 << 1);  //Layer:0                                 2bits
	szAdtsHeader[1] |= 1;         //protection absent:1                     1bit

	szAdtsHeader[2] = (audio_object_type - 1) << 6;             //profile:audio_object_type - 1                      2bits
	szAdtsHeader[2] |= (sampling_frequency_index & 0x0f) << 2;  //sampling frequency index:sampling_frequency_index  4bits
	szAdtsHeader[2] |= (0 << 1);                                //private bit:0                                      1bit
	szAdtsHeader[2] |= (channel_config & 0x04) >> 2;            //channel configuration:channel_config               ��1bit

	szAdtsHeader[3] = (channel_config & 0x03) << 6;  //channel configuration:channel_config      ��2bits
	szAdtsHeader[3] |= (0 << 5);                     //original��0                               1bit
	szAdtsHeader[3] |= (0 << 4);                     //home��0                                   1bit
	szAdtsHeader[3] |= (0 << 3);                     //copyright id bit��0                       1bit
	szAdtsHeader[3] |= (0 << 2);                     //copyright id start��0                     1bit
	szAdtsHeader[3] |= ((adtsLen & 0x1800) >> 11);   //frame length��value   ��2bits

	szAdtsHeader[4] = (uint8_t)((adtsLen & 0x7f8) >> 3);  //frame length:value    �м�8bits
	szAdtsHeader[5] = (uint8_t)((adtsLen & 0x7) << 5);    //frame length:value    ��3bits
	szAdtsHeader[5] |= 0x1f;                              //buffer fullness:0x7ff ��5bits
	szAdtsHeader[6] = 0xfc;
}

// gcc -g ffmpeg-extra-audio.c -o extra_audio.out `pkg-config --libs libavutil libavformat`
// ./extra_audio.out /home/ztiany/code/leaning/1.mp4 1.aac
int main(int argc, char const* argv[]) {
	//������������
	av_log_set_level(AV_LOG_INFO);

	//��ȡ����
	if (argc < 3) {
		av_log(NULL, AV_LOG_ERROR, "arguments count must more than 3.\n");
		system("pause");
		return -1;
	}
	char const* src = argv[1];
	char const* dest = argv[2];

	//����ͨ�÷���ֵ����
	int ret = 0;
	char buf[256];
	
	//��ʼ������
	av_register_all();

	//��ʼ����ʽ�����ģ����򿪶�ý���ļ���
	AVFormatContext* fmt_context = NULL;
	ret = avformat_open_input(&fmt_context, src, NULL, NULL);
	if (ret < 0) {
		av_strerror(ret, buf, sizeof(buf));
		av_log(NULL, AV_LOG_ERROR, "Can not open media file %s, error: %s\n", src, buf);
		system("pause");
		return -1;
	}
	//�����ý����Ϣ
	av_dump_format(fmt_context, 0, src, 0);

	//��ȡStream���ɹ�����Stream������
	ret = av_find_best_stream(fmt_context, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (ret < 0) {
		av_strerror(ret, buf, sizeof(buf));
		av_log(NULL, AV_LOG_ERROR, "Can not find bease stream %s\n", buf);
		avformat_close_input(&fmt_context);
		system("pause");
		return -1;
	}

	int audio_stream_index = ret;

	//��Ŀ���ļ�
	FILE* dest_fd = fopen(dest, "wb" /*wb д������ */);
	if (!dest_fd) {
		av_log(NULL, AV_LOG_ERROR, "Can not open dest file\n");
		avformat_close_input(&fmt_context);
		system("pause");
		return -1;
	}

	AVPacket pkt;
	//��ʼ��packet
	av_init_packet(&pkt);
	while (av_read_frame(fmt_context, &pkt) >= 0) {

		if (pkt.stream_index == audio_stream_index) {
			//ÿ��strem����Ҫһ�� adts ͷ������Ϣ����������ʡ��������ȣ����� ffplay �޷����š�
			char adts_header_buf[7];
			adts_header(adts_header_buf, pkt.size);
			fwrite(adts_header_buf, 1, 7, dest_fd);

			int len = fwrite(pkt.data, 1, pkt.size, dest_fd);
			if (len != pkt.size) {
				av_log(NULL, AV_LOG_WARNING, "warning, length of data is not equal size of pkt\n");
			}

			//�ͷ���Դ
			av_packet_unref(&pkt);
		}
	}

	avformat_close_input(&fmt_context);
	fclose(dest_fd);
	system("pause");
	return 0;
}
