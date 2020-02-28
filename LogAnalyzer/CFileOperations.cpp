#include "CFileOperations.h"
#include <QMessageBox>

CFileOperations::CFileOperations(const QString & filter)
{
    mFilter = filter;
}

CFileOperations::~CFileOperations() {}

QString    CFileOperations::selectFileForAnalysis(void)
{
    /* Select the file */
    QString filename = QFileDialog::getOpenFileName(nullptr, "", QDir::currentPath(), mFilter) ;

    //QMessageBox::information(nullptr, "", filename);
    return filename;
}

void CFileOperations::readFromFile(CDataContainer & dataContainer)
{
    QString selectedFileName = selectFileForAnalysis();

    QMessageBox::information(nullptr, "Status", "Started loading the file.");

    QFile inputFile(selectedFileName);

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       dataContainer.onNewFile();

       while (!in.atEnd())
       {
         QString line = in.readLine();
         dataContainer.onLineReceived(line);
       }

       inputFile.close();
    }
}
