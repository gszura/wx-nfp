#include "Crypto.h"
#include <wx/wfstream.h>
#include <wx/zstream.h>
#include <wx/log.h>
#include <wx/filename.h>

Crypto::~Crypto()
{
    //dtor
}

void Crypto::encryptFile()
{
    wxString zipFilePath = wxFileName::CreateTempFileName(_T("nfp"));
    wxLogDebug( wxString::Format( _T("[Crypto] tmp file: %s"), zipFilePath.c_str()) );

    compress(m_inputFilePath, zipFilePath);
    encrypt(zipFilePath, m_outputFilePath);
}

void Crypto::decryptFile()
{
    wxString zipFilePath = wxFileName::CreateTempFileName(_T("nfp"));
    wxLogDebug( wxString::Format( _T("[Crypto] tmp file: %s"), zipFilePath.c_str()) );

    decrypt(m_inputFilePath, zipFilePath);
    decompress(zipFilePath, m_outputFilePath);
}

void Crypto::compress(wxString inFile, wxString outFile)
{
    wxFFileInputStream inputStream(inFile);
    wxFFileOutputStream outputStream(outFile);
    wxZlibOutputStream zipOutputStream(outputStream);

    zipOutputStream.Write(inputStream);
    wxLogDebug( wxString::Format( _T("[Crypto] compressed %i bytes"), zipOutputStream.GetSize()) );

    zipOutputStream.Close();
    outputStream.Close();
}

void Crypto::decompress(wxString inFile, wxString outFile)
{
    wxFFileInputStream inputStream(inFile);
    wxFFileOutputStream outputStream(outFile);
    wxZlibInputStream zipInputStream(inputStream);

    outputStream.Write(zipInputStream);
    wxLogDebug( wxString::Format( _T("[Crypto] decompressed %i bytes"), zipInputStream.TellI()) );
    outputStream.Close();
}

void Crypto::encrypt(wxString inFile, wxString outFile)
{
    wxFFileInputStream inputStream(inFile);
    wxFFileOutputStream outputStream(outFile);

    int bytesRead = 0;
    int i = 0;
    char c;
    while ( !inputStream.Read(&c, 1).Eof() ) {
        c += m_password[i] - m_password[0];
        outputStream.Write(&c, 1);
        i++;
        i %= m_password.Length();
        bytesRead++;
    }

    wxLogDebug( wxString::Format( _T("[Crypto] encrypted %i bytes"), bytesRead) );

    outputStream.Close();
}

void Crypto::decrypt(wxString inFile, wxString outFile)
{
    wxFFileInputStream inputStream(inFile);
    wxFFileOutputStream outputStream(outFile);

    int bytesRead = 0;
    int i = 0;
    char c;
    while ( !inputStream.Read(&c, 1).Eof() ) {
        c += m_password[0] - m_password[i];
        outputStream.Write(&c, 1);
        i++;
        i %= m_password.Length();
        bytesRead++;
    }

    wxLogDebug( wxString::Format( _T("[Crypto] decrypted %i bytes"), bytesRead) );

    outputStream.Close();
}
