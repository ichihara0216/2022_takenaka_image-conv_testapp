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
	//int err = 0;

	wsaErr = WSAStartup(MAKEWORD(2, 0), &wsaData);

	winSocketCl* outward = new winSocketCl();			//行きのソケット
	winSocketCl* wayBack= new winSocketCl();		//帰りのソケット
	sonobuoy_buffer* snby = new sonobuoy_buffer();

	outward->SetServer();
	wayBack->SetServer();
	
	outward->MakeSocket();
	wayBack->MakeSocket();

	outward->ConnToServer();
	wayBack->ConnToServer();

	//if (err) {
	//	int errCode =WSAGetLastError();
	//	std::cout << errCode << std::endl;
	//}


	char* srcBuffer;
	srcBuffer = snby->GetBufferSnvi_src();
	snby->FillMemSnvi_src('f');

	char* recvBuffer = snby->GetBufferSnvi_recv();
	
	printf("send start\n");
	outward->SendToServer(srcBuffer);
	printf("送信したもの：%s\n送信したサイズ：%d\n", srcBuffer, sizeof(*srcBuffer));
	printf("send fin\n\n");
	
	char* packetBuffer;
	packetBuffer = snby->GetBufferSnvi_src();		
	int packetBufferSize = PACKETSIZE;
	int recv_cnt = 0;
	int total_recv = 0;

	printf("recv start\n");

	
	do{
		memset(packetBuffer, 0, PACKETSIZE);	//小分けバッファを0で初期化
		recv_cnt= outward->RecvFromServer(packetBuffer, packetBufferSize);//受信、受信バイト数保持
		printf("受け取ったもの：%s  受け取ったサイズ：%d\n", packetBuffer, recv_cnt);
		snby->SetRecv_Cnt(recv_cnt);//sonobuoyクラスに受信バイト数格納
		snby->SetBufferSnvi_recv(packetBuffer);	//小分けバッファから大きいバッファに移す
		total_recv += recv_cnt;
		if (total_recv >= FRAMESIZE)break;
	} while (!_kbhit());

	//
	recvBuffer[0] = 0;
	printf("\nrecv fin\n\n");
	snby->CompareData();

	delete outward;
	return 0;
}
