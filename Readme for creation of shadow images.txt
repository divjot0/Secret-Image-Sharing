
/*
Project - Secret Image Sharing
Team Members: 1) Rohit Kumar
		   2) Divjot Singh
Encryption Readme
*/


Steps to encrypt the image:

1) Run the file "Permute_text.cpp". It asks for the input image. It creates a permutation of the pixels of the input image in a text file named "permu.txt".

2) Copy the file permu.txt into the directory of the file "Permute.cpp". Then run this file. It creates a permuted version of the input image based on the text file "permu.txt".

3) Now run the file "Colored_Image_Sharing.cpp" and give the permuted image obtained above as its input. It asks for number of shadow images to be made and number of shadow images needed to recreate the input image.

Now these required shadow images are sent to the decryption part where the input image is retrieved using them.
