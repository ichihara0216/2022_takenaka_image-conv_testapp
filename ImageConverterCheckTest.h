#ifndef _win_client_
#define _win_client_
/***********************************************************************
 * インクルードファイル
 ***********************************************************************/

#include<iostream>
#include<winsock2.h	>	//TCP/IP 用の WinSock 2 Protocol-Specific Annex ドキュメントで導入された定義が含まれており、IP アドレスの取得に使用される新しい関数と構造が含まれている



class winSocketCl{
private:
	WSADATA wsaData;
	SOCKET sock;
	int wsaErr;		//wsa初期化時のエラー変数
	int connectErr;	//コネクト時のエラー変数
	struct sockaddr_in ser_addr;

protected:

public:
	winSocketCl();
	~winSocketCl();


	void SetServer();			/*サーバー情報の設定*/	
	int MakeSocket();		/*ソケット作成*/
	int ConnToServer();	/*コネクト*/
	void RecvFromServer();	/*受信*/
	void SendToServer();		/*送信*/
};

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
			sprintf_s(send_str, "%c", i );
			std::cout << send_str << std::endl;
			if (send(cl_sock, send_str, sizeof(send_str), 0) < 0) {
				perror("error : SendData");
			}
			else {
				recv(cl_sock, receive_str, sizeof(receive_str), 0);
				std::cout << send_str << std::endl;
				std::cout << "データ送信中%d/10" << i <<std::endl;
			}
			//ここで待つ、時間の計算
		}
	}
	
	/*通信終了時のクリーンアップ*/
	void CleanUp(){
		closesocket(cl_sock);
		WSACleanup();
	}
};
#endif

#endif