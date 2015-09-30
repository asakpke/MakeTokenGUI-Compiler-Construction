// Token.h: interface for the CToken class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKEN_H__1C02BD4C_794C_44CC_B4E9_17D78876575B__INCLUDED_)
#define AFX_TOKEN_H__1C02BD4C_794C_44CC_B4E9_17D78876575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHeader.h"

class CToken  
{
public:	
	CString GetMainToken();
	CToken();
	CToken(CString sSourceFile);
	virtual ~CToken();	
	bool OpenSourceFile(CString sSourceFile);	
	char GetNextChar();
	char GetCurrentChar();
	ETokenType GetNextToken(CString *psToken=NULL,CString *psTokenType=NULL);
	void CloseSourceFile();

private:	
	void FindSymbol();
	
	//int m_nTotalResvWords;
	//POSITION m_posResvWordFindPosition;
	CStringList m_slReserveWords;
	CStringList m_slSymbols;
	CString m_sSourceFile;
	CString m_sNextTokenType;
	CString m_sNextToken;
	CString m_sPrevToken;
	CString m_sMainToken;	//new statement 1st token
	char m_cNextChar;
	FILE *m_fp;
	ETokenType m_eNextTokenType;
	ETokenType m_ePrevTokenType;
	ETokenType m_eMainTokenType;

	
	void GetTTString();
	void GetTTComments();
	void GetTTNames();
	void GetTTNumber();
	void FindResvWord();
	void AddResvWord();
};

#endif // !defined(AFX_TOKEN_H__1C02BD4C_794C_44CC_B4E9_17D78876575B__INCLUDED_)
