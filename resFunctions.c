/*
 * resFunctions.c
 *
 *  Created on: May 12, 2021
 *      Author: ic20b094
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"resFunctions.h"

void create_restaurant(char* fname)
{
	FILE *fp=fopen(fname, "w+");
	fclose(fp);

}

int existence_cheque(char* fname)
{
	FILE *fp=fopen(fname, "r+");

	if(fp==NULL)  //Checks if Restaurant is created if not then creates the file
	{
		printf("Restaurant ins't yet created it will be created now\n");
		create_restaurant(fname); //Creates Restaurant
		existence_cheque(fname);
	}else{
		printf("Restaurant is created\n");
		// Inhate aus der Datei können hier importiert werden
		//get_table_positions(*fp);
	}

	fclose(fp);
	printf("\n%s",fname);

	return 1;
}

void export_data(char* fname, table *tisch)
{
	FILE *fp=fopen(fname,"w+");

	printf("\n%s\n", fname);

	if(fp!=NULL){
		fprintf(fp, "%d %d %d %d %d" ,tisch->id, tisch->xPos, tisch->yPos, tisch->width, tisch->height);
	}else{
		printf("\nERROR");
	}

	fclose(fp);

}

void  get_data(char* fname, table *tisch){

	FILE *fp=fopen(fname,"r+");

	if(fp!=NULL)
	{
		fscanf(fp,"%d%d%d%d%d",&tisch->id, &tisch->xPos, &tisch->yPos, &tisch->width, &tisch->height);

	}else
	{
		printf("\nERROR");
	}

	fclose(fp);
}

