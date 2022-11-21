/***********************************************************************/
/*  システム名  :ImageConverterCheckTest                                          */
/*  FILE  　　    :ImageConverterCheckTest.cpp                                   */
/*  DATE        :Tue,Nov,2022　　　　　 　　                                                 */
/*  DESCRIPTION :                                                                              */
/*                                                                                                          */
/*  Author      : ichihara                                                                        */
/*                                                                                                          */
/***********************************************************************/

#include <iostream>
#include <conio.h>
#include "ImageConverterCheckTest.h"

int main()
{
	int err = 0;
	winSocketCl* winCl = new winSocketCl();
	sonobuoy_buffer* snvi = new sonobuoy_buffer();

	winCl->SetServer();
		std::cout << "setserver:ok" << std::endl;
	
	winCl->MakeSocket();
		std::cout << "makeserver:ok" << std::endl;

	err = winCl->ConnToServer();
	if (err) {
		int errCode =WSAGetLastError();
		std::cout << errCode << std::endl;
	}
	else {
		std::cout << "connect:ok" << std::endl;
	}

	char* srcBuffer;
	srcBuffer = snvi->GetBufferSnvi_src();
	snvi->FillMemSnvi_src('f');

	char* recvBuffer = snvi->GetBufferSnvi_recv();
	
	printf("send start\n");
	winCl->SendToServer(srcBuffer);
	printf("送信したもの：%s\n送信したサイズ：%d\n", srcBuffer, sizeof(*srcBuffer));
	printf("send fin\n\n");
	
	char* packetBuffer;
	packetBuffer = snvi->GetBufferSnvi_src();		
	int packetBufferSize = PACKETSIZE;
	int recv_cnt = 0;
	int total_recv = 0;

	printf("recv start\n");

	
	do{
		memset(packetBuffer, 0, PACKETSIZE);	//小分けバッファを0で初期化
		recv_cnt= winCl->RecvFromServer(packetBuffer, packetBufferSize);//受信、受信バイト数保持
		printf("受け取ったもの：%s  受け取ったサイズ：%d\n", packetBuffer, recv_cnt);
		snvi->SetRecv_Cnt(recv_cnt);//sonobuoyクラスに受信バイト数格納
		snvi->SetBufferSnvi_recv(packetBuffer);	//小分けバッファから大きいバッファに移す
		total_recv += recv_cnt;
		if (total_recv >= FRAMESIZE)break;
	} while (!_kbhit());

	//
	recvBuffer[0] = 0;
	printf("\nrecv fin\n\n");
	snvi->CompareData();

	delete winCl;
	return 0;
}
