#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"
#include "MathForOcr.h"
#include "Network.h"
#include "SaveAndLoad.h"


void xor(Matrix sizes)
{
	Matrix xor1 = init_matrix(2,1); 
    Matrix xor2 = init_matrix(2,1); 
    Matrix xor3 = init_matrix(2,1); 
    Matrix xor4 = init_matrix(2,1); 

    *(xor1.pt) = 0;
    *(xor1.pt+1) = 0;

    *(xor2.pt) = 0;
    *(xor2.pt+1) = 1;

    *(xor3.pt) = 1;
    *(xor3.pt+1) = 0;

    *(xor4.pt) = 1;
    *(xor4.pt+1) = 1;

    StoreMatrix XOR = init_StoreMatrix(4);
    *(XOR.matrices) = xor1;
    *(XOR.matrices+1) = xor2;
    *(XOR.matrices+2) = xor3;
    *(XOR.matrices+3) = xor4;

    Matrix label1 = init_matrix(1,1);                                                                                                                                                                              
    Matrix label2 = init_matrix(1,1);                                                                                                                                                                                                                                      
    Matrix label3 = init_matrix(1,1);                                                                                                                                                                                                                                      
    Matrix label4 = init_matrix(1,1);                                                                                                                                                                                                                                      

    *(label1.pt) = 0;                                                                                                                                                                                                                                                      
    *(label2.pt) = 1;                                                                                                                                                                                                                                                      
    *(label3.pt) = 1;                                                                                                                                                                                                                                                      
    *(label4.pt) = 0;                                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                               
    StoreMatrix LABEL = init_StoreMatrix(4);                                                                                                                                                                                                                               
    *(LABEL.matrices) = label1;                                                                                                                                                                                                                                            
    *(LABEL.matrices+1) = label2;                                                                                                                                                                                                                                          
    *(LABEL.matrices+2) = label3;                                                                                                                                                                                                                                          
    *(LABEL.matrices+3) = label4;

    /////////////////////////

    int length = sizes.columns;

    /////////////////////////

    Network net = init_all(sizes, length);

    StoreMatrix Outputs = *(net.pt_wbo + 2);

	Matrix Input1;

	for (int k = 0; k < 2000000; k++)
    {
     	int r = rand();
        r = r%4;
        Input1 = *(XOR.matrices + r);


        *(Outputs.matrices) = Input1;

        //feedforward
        feedforward(net, length);

        Matrix Error = backprop_on_last(net, *(LABEL.matrices + r), length);
        backprop_on_hidden(net, Error, length);
        free(Error.pt); 
        printf("\n---NETWORK---\n");
        print_network(net, net.length);
    }
     
     free(Input1.pt);

     //test the network (after training)
     int out = 0;
     while (out != 4)
     {
     	printf("\nEnter 0 or 1 to test XOR : \n");
        double user_entry1 = 0;
        double user_entry2 = 0;
        double rien;

        printf("\n x1 : ");
        rien = scanf("%lf", &user_entry1);
        printf("%lf\n", user_entry1);

        if (user_entry1 != 1 && user_entry1 != 0)
        	break;

        printf("\n x2 : ");
        rien = scanf("%lf", &user_entry2);
        printf("%lf\n", user_entry2);

        if (rien == 0)
        {
        	printf("ERROR SCANF !!!!");
        }

        Matrix Input = init_matrix(2, 1);
        *(Input.pt) = user_entry1;
        *(Input.pt + 1) = user_entry2; 

        StoreMatrix O = *(net.pt_wbo + 2);
        //free((O.matrices)->pt);
        *(O.matrices) = Input;

        feedforward(net, length);
        O = *(net.pt_wbo + 2);
        printf("|-----------|\n");
        printf("Result : \n");
        print_network(net, length);
        out++;
        //free(Input.pt);
     }
     print_network(net, net.length);
     SaveNetwork(net);
     free_network(net);

}


