#include<stdio.h>

int main(int argc, char * argv[])

{

  FILE * myFile;

  int curr_num;

  int num_pages; 
  int num_frames;
  int num_requests;

  int * frame;
  int * sec_chance;
  
  int * next_use; //holds next use values of requests
  int * req_arr; //holds array of requests

  // open input file

  myFile = fopen(argv[1], "r");

  // read number of pages, number of frames and number of requests
  fscanf(myFile, "%d", & num_pages);
  fscanf(myFile, "%d", & num_frames);
  fscanf(myFile, "%d", & num_requests);

  // create frame
  frame = (int * ) malloc(num_frames * sizeof(int));
  
  /////// CLOCK Algorithm
  if (strcmp(argv[2], "CLOCK") == 0)
  {
    //initialize second chance array
    sec_chance = (int * ) malloc(num_frames * sizeof(int));
    
    printf("CLOCK\n");

    int free_frame = 0;
    int used_page = 0;
    int page_faults = 0;

    int curr_request = 0;
    while (curr_request < num_requests)
    {
      //read in the next value
      fscanf(myFile, "%d", &curr_num);

      int exist_flag = 0;

      //check if current number is in the frame yet
      for (int i = 0; i < num_frames; i++)
      {
        if (frame[i] == curr_num)
        {
          // set the exist flag and the second chance value to 1
          printf("Page %d already in Frame %d\n", curr_num, i);
          sec_chance[i] = 1;
          exist_flag = 1;
        }
      }

      //if the current number isn't in the frame yet
      if (exist_flag == 0)
      {
        page_faults++;

        // check if the frame has empty slots
        if (free_frame < num_frames)
        {
          // assign value to frame and set its second chance to 0
          frame[free_frame] = curr_num;
          sec_chance[free_frame] = 0;
          printf("Page %d loaded into Frame %d\n", curr_num, free_frame);

          free_frame++;
        }
        else
        // Replace by FIFO unless there's a second chance
        {
          while(sec_chance[used_page] != 0){
            //if second chance set it back to 0
            sec_chance[used_page] = 0;
            
            //move to the next page
            used_page = (used_page + 1) % num_frames;
          }

          //second chance should now be 0
          printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d \n", frame[used_page], used_page, curr_num, used_page);

          //set value in frame
          frame[used_page] = curr_num;

          // change the currently used page to the next
          used_page = (used_page + 1) % num_frames;
        }
      }
      curr_request++;
    }

    printf("%d page faults\n", page_faults);

  }


  ////OPTIMAL Algorithm
  if (strcmp(argv[2], "OPT") == 0){
    
    int free_frame = 0;
    int used_page = 0;
    int page_faults = 0;

    req_arr = (int * ) malloc(num_requests * sizeof(int));
    next_use = (int * ) malloc(num_frames * sizeof(int));

    //assign value to frame, and calculate the next use
    int j =0;
    while(j<num_requests){
      fscanf(myFile, "%d", &curr_num);
      req_arr[j] = curr_num;
    }
    j=0;
    while(j<num_requests){
      int flagExist = 0;
      curr_num = req_arr[j];

      for (int i = 0; i < num_frames; i++)
      {
        //if we find an existing value in frame
        if (frame[i] == curr_num)
        {
          // set the exist flag and the second chance value to 1
          printf("Page %d already in Frame %d\n", curr_num, i);
          flagExist = 1;
          // recalculate next use
          int found = 0;
          for(int k = j; k<num_requests;k++){
            if(curr_num == req_arr[k]){
              int next_use_value = k-j;
              next_use[i] = next_use_value;
              found =1;
              break;
            }
          }
          if(found ==0){
            //setting next use to an arbitrarily large number
            next_use[i] = 1000;
          }
        }
      }

      if(flagExist == 0){
        page_faults++;

        // if frame has empty slots
        if (free_frame < num_frames)
        {
          // assign value to frame and set its second chance to 0
          frame[free_frame] = curr_num;
          printf("Page %d loaded into Frame %d\n", curr_num, free_frame);

          free_frame++;
          // recalculate next use
          int found = 0;
          for(int k = j; k<num_requests;k++){
            if(curr_num == req_arr[k]){
              int next_use_value = k-j;
              next_use[free_frame] = next_use_value;
              found =1;
              break;
            }
          }
          if(found ==0){
            //setting next use to an arbitrarily large number
            next_use[free_frame] = 1000;
          }
        }
        else{
          //we have to replace the frame with the highest next use value
          //find the index of the largest value
          int largest_val = 0;
          int lv_index;
          for(int i=0;i<num_frames;i++){
            if(next_use[i] > largest_val){
              lv_index = i;
            }
          }
          frame[lv_index] = curr_num;
        }
      }
      j++;
    }
    
    
  }
}