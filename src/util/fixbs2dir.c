/*-------------------------------------------------------*/
/* util/fixbs2dir.c	( NTHU CS MapleBBS Ver 3.10 )	 */
/*-------------------------------------------------------*/
/* target : �ץ� BS2 .DIR �� ���P�B�� chrono �P xname	 */
/* create : 16/07/21					 */
/* update :   /  /  					 */
/* author : LHD.bbs@bbs.lhd.tw		                 */
/*-------------------------------------------------------*/


#include "bbs.h"


static inline int
fix_hdr(hdr)
  HDR *hdr;
{
  time_t newchrono;

  newchrono = chrono32(hdr->xname);

  /* LHD.160721: BS2 �� chrono ������ xname */

  if (newchrono == hdr->chrono)
    return 0;

  hdr->chrono = newchrono;
    return 1;
}


int
main(argc, argv)
  int argc;
  char *argv[];
{
  int pos;
  char *fname;
  HDR hdr;

  if (argc < 2)
  {
    printf("Usage: %s .DIR_path\n", argv[0]);
    exit(1);
  }

  fname = argv[1];
  if (strcmp(fname + strlen(fname) - 4, FN_DIR))
  {
    printf("This is not a .DIR file.\n");
    exit(1);
  }

  pos = 0;
  while (!rec_get(fname, &hdr, sizeof(HDR), pos))
  {
    if (fix_hdr(&hdr))
    { 
      rec_put(fname, &hdr, sizeof(HDR), pos, NULL);
      printf("�ץ� %05d �g\n", pos +1);
    }
    pos++;
  }

  printf("�����I\n");

  return 0;
}
