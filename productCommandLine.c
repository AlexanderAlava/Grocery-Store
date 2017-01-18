/*===================================================================================================================================================================*/
/*=04/03/2016																	     Alexander Alava=*/
/*=product2.c																		   U35432961=*/
/*=																				    =*/
/*=  This program reads different products from the "sale.txt" file, it saves them into a structure array and the sorts them in increasing order. After that, the   =*/
/*=   program lets the user input and a command the number of one of the products and searches for it inside the array, then printing all the information about it  =*/
/*===================================================================================================================================================================*/

#include <stdio.h>
#include <string.h>
#define NAME 35
#define PRODUCTS 1000

/* Declaring and defining a struct called product */
struct product
{
        char name[NAME];
        double price;
        double sold;
        double volume;
};

/* Declaring an array of product structures */
struct product products[PRODUCTS];

/* Declaring the selection_sort function with parameters struct product array and int */
void selection_sort(struct product products[], int n);

int main (int argc, char *argv[])
{
	/* Declaring an initializing character arrays, index variables, variables and file pointers */
        char name[NAME];
        int i = 0, j = 0;
        double price = 0;
        double sold = 0;
        double volume = 0;
        FILE *pFile, *rFile;

        /* Printing header and explaining the user what does this program do */
        printf("\nHello user!\nThis program runs with the \"sale.txt\" file and retrieves information about the product requested.\n");

        /* Establishing an error check in case the "sale.txt" file can't be opened */
        if ((pFile = fopen("sale.txt", "r")) == NULL)
        {
        	/* Printing error message and terminating the program */
                printf("Error opening the \"sales.txt\" file.");
                
		return 0;                                       
        }

	/* Establishing a while loop to read line by line the "sale.txt" with error check included */
	while (fscanf(pFile, "%s %lf %lf", name, &price, &sold) == 3)
  	{     
		/* Calculating the volume as instructed */
		volume = price * sold;

		/* Saving the name in the correspondent array index */
                strcpy(products[i].name, name);

                /* Saving the price in the correspondent array index */
                products[i].price = price;

                /* Saving the amount sold in the correspondent array index */
                products[i].sold = sold;

                /* Saving the volume in the correspondent array index */
                products[i].volume = volume;

                /* Increasing index variable */
                i++;
        }

        /* Calling the selection_sort function */
        selection_sort(products, i);

        /* Establishing an error check in case the "sorted_products.txt" file can't be created */
        if ((rFile = fopen("sorted_products.txt", "w")) == NULL)
        {
                /* Printing error message and terminating the program */
                printf("Error creating the \"sorted_products.txt\" file.");
                return 0;
        }

        /* Printing header into the new file created */
        fprintf(rFile, "Name\tUnit Price ($)\tAmount Sold\tTotal Volume ($)\n--------------------------------------------------------\n");

        /* Establishing while loop to run through the structures and print them into the new file created */
        while (j < i)
        {
		/* Printing information into the new file created */
                fprintf(rFile, "%s      %.3lf          %.3lf           %.3lf\n", products[j].name, products[j].price, products[j].sold, products[j].volume);
                
		/* Incrementing variable to make the while loop run correctly */
		j++;
        }

        /* Closing file pointer */
        fclose(pFile);
        fclose(rFile);

        /* Printing a success message to let the user know that the program has executed correctly */
        printf("\nThe program has executed correctly!\nThe whole output has been saved in the file called \"sorted_products.txt\".");

	/* Declaring the find_product function with parameters struct product array, int and character pointer */
	void find_product(struct product products[], int n, char *name);
	
	/* Calling the find_product function */
	find_product(products, i, argv[1]);
	
	return 0;
}
/* Defining the selection_sort function that will rank the products in increasing order of volume */
void selection_sort(struct product products[], int n)
{
        /* Declaring and initializing int variables and a struct product variable */
        int i, largest = 0;
        struct product temporary;

        /* Checking if the function has reached the base case to terminate it */
        if (n == 1)
        {
                return;
        }

        /* Establishing a for loop to run through all the product structures */
        for (i = 1; i < n; i++)
        {
                /* Checking if the current volume is largest than the current volume */
                if (products[i].volume > products[largest].volume)
                {
                        /* Setting the current index as the largest index */
                        largest = i;
                }
        }

        /* Sending the compared largest product to the bottom of the list */
        if (largest < n - 1)
        {
		/* Switching the places of the two products in question */
		temporary = products[n-1];
                products[n-1] = products[largest];
                products[largest] = temporary;
        }

        /* Calling recursively the selection_sort function */
        selection_sort(products, n - 1);
}

/* Defining the find_product function that will retrieve information about the product required by the user */
void find_product(struct product products[], int n, char *name)
{
	/* Declaring and initializing variables */
	int i, flag = 1;

	/* Establishing a for loop to run through all the products */
	for (i = 0; i < n; i++)
	{
		/* Checking if the name inputted as a command matches the name in the correspondent array position */
		if ((strcmp(name, products[i].name)) == 0)
		{
			/* Setting the flag to false so that the error message is not printed */
			flag = 0;
			
			/* Printing the information about the requested product */
			printf("\n\nYour product has been found!");
			printf("\nName: %s", products[i].name);
			printf("\nUnit Price: %.3lf", products[i].price);
			printf("\nNumber of pounds sold: %.3lf", products[i].sold);
			printf("\nSale Volume: %.3lf", products[i].volume);

			/* Breaking the for loop */
			break;
		}
	}

	/* Checking if there was a match between the input and the array */	
	if(flag)
	{
		/* Printing an error message in case the input didn't match any of the names in the array */
		printf("\n\nUnfortunately, %s is not in this product inventory.\nSorry!", name);
	}			
}

