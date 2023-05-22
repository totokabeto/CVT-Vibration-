 

#define ARRAY_SIZE 200

#define BUFFER_SIZE ARRAY_SIZE-1

float gBuffer[ARRAY_SIZE]; 
int pBufferWrite = 0;
int pBufferRead = 0;
int count = 0; 
int newarr[ARRAY_SIZE] = {};
int d = 0;
void FIFOBufferWrite(float pDataIn)
{
        // Write and increase pBufferWrite
        gBuffer[pBufferWrite] = pDataIn;
        if (pBufferWrite < BUFFER_SIZE)
        {
            pBufferWrite++;
        }
        else
        {
            pBufferWrite = 0;
        }
}
  
void fistCircularBufferHalf(){
    for (int i = pBufferWrite; i < ARRAY_SIZE; i++) {
        newarr[d] = gBuffer[i]; 
        d++;
    }
    }
void secondCircularBufferHalf(){
    for (int i = 0; i < count%10; i++) {
        newarr[d] = gBuffer[i]; 
        d++; 
    }
}
//    for (int i = 0; i < ARRAY_SIZE; i++) {
//      //  cout << "Gia tri mang sau khi sap xep la " << newarr[i] << endl;
//    }  
//}
