#include<stdio.h>
#include<string.h>

int comparator(const void *a,const void * b){

	int c= *(int *)a;
	int d= *(int *)b;

	return c-d;


}


int main(){

FILE *fp;
 


	fp=fopen("input.bin","rb");
	int input[1000];
	fseek(fp,0,SEEK_END);
	int size= ftell(fp)/sizeof(int);
	fseek(fp,0,SEEK_SET);
	int i;

	int runs=size/1000;
	if(size%1000)runs++;
	 printf("%d\n",size);
	for(i=0;i<runs;i++){

		fread(input,sizeof(int),1000,fp);	          //check if there are 1000 eleements
		qsort((void *)input,1000,sizeof(input[0]),comparator);
		FILE *fp1;
		
		
		
		char buffer[15];
		sprintf(buffer,"input.bin.%03d",i);
		fp1=fopen(buffer,"wb");
		fwrite(input,sizeof(int),1000,fp1);
		fclose(fp1);
	}	
	
	fclose(fp);
	int super_runs=runs/15;
	if(runs%15!=0) super_runs++;
	
	for(i=0;i<super_runs;i++) {
	int num_runs= 15;
	if((i+1)*15>runs)
		num_runs=runs- i*15;

	FILE *out;
	char buffer[25];
	sprintf(buffer,"input.bin.super.%03d",i);
        out=fopen(buffer,"wb");
        FILE *files[num_runs];
        int input_buffer[num_runs][1000/num_runs];
        int pointers[num_runs];	
	int k;
	for(k=i*15;k<i*15+num_runs;k++){
                char buffer[15]; 
		sprintf(buffer,"input.bin.%03d",k);
                files[k%15]=fopen(buffer,"rb");
                fread(input_buffer[k%15],sizeof(int),1000/num_runs,files[k%15]);
                pointers[k%15]=0;
	 	}
		
	int output_buffer[1000];
	int out_pointer=0;
	int empty_files=num_runs;
	int success_read[num_runs];
	for( k=0;k<num_runs;k++) success_read[k]=-1;
	while(empty_files>0){

		int max=-1,max_run=-1;
		for(k=0;k<num_runs;k++){
			if(pointers[k]!=-1 &&(max>input_buffer[k][pointers[k]] || max==-1 )){
				max=input_buffer[k][pointers[k]];
				max_run=k;	
			}
		}
	
		pointers[max_run]++;
		if(pointers[max_run]==1000/num_runs|| pointers[max_run]==success_read[max_run]){
	
			if(success_read[max_run]!=0){
				pointers[max_run]=0;
			success_read[max_run]=fread(input_buffer[max_run],sizeof(int),1000/num_runs,files[max_run]);
                                
				if(success_read[max_run]==0){
                                       
					empty_files--;
                                        pointers[max_run]=-1;
                                        fclose(files[max_run]);
                                }
	
			}
	
		}
		output_buffer[out_pointer]=max;                                                                         out_pointer++;
                if(out_pointer==1000 || empty_files==0){
                        fwrite(output_buffer,sizeof(int),out_pointer,out);
              		 
                	out_pointer=0;

                	for(k=0;k<1000;k++)
                        	output_buffer[k]=0;
                //write it to output buffer and reset the output pointer
                //                //and clear the output buffer and last write may not contain 1000 elements
                //                                }	
	
		}	

	
	}
	
	
	
	
	fclose(out);		
	}


	//creating super runs completed
	FILE *out;
	out=fopen("sort.bin","wb");
	FILE *files1[super_runs];	
	int input_buffer1[super_runs][1000/super_runs];
	int pointers1[super_runs];
	for(i=0;i<super_runs;i++){
		char buffer[25];
                sprintf(buffer,"input.bin.super.%03d",i);  
		files1[i]=fopen(buffer,"rb");
		fread(input_buffer1[i],sizeof(int),1000/super_runs,files1[i]);
		pointers1[i]=0;
	}
	
	int output_buffer[1000];
	int out_pointer=0;
	int empty_files=super_runs;
	int success_read[super_runs];
	for( i=0;i<super_runs;i++) success_read[i]=-1;
	while(empty_files >0){
		int max=-1,max_run=-1;
		for(i=0;i<super_runs;i++){
			//max shouldn't be initialized to -1
			if(pointers1[i]!=-1 
&& (max>input_buffer1[i][pointers1[i]] || max==-1)){
				max=input_buffer1[i][pointers1[i]];
				max_run=i;	
			}
		
			
		}
		
		pointers1[max_run]++;
		if(pointers1[max_run]==1000/super_runs || pointers1[max_run]==success_read[max_run]){
			if(success_read[max_run]!=0){

				pointers1[max_run]=0;
				success_read[max_run]=fread(input_buffer1[max_run],sizeof(int),1000/super_runs,files1[max_run]);
				if(success_read[max_run]==0){
					empty_files--;
					pointers1[max_run]=-1;
					fclose(files1[max_run]);
				}
				
				
			}

		}
		output_buffer[out_pointer]=max;
		out_pointer++;
		if(out_pointer==1000){
			fwrite(output_buffer,sizeof(int),1000,out);
		out_pointer=0;
	
		for(i=0;i<1000;i++)
			output_buffer[i]=0;
		//write it to output buffer and reset the output pointer
		//and clear the output buffer and last write may not contain 1000 elements
		}
	
	}
	fclose(out);		

	return 0;	

}


