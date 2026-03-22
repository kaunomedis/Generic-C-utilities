/* testing median filter module. To remove spurrious errors in data */

#include <stdint.h>
#include <stdio.h>
#define FIFO_SIZE 5
#define MIDDLE_INDEX 3
#define swap(x,y) ((x ^= y),(y ^= x),(x ^= y))

uint32_t median_filter( uint32_t latest_value)
{
    
    static uint32_t local_ADC_FIFO_copy[FIFO_SIZE] = {0};
    static uint32_t index_counter = 0 ; 
    /*-------------| median filter|------------------------
        1.add lastest vaue & get rid of oldest value (fifo)
        2.make local copy
        3.Sort local copy only  ("bubble sort")
        4.Increment index counter for fifo
        5.return median
    */
    //1
    local_ADC_FIFO_copy[index_counter%FIFO_SIZE] = latest_value;

    //2
    uint32_t temp_sorted[FIFO_SIZE] = {0}; //make a temp to store sorted version
    for(int i = 0 ; i < FIFO_SIZE  - 1; i++)
    {
        temp_sorted[i] = local_ADC_FIFO_copy[i];
    }
    //3
    uint8_t counter = FIFO_SIZE;
    while(counter)
    {
        for(int i = 0 ; i < (counter - 1) ; i++)
        {

            if(temp_sorted[i] > temp_sorted[i+1])
            {   //swap
                swap(temp_sorted[i] ,temp_sorted[i+1]) ;
            }
           
        }
        counter--;
    }
    //---------------
    //4
    index_counter++;
    //5
    return (uint32_t)temp_sorted[MIDDLE_INDEX]; 

}


int main(void)
{
    //each element here can be a new adc reading coming in
    uint32_t adc_data[20] = {1,2,3,425,2,1,3,4,2,1,1,2,3,4,3,2,1,4,5,6} ;

    for(int i = 0 ; i < 20; i++)
    {
        printf("Median : %d \n",median_filter(adc_data[i]));
    }

}