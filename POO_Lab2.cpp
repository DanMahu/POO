#include <iostream>
#include <string>

using namespace std;

class Image
{
    private:
        string denumireFisier;
        string formatCompresie;
        int latime, inaltime;
        int dimensiuneInOcteti;
        double procentajCompresie;

    public:
        //constructor de initializare
        Image(string fileName, string compressionFormat, int width, int height, int fileSize, double compressionPercentage);

        ~Image()
        {
            denumireFisier = "";
            formatCompresie = "";
            latime = NULL;
            inaltime = NULL;
            dimensiuneInOcteti = NULL;
            procentajCompresie = NULL;
            cout << "Destructor\n";
        }

        //prototipurile functiilor de afisare si de schimbare a atributelor
        void afisareInfo();
        void schimbareDenumireFisier(const string& newFileName);
        void schimbareFormatCompresie(const string& newCompressionFormat);
        void schimbareDimensiuni(int newWidth, int newHeight);
        void schimbareDimensiuneInOcteti(int newFileSize);
        void schimbareProcentajCompresie(double newCompressionPercentaje);
};

Image::Image(string fileName, string compressionFormat, int width, int height, int fileSize, double compressionPercentage)
{
    this->denumireFisier = fileName;
    this->formatCompresie = compressionFormat;
    this->latime = width;
    this->inaltime = height;
    this->dimensiuneInOcteti = fileSize;
    this->procentajCompresie = compressionPercentage;
}

//afisarea informatiilor
void Image::afisareInfo()
{
    cout << "\nDenumire fisier: " << denumireFisier
        << "\nFormat compresie: " << formatCompresie
        << "\nDimensiuni: " << latime << " x " << inaltime << " pixeli"
        << "\nDimensiune in octeti: " << dimensiuneInOcteti << " octeti"
        << "\nProcentaj compresie: " << procentajCompresie << "%" << endl;
}

//schimbarea denumirii de fisier
void Image::schimbareDenumireFisier(const string& newFileName)
{
    this->denumireFisier = newFileName;
}


//schimbarea formatului de compresie
void Image::schimbareFormatCompresie(const string& newCompressionFormat)
{
    this->formatCompresie = newCompressionFormat;
}

//schimbarea dimensiunii imaginii
void Image::schimbareDimensiuni(int newWidth, int newHeight)
{
    this->latime = newWidth;
    this->inaltime = newHeight;
}

//schimbarea dimensiunii fisierului
void Image::schimbareDimensiuneInOcteti(int newFileSize)
{
    this->dimensiuneInOcteti = newFileSize;
}

//schimbarea procentajului de compresie
void Image::schimbareProcentajCompresie(double newCompressionPercentage)
{
    this->procentajCompresie = newCompressionPercentage;
}

int main()
{
    //initializarea cu valori
    Image myImage("denumire.jpg", "JPEG", 1920, 1080, 1024000, 80.6);
    cout << "Informatiile imaginii: ";
    myImage.afisareInfo();
    myImage.schimbareDenumireFisier("poza.jpg");
    cout << "\nImagine cu denumire schimbata: ";
    myImage.afisareInfo();
    myImage.schimbareFormatCompresie("PNG");
    cout << "\nImagine cu format schimbat: ";
    myImage.afisareInfo();
    myImage.schimbareDimensiuni(1024, 720);
    cout << "\nImagine cu dimensiuni schimbate: ";
    myImage.afisareInfo();
    myImage.schimbareDimensiuneInOcteti(512000);
    cout << "\nImagine cu dimensiune a fisierului schimbata: ";
    myImage.afisareInfo();
    myImage.schimbareProcentajCompresie(57.7);
    cout << "\nImagine cu procentaj de compresie schimbat: ";
    myImage.afisareInfo();
    return 0;
}