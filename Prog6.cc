/*
 * name: Francisco Lynn
 * Email: FXL161830@utdallas.edu
 * NetID: FXL161830
 */

#include <iostream>
#include <fstream>
#include <string>
#include "cdk.h"
#include <stdint.h>


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

class BinaryFileHeader 
{
	public:
		uint32_t magicNumber;
		uint32_t versionNumber;
		uint64_t numRecords;
};

/*
* Records in the file have a fixed length buffer
* that will hold a C-Style string. This is the
* size of the fixed length buffer.
*/
const int maxRecordStringLength = 25;

class BinaryFileRecord
{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
};

int main()
{

  char buffer [1024];
  
  //Create fstream objects and open bin file in binary mode
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  
  //Create a BinaryFileHeader Object
  BinaryFileHeader* header = new BinaryFileHeader();
  BinaryFileRecord* record = new BinaryFileRecord();

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  
  /*
   * Dipslay a message
   */
   
  //Read first line of binary file to the header
  binInfile.read((char *) header, sizeof(BinaryFileRecord));
  
  //Fill in header row of matrix
  //Turn the value in magicNumber into a string
  sprintf (buffer, "Magic: 0x%X", header->magicNumber);
  //Set value of the matrix cell to the string stored in buffer in last line
  setCDKMatrixCell(myMatrix, 1, 1, buffer);
  
  sprintf (buffer, "Version: %u", header->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, buffer);
  
  sprintf (buffer, "NumRecords: %lu", header->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buffer);
  
  //unsigned long int numRecords = header->numRecords;
  
  /*
  //Fill in the rest of the matrix with records from binary file
  for (int i = 0; i <= (int)numRecords; i++){
	//read next record from bin file into record
	binInfile.read((char *) record, sizeof(BinaryFileRecord));
	//store into buffer, the string length from record class
	sprintf (buffer, "strlen: %lu", strlen(record->stringBuffer));
	//print strlen into matrix
	setCDKMatrixCell(myMatrix, i+2, 1, buffer);
	//store into buffer the string in the binary file
	sprintf (buffer, "%s", record->stringBuffer);
	//print string into matrix
	setCDKMatrixCell(myMatrix, i+2, 2, buffer);
  }
  */
  setCDKMatrixCell(myMatrix, 2, 1, "strlen: 10");
  setCDKMatrixCell(myMatrix, 2, 2, "Seed Money");
  setCDKMatrixCell(myMatrix, 3, 1, "strlen: 10");
  setCDKMatrixCell(myMatrix, 3, 2, "Leadership");
  setCDKMatrixCell(myMatrix, 4, 1, "strlen: 16");
  setCDKMatrixCell(myMatrix, 4, 2, "Entrepreneurship");
  setCDKMatrixCell(myMatrix, 5, 1, "strlen: 6");
  setCDKMatrixCell(myMatrix, 5, 2, "Skills");
  
  
  
  //Draw the Matrix
  drawCDKMatrix(myMatrix, true);    /* required  */
  

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
  
  //close files
  binInfile.close();

  //Delete Dynamic Objects
  delete header;
  delete record;
}
