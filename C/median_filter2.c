/* testing median filter module. To remove spurrious errors in data */

#include <stdint.h>
#include <stdio.h>


#define swap(x,y) ((x ^= y),(y ^= x),(x ^= y))

typedef struct
{
   uint32_t          *adc_fifo;            //this is where the local copy will be stored 
   uint8_t            fifo_width;
   uint8_t            median_index;
   uint8_t            internal_counter; 
} ADCFilterdValues_T;



uint32_t median_filter(ADCFilterdValues_T *adc_filter , uint32_t latest_value)
{
    /*-------------| median filter|------------------------
        1.add lastest vaue & get rid of oldest value (fifo)
        2.make local copy
        3.Sort local copy only  ("bubble sort")
        4.Increment index counter for fifo
        5.return median
    */
    //1
    adc_filter->adc_fifo[adc_filter->internal_counter%adc_filter->fifo_width] = latest_value;
    
    //2
    uint32_t temp_sorted_raw[adc_filter->fifo_width] ; 
    for(int i = 0 ; i < adc_filter->fifo_width ; i++)
    {
        temp_sorted_raw[i] = adc_filter->adc_fifo[i];
    }

    //3
    uint8_t counter = adc_filter->fifo_width;
    while(counter)
    {
        for(int i = 0 ; i < (counter - 1) ; i++)
        {

            if(temp_sorted_raw[i] > temp_sorted_raw[i+1])
            {   //swap
                swap(temp_sorted_raw[i] ,temp_sorted_raw[i+1]) ;
            }
        }
        counter--;
    }
    //4
    adc_filter->internal_counter++;
    //5
    return (uint32_t)temp_sorted_raw[adc_filter->median_index]; 

}

void main(void)
{
    //simualted stream of data coming in
    uint32_t adc_data_1[20] = {1,2,3,425,2,1,3,4,2,1,1,2,3,4,3,2,1,4,5,6} ;
    uint32_t adc_data_2[40] = {1,2,3,425,2,1,3,4,2,1,1,2,300,4,3,2,1,4,5,6,1,2,3,425,2,1,3,4,2,1,100,2,3,4,3,2,1,4,5,6} ;

    //make instances of median filter type
    ADCFilterdValues_T myFilter_1 ;
    uint32_t adc_fifo_1[5] = {0}; 

    ADCFilterdValues_T myFilter_2 ;
    uint32_t adc_fifo_2[11] = {0};

    //configure the filter
    myFilter_1.adc_fifo = adc_fifo_1;
    myFilter_1.fifo_width = 5;
    myFilter_1.median_index = 2; 

    myFilter_2.adc_fifo = adc_fifo_2;
    myFilter_2.fifo_width = 11;
    myFilter_2.median_index = 5; 

    for(int i = 0 ; i < 20; i++)
    {
        //call median filter and give it instance 1 and feed it fake data from adc_data_1
        printf("Median : %d \n",median_filter(&myFilter_1 ,adc_data_1[i] ));
    }
    printf("-----\n");
    for(int i = 0 ; i < 40; i++)
    {
        //call median filter and give it instance 1 and feed it fake data from adc_data_1
        printf("Median : %d \n",median_filter(&myFilter_2 ,adc_data_2[i] ));
    }

}
