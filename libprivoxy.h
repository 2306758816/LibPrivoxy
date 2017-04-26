#ifndef _LIBPRIVOXY_EXPORT_H
#define _LIBPRIVOXY_EXPORT_H

/** @brief Many people want to integrate Privoxy into their own projects, 
* I made some changes to the Privoxy codes to compiled into a DLL or static library, 
* so that you can better integrate it into their own projects. https://www.sockscap64.com
*
* @Author: Taro, https://www.sockscap64.com
*/

#ifdef LIBPRIVOXY_EXPORTS
#define LIBPRIVOXY_API __declspec(dllexport)
#else
#define LIBPRIVOXY_API __declspec(dllimport)
#endif

// http/https
#define HTTP	3
// SOCKS 4/4A
#define SOCKS4  4
// SOCKS 5
#define SOCKS5  5

/** @brief ����privoxy, ���Է�������, ����������Ѿ�����, �ٴε���ֻ�����privoxy�����������Ϣ, 
* �������forwarding socks5 ip,forwarding port, privoxy service port����Ϣ
*
* @param listen_port: PRIVOXY�����˿�, 0�Զ������������ö˿�
* @param forward_socks_5_ip: ת������SOCKS 5 IP
* @param forward_socks5_port: ת������SOCKS 5 PORT
* @param pac_file: pac �ļ�����·��
*
* @return 0 �����ɹ�, ��������ʧ��
*/
extern "C" LIBPRIVOXY_API int __stdcall start_privoxy( 
	int proxy_type, /* HTTP,SOCKS4,SOCKS5 */
	const char *forward_socks_5_ip, 
	int forward_socks5_port,
	const char *username = NULL,
	const char *password = NULL,
	const char *listen_addr = "127.0.0.1",
	int listen_port = 0 ,
	const char *pac_file = "unset"
	);
/** @brief ֹͣprivoxy
*/
extern "C" LIBPRIVOXY_API void __stdcall stop_privoxy();
/** ���privoxy�������ĸ��˿�. һ������listen_port=0�������, ��֪��privoxy�������ĸ��˿�֮��
*/
extern "C" LIBPRIVOXY_API int __stdcall get_privoxy_port();

/** @brief ����cmd��hash ,�����¼����µ�cmd configʱ.
*/
extern "C" LIBPRIVOXY_API unsigned int __stdcall calc_cmd_hash( const char *cmd );

/** @biref ȡ��PAC��ַ
*/
extern "C" LIBPRIVOXY_API BOOL __stdcall GetPrivoxyPacUrl( char *buf, int buflen );

/** @brief ȡ��PRIVOXY��ַ
*/
extern "C" LIBPRIVOXY_API BOOL __stdcall GetPrivoxyProxyAddr( char *buf, int buflen );

extern "C" LIBPRIVOXY_API int __stdcall is_privoxy_started();
#endif