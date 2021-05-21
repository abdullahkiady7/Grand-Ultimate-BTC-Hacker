/* Copyright (c) 2015 Ryan Castellucci, All Rights Reserved */
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "bloom.h"
#include "mmapf.h"
#include "hash160.h"

static mmapf_ctx bloom_mmapf;
unsigned char *bloom = NULL;


 hash160_t Hash160; //global static memory version

//extern char *bopt;

void bloom_alloc(char *);
uint64_t test_bloom(void);
 
 void bloom_alloc(char *bname)
{
 int ret;

    printf("Loading Bloom File %s\n", bname);
    if ((ret = mmapf(&bloom_mmapf, bname, BLOOM_SIZE, MMAPF_RNDRD)) != MMAPF_OKAY) {
      bail(1, "failed to open gpu bloom filter '%s': %s\n", bname, mmapf_strerror(ret));
    } else if (bloom_mmapf.mem == NULL) {
      bail(1, "got NULL pointer trying to set up gpu bloom filter\n");
    }

    bloom = bloom_mmapf.mem;
}


void dumpbh(char* s,uint32_t *h)
{
 //int i;
  printf("\n%s: ", s );
  for ( int i=0;i<5;i++) printf("%lx:",h[i]);
  printf("\n");
}

 int bloom_chk(  uint32_t *h )
{
  int ret;
//dumphex(h,20);
    ret = bloom_chk_hash160(bloom, h);
//printf("bloom(%d)\n", ret);
    return ret;
}

// see how far you must search bloom, just to make sure the array has non-zero
uint64_t test_bloom(void)
{
    uint64_t i;
  for (  i=0;i<BLOOM_SIZE;i++) if ( bloom[i]  ) return(i);
  return(-1);
}

void gethex( unsigned char *src, int len, unsigned char *result) {

//unsigned int c;
//unsigned char *p;
unsigned char *pos=src;

/*
  for (int i=0,p=src; i < len; p += 2) {
    if (sscanf(p, "%2hhx", (unsigned int *)&c) != 1) { // was %02X
        break; // Didn't parse as expected
    }
    result[i++] = c;
  }
*/
		for (size_t count = 0; count < len; count++) {
				sscanf(pos, "%2hhx", &result[count]);
				pos += 2;
		}

  //return(result);
}

/*
void bloom_set_hash160(unsigned char *bloom, uint32_t *h) {
//  unsigned int t;
//poc int32 to int64
 uint32_t t;

//dumpbh("Begin",h);
//printf("Begin h=%ld\n",h[0]);

  t = BH00(h); BLOOM_SET_BIT(t);
//printf("bh00-t bloom[(N)>>1] | (0x1UL<<((N)&0x7UL))) %lx %lx %ld\n",t,(t)>>2, (0x1UL<<((t)&0x7UL)) );fflush(stdout);

  t = BH01(h); BLOOM_SET_BIT(t);
  t = BH02(h); BLOOM_SET_BIT(t);
  t = BH03(h); BLOOM_SET_BIT(t);
  t = BH04(h); BLOOM_SET_BIT(t);
  t = BH05(h); BLOOM_SET_BIT(t);
  t = BH06(h); BLOOM_SET_BIT(t);
  t = BH07(h); BLOOM_SET_BIT(t);
  t = BH08(h); BLOOM_SET_BIT(t);
  t = BH09(h); BLOOM_SET_BIT(t);
  t = BH10(h); BLOOM_SET_BIT(t);
  t = BH11(h); BLOOM_SET_BIT(t);
  t = BH12(h); BLOOM_SET_BIT(t);
  t = BH13(h); BLOOM_SET_BIT(t);
  t = BH14(h); BLOOM_SET_BIT(t);
  t = BH15(h); BLOOM_SET_BIT(t);
  t = BH16(h); BLOOM_SET_BIT(t);
  t = BH17(h); BLOOM_SET_BIT(t);
  t = BH18(h); BLOOM_SET_BIT(t);
  t = BH19(h); BLOOM_SET_BIT(t);


//poc add more bits, 10 added
  t = BH20(h); BLOOM_SET_BIT(t);

//printf("bh20-t bloom[(N)>>1] | (0x1UL<<((N)&0x7UL))) %ld %ld %ld\n",t,(t)>>1, (0x1UL<<((t)&0x7UL)) );

// t = BH21(h); BLOOM_SET_BIT(t);
//  t = BH22(h); BLOOM_SET_BIT(t);
//  t = BH23(h); BLOOM_SET_BIT(t);
//  t = BH24(h); BLOOM_SET_BIT(t);

//  t = BH25(h); BLOOM_SET_BIT(t);
// t = BH26(h); BLOOM_SET_BIT(t);
//  t = BH27(h); BLOOM_SET_BIT(t);
//  t = BH28(h); BLOOM_SET_BIT(t);
// t = BH29(h); BLOOM_SET_BIT(t);

}
*/
/*
int bloom_save(unsigned char *filename, unsigned char *bloom);
*/

/*  vim: set ts=2 sw=2 et ai si: */
