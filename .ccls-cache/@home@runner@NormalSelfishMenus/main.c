#include<stdio.h>

int main(int argc, char * argv[])

{

  FILE * myFile;

  int num;

  int no_pages, no_frames, requests;

  int * frame;
  int * sec_chance;

  // open input file

  myFile = fopen(argv[1], "r");

  // read number of pages, number of frames and number of requests

  fscanf(myFile, "%d", & no_pages);

  fscanf(myFile, "%d", & no_frames);

  fscanf(myFile, "%d", & requests);

  // create frame

  frame = (int * ) malloc(no_frames * sizeof(int));
  sec_chance = (int * ) malloc(no_frames * sizeof(int));
  
  // If user requests FIFO

  if (strcmp(argv[2], "CLOCK") == 0)

  {

    printf("**FIFO**\n");

    int frameFree = 0; //intially no page is loaded

    int pageToUnload = 0;

    int pageFaults = 0;

    int j = 0;

    while (j < requests)

    {

      fscanf(myFile, "%d", & num);

      int flagExist = 0;

      for (int i = 0; i < no_frames; i++)
      {
        if (frame[i] == num)
        {
          // set the exist flag and the second chance value to 1
          printf("Page %d already in Frame %d\n", num, i);
          sec_chance[frameFree] = 1;
          flagExist = 1;
        }
      }

      if (flagExist == 0)
      {
        pageFaults++;

        // if frame has empty slots
        if (frameFree < no_frames)
        {
          // assign value to frame and set its second chance to 0
          frame[frameFree] = num;
          sec_chance[frameFree] = 0;
          printf("Page %d loaded into Frame %d\n", num, frameFree);

          frameFree++;
        }
        else
        // Replace by FIFO unless there's a second chance
        {
          //if the second chance is not 0


          //if the second chance is 0
          printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d \n", frame[pageToUnload], pageToUnload, num, pageToUnload);

          frame[pageToUnload] = num;

          // update first in page

          pageToUnload = (pageToUnload + 1) % no_frames;

        }

      }

      j++;

    }

    printf("%d page faults\n", pageFaults);

  }
}