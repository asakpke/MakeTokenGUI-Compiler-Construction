// Token.cpp: implementation of the CToken class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MakeTokenGUI.h"
#include "Token.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToken::CToken()
{

}

CToken::CToken(CString sSourceFile)
{
	OpenSourceFile(sSourceFile);
	
	//if(m_fp == NULL)
		//m_fp = fopen("..\\" + m_sTXT_FILE_NAME, "r");
	//if(m_fp == NULL)
}

CToken::~CToken()
{

}

char CToken::GetNextChar()
{
	if(m_cNextChar != EOF)	
		m_cNextChar = fgetc(m_fp);
	//else
		//MessageBox("EOF");

	return m_cNextChar;
}

char CToken::GetCurrentChar()
{
	return m_cNextChar;
}

ETokenType CToken::GetNextToken(CString *psToken,CString *psTokenType)
{	
	int nsLen;
	//bool bReadChar;
	//CString sPrevToken = m_sPrevToken;

	m_eNextTokenType = ttNull;
	m_sNextTokenType = "Null";
		
	m_sPrevToken = m_sNextToken;
	m_ePrevTokenType = m_eNextTokenType;
	m_sNextToken.Empty();
	
	//if(m_cNextChar == EOF)
	//{
		//MessageBox("EOF");
		//return;// m_sNextToken;
	//}

	while(m_cNextChar != EOF)
	{
		//bReadChar = true;

		while(m_cNextChar == ' ')
		{
			GetNextChar();
			//if(m_cNextChar == EOF)
				//MessageBox("EOF");
		}

		//if eof

		if(m_cNextChar >= '0' && m_cNextChar <= '9') // number
		{			
			GetTTNumber();			
			break;
		} 
		else if(m_cNextChar >= 'A' && m_cNextChar <= 'Z' // names
			 || m_cNextChar >= 'a' && m_cNextChar <= 'z'
			 || m_cNextChar == '_')
		{			
			GetTTNames();

			FindResvWord();

			if(m_eNextTokenType >= 66)//total resv word = 66
				FindSymbol();				
						
			break;
		} // else if(m_cNextChar >= 'A' && m_cNextChar <= 'Z'
		else if(m_cNextChar == '/') // comments
		{			
			nsLen = m_sNextToken.GetLength();
			m_sNextToken.Insert(nsLen, m_cNextChar);

			GetNextChar();
			if(m_cNextChar == '/' || m_cNextChar == '*')
				GetTTComments();

			break;
		}
		else if(m_cNextChar == '\"') // string
		{
			GetTTString();									
			break;
		}
		else if(m_cNextChar == '#') // pre processor
		{
			nsLen = m_sNextToken.GetLength();
			m_sNextToken.Insert(nsLen, m_cNextChar);
			GetNextChar();

			GetTTNames();

			m_eNextTokenType = ttPreProcessor;
			m_sNextTokenType = "Pre-Processor Directive";			

			break;
		}
		else if(m_cNextChar == 10) // end of line
			; // do nothing. note only semi-colon
		else if(m_cNextChar == ';')
		{
			m_eNextTokenType = ttStatementEnd;
			m_sNextTokenType = "Statement end";	

			nsLen = m_sNextToken.GetLength();
			m_sNextToken.Insert(nsLen, m_cNextChar);

			GetNextChar();

			break;
		}
		else // do nothing
		{
/*
			m_eNextTokenType = ttNull;			
			m_sNextTokenType = "Not yet defined";

			nsLen = m_sNextToken.GetLength();
			m_sNextToken.Insert(nsLen, m_cNextChar);

			GetNextChar();

			break;
*/
		}
		
		GetNextChar();
	} // while(ch != EOF)
	//if(m_cNextChar == EOF)
		//MessageBox("EOF");

	if(m_sPrevToken == ";") // make main token
	{
		m_sMainToken = m_sNextToken;
		m_eMainTokenType = m_eNextTokenType;
	}
	
	if(psToken != NULL)
		*psToken = m_sNextToken;

	if(psTokenType != NULL)
		*psTokenType = m_sNextTokenType;

	return m_eNextTokenType;//m_sNextToken;
} // CToken::GetNextToken()

bool CToken::OpenSourceFile(CString sSourceFile)
{
	m_sSourceFile = sSourceFile;

	m_fp = fopen(m_sSourceFile, "r");
	if(m_fp == NULL)
		return false;

	AddResvWord();

	m_sPrevToken = ";";
	m_ePrevTokenType = ttStatementEnd;
	m_eMainTokenType = ttNull;

	return true;
}

void CToken::CloseSourceFile()
{
	fclose(m_fp);	

	m_fp = NULL;
}

void CToken::GetTTNumber()
{
	int nsLen;

	m_eNextTokenType = ttNumber;
	m_sNextTokenType = "Number";

	while(m_cNextChar >= '0' && m_cNextChar <= '9')
	{
		nsLen = m_sNextToken.GetLength();
		m_sNextToken.Insert(nsLen, m_cNextChar);
		GetNextChar();
	}			
}

void CToken::GetTTNames()
{
	int nsLen;	

	m_eNextTokenType = ttNames;
	m_sNextTokenType = "variable/constant/class etc";

	while(m_cNextChar >= 'A' && m_cNextChar <= 'Z'
	   || m_cNextChar >= 'a' && m_cNextChar <= 'z'
	   || m_cNextChar == '_'
	   || m_cNextChar >= '0' && m_cNextChar <= '9')
	{
		nsLen = m_sNextToken.GetLength();
		m_sNextToken.Insert(nsLen, m_cNextChar);
		GetNextChar();
	}
	while(m_cNextChar == ' ')
		GetNextChar();
	if(m_cNextChar == '(')
	{
		m_eNextTokenType = ttFunction;
		m_sNextTokenType = "Function Name";
	}
}

void CToken::GetTTComments()
{
	int nsLen;

	if(m_cNextChar == '/')
	{
		m_eNextTokenType = ttCPPComments;
		m_sNextTokenType = "CPP's Comments";				

		while(m_cNextChar != 10) // end of line
		{
			nsLen = m_sNextToken.GetLength();
			m_sNextToken.Insert(nsLen, m_cNextChar);
			GetNextChar();
		}				
	}
	else if(m_cNextChar == '*')
	{
		char cPrevChar='x';
		m_eNextTokenType = ttCComments;
		m_sNextTokenType = "C's Comments";				

		//store '*'
		nsLen = m_sNextToken.GetLength();
		m_sNextToken.Insert(nsLen, m_cNextChar);

		GetNextChar();
		while(cPrevChar != '*' && m_cNextChar != '/')
		{
			nsLen = m_sNextToken.GetLength();
			m_sNextToken.Insert(nsLen, m_cNextChar);

			cPrevChar = m_cNextChar;
			GetNextChar();
		}
		// store last '/'
		nsLen = m_sNextToken.GetLength();
		m_sNextToken.Insert(nsLen, m_cNextChar);

		GetNextChar();
	}
}

void CToken::GetTTString()
{
	int nsLen;

	m_eNextTokenType = ttString;
	m_sNextTokenType = "String";

	nsLen = m_sNextToken.GetLength();
	m_sNextToken.Insert(nsLen, m_cNextChar);

	GetNextChar();
	char cPrevChar='x';
	bool bHasRemnString;
	do
	{
		bHasRemnString = false;

		while(m_cNextChar != '\"')
		{
			nsLen = m_sNextToken.GetLength();
			m_sNextToken.Insert(nsLen, m_cNextChar);
			cPrevChar = m_cNextChar;
			GetNextChar();
		}

		nsLen = m_sNextToken.GetLength();
		m_sNextToken.Insert(nsLen, m_cNextChar);

		if(cPrevChar == '\\')
			bHasRemnString = true;

		GetNextChar();
	}while(bHasRemnString == true);
}

//temp CToken::temp1()
//{

//}

void CToken::AddResvWord()
{
	//m_saReserveWords.AddTail("if");
	//m_saReserveWords.AddTail("for");
	//m_saReserveWords.AddTail("while");
	//m_saReserveWords.AddTail("do");

	//m_nTotalResvWords = m_slReserveWords.GetCount();

// / *
	////////////////////////
	// start	resv word //
	////////////////////////
	// total Resv Words = 66
	m_slReserveWords.AddTail("asm");
	m_slReserveWords.AddTail("auto");
	m_slReserveWords.AddTail("bad_cast");
	m_slReserveWords.AddTail("bad_typeid");
	m_slReserveWords.AddTail("bool");
	m_slReserveWords.AddTail("break");
	m_slReserveWords.AddTail("case");
	m_slReserveWords.AddTail("catch");
	m_slReserveWords.AddTail("char");
	m_slReserveWords.AddTail("class");
	m_slReserveWords.AddTail("const");
	m_slReserveWords.AddTail("const_cast");
	m_slReserveWords.AddTail("continue");
	m_slReserveWords.AddTail("default");
	m_slReserveWords.AddTail("delete");
	m_slReserveWords.AddTail("do");
	m_slReserveWords.AddTail("double");
	m_slReserveWords.AddTail("dynamic_cast");
	m_slReserveWords.AddTail("else");
	m_slReserveWords.AddTail("enum");
	m_slReserveWords.AddTail("except");
	m_slReserveWords.AddTail("explicit");
	m_slReserveWords.AddTail("extern");
	m_slReserveWords.AddTail("false");
	m_slReserveWords.AddTail("finally");
	m_slReserveWords.AddTail("float");
	m_slReserveWords.AddTail("for");
	m_slReserveWords.AddTail("friend");
	m_slReserveWords.AddTail("goto");
	m_slReserveWords.AddTail("if");
	m_slReserveWords.AddTail("inline");
	m_slReserveWords.AddTail("int");
	m_slReserveWords.AddTail("long");
	m_slReserveWords.AddTail("mutable");
	m_slReserveWords.AddTail("namespace");
	m_slReserveWords.AddTail("new");
	m_slReserveWords.AddTail("operator");
	m_slReserveWords.AddTail("private");
	m_slReserveWords.AddTail("protected");
	m_slReserveWords.AddTail("public");
	m_slReserveWords.AddTail("retister");
	m_slReserveWords.AddTail("reinterpret_cast");
	m_slReserveWords.AddTail("return");
	m_slReserveWords.AddTail("short");
	m_slReserveWords.AddTail("signed");
	m_slReserveWords.AddTail("sizeof");
	m_slReserveWords.AddTail("static");
	m_slReserveWords.AddTail("static_cast");
	m_slReserveWords.AddTail("struct");
	m_slReserveWords.AddTail("switch");
	m_slReserveWords.AddTail("template");
	m_slReserveWords.AddTail("this");
	m_slReserveWords.AddTail("throw");
	m_slReserveWords.AddTail("true");
	m_slReserveWords.AddTail("try");
	m_slReserveWords.AddTail("type_info");
	m_slReserveWords.AddTail("typedef");
	m_slReserveWords.AddTail("typeid");
	m_slReserveWords.AddTail("typename");
	m_slReserveWords.AddTail("union");
	m_slReserveWords.AddTail("unsigned");
	m_slReserveWords.AddTail("using");
	m_slReserveWords.AddTail("virtual");
	m_slReserveWords.AddTail("void");
	m_slReserveWords.AddTail("volatile");
	m_slReserveWords.AddTail("while");
	// total Resv Words = 66
	////////////////////////
	// ended	resv word //
	////////////////////////
// * /
}

void CToken::FindResvWord()
{
	POSITION posNext;
	int nPos = 0;
	CString sResvWord;

	posNext = m_slReserveWords.Find(m_sNextToken);

	if(posNext != NULL)		
	{		
		posNext = m_slReserveWords.GetHeadPosition();
		while(posNext)
		{
			sResvWord = m_slReserveWords.GetNext(posNext);
			if(sResvWord == m_sNextToken)
			{
				m_eNextTokenType = ETokenType(nPos);				
				m_sNextTokenType = "Reserve Word";
				return;
			}
			nPos++;
		}
	}
	//else
	//{
		//m_eNextTokenType = ttNull;
		//m_sNextTokenType = "const/variable etc";
	//}
}

void CToken::FindSymbol()
{
	POSITION posFind;
	
	posFind = m_slSymbols.Find(m_sNextToken);
	if(posFind == NULL)
		m_slSymbols.AddTail(m_sNextToken);
}

CString CToken::GetMainToken()
{
	return m_sMainToken;
}
