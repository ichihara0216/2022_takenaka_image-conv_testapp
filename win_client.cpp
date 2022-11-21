
/***********************************************************************
 * インクルードファイル
 ***********************************************************************/

#include<iostream>
#include<winsock2.h	>	//TCP/IP 用の WinSock 2 Protocol-Specific Annex ドキュメントで導入された定義が含まれており、IP アドレスの取得に使用される新しい関数と構造が含まれている
#include<stdio.h>
#include<WS2tcpip.h>
#include<chrono>
#include<thread>
#include "ImageConverterCheckTest.h"




#define SECONDCODE
#ifdef SECONDCODE


	winSocketCl::winSocketCl() {
		wsaData = { 0 };
		sock = 0;
		wsaErr = WSAStartup(MAKEWORD(2, 0), &wsaData);
		connectErr = 0;
		ser_addr = { 0 };
	}
	winSocketCl::~winSocketCl() {
		std::cout << "デストラクタ：" __FUNCTION__ << std::endl;
		WSACleanup();
	}


	void winSocketCl::SetServer() {
		ser_addr.sin_family = AF_INET;
		ser_addr.sin_port = htons(PORT_NUM_SERVER);
		inet_pton(AF_INET, IP_ADDR_SERVER, &ser_addr.sin_addr.S_un.S_addr);
	}

	int winSocketCl::MakeSocket() {
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			std::cout << "ソケット作成エラー" << std::endl;
			perror("socket");
			return 1;
		}
		return 0;
	}

	int winSocketCl::ConnToServer() {
		if ((connectErr = connect(sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr))) < 0) {
			std::cout << "コネクト失敗エラー" << std::endl;
			perror("connect");
			return 1;
		}
		return 0;
	}

	//void winSocketCl::RecvFromServer() {
	//	//char buf[1024];
	//	memset(buf, 0, sizeof(buf));
	//	int rs = recv(sock, buf, sizeof(buf), 0);
	//	std::cout << "受信した文字列：" << buf << std::endl << "受信した文字数：" << rs << std::endl;
	//	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//}

	int winSocketCl::RecvFromServer(char* packet_pt, int packet_size) {
		int rsize;
			rsize = recv(sock	, packet_pt, packet_size, 0);

			if (rsize < 0) {
				perror("recv");
				return 0;
			}
			else {
				//std::cout << "receive : %s" << *buf_pt << std::endl;
				return rsize;
			}
		}
	

	void winSocketCl::SendToServer(char* src) {
		//char buf[1024] = { 'e', 'u', 'r', 'a' };
		std::cout << "send contents ： " << src << "\nsend size : " <<sizeof(src)<< std:: endl;
		send(sock, src, FRAMESIZE, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}



#endif

#ifdef FIRSTCODE
class WinClient {
private:
	int cl_sock;				//ソケット
	struct sockaddr_in dst_addr; //接続先情報の構造体

protected:
	int err;

public:
	WinClient() {
		err = 0;
		/*ソケット接続先（サーバー）の設定*/
		cl_sock = 0;
		dst_addr.sin_family = AF_INET;
		dst_addr.sin_port = ::htons(1234);//通信ポート番号(port番号設定)
		dst_addr.sin_addr.s_addr = INADDR_ANY;
		//inet_addr("127.0.0.1");//ドット付きアドレスを適切に変換
	}
	~WinClient()
	{
		std::cout << __FUNCTION__ << std::endl;
		CleanUp();
	}

	/*ソケット作成*/
	int MakeSocket() {
		if (cl_sock = socket(AF_INET, SOCK_STREAM, 0) < 0) {
			perror("error : MakeSocket");
			return 1;
		}
		return 0;
	}

	/*サーバー接続*/
	int ConnectSocket() {//エラー時なんか返す？
		err = connect(cl_sock, (struct sockaddr*)&dst_addr, sizeof(struct sockaddr_in));
		//接続失敗時のエラー処理
		if (err < 0) {
			perror("error : ConnectSocket");
			return 1;
		}
		return 0;
	}

	/*データ送信*/
	void SendData() {
		char send_str[10] = { 0 };
		char receive_str[10] = { 0 };
		for (int i = 0; i < 10; i++) {
			sprintf_s(send_str, "%c", i);
			std::cout << send_str << std::endl;
			if (send(cl_sock, send_str, sizeof(send_str), 0) < 0) {
				perror("error : SendData");
			}
			else {
				recv(cl_sock, receive_str, sizeof(receive_str), 0);
				std::cout << send_str << std::endl;
				std::cout << "データ送信中%d/10" << i << std::endl;
			}
			//ここで待つ、時間の計算
		}
	}

	/*通信終了時のクリーンアップ*/
	void CleanUp() {
		closesocket(cl_sock);
		WSACleanup();
	}
};
#endif
