/*
    Winter 2021
    Automate your work assignment
    Written by SeungGeon Kim

    Filename : XLDataWrapper.cpp
	Edited : 2021-11-27
*/

#include "XLDataWrapper.h"

#include "ConsoleManager.h"
#include <iostream>
#include "libxl.h"

using namespace libxl;



XLDataWrapper& XLDataWrapper::Instance() noexcept
{
	static XLDataWrapper instance;
	return instance;
}

void XLDataWrapper::ScanXLSX(KR_STR paramFileName)
{
    Book* book = CreateXLSXBook<Book*>();

    if (book->load(paramFileName) == true)
    {
        P_STRING(paramFileName, C_PARAMETER, false);
        P_STRING(" ~ File was successfully loaded.");
        P_STRING("Resource allocated.", C_SPECIAL);

        system("PAUSE");



        int totalSheetCount = book->sheetCount();

        P_STRING("The file has a total of : ", C_GREEN, false);
        P_DOUBLE(totalSheetCount, C_PARAMETER, false);
        P_STRING(" sheets, each of them having indices and names of...");

        for (int i = 0; i < totalSheetCount; i++)
        {
            P_STRING("");
            P_DOUBLE(i, C_PARAMETER, false);
            P_STRING(") <-> ", C_GREEN, false);
            P_STRING(book->getSheetName(i), C_PARAMETER);
        }

        P_STRING("", C_GREEN);

        P_STRING("Please type in the index of the sheet to be scanned - ", C_GREEN, false);



        int inputSheetNo = 0;

        while (true)
        {
            std::wstring tempStringBuffer;

            std::wcin >> tempStringBuffer;

            try 
            {
                inputSheetNo = std::stoi(tempStringBuffer);
            }
            catch (std::invalid_argument msg)
            {
                P_STRING(msg.what(), C_ERROR);
                P_STRING("ERROR!!! ", C_ERROR, false);
                P_STRING("Please type in a number between : ", C_GREEN, false);
                P_DOUBLE(0, C_PARAMETER, false);
                P_STRING(", and ", C_GREEN, false);
                P_DOUBLE(totalSheetCount - 1, C_PARAMETER, false);
                P_STRING(" - ", C_GREEN, false);

                continue;
            }

            if (inputSheetNo >= 0 && inputSheetNo < totalSheetCount)
            {
                break;
            }
            else
            {
                P_STRING("ERROR!!! ", C_ERROR, false);
                P_STRING("Please type in a number between : ", C_GREEN, false);
                P_DOUBLE(0, C_PARAMETER, false);
                P_STRING(", and ", C_GREEN, false);
                P_DOUBLE(totalSheetCount - 1, C_PARAMETER, false);
                P_STRING(" - ", C_GREEN, false);
            }
        }

        P_STRING("Ready to scan...", C_PARAMETER);

        system("PAUSE");



        Sheet* sheet = book->getSheet(inputSheetNo);

        if (sheet != nullptr) 
        {
            // Find the true last column index of a sheet and keep it
            int trueLastColIndex = 0;
            int i = 0;
            while (i < sheet->lastCol())
            {
                CellType cellType = sheet->cellType(0, i);
                if (cellType == CELLTYPE_EMPTY)
                {
                    break;
                }
                else
                {
                    trueLastColIndex = i;
                    i++;
                }
            }

            // Go through each cell of the entire sheet, in a 2D nested array fashion
            for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
            {
                for (int col = sheet->firstCol(); col < trueLastColIndex; ++col)
                {
                    // Fetch and keep the cellType
                    CellType cellType = sheet->cellType(row, col);

                    if (sheet->isFormula(row, col))
                    {
                        P_POS(row, col, C_BLUE, false);
                        P_STRING(sheet->readFormula(row, col), C_PROMPT);
                    }
                    else
                    {
                        switch (cellType)
                        {
                        case CELLTYPE_NUMBER:
                            //P_POS(row, col, C_BLUE, false);
                            //P_DOUBLE(sheet->readNum(row, col), C_GREEN);
                            break;
                        case CELLTYPE_STRING:
                            //P_POS(row, col, C_BLUE, false);
                            //P_STRING(sheet->readStr(row, col), C_DARKRED);
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            P_STRING("ERROR!!! ", C_ERROR, false);
            P_STRING("Sheet with the number of : ", C_GREEN, false);
            P_DOUBLE(inputSheetNo, C_PARAMETER, false);
            P_STRING(" was not found.");
        }

        P_STRING(paramFileName, C_PARAMETER, false);
        P_STRING(" ~ Scanning complete.", C_PARAMETER);
    } 
    else 
    {
        P_STRING("ERROR!!!", C_ERROR, false);
        P_STRING("XLSX with the name of : ", C_GREEN, false);
        P_STRING(paramFileName, C_PARAMETER, false);
        P_STRING(" was not found.", C_GREEN);
    }

    system("PAUSE");

    book->release();

    P_STRING(paramFileName, C_PARAMETER, false);
    P_STRING(" ~ File was successfully unloaded.");
    P_STRING("Resource deallocated.", C_SPECIAL);

    system("PAUSE");
}

template <class T>
T XLDataWrapper::CreateXLSXBook()
{
    Book* book = xlCreateXMLBook(); // xlCreateXMLBook() is a method of LibXL library for loading a file of XLSX format (there's another for XLS)
    book->setKey(L"SeungGeon Kim", L"windows-2f24290302cbeb016bbd6363a0wdlft8"); // Product Key, prefix is there in order to match argument type

    return book;
}