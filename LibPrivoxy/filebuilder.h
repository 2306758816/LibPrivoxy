#pragma once
#include <tchar.h>

#define SYSCBCKEY "*&-sockscap64-&*dkdksdkj83-02(*&#!@&*(@)(*%)jsdfuio)(*$)*@#$"
#define SYSCBCKEY_IV "000000000000000000000000000000000000000000000000000000000000000"

#define FILE_BEGINFLAG "MC##" // 4 bytes
#define FILE_VERSION1 1
#define FILE_VERSION2 1
#define FILE_VERSION3 1
#define FILE_VERSION4 1
#define FILE_COPYRIGHT "sockscap64.com#"
#define FILE_ENDFLAG "#MC\0"

#define ERR_OK			0
#define ERR_BEGINFLAG	1			// �ļ���ʼ��ʶ����.
#define ERR_VERSION		2			// �汾����
#define ERR_COPYRIGHT	3			// ��Ȩ����
#define ERR_ENDFLAG		4			// �ļ�������ʶ����
#define ERR_OPENFILE	5			// ���ļ�����
#define ERR_MD5			6			// ����MD5����
#define ERR_OTHER		7			// ��������
#define ERR_EMPTYBODY	8			// ����Ϊ��.
#define ERR_COMPRESS    9			// ѹ�����߽�ѹ��ʧ��
#define ERR_BASE64      10

/** ����ר�е��ļ���չ��*/
#define FILE_EXTENSION	".dat"
#define FILE_BGFLAG_LENGTH (8 + strlen( FILE_COPYRIGHT ) ) // 4 (begin flag) + 1 + 1 + 1 + 1 ( version ) + strlen( copyright ) 
#define FILE_MD5LEN	16	// md5 length 16 bytes
#define FILE_BEGIN_LENGTH (FILE_BGFLAG_LENGTH+FILE_MD5LEN)
#define FILE_BODY_LENGTH_FLAG 4 // ��ʵ���ļ����ݳ���(4�ֽ�) �����ž���֮����������ļ�����
#define FILE_END_LENGTH 4	// 4 bytes
#define FILE_ALLFLAG_LENGTH (FILE_BEGIN_LENGTH + FILE_BODY_LENGTH_FLAG + FILE_END_LENGTH)  // �����ļ�����֮���������ʶ�ܳ���

#ifndef MY_FREE
#define MY_FREE(x) {if(x) { free( x ); x = NULL; } }
#endif
/** \brief
* ������ר���ļ���
* 
* \author blode(blodes@gmail.com)
*/
#define   BASICLIB_API

class BASICLIB_API CFileBuilder
{
public:
	CFileBuilder();
	CFileBuilder(const TCHAR *file);
	~CFileBuilder();

	/** @brief ���ļ�.
	*
	* @param bRead 
	* - TRUE: ��2���ƶ��ķ�ʽ���ļ�
	* - FALSE: ��2����д���ļ����ļ�
	*
	* @param bShowErrorMsg ����򿪳���ʱ�Ƿ���ʾ������Ϣ.
	* 
	* @return
	* - TRUE: ���ļ��ɹ�
	* - FALSE: ���ļ�ʧ��
	*/
	virtual BOOL Open( BOOL bRead = TRUE , BOOL bShowErrorMsg = FALSE );

	unsigned char * Read( );
	virtual BOOL Write( unsigned char *buffer,int leng );
public:
	void Close();
	BOOL IsFileOpend()
	{
		return ( file_handle != NULL ) ? TRUE: FALSE;
	}
	TCHAR *GetFileName()
	{
		return (TCHAR *)szPathFile;
	}
	int GetLastError()
	{
		return nLastError;
	}
	/** @brief ��ȡԭʼ�ļ���С(�մ�ʱ�Ĵ�С,�ǽ��ܺ�Ĵ�С)
	*/
	long GetOriginalFileLength()
	{
		return nFileLength;
	}
	long GetFileBodyLength()
	{
		return nFileBodyLength;
	}
	unsigned char *GetFileBuffer()
	{
		return pFileBuffer;
	}
	void SetBareMode(bool bMode= false)
	{
		m_bBareMode = bMode ;
	}
	// ���ļ��Ƿ�����.
	// lastModified:  �Ὣ�ļ�������޸�ʱ�������Ƚ�,���ж��Ƿ������ʱ��֮�󱻸Ĺ���.
	// ����ļ����޸Ĺ���, lastModified ���������޸�Ϊ�ļ�����޸�ʱ��.
	BOOL IsFileModified( time_t &lastModified );
	BOOL GetFileLastModifiTime( time_t &lastModified );
protected:
	/** @brief ��ȡԭʼ�ļ�����, ����_filelength
	*/
	long _GetFileLength();

	/** @brief ��ȡԭʼ �ļ����ݳ���
	*/
	unsigned char * ReadOrignalFileBody();

	void des_encrypt(unsigned char *in,unsigned char *out,unsigned int length);
	void des_decrypt(unsigned char *in,unsigned char *out,unsigned int length);

	unsigned char *pFileBuffer;
	int nLastError;
	long nFileLength;		// ��������ԭʼ�ļ�����.
	long nFileBodyLength;	// ������������ļ����ݳ���.
	
	/** ����ģʽ����ȥ�����еı�ǣ����ܣ�����ԭ�ı��棬��ȡ*/
	bool m_bBareMode;
protected:
	FILE *file_handle;
	TCHAR szPathFile[260];		// ��ǰ�������ļ�
	unsigned char fileflag[4];//MC?0
	unsigned char version[4]; //1111
	unsigned char copyright[14];//moencycopy.cn0
	unsigned char md5_check[32];
	unsigned char endflag[4];//##MC
	static unsigned char cfb_iv[8];
};
