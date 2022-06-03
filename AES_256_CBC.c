#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

uint32_t word[60];

uint8_t sBox[16][16] = {
        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
        {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
        {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
        {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
        {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
        {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
        {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
        {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
        {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
        {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
        {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
        {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
        {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
        {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
        {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
        {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};
        
uint8_t invSBox[16][16] = {
		{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
		{0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
		{0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
		{0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
		{0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
		{0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
		{0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
		{0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
		{0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
		{0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
		{0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
		{0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
		{0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
		{0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
		{0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
		{0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};
        
uint32_t rCon[10] = {(uint32_t) 0x01000000, (uint32_t) 0x02000000, (uint32_t) 0x04000000, (uint32_t) 0x08000000, (uint32_t) 0x10000000, (uint32_t) 0x20000000, (uint32_t) 0x40000000, (uint32_t) 0x80000000, (uint32_t) 0x1B000000, (uint32_t) 0x36000000};

// key scheduling -- rotate word
uint32_t rotWord(uint32_t w){
    uint32_t temp = w>>24;
    w<<=8;
    w|=temp;
    return w;
}

// key scheduling -- substitution word
uint32_t subWord(uint32_t w) {
    uint32_t retme=0;
    int i;
    for(i=0;i<4;i++){
        retme<<=8;
        uint8_t temp = (w>>(8*(3-i)))& 0xff;
        uint8_t r = temp >> 4;
        uint8_t c = temp & 15;
        retme |= sBox[r][c];
    }
    return retme;
}

// key scheduling algorithm of AES-256
void aes_key_schedule_256(const uint8_t *key) {
	uint32_t temp;
	int i=0, k=0;
	printf("\nRound keys:\n");
	for(i=0; i<8; i++) {
		word[i] = (key[4*i]<<24 | key[4*i+1]<<16 | key[4*i+2]<<8 | key[4*i+3]);
		printf("%02x ", word[i]);
		k++;
	}
	
	for(i=8; i<120; i++) {
		temp = word[i-1];
		if(k%8==0) {
			printf("\n");
		}
		if(i%4==0) {
			temp = subWord(rotWord(temp)) ^ rCon[i/4-1];
		}
		word[i] = word[i-4] ^ temp;
		printf("%02x ", word[i]);
		k++;
	}
}

// subByte function
void subByte(uint8_t matrix[4][4]) {
	int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            uint8_t temp = matrix[i][j];
            uint8_t r = temp >> 4;
            uint8_t c = temp & 15;
            matrix[i][j] = sBox[r][c];
        }
    }
}

// inverse SubByte function
void invSubByte(uint8_t matrix[4][4]) {
	int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            uint8_t temp = matrix[i][j];
            uint8_t r = temp >> 4;
            uint8_t c = temp & 15;
            matrix[i][j] = invSBox[r][c];
        }
    }
}

// shift rows function
void shiftRows(uint8_t matrix[4][4]) {
	int i, k, j;
    for (i = 1; i < 4; i++) {
        int arr[4];
        for (k = i; k < 4; k++) {
            arr[k - i] = matrix[i][k];
        }
        for (j = 0; j < i; j++) {
            arr[4 - i + j] = matrix[i][j];
        }
        for (j = 0; j < 4; j++) {
            matrix[i][j] = arr[j];
        }
    }
}

// inverse shift rows function
void invShiftRows(uint8_t matrix[4][4]) {
	int i, k, j;
    for (i = 1; i < 4; i++) {
        int arr[4];
        for (k = i; k <= 4; k++) {
            arr[k] = matrix[i][k-i];
        }
        for (j = 0; j < i; j++) {
        	arr[j] = matrix[i][4-i+j];
        }
        for (j = 0; j < 4; j++) {
            matrix[i][j] = arr[j];
        }
    }
}

// helper function used in mix Column
uint8_t mult(uint8_t x) 
{ 
	uint8_t temp = x, g;
	if(temp>>7 == 0) {
		g = x<<1;
	} else {
		g = (x<<1)^27;
	}
	return g;
}

// mix column function
void mixCol(uint8_t matrix[4][4]) {

	uint8_t G[4][4] = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2}};
    int8_t temp[4][4];
    
    int row, col, r;
    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            temp[row][col] = 0;
        }
    }
    // simple matrix multiplication
    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            for (r = 0; r < 4; r++)
            {
                if (G[row][r] == 2)
                {
                    temp[row][col] ^= mult(matrix[r][col]);
                }
                else if (G[row][r] == 3)
                {
                    temp[row][col] ^= (mult(matrix[r][col]) ^ matrix[r][col]);
                }
                else
                {
                    temp[row][col] ^= matrix[r][col];
                }
            }
        }
    }

    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            matrix[row][col] = temp[row][col];
        }
    }
}

// inverse mix column function
void invMixCol(uint8_t matrix[4][4]) {
	//  it is true that M^4=I. So, by performing this transformation trice you get its inverse (M^3=M^-1)
	mixCol(matrix);
	mixCol(matrix);
	mixCol(matrix);
}

// function to print state matrix
void printMatrix(uint8_t matrix[4][4]) {
	int i=0, j=0;
	printf("\n");
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			printf("%02x ", matrix[i][j]);
		}
		printf("\n");
	}
}

// AES-256 Encryption
void aes_256_encryption(uint8_t MA[32], uint8_t iv[16], uint8_t key[32], uint8_t ciphertext[32]) {
	printf("\n\n----------------AES_256 Encryption process---------------\n");
	int sets = 0;
	printf("\nInitial key:\n");
	int i;
	for(i=0; i<32; i++) {
		printf("%02x ", key[i]);
	}
	printf("\n");
	
	aes_key_schedule_256(key);
	printf("\n");
	while(sets<2) {
		uint8_t message[16];
		printf("\nMessage part %d (16 bytes):\n", sets+1);
		for(i=0; i<16; i++) {
			message[i] = MA[16*sets+i];
			printf("%02x ", message[i]);
			message[i] = message[i] ^ iv[i];
		}
		printf("\n");
		
		uint8_t matrix[4][4] = {
			{message[0], message[4], message[8], message[12]},
			{message[1], message[5], message[9], message[13]},
			{message[2], message[6], message[10], message[14]},
			{message[3], message[7], message[11], message[15]} };
			
		int j=0, l=0, k=0;
		// Round 0 -- add round key to state matrix
	    for(i=0;i<4;i++){
	        for(j=0;j<4;j++) {
	        	uint8_t roundKey[4];
				roundKey[0] = word[i]>>24;
				roundKey[1] = word[i]>>16 & 0xFFFFFFFF;
				roundKey[2] = word[i]>>8 & 0xFFFFFFFFFFFFFFFF;
				roundKey[3] = word[i] & 0xFFFFFFFF;
	            matrix[j][i] ^= roundKey[j];
	        }
	    }

		// Rounds 1 to 13 -- SUBBYTE, SHIFTROWS, MIXCOL, ADDROUNDKEY
		l=4;
	    for(k=1;k<14;k++){
	        subByte(matrix);
	        shiftRows(matrix);
	        mixCol(matrix);
			for(i=0;i<4;i++){
	            for(j=0;j<4;j++){
	                uint8_t roundKey[4];
					roundKey[0] = word[l]>>24;
					roundKey[1] = word[l]>>16 & 0xFFFFFFFF;
					roundKey[2] = word[l]>>8 & 0xFFFFFFFFFFFFFFFF;
					roundKey[3] = word[l] & 0xFFFFFFFF;
		            matrix[j][i] ^= roundKey[j];
	            }
	            l++;
	        }
	    }
	    
		// Round 14 -- SUBBYTE, SHIFTROWS, ADDROUNDKEY
	    subByte(matrix);
	    shiftRows(matrix);
	    for(i=0;i<4;i++){
	        for(j=0;j<4;j++){
	            uint8_t roundKey[4];
				roundKey[0] = word[l]>>24;
				roundKey[1] = word[l]>>16 & 0xFFFFFFFF;
				roundKey[2] = word[l]>>8 & 0xFFFFFFFFFFFFFFFF;
				roundKey[3] = word[l] & 0xFFFFFFFF;
	            matrix[j][i] ^= roundKey[j];
	        }
	        l++;
	    }

	    k=0;
		//  storing matrix into ciphertext array
	    for(i=0;i<4;i++) {
	        for(j=0;j<4;j++) {
	            ciphertext[16*sets+k] = matrix[j][i];
	            k++;
	        }
	    }
	    
		// updating IV array with ciphertext of previous chunk
	    for(i=0; i<16; i++) {
	    	iv[i] = ciphertext[16*sets + i];
		}
		sets++;
	}
}

void aes_256_decryption(uint8_t ciphertext[32], uint8_t iv[16], uint8_t key[32], uint8_t decryptedtext[32]) {
	printf("\n\n----------------AES_256 Decryption process---------------\n");
	int sets = 0, i;
	// aes_key_schedule_256(key);
	
	while(sets<2) {
		
		uint8_t cipher[16];
		printf("\nCiphertext part %d (16 bytes):\n", sets+1);
		for(i=0; i<16; i++) {
			cipher[i] = ciphertext[16*sets+i];
			printf("%02x ", cipher[i]);
		}
		printf("\n");
		
		uint8_t matrix[4][4] = {
			{cipher[0], cipher[4], cipher[8], cipher[12]},
			{cipher[1], cipher[5], cipher[9], cipher[13]},
			{cipher[2], cipher[6], cipher[10], cipher[14]},
			{cipher[3], cipher[7], cipher[11], cipher[15]} };
			
		int j=0, l=56, k=0;
		// adding round key
	    for(i=0;i<4;i++){
	        for(j=0;j<4;j++) {
	        	uint8_t roundKey[4];
				roundKey[0] = word[l]>>24;
				roundKey[1] = word[l]>>16 & 0xFFFFFFFF;
				roundKey[2] = word[l]>>8 & 0xFFFFFFFFFFFFFFFF;
				roundKey[3] = word[l] & 0xFFFFFFFF;
	            matrix[j][i] ^= roundKey[j];
	        }
	        l++;
	    }

		l=52;
		// performing operations of 13 rounds
	    for(k=1;k<14;k++){
	        invShiftRows(matrix);
	        invSubByte(matrix);
			for(i=0;i<4;i++){
	            for(j=0;j<4;j++){
	                uint8_t roundKey[4];
					roundKey[0] = word[l]>>24;
					roundKey[1] = word[l]>>16 & 0xFFFFFFFF;
					roundKey[2] = word[l]>>8 & 0xFFFFFFFFFFFFFFFF;
					roundKey[3] = word[l] & 0xFFFFFFFF;
		            matrix[j][i] ^= roundKey[j];
	            }
	            l++;
	        }
	        l = l-8;
	        invMixCol(matrix);
	    }
	    
	    invShiftRows(matrix);
	    invSubByte(matrix);
	    l=0;
	    for(i=0;i<4;i++){
	        for(j=0;j<4;j++){
	            uint8_t roundKey[4];
				roundKey[0] = word[l]>>24;
				roundKey[1] = word[l]>>16 & 0xFFFFFFFF;
				roundKey[2] = word[l]>>8 & 0xFFFFFFFFFFFFFFFF;
				roundKey[3] = word[l] & 0xFFFFFFFF;
	            matrix[j][i] ^= roundKey[j];
	        }
	        l++;
	    }
	    
	    // xor of iv and decrypted text to get plaintext
	    k=0;
	    for(i=0; i<4; i++) {
	    	for(j=0; j<4; j++) {
		    	matrix[j][i] = matrix[j][i] ^ iv[k];
		    	decryptedtext[16*sets + k] = matrix[j][i];
		    	k++;
		    }
		}
		
		// updating IV array with ciphertext of previous chunk
		for(i=0; i<16; i++) {
			iv[i] = ciphertext[16*sets + i];
		}
		
		sets++;
	}
	
}

int main() {

	int i;
	
	uint8_t msg[32] = { 	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 
						0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	
	uint8_t iv[16] = { 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
						
	uint8_t K[32] = { 	0xfa, 0x4b, 0xf4, 0x72, 0x1c, 0x9f, 0xc5, 0x2e, 0x9f, 0xca, 0x9c, 0xcf, 0x22, 0xce, 0xa9, 0xd2, 
						0xfb, 0x44, 0x90, 0x0e, 0xf9, 0x48, 0x64, 0x62, 0xa9, 0x14, 0xfe, 0x12, 0x77, 0xd3, 0x59, 0x71 };
	
	uint8_t CA[32];
	aes_256_encryption(msg, iv, K, CA);
	
	printf("\nCiphertext: \n");
	for(i=0; i<32; i++) {
		printf("%02x ", CA[i]);
	}
	
	for(i=0; i<16; i++) {
		iv[i] = 0x00;
	}
	
	uint8_t MB[32];
	aes_256_decryption(CA, iv, K, MB);
	
	printf("\nDecrypted Text: \n");
	for(i=0; i<32; i++) {
		printf("%02x ", MB[i]);
	}
}
