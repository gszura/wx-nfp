#ifndef CRYPTO_H
#define CRYPTO_H

#include <wx/string.h>

class Crypto
{
public:

    Crypto(wxString password, wxString inputFilePath, wxString outputFilePath) {
        m_password = password;
        m_inputFilePath = inputFilePath;
        m_outputFilePath = outputFilePath;
    }
    virtual ~Crypto();

    void encryptFile();
    void decryptFile();
private:

    void compress(wxString, wxString);
    void decompress(wxString, wxString);
    void encrypt(wxString, wxString);
    void decrypt(wxString, wxString);

private:
    wxString m_password;
    wxString m_inputFilePath;
    wxString m_outputFilePath;
};

#endif // CRYPTO_H
