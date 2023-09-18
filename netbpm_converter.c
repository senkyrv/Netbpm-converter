#include <stdio.h>
#include <stdlib.h>
#include <string.h>
                             
void transfer(char* input, char* output, int how); // 0 = txt file
void pbm(char* input, char* output, int how);
void pgm(char* input, char* output, int how);
void ppm(char* input, char* output, int how);

int main(void)
{   
    transfer("input.pbm","result.ppm",0);

    return 0;
}

void transfer(char* input, char* output, int how)
{

    if(strstr(input,".pbm") != NULL) 
    {   
        pbm(input,output,0);
    }

    if(strstr(input,".pgm") != NULL) 
    {
        pgm(input,output,0);
    }
    if(strstr(input,".ppm") != NULL) 
    {
        ppm(input,output,0);
    }
}

void pbm(char* input, char* output, int how)
{
    const char *type;
    int cols;
    int rows;
    int max_value = 255;

    FILE* in = fopen(input,"r");
    fscanf(in, "%s\n", &type);
    fscanf(in, "%d %d\n", &rows, &cols);
    int* array = (int*)malloc(sizeof(int) * rows * cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(in, "%d", &array[i * cols + j]);
        }
        fscanf(in,"\n");
    }
    fclose(in);

    if(strstr(output,".pgm") != NULL)
        {
        printf("pbm to pgm\n");
        FILE* out = fopen(output,"w");
        fprintf(out, "P2\n");
	    fprintf(out, "%d %d\n", rows, cols);
	    fprintf(out, "%d\n", max_value);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (array[i * cols + j] == 0)
                {
                    fprintf(out,"%d ",max_value);
                }
                else
                {
                    fprintf(out,"%d ",0);
                }   
            }
            fprintf(out,"\n");
        }
        fclose(out);
        }

    if(strstr(output,".ppm") != NULL) 
        {
        printf("pbm to ppm\n");
        int rgb[3];
        FILE* out = fopen(output,"w");
        fprintf(out, "P3\n");
	    fprintf(out, "%d %d\n", rows, cols);
	    fprintf(out, "%d\n", max_value);
        for (int i = 0; i < rows; i++)
            {
            for (int j = 0; j < cols; j++)
            {
            if (array[i * cols + j] == 0)
            {
                rgb[0] = 255;
                rgb[1] = 255;
                rgb[2] = 255;
                fprintf(out,"%d %d %d ",rgb[0], rgb[1], rgb[2]);
            }
            else
            {
                rgb[0] = 0;
                rgb[1] = 0;
                rgb[2] = 0;
                fprintf(out,"%d %d %d ",rgb[0], rgb[1], rgb[2]);
            } 
            }
            fprintf(out,"\n");
        }
        fclose(out);
        }
    free(array);
    array = NULL;
}

void pgm(char* input, char* output, int how)
{
    const char *type;
    int cols;
    int rows;
    int max_value;
    FILE* in = fopen(input,"r");
    fscanf(in, "%s\n", &type);
    fscanf(in, "%d %d\n", &rows, &cols);
    fscanf(in, "%d\n", &max_value);
    int* array = (int*)malloc(sizeof(int) * rows * cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(in, "%d", &array[i * cols + j]);
        }
        fscanf(in,"\n");
    }
    fclose(in);

    if(strstr(output,".pbm") != NULL)
        {
        printf("pgm to pbm\n");
        FILE* out = fopen(output,"w");
        fprintf(out, "P1\n");
	    fprintf(out, "%d %d\n", rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (array[i * cols + j] < (max_value/1.25))
                {
                    fprintf(out,"%d ",1);
                }
                else
                {
                    fprintf(out,"%d ",0);
                }   
            }
            fprintf(out,"\n");
        }
        fclose(out);
        }

    if(strstr(output,".ppm") != NULL)
        {
        printf("pgm to ppm\n");
        int rgb[3];
        FILE* out = fopen(output,"w");
        fprintf(out, "P3\n");
	    fprintf(out, "%d %d\n", rows, cols);
	    fprintf(out, "%d\n", max_value);
        for (int i = 0; i < rows; i++)
            {
            for (int j = 0; j < cols; j++)
            {
                rgb[0] = array[i * cols + j];
                rgb[1] = array[i * cols + j];
                rgb[2] = array[i * cols + j];
                fprintf(out,"%d %d %d ",rgb[0], rgb[1], rgb[2]);
            }
            fprintf(out,"\n");
        }
        fclose(out);
        }    
    free(array);
    array = NULL;
}
void ppm(char* input, char* output, int how)
{
    const char *type;
    int cols;
    int rows;
    int max_value;
    FILE* in = fopen(input,"r");
    fscanf(in, "%s\n", &type);
    fscanf(in, "%d %d\n", &rows, &cols);
    fscanf(in, "%d\n", &max_value);
    int* array = (int*)malloc(sizeof(int) * rows * cols * 3);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols * 3; j++)
        {
            fscanf(in, "%d", &array[i * cols + j]);
            fscanf(in, "%d", &array[(i * cols + j) + 1]);
            fscanf(in, "%d", &array[(i * cols + j) + 2]);
            j += 2;
        }
        fscanf(in,"\n");
    }
    fclose(in);

    if(strstr(output,".pbm") != NULL)
        {
        int res = 0;
        printf("ppm to pbm\n");
        FILE* out = fopen(output,"w");
        fprintf(out, "P1\n");
	    fprintf(out, "%d %d\n", rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols * 3; j++)
            {
                res = (array[i * cols + j] + array[(i * cols + j) + 1] + array[(i * cols + j) + 2])/3;
                if (res < (max_value/1.25))
                {
                    fprintf(out,"%d ",1);
                }
                else
                {
                    fprintf(out,"%d ",0);
                }
                j += 2;  
            }
            fprintf(out,"\n");
        }
        fclose(out);
        }

    if(strstr(output,".pgm") != NULL)
        {
        int res = 0;
        printf("ppm to pgm\n");
        FILE* out = fopen(output,"w");
        fprintf(out, "P2\n");
	    fprintf(out, "%d %d\n", rows, cols);
	    fprintf(out, "%d\n", max_value);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols * 3; j++)
            {
                res = (array[i * cols + j] + array[(i * cols + j) + 1] + array[(i * cols + j) + 2])/3;
                fprintf(out,"%d ",res);
                j += 2;
            }
            fprintf(out,"\n");
        }
        fclose(out);
        }        
    free(array);
    array = NULL;
}