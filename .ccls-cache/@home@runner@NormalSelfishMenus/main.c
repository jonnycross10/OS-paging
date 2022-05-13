#include<stdio.h>

int main(int argc, char * argv[])

{

  FILE * myFile;

  int num;

  int no_pages, no_frames, requests;

  int * frame;

  // open input file

  myFile = fopen(argv[1], "r");

  // read number of pages, number of frames and number of requests

  fscanf(myFile, "%d", & no_pages);

  fscanf(myFile, "%d", & no_frames);

  fscanf(myFile, "%d", & requests);

  // create frame

  frame = (int * ) malloc(no_frames * sizeof(int));

  // If user requests FIFO

  if (strcmp(argv[2], "FIFO") == 0)

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

          printf("Page %d already in Frame %d\n", num, i);

          flagExist = 1;

        }

      }

      if (flagExist == 0)

      {

        pageFaults++;

        // if frame has empty slots

        if (frameFree < no_frames)

        {

          frame[frameFree] = num;

          printf("Page %d loaded into Frame %d\n", num, frameFree);

          frameFree++;

        }

        // otherwise
        else

        {

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