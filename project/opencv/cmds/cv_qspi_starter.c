#include <stdint.h>
#include <string.h>
#include <util/macro.h>

#include <arm/cpu_cache.h>

#define APP_DATA(app, x)    MACRO_CONCAT(MACRO_CONCAT(_ ## app, _data_), x)
#define APP_BSS(app, x)     MACRO_CONCAT(MACRO_CONCAT(_ ## app, _bss_), x)

extern char APP_DATA(cv, vma), APP_DATA(cv, lma), APP_DATA(cv, len);
extern char APP_DATA(edges, vma), APP_DATA(edges, lma), APP_DATA(edges, len);
extern char APP_DATA(facedetect, vma), APP_DATA(facedetect, lma), APP_DATA(facedetect, len);
extern char APP_DATA(libstdcxx, vma), APP_DATA(libstdcxx, lma), APP_DATA(libstdcxx, len);
extern char APP_DATA(libsupcxx, vma), APP_DATA(libsupcxx, lma), APP_DATA(libsupcxx, len);

extern char APP_BSS(cv, vma), APP_BSS(cv, lma), APP_BSS(cv, len);
extern char APP_BSS(edges, vma), APP_BSS(edges, lma), APP_BSS(edges, len);
extern char APP_BSS(facedetect, vma), APP_BSS(facedetect, lma), APP_BSS(facedetect, len);
extern char APP_BSS(libstdcxx, vma), APP_BSS(libstdcxx, lma), APP_BSS(libstdcxx, len);
extern char APP_BSS(libsupcxx, vma), APP_BSS(libsupcxx, lma), APP_BSS(libsupcxx, len);

static void load_section(void *vma, void *lma, unsigned int len) {
	if (vma != lma) {
		memcpy(vma, lma, len);
	}
}

static void zero_bss_section(void *vma, unsigned int len) {
	memset(vma, 0, len);
}

extern void cxx_invoke_constructors(void);

int main(int argc, char **argv) {
	load_section(&APP_DATA(cv, vma), &APP_DATA(cv, lma), (unsigned int) &APP_DATA(cv, len));
	load_section(&APP_DATA(edges, vma), &APP_DATA(edges, lma), (unsigned int) &APP_DATA(edges, len));
	load_section(&APP_DATA(facedetect, vma), &APP_DATA(facedetect, lma), (unsigned int) &APP_DATA(facedetect, len));
	load_section(&APP_DATA(libstdcxx, vma), &APP_DATA(libstdcxx, lma), (unsigned int) &APP_DATA(libstdcxx, len));
	load_section(&APP_DATA(libsupcxx, vma), &APP_DATA(libsupcxx, lma), (unsigned int) &APP_DATA(libsupcxx, len));

	zero_bss_section(&APP_BSS(cv, vma), (unsigned int) &APP_BSS(cv, len));
	zero_bss_section(&APP_BSS(edges, vma), (unsigned int) &APP_BSS(edges, len));
	zero_bss_section(&APP_BSS(facedetect, vma), (unsigned int) &APP_BSS(facedetect, len));
	zero_bss_section(&APP_BSS(libstdcxx, vma), (unsigned int) &APP_BSS(libstdcxx, len));
	zero_bss_section(&APP_BSS(libsupcxx, vma), (unsigned int) &APP_BSS(libsupcxx, len));

	//dcache_flush_all();

	cxx_invoke_constructors();

	return 0;
}
